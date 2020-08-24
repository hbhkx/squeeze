#ifndef SQUEEZE_SIMD_HH
#define SQUEEZE_SIMD_HH

#include <type_traits>
#include <array>
#include <tuple>
#include <functional>
#include "vectorization.hh"

namespace Squeeze {

enum class _StorageKind {
  _Scalar,
  _Array,
};

namespace simd {

template <_StorageKind __kind, Idx __n>
struct __simd_abi {};

template <class _Tp, class _Abi>
class __simd_storage {};

template <class _Tp, Idx __num_element>
class __simd_storage<_Tp, __simd_abi<_StorageKind::_Array, __num_element>> {
  std::array<_Tp, __num_element> __storage_;

  template <class, class>
  friend struct simd;

  template <class, class>
  friend struct simd_mask;

public:
  _Tp __get(Idx __index) const noexcept { return __storage_[__index]; };
  void __set(Idx __index, _Tp __val) noexcept
  {
    __storage_[__index] = __val;
  }
};

template <class _Tp>
class __simd_storage<_Tp, __simd_abi<_StorageKind::_Scalar, 1>> {
  _Tp __storage_;

  template <class, class>
  friend struct simd;

  template <class, class>
  friend struct simd_mask;

public:
  _Tp __get(Idx __index) const noexcept { return (&__storage_)[__index]; };
  void __set(Idx __index, _Tp __val) noexcept {
    (&__storage_)[__index] = __val;
  }
};

template <class _Vp, class _Tp, class _Abi>
class __simd_reference {
  static_assert(std::is_same<_Vp, _Tp>::value, "");

  template <class, class>
  friend struct simd;

  template <class, class>
  friend struct simd_mask;

  __simd_storage<_Tp, _Abi>* __ptr_;
  Idx __index_;

  __simd_reference(__simd_storage<_Tp, _Abi>* __ptr, Idx __index)
      : __ptr_(__ptr), __index_(__index) {}

  __simd_reference(const __simd_reference&) = default;

public:
  __simd_reference() = delete;
  __simd_reference& operator=(const __simd_reference&) = delete;

  operator _Vp() const { return __ptr_->__get(__index_); }

  __simd_reference operator=(_Vp __value) && {
    __ptr_->__set(__index_, __value);
    return *this;
  }

  __simd_reference operator++() && {
    return std::move(*this) = __ptr_->__get(__index_) + 1;
  }

  _Vp operator++(int) && {
    auto __val = __ptr_->__get(__index_);
    __ptr_->__set(__index_, __val + 1);
    return __val;
  }

  __simd_reference operator--() && {
    return std::move(*this) = __ptr_->__get(__index_) - 1;
  }

  _Vp operator--(int) && {
    auto __val = __ptr_->__get(__index_);
    __ptr_->__set(__index_, __val - 1);
    return __val;
  }

  __simd_reference operator+=(_Vp __value) && {
    return std::move(*this) = __ptr_->__get(__index_) + __value;
  }

  __simd_reference operator-=(_Vp __value) && {
    return std::move(*this) = __ptr_->__get(__index_) - __value;
  }

  __simd_reference operator*=(_Vp __value) && {
    return std::move(*this) = __ptr_->__get(__index_) * __value;
  }

  __simd_reference operator/=(_Vp __value) && {
    return std::move(*this) = __ptr_->__get(__index_) / __value;
  }

  __simd_reference operator%=(_Vp __value) && {
    return std::move(*this) = __ptr_->__get(__index_) % __value;
  }

  __simd_reference operator>>=(_Vp __value) && {
    return std::move(*this) = __ptr_->__get(__index_) >> __value;
  }

  __simd_reference operator<<=(_Vp __value) && {
    return std::move(*this) = __ptr_->__get(__index_) << __value;
  }

  __simd_reference operator&=(_Vp __value) && {
    return std::move(*this) = __ptr_->__get(__index_) & __value;
  }

  __simd_reference operator|=(_Vp __value) && {
    return std::move(*this) = __ptr_->__get(__index_) | __value;
  }

