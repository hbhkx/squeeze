#ifndef SQUEEZE_VECTOR_HH
#define SQUEEZE_VECTOR_HH

#include <array>
#include <iostream>
#include "../proxy/eval.hh"
#include "allocator.hh"

namespace Squeeze {

template<class _Tp, Idx _size = Dynamic,
         StdUIdx _alignment = SQUEEZE_DEFAULT_ALIGN_BYTES>
class Vector;

namespace internal {

template<class _Tp, Idx _size, StdUIdx _alignment>
struct IsVector<Vector<_Tp, _size, _alignment>> : public std::true_type { };


#if SQUEEZE_HAS_FOLD_EXPR
  template<class... _Ints>
  constexpr Idx sum(_Ints... ints) { return (... + ints); }
#else
  constexpr Idx sum(Idx i1, Idx i2) { return i1 + i2; }

  template<class... _Ints>
  constexpr Idx sum(Idx i, _Ints... ints) { return i + sum(ints...); }
#endif

template<class _Tp, StdUIdx _alignment, class _Vec>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
Vector<_Tp, Dynamic, _alignment>&
_concat(Vector<_Tp, Dynamic, _alignment>& vec0, const _Vec& vec1) {
  blas::copy(vec1.size(), vec1.begin(), vec0.end());
  vec0.m_size += vec1.size();
  return vec0;
}

template<class _Tp, StdUIdx _alignment, class _Vec, class... _Vecs>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
Vector<_Tp, Dynamic, _alignment>&
_concat(Vector<_Tp, Dynamic, _alignment>& vec0,
        const _Vec& vec1, const _Vecs&... vecs)
{
  return _concat(_concat(vec0, vec1), vecs...);
}

} // namespace internal


#define CHECK_STATIC_ALLOCATION_SIZE(Tp, size)                             \
  static_assert(size * sizeof(Tp) <= SQUEEZE_STACK_ALLOCATION_LIMIT ||     \
                SQUEEZE_STACK_ALLOCATION_LIMIT == 0,                       \
                "You are allocating too much on stack, try using Dynamic " \
                "allocation on heap!!!")

#define CHECK_TYPE(Tp) static_assert(internal::SupportedType<Tp>::value,   \
  "Only arithmetic types and Complex types are supported!!")

#define CHECK_ALIGNMENT(alignment) static_assert(alignment == 0 ||         \
  (alignment >= sizeof(void*) && (alignment & (alignment-1)) == 0),        \
  "alignment must be no less than sizeof(void*) and must be power of 2!!")


/** \internal
  *
  * \class Vector
  * \ingroup Core_Module
  *
  * \brief Stores the data with aligned continous memory
  */

// fixed-size array
template<class _Tp, Idx _size, StdUIdx _alignment>
class Vector
{
  static_assert(_size > 0, "Wrong size!!");
  CHECK_STATIC_ALLOCATION_SIZE(_Tp, _size);
  CHECK_TYPE(_Tp);
  CHECK_ALIGNMENT(_alignment);

  alignas(_alignment) std::array<_Tp, _size> m_data;
public:
  using ValueType = _Tp;

  SQUEEZE_DEVICE_FUNC constexpr Vector() = default;

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14 Vector(Idx size) {
    if (size != _size)
      throw std::logic_error("Cannot resize a fixed size container!!");
  }

  SQUEEZE_DEVICE_FUNC constexpr Vector(const Vector&) = default;

  template<class _Vec, internal::IdxIfVec<_Vec> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector(const _Vec& other) {
    if (other.size() != _size)
      throw std::logic_error("Cannot resize a fixed size container!!");

    blas::copy(_size, other.data(), m_data.data());
  }

