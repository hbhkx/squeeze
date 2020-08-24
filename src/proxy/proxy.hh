#ifndef SQUEEZE_PROXY_HH
#define SQUEEZE_PROXY_HH

#include "../init/type_traits.hh"

namespace Squeeze {

namespace internal {

/* --------------------- helper classes for type_traits --------------------- */
struct Proxy
{
  Idx m_size = 0;

  SQUEEZE_DEVICE_FUNC constexpr Proxy(Idx size) : m_size(size) {}
  SQUEEZE_DEVICE_FUNC constexpr Idx size() const { return m_size; }
};

template<class _Pro>
using VoidIfProxy =
    SQUEEZE_ENABLE_IF((std::is_base_of<Proxy, _Pro>::value), void);

template<class _Pro>
using IdxIfProxy =
    SQUEEZE_ENABLE_IF((std::is_base_of<Proxy, _Pro>::value), Idx);

template<class _Obj>
using IdxIfProxyOrAri =
    SQUEEZE_ENABLE_IF((std::is_base_of<Proxy, _Obj>::value ||
                       SupportedType<_Obj>::value), Idx);

} // namespace internal


template<class _Obj>
using ValueType = typename internal::ValueType<_Obj>::type;


/* ------------- Unary and binary proxies for lazy calculation -------------- */
// unary proxy for an object
template<class _Op, class _Obj>
struct UnaProxy : public internal::Proxy
{
  using ValueType = ValueType<_Obj>;

  const _Obj& obj;

  SQUEEZE_DEVICE_FUNC constexpr UnaProxy(const _Obj& o)
  : obj(o), internal::Proxy(o.size()) {}

  SQUEEZE_DEVICE_FUNC SQUEEZE_ALWAYS_INLINE ValueType operator[](Idx i) const {
    return _Op::run(obj[i]);
  }
};

// binary proxy for two objects
template<class _Op, class _Obj1, class _Obj2 = _Obj1, class _Sfinae = void>
struct BinProxy : public internal::Proxy
{
  using ValueType = SQUEEZE_COMMON_TYPE(ValueType<_Obj1>, ValueType<_Obj2>);

  const _Obj1& obj1;
  const _Obj2& obj2;

  SQUEEZE_DEVICE_FUNC constexpr BinProxy(const _Obj1& o1, const _Obj2& o2)
  : obj1(o1), obj2(o2), internal::Proxy(o1.size())
  {
#ifdef SQUEEZE_HAS_DEBUG
    if (o1.size() != o2.size())
      throw std::length_error("Binary operator is applied to containers \
                               with different sizes!!");
#endif
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_ALWAYS_INLINE ValueType operator[](Idx i) const {
    return _Op::run(obj1[i], obj2[i]);
  }
};

// binary proxy for arithmetic and object
template<class _Op, class _Ari, class _Obj>
struct BinProxy<_Op, _Ari, _Obj, internal::VoidIfAri<_Ari>>
: public internal::Proxy
{
  using ValueType = SQUEEZE_COMMON_TYPE(_Ari, ValueType<_Obj>);

  const _Ari& ari;
  const _Obj& obj;

  SQUEEZE_DEVICE_FUNC constexpr BinProxy(const _Ari& a, const _Obj& o)
  : ari(a), obj(o), internal::Proxy(o.size()) {}

  SQUEEZE_DEVICE_FUNC SQUEEZE_ALWAYS_INLINE ValueType operator[](Idx i) const {
    return _Op::run(ari, obj[i]);
  }
};

// binary proxy for object and arithmetic
template<class _Op, class _Obj, class _Ari>
struct BinProxy<_Op, _Obj, _Ari, internal::VoidIfAri<_Ari>>
: public internal::Proxy
{
  using ValueType = SQUEEZE_COMMON_TYPE(ValueType<_Obj>, _Ari);

  const _Obj& obj;
  const _Ari& ari;

  SQUEEZE_DEVICE_FUNC constexpr BinProxy(const _Obj& o, const _Ari& a)
  : obj(o), ari(a), internal::Proxy(o.size()) {}

  SQUEEZE_DEVICE_FUNC SQUEEZE_ALWAYS_INLINE ValueType operator[](Idx i) const {
    return _Op::run(obj[i], ari);
  }
};


#define SQUEEZE_UNAPROXY(Op, Obj) UnaProxy<Op<ValueType<Obj>>, Obj>
#define SQUEEZE_BINPROXY(Op, Obj1, Obj2)                              \
  BinProxy<Op<SQUEEZE_COMMON_TYPE(ValueType<Obj1>, ValueType<Obj2>)>, \
           Obj1, Obj2>

/* ---------------------------- unary functions ----------------------------- */
template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(Negate, _Obj) operator-(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(Negate, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(Exp, _Obj) exp(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(Exp, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(Exp2, _Obj) exp2(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(Exp2, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(Expm1, _Obj) expm1(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(Expm1, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(Ln, _Obj) ln(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(Ln, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(Log10, _Obj) log10(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(Log10, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(Log2, _Obj) log2(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(Log2, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(Log1p, _Obj) log1p(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(Log1p, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(Sqrt, _Obj) sqrt(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(Sqrt, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(Cbrt, _Obj) cbrt(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(Cbrt, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(Sin, _Obj) sin(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(Sin, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(Cos, _Obj) cos(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(Cos, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(Tan, _Obj) tan(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(Tan, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(ASin, _Obj) asin(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(ASin, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(ACos, _Obj) acos(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(ACos, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(ATan, _Obj) atan(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(ATan, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(Sinh, _Obj) sinh(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(Sinh, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(Cosh, _Obj) cosh(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(Cosh, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(Tanh, _Obj) tanh(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(Tanh, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(ASinh, _Obj) asinh(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(ASinh, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(ACosh, _Obj) acosh(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(ACosh, _Obj)(obj);
}

template<class _Obj>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_UNAPROXY(ATanh, _Obj) atanh(const _Obj& obj) {
  return SQUEEZE_UNAPROXY(ATanh, _Obj)(obj);
}


/* ---------------------------- binary functions ---------------------------- */
template<class _Obj1, class _Obj2>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_BINPROXY(Plus, _Obj1, _Obj2)
operator+(const _Obj1& obj1, const _Obj2& obj2) {
  return SQUEEZE_BINPROXY(Plus, _Obj1, _Obj2)(obj1, obj2);
}

template<class _Obj1, class _Obj2>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_BINPROXY(Minus, _Obj1, _Obj2)
operator-(const _Obj1& obj1, const _Obj2& obj2) {
  return SQUEEZE_BINPROXY(Minus, _Obj1, _Obj2)(obj1, obj2);
}

template<class _Obj1, class _Obj2>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_BINPROXY(Multiplies, _Obj1, _Obj2)
operator*(const _Obj1& obj1, const _Obj2& obj2) {
  return SQUEEZE_BINPROXY(Multiplies, _Obj1, _Obj2)(obj1, obj2);
}

template<class _Obj1, class _Obj2>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_BINPROXY(Divides, _Obj1, _Obj2)
operator/(const _Obj1& obj1, const _Obj2& obj2) {
  return SQUEEZE_BINPROXY(Divides, _Obj1, _Obj2)(obj1, obj2);
}

template<class _Obj1, class _Obj2>
SQUEEZE_DEVICE_FUNC constexpr
SQUEEZE_BINPROXY(Pow, _Obj1, _Obj2)
pow(const _Obj1& obj1, const _Obj2& obj2) {
  return SQUEEZE_BINPROXY(Pow, _Obj1, _Obj2)(obj1, obj2);
}

} // namespace Squeeze
#endif // include guard
