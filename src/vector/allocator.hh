#ifndef SQUEEZE_ALLOCATOR_HH
#define SQUEEZE_ALLOCATOR_HH

#include <cstring> // for std::memmove
#include <memory>  // for std::Allocator
#include "../init/type_traits.hh"
#include "../simd/vectorization.hh"

namespace Squeeze {

namespace internal {

#ifdef SQUEEZE_USE_MKL
void* aligned_alloc(StdUIdx alignment, StdUIdx size) noexcept {
  return mkl_malloc(size, alignment);
}

void aligned_free(void* ptr) noexcept {
  if (ptr != nullptr) mkl_free(ptr);
}

void* aligned_realloc(void* ptr, StdUIdx, StdUIdx size) noexcept {
  return mkl_realloc(ptr, size);
}
#elif SQUEEZE_HAS_ALIGNED_ALLOC
using std::aligned_alloc;

// function-like macro. ptr is void* and alignment is StdUIdx(aka size_t)
#define IS_ALIGNED(ptr, alignment)                        \
  (reinterpret_cast<StdUIdx>(ptr) & (alignment - 1)) == 0

SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void aligned_free(void* ptr) noexcept { if (ptr != nullptr) std::free(ptr); }

SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void* aligned_realloc(void* ptr, StdUIdx alignment, StdUIdx size) noexcept {
  if (ptr == nullptr) return aligned_alloc(alignment, size);

  void* previous = ptr;
  ptr = std::realloc(ptr, size);
  if (ptr == nullptr) return nullptr;
  if (ptr == previous || IS_ALIGNED(ptr, alignment)) return ptr;

  previous = ptr;
  ptr = aligned_alloc(alignment, size);
  if (ptr == nullptr) return nullptr;
  std::memcpy(ptr, previous, size);
  std::free(previous);
  return ptr;
}
#undef IS_ALIGNED
#else
// function-like macro. ptr is void* and alignment is StdUIdx(aka size_t)
#define ALIGN_PTR(ptr, alignment) reinterpret_cast<void*>(         \
  (reinterpret_cast<StdUIdx>(ptr) & ~(alignment - 1)) + alignment)

SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void* aligned_alloc(StdUIdx alignment, StdUIdx size) noexcept {
  void* raw = std::malloc(size + alignment);
  if (raw == nullptr) return nullptr;

  void* data = ALIGN_PTR(raw, alignment);
  *(reinterpret_cast<void**>(data) - 1) = raw;
  return data;
}

SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void aligned_free(void* ptr) noexcept {
  if (ptr != nullptr) std::free(*(reinterpret_cast<void**>(ptr) - 1));
}

SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void* aligned_realloc(void* ptr, StdUIdx alignment, StdUIdx size) noexcept {
  if (ptr == nullptr) return aligned_alloc(alignment, size);

  void* raw = *(reinterpret_cast<void**>(ptr) - 1);
  StdUIdx offset = reinterpret_cast<StdUIdx>(ptr)
                 - reinterpret_cast<StdUIdx>(raw);

  raw = std::realloc(raw, size + alignment);
  if (raw == nullptr) return nullptr;

  void* data = ALIGN_PTR(raw, alignment);
  void* olddata = reinterpret_cast<void*>(
                    reinterpret_cast<StdUIdx>(raw) + offset);
  if (data != olddata) std::memmove(data, olddata, size);

  *(reinterpret_cast<void**>(data) - 1) = raw;
  return data;
}
#undef ALIGN_PTR
#endif // SQUEEZE_USE_MKL || SQUEEZE_HAS_ALIGNED_ALLOC

} // namespace internal


template<class _Tp, StdUIdx _alignment = SQUEEZE_DEFAULT_ALIGN_BYTES>
struct AlignedAllocator : std::allocator<_Tp>
{
  static_assert(internal::SupportedType<_Tp>::value,
                "Only arithmetic types are supported!!");

  using value_type      = _Tp;
  using size_type       = std::size_t;
  using difference_type = std::ptrdiff_t;
#if __cplusplus <= 201703L
  using pointer = _Tp*;
  using const_pointer = const _Tp*;
  using reference = _Tp&;
  using const_reference = const _Tp&;

  template<typename _Up>
  struct rebind
  { using other = AlignedAllocator<_Up, _alignment>; };
#endif

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE static
  _Tp* allocate(StdUIdx size) {
    if (size == 0) return nullptr;
    void* dest = internal::aligned_alloc(_alignment, size * sizeof(_Tp));
    if (dest == nullptr) throw std::bad_alloc();
    return reinterpret_cast<_Tp*>(dest);
  }

  SQUEEZE_DEVICE_FUNC constexpr static void construct(_Tp*) {}

  template<class _Args>
  SQUEEZE_DEVICE_FUNC constexpr static
  void construct(_Tp*, _Args&& ...) {}

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE static
  _Tp* reallocate(_Tp* ptr, StdUIdx size) {
    if (size == 0) {
      internal::aligned_free(ptr);
      return nullptr;
    }
    void* dest = internal::aligned_realloc(ptr, _alignment, size * sizeof(_Tp));
    if (dest == nullptr) {
      internal::aligned_free(ptr);
      throw std::bad_alloc();
    }
    return reinterpret_cast<_Tp*>(dest);
  }

  // the second argument is only for API consistency
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE static
  void deallocate(_Tp* ptr, StdUIdx) noexcept {
    internal::aligned_free(ptr);
  }
};

// without alignment
template<class _Tp>
struct AlignedAllocator<_Tp, 0> : std::allocator<_Tp>
{
  static_assert(internal::SupportedType<_Tp>::value,
                "Only arithmetic types are supported!!");

  using value_type      = _Tp;
  using size_type       = std::size_t;
  using difference_type = std::ptrdiff_t;
#if __cplusplus <= 201703L
  using pointer = _Tp*;
  using const_pointer = const _Tp*;
  using reference = _Tp&;
  using const_reference = const _Tp&;

  template<typename _Up>
  struct rebind
  { using other = AlignedAllocator<_Up, 0>; };
#endif

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE static _Tp* allocate(StdUIdx size) {
    if (size == 0) return nullptr;
    _Tp* dest = std::malloc(size * sizeof(_Tp));
    if (dest == nullptr) throw std::bad_alloc();
    return dest;
  }

  SQUEEZE_DEVICE_FUNC constexpr static void construct(_Tp*) {}

  template<class _Args>
  SQUEEZE_DEVICE_FUNC constexpr static
  void construct(_Tp*, _Args&& ...) {}

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  static _Tp* reallocate(_Tp* ptr, StdUIdx size) {
    if (size == 0) {
      std::free(ptr);
      return nullptr;
    }
    _Tp* dest = std::realloc(ptr, size * sizeof(_Tp));
    if (dest == nullptr) {
      std::free(ptr);
      throw std::bad_alloc();
    }
    return dest;
  }

  // the second argument is only for API consistency
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE static
  void deallocate(_Tp* ptr, StdUIdx) noexcept {
    std::free(ptr);
  }
};

} // namespace Squeeze
#endif // include guard