  __simd_reference operator^=(_Vp __value) && {
    return std::move(*this) = __ptr_->__get(__index_) ^ __value;
  }
};

template <class _To, class _From>
constexpr decltype(_To{std::declval<_From>()}, true)
__is_non_narrowing_convertible_impl(_From) {
  return true;
}

template <class _To>
constexpr bool __is_non_narrowing_convertible_impl(...) {
  return false;
}

template <class _From, class _To>
constexpr typename std::enable_if<std::is_arithmetic<_To>::value &&
                  std::is_arithmetic<_From>::value,
                  bool>::type
__is_non_narrowing_arithmetic_convertible() {
  return __is_non_narrowing_convertible_impl<_To>(_From{});
}

template <class _From, class _To>
constexpr typename std::enable_if<!(std::is_arithmetic<_To>::value &&
                  std::is_arithmetic<_From>::value),
                  bool>::type
__is_non_narrowing_arithmetic_convertible()
{
  return false;
}

template <class _Tp>
constexpr _Tp __variadic_sum()
{
  return _Tp{};
}

template <class _Tp, class _Up, class... _Args>
constexpr _Tp __variadic_sum(_Up __first, _Args... __rest)
{
  return static_cast<_Tp>(__first) + __variadic_sum<_Tp>(__rest...);
}

template <class _Tp>
struct __nodeduce {
  using type = _Tp;
};

template <class _Tp>
constexpr bool __vectorizable()
{
  return std::is_arithmetic<_Tp>::value && !std::is_const<_Tp>::value &&
       !std::is_volatile<_Tp>::value && !std::is_same<_Tp, bool>::value;
}

} // namespace simd

namespace simd_abi {

using scalar = simd::__simd_abi<_StorageKind::_Scalar, 1>;

template <Idx __n>
using fixed_size = simd::__simd_abi<_StorageKind::_Array, __n>;

// template <class _Tp>
// constexpr Idx max_fixed_size = SQUEEZE_MAX_STATIC_ALIGN_BYTES / sizeof(_Tp);

template <class _Tp>
using compatible = fixed_size<16 / sizeof(_Tp)>;

template <class _Tp>
using native = fixed_size<SQUEEZE_MAX_ALIGN_BYTES / sizeof(_Tp)>;

} // namespace simd_abi

namespace simd {

template <class _Tp, class _Abi = simd_abi::compatible<_Tp>>
class simd;
template <class _Tp, class _Abi = simd_abi::compatible<_Tp>>
class simd_mask;

struct element_aligned_tag {};
struct vector_aligned_tag {};
template <Idx>
struct overaligned_tag {};
// constexpr element_aligned_tag element_aligned{};
// constexpr vector_aligned_tag vector_aligned{};
// template <Idx __n>
// constexpr overaligned_tag<__n> overaligned{};

// traits [simd.traits]
template <class _Tp>
struct is_abi_tag : std::integral_constant<bool, false> {};

template <_StorageKind __kind, Idx __n>
struct is_abi_tag<__simd_abi<__kind, __n>>
    : std::integral_constant<bool, true> {};

template <class _Tp>
struct is_simd : std::integral_constant<bool, false> {};

template <class _Tp, class _Abi>
struct is_simd<simd<_Tp, _Abi>> : std::integral_constant<bool, true> {};

template <class _Tp>
struct is_simd_mask : std::integral_constant<bool, false> {};

template <class _Tp, class _Abi>
struct is_simd_mask<simd_mask<_Tp, _Abi>> : std::integral_constant<bool, true> {
};

template <class _Tp>
struct is_simd_flag_type : std::integral_constant<bool, false> {};

template <>
struct is_simd_flag_type<element_aligned_tag>
: std::integral_constant<bool, true> {};

template <>
struct is_simd_flag_type<vector_aligned_tag>
: std::integral_constant<bool, true> {};

template <Idx _Align>
struct is_simd_flag_type<overaligned_tag<_Align>>
: std::integral_constant<bool, true> {};

// template <class _Tp>
// constexpr bool is_abi_tag_v = is_abi_tag<_Tp>::value;
// template <class _Tp>
// constexpr bool is_simd_v = is_simd<_Tp>::value;
// template <class _Tp>
// constexpr bool is_simd_mask_v = is_simd_mask<_Tp>::value;
// template <class _Tp>
// constexpr bool is_simd_flag_type_v = is_simd_flag_type<_Tp>::value;

template <class _Tp, Idx __n>
struct abi_for_size {
  using type = simd_abi::fixed_size<__n>;
};
template <class _Tp, Idx __n>
using abi_for_size_t = typename abi_for_size<_Tp, __n>::type;

template <class _Tp, class _Abi = simd_abi::compatible<_Tp>>
struct simd_size;

template <class _Tp, _StorageKind __kind, Idx __n>
struct simd_size<_Tp, __simd_abi<__kind, __n>>
: std::integral_constant<Idx, __n> {
  static_assert(std::is_arithmetic<_Tp>::value &&
          !std::is_same<typename std::remove_const<_Tp>::type,
                bool>::value,
          "Element type should be vectorizable");
};

// TODO: implement it.
template <class _Tp, class _Up = typename _Tp::value_type>
struct memory_alignment;

// template <class _Tp, class _Abi = simd_abi::compatible<_Tp>>
// constexpr Idx simd_size_v = simd_size<_Tp, _Abi>::value;

// template <class _Tp, class _Up = typename _Tp::value_type>
// constexpr Idx memory_alignment_v = memory_alignment<_Tp, _Up>::value;

// class template simd [simd.class]
template <class _Tp>
using native_simd = simd<_Tp, simd_abi::native<_Tp>>;

template <class _Tp, Idx __n>
using fixed_size_simd = simd<_Tp, simd_abi::fixed_size<__n>>;

// class template simd_mask [simd.mask.class]
template <class _Tp>
using native_simd_mask = simd_mask<_Tp, simd_abi::native<_Tp>>;

template <class _Tp, Idx __n>
using fixed_size_simd_mask = simd_mask<_Tp, simd_abi::fixed_size<__n>>;

// casts [simd.casts]
template <class _Tp>
struct __static_simd_cast_traits {
  template <class _Up, class _Abi>
  static simd<_Tp, _Abi> __apply(const simd<_Up, _Abi>& __v);
};

template <class _Tp, class _NewAbi>
struct __static_simd_cast_traits<simd<_Tp, _NewAbi>> {
  template <class _Up, class _Abi>
  static typename std::enable_if<simd<_Up, _Abi>::size() ==
                   simd<_Tp, _NewAbi>::size(),
                   simd<_Tp, _NewAbi>
                  >::type
  __apply(const simd<_Up, _Abi>& __v);
};

template <class _Tp>
struct __simd_cast_traits {
  template <class _Up, class _Abi>
  static typename std::enable_if<
      __is_non_narrowing_arithmetic_convertible<_Up, _Tp>(),
      simd<_Tp, _Abi>>::type
  __apply(const simd<_Up, _Abi>& __v);
};

template <class _Tp, class _NewAbi>
struct __simd_cast_traits<simd<_Tp, _NewAbi>> {
  template <class _Up, class _Abi>
  static typename
  std::enable_if<__is_non_narrowing_arithmetic_convertible<_Up, _Tp>() &&
           simd<_Up, _Abi>::size() == simd<_Tp, _NewAbi>::size(),
           simd<_Tp, _NewAbi>
          >::type
  __apply(const simd<_Up, _Abi>& __v);
};

template <class _Tp, class _Up, class _Abi>
auto simd_cast(const simd<_Up, _Abi>& __v)
    -> decltype(__simd_cast_traits<_Tp>::__apply(__v))
{
  return __simd_cast_traits<_Tp>::__apply(__v);
}

template <class _Tp, class _Up, class _Abi>
auto static_simd_cast(const simd<_Up, _Abi>& __v)
    -> decltype(__static_simd_cast_traits<_Tp>::__apply(__v)) {
  return __static_simd_cast_traits<_Tp>::__apply(__v);
}

template <class _Tp, class _Abi>
fixed_size_simd<_Tp, simd_size<_Tp, _Abi>::value>
to_fixed_size(const simd<_Tp, _Abi>&) noexcept;

template <class _Tp, class _Abi>
fixed_size_simd_mask<_Tp, simd_size<_Tp, _Abi>::value>
to_fixed_size(const simd_mask<_Tp, _Abi>&) noexcept;

template <class _Tp, Idx __n>
native_simd<_Tp> to_native(const fixed_size_simd<_Tp, __n>&) noexcept;

template <class _Tp, Idx __n>
native_simd_mask<_Tp> to_native(const fixed_size_simd_mask<_Tp, __n>&) noexcept;

template <class _Tp, Idx __n>
simd<_Tp> to_compatible(const fixed_size_simd<_Tp, __n>&) noexcept;

template <class _Tp, Idx __n>
simd_mask<_Tp> to_compatible(const fixed_size_simd_mask<_Tp, __n>&) noexcept;

template <Idx... __sizes, class _Tp, class _Abi>
std::tuple<simd<_Tp, abi_for_size_t<_Tp, __sizes>>...>
split(const simd<_Tp, _Abi>&);

template <Idx... __sizes, class _Tp, class _Abi>
std::tuple<simd_mask<_Tp, abi_for_size_t<_Tp, __sizes>>...>
split(const simd_mask<_Tp, _Abi>&);

template <class _SimdType, class _Abi>
std::array<_SimdType, simd_size<typename _SimdType::value_type, _Abi>::value /
                          _SimdType::size()>
split(const simd<typename _SimdType::value_type, _Abi>&);

template <class _SimdType, class _Abi>
std::array<_SimdType, simd_size<typename _SimdType::value_type, _Abi>::value /
                          _SimdType::size()>
split(const simd_mask<typename _SimdType::value_type, _Abi>&);

template <class _Tp, class... _Abis>
simd<_Tp, abi_for_size_t<_Tp, __variadic_sum(simd_size<_Tp, _Abis>::value...)>>
concat(const simd<_Tp, _Abis>&...);

template <class _Tp, class... _Abis>
simd_mask<_Tp,
          abi_for_size_t<_Tp, __variadic_sum(simd_size<_Tp, _Abis>::value...)>>
concat(const simd_mask<_Tp, _Abis>&...);

// reductions [simd.mask.reductions]
template <class _Tp, class _Abi>
bool all_of(const simd_mask<_Tp, _Abi>&) noexcept;
template <class _Tp, class _Abi>
bool any_of(const simd_mask<_Tp, _Abi>&) noexcept;
template <class _Tp, class _Abi>
bool none_of(const simd_mask<_Tp, _Abi>&) noexcept;
template <class _Tp, class _Abi>
bool some_of(const simd_mask<_Tp, _Abi>&) noexcept;
template <class _Tp, class _Abi>
Idx popcount(const simd_mask<_Tp, _Abi>&) noexcept;
template <class _Tp, class _Abi>
Idx find_first_set(const simd_mask<_Tp, _Abi>&);
template <class _Tp, class _Abi>
Idx find_last_set(const simd_mask<_Tp, _Abi>&);
bool all_of(bool) noexcept;
bool any_of(bool) noexcept;
bool none_of(bool) noexcept;
bool some_of(bool) noexcept;
Idx popcount(bool) noexcept;
Idx find_first_set(bool) noexcept;
Idx find_last_set(bool) noexcept;

// masked assignment [simd.whereexpr]
template <class _MaskType, class _Tp>
class const_where_expression;
template <class _MaskType, class _Tp>
class where_expression;

// masked assignment [simd.mask.where]
template <class _Tp, class _Abi>
where_expression<simd_mask<_Tp, _Abi>, simd<_Tp, _Abi>>
where(const typename simd<_Tp, _Abi>::mask_type&, simd<_Tp, _Abi>&) noexcept;

template <class _Tp, class _Abi>
const_where_expression<simd_mask<_Tp, _Abi>, const simd<_Tp, _Abi>>
where(const typename simd<_Tp, _Abi>::mask_type&,
      const simd<_Tp, _Abi>&) noexcept;

template <class _Tp, class _Abi>
where_expression<simd_mask<_Tp, _Abi>, simd_mask<_Tp, _Abi>>
where(const typename __nodeduce<simd_mask<_Tp, _Abi>>::type&,
      simd_mask<_Tp, _Abi>&) noexcept;

template <class _Tp, class _Abi>
const_where_expression<simd_mask<_Tp, _Abi>, const simd_mask<_Tp, _Abi>>
where(const typename __nodeduce<simd_mask<_Tp, _Abi>>::type&,
      const simd_mask<_Tp, _Abi>&) noexcept;

template <class _Tp>
where_expression<bool, _Tp> where(bool, _Tp&) noexcept;

template <class _Tp>
const_where_expression<bool, const _Tp> where(bool, const _Tp&) noexcept;

// reductions [simd.reductions]
template <class _Tp, class _Abi, class _BinaryOp = std::plus<_Tp>>
_Tp reduce(const simd<_Tp, _Abi>&, _BinaryOp = _BinaryOp());

template <class _MaskType, class _SimdType, class _BinaryOp>
typename _SimdType::value_type
reduce(const const_where_expression<_MaskType, _SimdType>&,
       typename _SimdType::value_type neutral_element, _BinaryOp binary_op);

template <class _MaskType, class _SimdType>
typename _SimdType::value_type
reduce(const const_where_expression<_MaskType, _SimdType>&,
       std::plus<typename _SimdType::value_type> binary_op = {});

template <class _MaskType, class _SimdType>
typename _SimdType::value_type
reduce(const const_where_expression<_MaskType, _SimdType>&,
       std::multiplies<typename _SimdType::value_type> binary_op);

template <class _MaskType, class _SimdType>
typename _SimdType::value_type
reduce(const const_where_expression<_MaskType, _SimdType>&,
       std::bit_and<typename _SimdType::value_type> binary_op);

template <class _MaskType, class _SimdType>
typename _SimdType::value_type
reduce(const const_where_expression<_MaskType, _SimdType>&,
       std::bit_or<typename _SimdType::value_type> binary_op);

template <class _MaskType, class _SimdType>
typename _SimdType::value_type
reduce(const const_where_expression<_MaskType, _SimdType>&,
       std::bit_xor<typename _SimdType::value_type> binary_op);

template <class _Tp, class _Abi>
_Tp hmin(const simd<_Tp, _Abi>&);
template <class _MaskType, class _SimdType>
typename _SimdType::value_type
hmin(const const_where_expression<_MaskType, _SimdType>&);
template <class _Tp, class _Abi>
_Tp hmax(const simd<_Tp, _Abi>&);
template <class _MaskType, class _SimdType>
typename _SimdType::value_type
hmax(const const_where_expression<_MaskType, _SimdType>&);

// algorithms [simd.alg]
template <class _Tp, class _Abi>
simd<_Tp, _Abi> min(const simd<_Tp, _Abi>&, const simd<_Tp, _Abi>&) noexcept;

template <class _Tp, class _Abi>
simd<_Tp, _Abi> max(const simd<_Tp, _Abi>&, const simd<_Tp, _Abi>&) noexcept;

template <class _Tp, class _Abi>
std::pair<simd<_Tp, _Abi>, simd<_Tp, _Abi>>
minmax(const simd<_Tp, _Abi>&, const simd<_Tp, _Abi>&) noexcept;

template <class _Tp, class _Abi>
simd<_Tp, _Abi> clamp(const simd<_Tp, _Abi>&, const simd<_Tp, _Abi>&,
                      const simd<_Tp, _Abi>&);

// [simd.whereexpr]
// TODO implement where expressions.
template <class _MaskType, class _Tp>
class const_where_expression {
public:
  const_where_expression(const const_where_expression&) = delete;
  const_where_expression& operator=(const const_where_expression&) = delete;
  typename std::remove_const<_Tp>::type operator-() const&&;
  template <class _Up, class _Flags>
  void copy_to(_Up*, _Flags) const&&;
};

template <class _MaskType, class _Tp>
class where_expression : public const_where_expression<_MaskType, _Tp> {
public:
  where_expression(const where_expression&) = delete;
  where_expression& operator=(const where_expression&) = delete;
  template <class _Up>
  void operator=(_Up&&);
  template <class _Up>
  void operator+=(_Up&&);
  template <class _Up>
  void operator-=(_Up&&);
  template <class _Up>
  void operator*=(_Up&&);
  template <class _Up>
  void operator/=(_Up&&);
  template <class _Up>
  void operator%=(_Up&&);
  template <class _Up>
  void operator&=(_Up&&);
  template <class _Up>
  void operator|=(_Up&&);
  template <class _Up>
  void operator^=(_Up&&);
  template <class _Up>
  void operator<<=(_Up&&);
  template <class _Up>
  void operator>>=(_Up&&);
  void operator++();
  void operator++(int);
  void operator--();
  void operator--(int);
  template <class _Up, class _Flags>
  void copy_from(const _Up*, _Flags);
};

// [simd.class]
// TODO: implement simd
template <class _Tp, class _Abi>
class simd {
public:
  using value_type = _Tp;
  using reference = __simd_reference<_Tp, _Tp, _Abi>;
  using mask_type = simd_mask<_Tp, _Abi>;
  using abi_type = _Abi;

