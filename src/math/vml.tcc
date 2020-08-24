// //for debug only
// #include "math.hh"
// #include <mkl_vml.h>
// // #define SQUEEZE_VML_USE_FLOAT
// #define SQUEEZE_VML_USE_DOUBLE
// // #define SQUEEZE_VML_USE_COMPLEX_FLOAT
// // #define SQUEEZE_VML_USE_COMPLEX_DOUBLE

// namespace Squeeze { namespace internal {

#ifdef SQUEEZE_VML_USE_DOUBLE
  #define TYPE double
  #define CONST_CAST(x) x
  #define CAST(x) x
  #define FUNC(func) v ## d ## func
#elif defined SQUEEZE_VML_USE_FLOAT
  #define TYPE float
  #define CONST_CAST(x) x
  #define CAST(x) x
  #define FUNC(func) v ## s ## func
#elif defined SQUEEZE_VML_USE_COMPLEX_DOUBLE
  #define TYPE Complex<double>
  #define CONST_CAST(x) reinterpret_cast<const MKL_Complex16*>(x)
  #define CAST(x) reinterpret_cast<MKL_Complex16*>(x)
  #define FUNC(func) v ## z ## func
#elif defined SQUEEZE_VML_USE_COMPLEX_FLOAT
  #define TYPE Complex<float>
  #define CONST_CAST(x) reinterpret_cast<const MKL_Complex8*>(x)
  #define CAST(x) reinterpret_cast<MKL_Complex8*>(x)
  #define FUNC(func) v ## c ## func
#endif


template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_add(Idx size, const TYPE* x, const TYPE* y, TYPE* out) {
  FUNC(Add)(size, CONST_CAST(x), CONST_CAST(y), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_sub(Idx size, const TYPE* x, const TYPE* y, TYPE* out) {
  FUNC(Sub)(size, CONST_CAST(x), CONST_CAST(y), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_mul(Idx size, const TYPE* x, const TYPE* y, TYPE* out) {
  FUNC(Mul)(size, CONST_CAST(x), CONST_CAST(y), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_div(Idx size, const TYPE* x, const TYPE* y, TYPE* out) {
  FUNC(Div)(size, CONST_CAST(x), CONST_CAST(y), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_pow(Idx size, const TYPE* x, const TYPE* y, TYPE* out) {
  FUNC(Pow)(size, CONST_CAST(x), CONST_CAST(y), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_exp(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Exp)(size, CONST_CAST(x), CAST(out));
}

#if (defined SQUEEZE_VML_USE_FLOAT || defined SQUEEZE_VML_USE_DOUBLE)
template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_exp2(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Exp2)(size, CONST_CAST(x), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_expm1(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Expm1)(size, CONST_CAST(x), CAST(out));
}
#endif

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_ln(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Ln)(size, CONST_CAST(x), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_log10(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Log10)(size, CONST_CAST(x), CAST(out));
}

#if (defined SQUEEZE_VML_USE_FLOAT || defined SQUEEZE_VML_USE_DOUBLE)
template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_log2(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Log2)(size, CONST_CAST(x), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_log1p(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Log1p)(size, CONST_CAST(x), CAST(out));
}
#endif

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_sqrt(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Sqrt)(size, CONST_CAST(x), CAST(out));
}

#if (defined SQUEEZE_VML_USE_FLOAT || defined SQUEEZE_VML_USE_DOUBLE)
template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_cbrt(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Cbrt)(size, CONST_CAST(x), CAST(out));
}
#endif

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_sin(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Sin)(size, CONST_CAST(x), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_cos(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Cos)(size, CONST_CAST(x), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_tan(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Tan)(size, CONST_CAST(x), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_asin(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Asin)(size, CONST_CAST(x), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_acos(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Acos)(size, CONST_CAST(x), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_atan(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Atan)(size, CONST_CAST(x), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_sinh(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Sinh)(size, CONST_CAST(x), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_cosh(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Cosh)(size, CONST_CAST(x), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_tanh(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Tanh)(size, CONST_CAST(x), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_asinh(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Asinh)(size, CONST_CAST(x), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_acosh(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Acosh)(size, CONST_CAST(x), CAST(out));
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_atanh(Idx size, const TYPE* x, TYPE* out) {
  FUNC(Atanh)(size, CONST_CAST(x), CAST(out));
}

#undef TYPE
#undef CONST_CAST
#undef CAST
#undef FUNC


// // for debug only
// }}