  template<class _Proxy, internal::IdxIfProxy<_Proxy> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector(const _Proxy& proxy) {
    if (proxy.size() != _size)
      throw std::logic_error("Cannot resize a fixed size container!!");

    eval(proxy, m_data);
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14 Vector(Vector&&) = default;

  template<class _Vec, internal::IdxIfVec<_Vec> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  Vector(_Vec&& other) {
    if (other.size() != _size)
      throw std::logic_error("Cannot resize a fixed size container!!");

    m_data = std::move(other.m_data);
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  Vector& operator=(const Vector&) = default;

  template<class _Vec, internal::IdxIfVec<_Vec> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator=(const _Vec& other) {
    Vector tmp(other);
    this->swap(tmp);
    return *this;
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  Vector& operator=(Vector&&) = default;

  template<class _Vec, internal::IdxIfVec<_Vec> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  Vector& operator=(_Vec&& other) {
    Vector tmp(std::move(other));
    this->swap(tmp);
    return *this;
  }

  template<class _Obj, internal::IdxIfProxyOrAri<_Obj> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator=(const _Obj& obj) {
    return eval(obj, *this);
  }

  template<class _Obj, Idx = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator+=(const _Obj& obj) {
    return eval(*this + obj, *this);
  }

  template<class _Ari, class _Vec,
           internal::IdxIfAri<_Ari> = 0, internal::IdxIfVec<_Vec> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator+=(const BinProxy<Multiplies<_Ari,
                                               typename _Vec::ValueType>,
                                    _Ari, _Vec>& proxy)
  {
    blas::axpy(proxy.size(), proxy.ari, proxy.obj.data(), this->data());
    return *this;
  }

  template<class _Vec, class _Ari,
           internal::IdxIfVec<_Vec> = 0, internal::IdxIfAri<_Ari> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator+=(const BinProxy<Multiplies<typename _Vec::ValueType,
                                               _Ari>,
                                    _Vec, _Ari>& proxy)
  {
    blas::axpy(proxy.size(), proxy.ari, proxy.obj.data(), this->data());
    return *this;
  }

  template<class _Obj, Idx = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator-=(const _Obj& obj) {
    return eval(*this - obj, *this);
  }

  template<class _Obj, internal::IdxIfNotAri<_Obj> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator*=(const _Obj& obj) {
    return eval(*this * obj, *this);
  }

  template<class _Ari, internal::IdxIfAri<_Ari> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator*=(const _Ari& ari) {
    blas::scal(this->size(), ari, this->data());
    return *this;
  }

  template<class _Obj, Idx = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator/=(const _Obj& obj) {
    return eval(*this / obj, *this);
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR20
  void swap(Vector& other) noexcept { std::swap(m_data, other.m_data); }

  SQUEEZE_DEVICE_FUNC constexpr static Idx size() { return _size; }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14 void resize(Idx size) {
    if (size != _size)
      throw std::logic_error("Cannot resize a fixed size container!!");
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR17
  const _Tp* data() const { return m_data.data(); }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR17
  _Tp* data() { return m_data.data(); }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR17
  const _Tp* begin() const { return m_data.begin(); }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR17
  _Tp* begin() { return m_data.begin(); }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR17
  const _Tp* end() const { return m_data.end(); }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR17
  _Tp* end() { return m_data.end(); }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  const _Tp& operator[](Idx n) const {
#ifdef SQUEEZE_HAS_DEBUG
    if (n < 0 || n >= _size) throw std::out_of_range("Invalid index!!");
#endif
    return m_data[n];
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR17
  _Tp& operator[](Idx n) {
#ifdef SQUEEZE_HAS_DEBUG
    if (n < 0 || n >= _size) throw std::out_of_range("Invalid index!!");
#endif
    return m_data[n];
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  const _Tp& operator()(Idx n) const {
#ifdef SQUEEZE_HAS_DEBUG
    if (n < 0 || n >= _size) throw std::out_of_range("Invalid index!!");
#endif
    return m_data[n];
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR17
  _Tp& operator()(Idx n) {
#ifdef SQUEEZE_HAS_DEBUG
    if (n < 0 || n >= _size) throw std::out_of_range("Invalid index!!");
#endif
    return m_data[n];
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  _Tp get(Idx n) const { return m_data.at(n); }

  template<class _Vec>
  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR20
  bool operator==(const _Vec& other) const {
    if (this == &other) return true;
    return std::equal(this->begin(), this->end(), other.begin(), other.end());
  }

  template<class _Vec, internal::IdxIfVec<_Vec> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  auto dot(const _Vec& other) const
  -> decltype(blas::dot(size(), data(), other.data()))
  {
#ifdef SQUEEZE_HAS_DEBUG
    if (other.size() != this->size())
      throw std::logic_error("Cannot apply dot product to vectors \
                              with different sizes!!");
#endif
    return blas::dot(this->size(), this->data(), other.data());
  }

  template<class _Proxy, internal::IdxIfProxy<_Proxy> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  auto dot(const _Proxy& proxy) const
  -> SQUEEZE_COMMON_TYPE(_Tp, typename _Proxy::ValueType)
  {
#ifdef SQUEEZE_HAS_DEBUG
    if (proxy.size() != this->size())
      throw std::logic_error("Cannot apply dot product to vectors \
                              with different sizes!!");
#endif
    Vector<typename _Proxy::ValueType, _size> tmp(proxy);

    return blas::dot(this->size(), this->data(), tmp.data());
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  auto squ() const -> decltype(blas::dot(size(), data()))
  { return blas::dot(this->size(), this->data()); }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  auto norm() const -> decltype(blas::nrm2(size(), data()))
  { return blas::nrm2(this->size(), this->data()); }

  template<class _Up, Idx _s, StdUIdx _align>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector cross(const Vector<_Up, _s, _align>& other) const {
    if (this->size() != 3 || other.size() != 3)
      throw std::logic_error("Cross product is only for 3-dimension vectors");

    Vector out;
    out[0] = (*this)[1] * other[2] - (*this)[2] * other[1];
    out[1] = (*this)[2] * other[0] - (*this)[0] * other[2];
    out[2] = (*this)[0] * other[1] - (*this)[1] * other[0];

    return out;
  }
};
#undef CHECK_STATIC_ALLOCATION_SIZE

// null array
template<class _Tp, StdUIdx _alignment>
class Vector<_Tp, 0, _alignment>
{
  CHECK_TYPE(_Tp);
  CHECK_ALIGNMENT(_alignment);
public:
  using ValueType = _Tp;
  SQUEEZE_DEVICE_FUNC constexpr Vector() = default;
  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14 Vector& operator=(const Vector&) {}
  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR20 void swap(Vector&) noexcept {}
  SQUEEZE_DEVICE_FUNC constexpr static Idx size() { return 0; }
  SQUEEZE_DEVICE_FUNC constexpr const _Tp* data() const { return nullptr; }
};

// dynamic vector
template<class _Tp, StdUIdx _alignment>
class Vector<_Tp, Dynamic, _alignment>
{
  CHECK_TYPE(_Tp);
  CHECK_ALIGNMENT(_alignment);
private:
  using Alloc = AlignedAllocator<_Tp, _alignment>;

  _Tp* m_data = nullptr;
  Idx  m_size = 0;

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  void conserve(Idx size) {
    m_data = Alloc::reallocate(m_data, size);
  }
public:
  using ValueType = _Tp;

  SQUEEZE_DEVICE_FUNC constexpr Vector() = default;

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector(Idx size) {
    if (size < 0)
      throw std::length_error("Cannot resize with a negative size!!");

    m_data = Alloc::allocate(size);
    m_size = size;
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE Vector(const Vector& other)
  : m_data(Alloc::allocate(other.m_size)), m_size(other.m_size)
  { blas::copy(other.size(), other.data(), m_data); }

  template<class _Vec, internal::IdxIfVec<_Vec> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector(const _Vec& other)
  : m_data(Alloc::allocate(other.size())), m_size(other.size())
  { blas::copy(other.size(), other.data(), m_data); }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14 Vector(Vector&&) = default;

  template<class _Vec, internal::IdxIfVec<_Vec> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  Vector(_Vec&& other) {
    m_data = std::move(other.m_data);
    m_size = std::move(other.size());
  }

  template<class _Proxy, internal::IdxIfProxy<_Proxy> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector(const _Proxy& proxy) : Vector(proxy.size()) {
    eval(proxy, m_data);
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator=(const Vector& other) {
    if (this != &other) {
      Vector tmp(other);
      this->swap(tmp);
    }
    return *this;
  }

  template<class _Vec, internal::IdxIfVec<_Vec> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator=(const _Vec& other) {
    Vector tmp(other);
    this->swap(tmp);
    return *this;
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  Vector& operator=(Vector&& other) noexcept {
    m_data = std::move(other.m_data);
    m_size = std::move(other.m_size);
    return *this;
  }

  template<class _Vec, internal::IdxIfVec<_Vec> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  Vector& operator=(_Vec&& other) {
    Vector tmp(std::move(other));
    this->swap(tmp);
    return *this;
  }

  template<class _Obj, internal::IdxIfProxyOrAri<_Obj> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator=(const _Obj& obj) {
    return eval(obj, *this);
  }

  template<class _Obj, Idx = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator+=(const _Obj& obj) {
    return eval(*this + obj, *this);
  }

  template<class _Ari, class _Vec,
           internal::IdxIfAri<_Ari> = 0, internal::IdxIfVec<_Vec> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator+=(const BinProxy<Multiplies<_Ari, typename _Vec::ValueType>,
                                    _Ari, _Vec>& proxy)
  {
    blas::axpy(proxy.size(), proxy.ari, proxy.obj.data(), this->data());
    return *this;
  }

  template<class _Vec, class _Ari,
           internal::IdxIfVec<_Vec> = 0, internal::IdxIfAri<_Ari> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator+=(const BinProxy<Multiplies<typename _Vec::ValueType, _Ari>,
                                    _Vec, _Ari>& proxy)
  {
    blas::axpy(proxy.size(), proxy.ari, proxy.obj.data(), this->data());
    return *this;
  }

  template<class _Obj, Idx = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator-=(const _Obj& obj) {
    return eval(*this - obj, *this);
  }

  template<class _Obj, internal::IdxIfNotAri<_Obj> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator*=(const _Obj& obj) {
    return eval(*this * obj, *this);
  }

  template<class _Ari, internal::IdxIfAri<_Ari> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator*=(const _Ari& ari) {
    blas::scal(this->size(), ari, this->data());
    return *this;
  }

  template<class _Obj, Idx = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& operator/=(const _Obj& obj) {
    return eval(*this / obj, *this);
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE ~Vector() noexcept {
    Alloc::deallocate(m_data, m_size);
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR20 void swap(Vector& other) noexcept {
    std::swap(m_data, other.m_data);
    std::swap(m_size, other.m_size);
  }

  SQUEEZE_DEVICE_FUNC constexpr Idx size() const { return m_size; }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  void resize(Idx size) {
    if(size != m_size) {
      if (size > 0) {
        m_data = Alloc::reallocate(m_data, size);
        m_size = size;
      }
      else if (size == 0) {
        Alloc::deallocate(m_data, m_size);
        m_data = nullptr;
        m_size = 0;
      }
      else
        throw std::length_error("Cannot resize with a negative size!!");
    }
  }

  SQUEEZE_DEVICE_FUNC constexpr const _Tp* data() const { return m_data; }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14 _Tp* data() { return m_data; }

  SQUEEZE_DEVICE_FUNC constexpr const _Tp* begin() const { return m_data; }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14 _Tp* begin() { return m_data; }

  SQUEEZE_DEVICE_FUNC constexpr
  const _Tp* end() const { return m_data + m_size; }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  _Tp* end() { return m_data + m_size; }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  const _Tp& operator[](Idx n) const {
#ifdef SQUEEZE_HAS_DEBUG
    if (n < 0 || n >= m_size) throw std::out_of_range("Invalid index!!");
#endif
    return *(m_data + n);
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  _Tp& operator[](Idx n) {
#ifdef SQUEEZE_HAS_DEBUG
    if (n < 0 || n >= m_size) throw std::out_of_range("Invalid index!!");
#endif
    return *(m_data + n);
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  const _Tp& operator()(Idx n) const {
#ifdef SQUEEZE_HAS_DEBUG
    if (n < 0 || n >= m_size) throw std::out_of_range("Invalid index!!");
#endif
    return *(m_data + n);
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  _Tp& operator()(Idx n) {
#ifdef SQUEEZE_HAS_DEBUG
    if (n < 0 || n >= m_size) throw std::out_of_range("Invalid index!!");
#endif
    return *(m_data + n);
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  _Tp get(Idx n) const {
    if (n < 0 || n >= m_size) throw std::out_of_range("Invalid index!!");

    return *(m_data + n);
  }

  template<class _Vec>
  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR20
  bool operator==(const _Vec& other) const {
    if (this == &other) return true;
    return std::equal(this->begin(), this->end(), other.begin(), other.end());
  }

  template<class... _Vecs>
  friend Vector& concat(const _Vecs&...);

  template<class... _Vecs>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector& concat(const _Vecs&... vecs) {
    this->conserve(m_size + internal::sum(vecs.size()...));
    internal::_concat(*this, vecs...);
    return *this;
  }

  template<class _Vec, internal::IdxIfVec<_Vec> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  auto dot(const _Vec& other) const
  -> decltype(blas::dot(size(), data(), other.data()))
  {
#ifdef SQUEEZE_HAS_DEBUG
    if (other.size() != this->size())
      throw std::logic_error("Cannot apply dot product to vectors \
                              with different sizes!!");
#endif
    return blas::dot(this->size(), this->data(), other.data());
  }

  template<class _Proxy, internal::IdxIfProxy<_Proxy> = 0>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  auto dot(const _Proxy& proxy) const
  -> SQUEEZE_COMMON_TYPE(_Tp, typename _Proxy::ValueType)
  {
#ifdef SQUEEZE_HAS_DEBUG
    if (proxy.size() != this->size())
      throw std::logic_error("Cannot apply dot product to vectors \
                              with different sizes!!");
#endif
    Vector<typename _Proxy::ValueType> tmp(proxy);

    return blas::dot(this->size(), this->data(), tmp.data());
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  auto squ() const -> decltype(blas::dot(size(), data()))
  { return blas::dot(this->size(), this->data()); }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  auto norm() const -> decltype(blas::nrm2(size(), data()))
  { return blas::nrm2(this->size(), this->data()); }

  template<class _Up, Idx _s, StdUIdx _align>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Vector cross(const Vector<_Up, _s, _align>& other) const {
    if (this->size() != 3 || other.size() != 3)
      throw std::logic_error("Cross product is only for 3-dimension vectors");

    Vector out(3);
    out[0] = (*this)[1] * other[2] - (*this)[2] * other[1];
    out[1] = (*this)[2] * other[0] - (*this)[0] * other[2];
    out[2] = (*this)[0] * other[1] - (*this)[1] * other[0];

    return out;
  }
};
#undef CHECK_TYPE
#undef CHECK_ALIGNMENT

template<class _Tp, StdUIdx _alignment, class... _Vecs>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
Vector<_Tp, Dynamic, _alignment>
concat(const Vector<_Tp, Dynamic, _alignment>& vec, const _Vecs&... vecs) {
  Vector<_Tp, Dynamic, _alignment> vec0();
  vec0.conserve(vec.size() + internal::sum(vecs.size()...));

  internal::_concat(vec0, vec, vecs...);
  return vec0;
}


/* ---------------------------- unary functions ----------------------------- */
template<class _Vec1, class _Vec2,
         internal::IdxIfVec<_Vec1> = 0, internal::IdxIfVec<_Vec2> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
auto inner_product(const _Vec1& a, const _Vec2& b)
-> decltype(blas::dot(a.size(), a.data(), b.data()))
{
#ifdef SQUEEZE_HAS_DEBUG
  if (a.size() != b.size())
    throw std::logic_error("Cannot apply dot product to vectors \
                            with different sizes!!");
#endif
  return blas::dot(a.size(), a.data(), b.data());
}

template<class _Vec, class _Proxy,
         internal::IdxIfVec<_Vec> = 0, internal::IdxIfProxy<_Proxy> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
auto inner_product(const _Vec& vec, const _Proxy& proxy)
-> SQUEEZE_COMMON_TYPE(typename _Vec::ValueType, typename _Proxy::ValueType)
{
#ifdef SQUEEZE_HAS_DEBUG
  if (vec.size() != proxy.size())
    throw std::logic_error("Cannot apply dot product to vectors \
                            with different sizes!!");
#endif
  Vector<typename _Proxy::ValueType> tmp(proxy);

  return blas::dot(vec.size(), vec.data(), tmp.data());
}

template<class _Proxy, class _Vec,
         internal::IdxIfProxy<_Proxy> = 0, internal::IdxIfVec<_Vec> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
auto inner_product(const _Proxy& proxy, const _Vec& vec)
-> SQUEEZE_COMMON_TYPE(typename _Proxy::ValueType, typename _Vec::ValueType)
{
#ifdef SQUEEZE_HAS_DEBUG
  if (vec.size() != proxy.size())
    throw std::logic_error("Cannot apply dot product to vectors \
                            with different sizes!!");
#endif
  Vector<typename _Proxy::ValueType> tmp(proxy);

  return blas::dot(vec.size(), tmp.data(), vec.data());
}

template<class _Proxy1, class _Proxy2,
         internal::IdxIfProxy<_Proxy1> = 0, internal::IdxIfProxy<_Proxy2> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
auto inner_product(const _Proxy1& p1, const _Proxy2& p2)
-> SQUEEZE_COMMON_TYPE(typename _Proxy1::ValueType, typename _Proxy2::ValueType)
{
#ifdef SQUEEZE_HAS_DEBUG
  if (p1.size() != p2.size())
    throw std::logic_error("Cannot apply dot product to vectors \
                            with different sizes!!");
#endif
  Vector<typename _Proxy1::ValueType> tmp1(p1);
  Vector<typename _Proxy2::ValueType> tmp2(p2);

  return blas::dot(p1.size(), p1.data(), p2.data());
}

template<class _Vec, internal::IdxIfVec<_Vec> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
auto inner_product(const _Vec& vec)
-> decltype(blas::dot(vec.size(), vec.data()))
{
  return blas::dot(vec.size(), vec.data());
}

template<class _Proxy, internal::IdxIfProxy<_Proxy> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
auto inner_product(const _Proxy& proxy)
-> decltype(blas::dot(proxy.size(),
                      std::declval<typename _Proxy::ValueType*>()))
{
  Vector<typename _Proxy::ValueType> vec(proxy);

  return blas::dot(vec.size(), vec.data());
}

template<class _Vec, internal::IdxIfVec<_Vec> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
auto norm(const _Vec& vec)
-> decltype(blas::nrm2(vec.size(), vec.data()))
{
  return blas::nrm2(vec.size(), vec.data());
}

template<class _Proxy, internal::IdxIfProxy<_Proxy> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
auto norm(const _Proxy& proxy)
-> decltype(blas::nrm2(proxy.size(),
                       std::declval<typename _Proxy::ValueType*>()))
{
  Vector<typename _Proxy::ValueType> vec(proxy);

  return blas::nrm2(vec.size(), vec.data());
}


/* --------------------------- output of vectors ---------------------------- */
template<class _Vec, internal::IdxIfVec<_Vec> = 0>
std::ostream& operator<<(std::ostream& os, const _Vec& vec) {
  if (vec.size() == 0) return os << "[]";

  os << '[' << vec[0];
  for (Idx i = 1; i < vec.size(); i++) {
    os << ", " << vec[i];
  }
  return os << ']';
}

template<class _Proxy, internal::IdxIfProxy<_Proxy> = 0>
std::ostream& operator<<(std::ostream& os, const _Proxy& proxy) {
  auto vec = Vector<typename _Proxy::ValueType, Dynamic>(proxy);

  return os << vec;
}

} // end namespace Squeeze

#endif // include guard