  simd() = default;
  simd(const simd&) = default;
  simd& operator=(const simd&) = default;

  static constexpr Idx size() noexcept {
    return simd_size<_Tp, _Abi>::value;
  }

private:
  __simd_storage<_Tp, _Abi> __s_;

  template <class _Up>
  static constexpr bool __can_broadcast()
  {
    using namespace std;
    return (is_arithmetic<_Up>::value &&
        __is_non_narrowing_arithmetic_convertible<_Up, _Tp>()) ||
         (!is_arithmetic<_Up>::value &&
        is_convertible<_Up, _Tp>::value) ||
         is_same<typename remove_const<_Up>::type, Idx>::value ||
         (is_same<typename remove_const<_Up>::type,
        unsigned int>::value &&
        std::is_unsigned<_Tp>::value);
  }

#if __cplusplus >= 201402L
  template <class _Generator, Idx... __indicies>
  static constexpr decltype(
      std::forward_as_tuple(std::declval<_Generator>()(
          std::integral_constant<Idx, __indicies>())...),
      bool())
  __can_generate(std::index_sequence<__indicies...>) {
    return !__variadic_sum<bool>(
        !__can_broadcast<decltype(std::declval<_Generator>()(
            std::integral_constant<Idx, __indicies>()))>()...);
  }

