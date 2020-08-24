#ifndef SQUEEZE_FUNCTIONAL_HH
#define SQUEEZE_FUNCTIONAL_HH

#include <cmath>
#include "../init/macros.hh"

namespace Squeeze {

/* ------------------------- some basic functionals ------------------------- */
// unary operator: negate
template <class _Tp>
struct Negate
{
  SQUEEZE_DEVICE_FUNC static constexpr
  _Tp run(const _Tp& x) { return -x; }
};

// unary operator: exp
template <class _Tp>
struct Exp
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::exp(x); }
};

// unary operator: exp2
template <class _Tp>
struct Exp2
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::exp2(x); }
};

// unary operator: exp(x) - 1
template <class _Tp>
struct Expm1
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::expm1(x); }
};

// unary operator: ln
template <class _Tp>
struct Ln
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::log(x); }
};

// unary operator: log10
template <class _Tp>
struct Log10
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::log10(x); }
};

// unary operator: log2
template <class _Tp>
struct Log2
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::log2(x); }
};

// unary operator: log(1+x)
template <class _Tp>
struct Log1p
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::log1p(x); }
};

// unary operator: sqrt
template <class _Tp>
struct Sqrt
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::sqrt(x); }
};

// unary operator: cbrt
template <class _Tp>
struct Cbrt
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::cbrt(x); }
};

// unary operator: sin
template <class _Tp>
struct Sin
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::sin(x); }
};

// unary operator: cos
template <class _Tp>
struct Cos
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::cos(x); }
};

// unary operator: tan
template <class _Tp>
struct Tan
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::tan(x); }
};

// unary operator: arcsin
template <class _Tp>
struct ASin
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::asin(x); }
};

// unary operator: arccos
template <class _Tp>
struct ACos
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::acos(x); }
};

// unary operator: arctan
template <class _Tp>
struct ATan
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::atan(x); }
};

// unary operator: sinh
template <class _Tp>
struct Sinh
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::sinh(x); }
};

// unary operator: cosh
template <class _Tp>
struct Cosh
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::cosh(x); }
};

// unary operator: tanh
template <class _Tp>
struct Tanh
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::tanh(x); }
};

// unary operator: arcsinh
template <class _Tp>
struct ASinh
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::asinh(x); }
};

// unary operator: arccosh
template <class _Tp>
struct ACosh
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::acosh(x); }
};

// unary operator: arctanh
template <class _Tp>
struct ATanh
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  _Tp run(const _Tp& x) { return std::atanh(x); }
};


// binary operator: plus
template <class _Tp, class _Up = _Tp>
struct Plus
{
  SQUEEZE_DEVICE_FUNC static constexpr
  SQUEEZE_COMMON_TYPE(_Tp, _Up)
  run(const _Tp& x, const _Up& y) { return x + y; }
};

// binary operator: minus
template <class _Tp, class _Up = _Tp>
struct Minus
{
  SQUEEZE_DEVICE_FUNC static constexpr
  SQUEEZE_COMMON_TYPE(_Tp, _Up)
  run(const _Tp& x, const _Up& y) { return x - y; }
};

// binary operator: multiplies
template <class _Tp, class _Up = _Tp>
struct Multiplies
{
  SQUEEZE_DEVICE_FUNC static constexpr
  SQUEEZE_COMMON_TYPE(_Tp, _Up)
  run(const _Tp& x, const _Up& y) { return x * y; }
};

// binary operator: divides
template <class _Tp, class _Up = _Tp>
struct Divides
{
  SQUEEZE_DEVICE_FUNC static constexpr
  SQUEEZE_COMMON_TYPE(_Tp, _Up)
  run(const _Tp& x, const _Up& y) { return x / y; }
};

// binary operator: pow
template <class _Tp, class _Up = _Tp>
struct Pow
{
  SQUEEZE_DEVICE_FUNC static SQUEEZE_ALWAYS_INLINE
  SQUEEZE_COMMON_TYPE(_Tp, _Up)
  run(const _Tp& x, const _Up& y) { return std::pow(x, y); }
};

} // namespace Squeeze
#endif //include guard