  template <class _Generator>
  static bool __can_generate(...) {
    return false;
  }

  template <class _Generator, Idx... __indicies>
  void __generator_init(_Generator&& __g, std::index_sequence<__indicies...>)
  {
    Idx __not_used[]{((*this)[__indicies] =
        __g(std::integral_constant<Idx, __indicies>()), 0)...};
    (void)__not_used;
  }
#endif

public:
  // implicit type conversion constructor
  template <class _Up,
        class = typename std::enable_if<
          std::is_same<_Abi, simd_abi::fixed_size<size()>>::value &&
          __is_non_narrowing_arithmetic_convertible<_Up, _Tp>()>::type>
  simd(const simd<_Up, simd_abi::fixed_size<size()>>& __v)
  {
    for (Idx __i = 0; __i < size(); __i++) {
      (*this)[__i] = static_cast<_Tp>(__v[__i]);
    }
  }

  // implicit broadcast constructor
  template <class _Up,
        class = typename std::enable_if<__can_broadcast<_Up>()>::type>
  simd(_Up&& __rv)
  {
    auto __v = static_cast<_Tp>(__rv);
    for (Idx __i = 0; __i < size(); __i++) {
      (*this)[__i] = __v;
    }
  }

#if __cplusplus >= 201402L
  // generator constructor
  template <class _Generator,
        Idx = typename std::enable_if<
        __can_generate<_Generator>(std::make_index_sequence<size()>()),
        Idx>::type()>
  explicit simd(_Generator&& __g) {
    __generator_init(std::forward<_Generator>(__g),
             std::make_index_sequence<size()>());
  }
#endif

  // load constructor
  template <
    class _Up, class _Flags,
    class = typename std::enable_if<__vectorizable<_Up>()>::type,
    class = typename std::enable_if<is_simd_flag_type<_Flags>::value>::type
  >
  simd(const _Up* __buffer, _Flags)
  {
    // TODO: optimize for overaligned flags
    for (Idx __i = 0; __i < size(); __i++) {
      (*this)[__i] = static_cast<_Tp>(__buffer[__i]);
    }
  }

  // loads [simd.load]
  template <class _Up, class _Flags>
  typename std::enable_if<__vectorizable<_Up>() &&
              is_simd_flag_type<_Flags>::value>::type
  copy_from(const _Up* __buffer, _Flags) {
    *this = simd(__buffer, _Flags());
  }

  // stores [simd.store]
  template <class _Up, class _Flags>
  typename std::enable_if<__vectorizable<_Up>() &&
              is_simd_flag_type<_Flags>::value>::type
  copy_to(_Up* __buffer, _Flags) const {
    // TODO: optimize for overaligned flags
    for (Idx __i = 0; __i < size(); __i++) {
      __buffer[__i] = static_cast<_Up>((*this)[__i]);
    }
  }

  // scalar access [simd.subscr]
  reference operator[](Idx __i) { return reference(&__s_, __i); }

  value_type operator[](Idx __i) const { return __s_.__get(__i); }

  // unary operators [simd.unary]
  simd& operator++();
  simd operator++(int);
  simd& operator--();
  simd operator--(int);
  mask_type operator!() const;
  simd operator~() const;
  simd operator+() const;
  simd operator-() const;

  // binary operators [simd.binary]
  friend simd operator+(const simd&, const simd&);
  friend simd operator-(const simd&, const simd&);
  friend simd operator*(const simd&, const simd&);
  friend simd operator/(const simd&, const simd&);
  friend simd operator%(const simd&, const simd&);
  friend simd operator&(const simd&, const simd&);
  friend simd operator|(const simd&, const simd&);
  friend simd operator^(const simd&, const simd&);
  friend simd operator<<(const simd&, const simd&);
  friend simd operator>>(const simd&, const simd&);
  friend simd operator<<(const simd&, Idx);
  friend simd operator>>(const simd&, Idx);

  // compound assignment [simd.cassign]
  friend simd& operator+=(simd&, const simd&);
  friend simd& operator-=(simd&, const simd&);
  friend simd& operator*=(simd&, const simd&);
  friend simd& operator/=(simd&, const simd&);
  friend simd& operator%=(simd&, const simd&);

  friend simd& operator&=(simd&, const simd&);
  friend simd& operator|=(simd&, const simd&);
  friend simd& operator^=(simd&, const simd&);
  friend simd& operator<<=(simd&, const simd&);
  friend simd& operator>>=(simd&, const simd&);
  friend simd& operator<<=(simd&, Idx);
  friend simd& operator>>=(simd&, Idx);

  // compares [simd.comparison]
  friend mask_type operator==(const simd&, const simd&);
  friend mask_type operator!=(const simd&, const simd&);
  friend mask_type operator>=(const simd&, const simd&);
  friend mask_type operator<=(const simd&, const simd&);
  friend mask_type operator>(const simd&, const simd&);
  friend mask_type operator<(const simd&, const simd&);
};

// [simd.mask.class]
template <class _Tp, class _Abi>
// TODO: implement simd_mask
class simd_mask {
public:
  using value_type = bool;
  // TODO: this is strawman implementation. Turn it into a proxy type.
  using reference = bool&;
  using simd_type = simd<_Tp, _Abi>;
  using abi_type = _Abi;
  static constexpr Idx size() noexcept;
  simd_mask() = default;

  // broadcast constructor
  explicit simd_mask(value_type) noexcept;

  // implicit type conversion constructor
  template <class _Up>
  simd_mask(const simd_mask<_Up, simd_abi::fixed_size<size()>>&) noexcept;

  // load constructor
  template <class _Flags>
  simd_mask(const value_type*, _Flags);

  // loads [simd.mask.copy]
  template <class _Flags>
  void copy_from(const value_type*, _Flags);
  template <class _Flags>
  void copy_to(value_type*, _Flags) const;

  // scalar access [simd.mask.subscr]
  reference operator[](Idx);
  value_type operator[](Idx) const;

  // unary operators [simd.mask.unary]
  simd_mask operator!() const noexcept;

  // simd_mask binary operators [simd.mask.binary]
  friend simd_mask operator&&(const simd_mask&, const simd_mask&) noexcept;
  friend simd_mask operator||(const simd_mask&, const simd_mask&) noexcept;
  friend simd_mask operator&(const simd_mask&, const simd_mask&)noexcept;
  friend simd_mask operator|(const simd_mask&, const simd_mask&) noexcept;
  friend simd_mask operator^(const simd_mask&, const simd_mask&) noexcept;

  // simd_mask compound assignment [simd.mask.cassign]
  friend simd_mask& operator&=(simd_mask&, const simd_mask&) noexcept;
  friend simd_mask& operator|=(simd_mask&, const simd_mask&) noexcept;
  friend simd_mask& operator^=(simd_mask&, const simd_mask&) noexcept;

  // simd_mask compares [simd.mask.comparison]
  friend simd_mask operator==(const simd_mask&, const simd_mask&) noexcept;
  friend simd_mask operator!=(const simd_mask&, const simd_mask&) noexcept;
};

}} // namespace Squeeze::(inline)simd

#endif // include guard
