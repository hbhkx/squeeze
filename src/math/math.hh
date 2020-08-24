#ifndef SQUEEZE_MATH_HH
#define SQUEEZE_MATH_HH

#include <algorithm>
#include <numeric>
#include "../simd/vectorization.hh"
#include "complex.hh"

#ifdef SQUEEZE_USE_MKL
  #define MKL_INT       Squeeze::Idx
  #define MKL_Complex8  Squeeze::Complex<float>
  #define MKL_Complex16 Squeeze::Complex<double>

  #include <mkl_service.h>
  #include <mkl_cblas.h>
  #include <mkl_lapacke.h>
  #include <fftw/fftw3_mkl.h>
  #include <mkl_vml.h>
  #include <mkl_vsl.h>
  #include <mkl_spblas.h>
#else
  #ifdef SQUEEZE_USE_BLAS
    #include <cblas.h>
  #endif
  #ifdef SQUEEZE_USE_LAPACK
    #define lapack_int            Squeeze::Idx
    #define lapack_complex_float  Squeeze::Complex<float>
    #define lapack_complex_double Squeeze::Complex<double>
    #include <lapacke.h>
  #endif
  #ifdef SQUEEZE_USE_FFTW
    #include <fftw3.h>
  #endif
#endif

#define SQUEEZE_NON_PAR_COPY_BYTES 1048576 * SQUEEZE_MAX_ALIGN_BYTES

#ifdef SQUEEZE_USE_BLAS
  #define SQUEEZE_NON_PAR_CAL_BYTES  4096 * SQUEEZE_MAX_ALIGN_BYTES
#else
  #define SQUEEZE_NON_PAR_CAL_BYTES 16384 * SQUEEZE_MAX_ALIGN_BYTES
#endif


namespace Squeeze {

namespace internal {

/* ----------------------------- parallel_copy ------------------------------ */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_copy(Idx size, const _Tp* src, _Up* dest) {
  #pragma omp parallel for simd aligned(src, dest)
  for (Idx i = 0; i < size; i++) {
    *(dest + i) = *(src + i);
  }
}


/* ----------------------------- parallel_dot(u) ---------------------------- */
// for non-complex types
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
SQUEEZE_COMMON_TYPE(_Tp, _Up)
parallel_dot(Idx size, const _Tp* x, const _Up* y) {
  SQUEEZE_COMMON_TYPE(_Tp, _Up) sum = 0;
  #pragma omp parallel for simd aligned(x, y) reduction(+: sum)
  for (Idx i = 0; i < size; i++) {
      sum += *(x + i) * *(y + i);
  }
  return sum;
}

// for complex types, calculate conj(a) dot b
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
SQUEEZE_COMMON_TYPE(Complex<_Tp>, Complex<_Up>)
parallel_dot(Idx size, const Complex<_Tp>* x, const Complex<_Up>* y) {
  using ValueType = SQUEEZE_COMMON_TYPE(_Tp, _Up);
  ValueType sum[2] = {0, 0};
  #pragma omp parallel
  {
    ValueType sum_div[2] = {0, 0};
    Complex<ValueType> temp;

    #pragma omp for simd aligned(x, y) nowait
    for (Idx i = 0; i < size; i++) {
      temp = std::conj(*(x + i)) * *(y + i);
      sum_div[0] += temp.real();
      sum_div[1] += temp.imag();
    }
    #pragma omp critical
    {
      sum[0] += sum_div[0];
      sum[1] += sum_div[1];
    }
  }
  return Complex<ValueType>(sum[0], sum[1]);
}

// get square of a complex vector
template<class _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Tp parallel_dot(Idx size, const Complex<_Tp>* x) {
  _Tp sum = 0;
  #pragma omp parallel for simd aligned(x) reduction(+: sum)
  for (Idx i = 0; i < size; i++) {
      sum += std::real(std::conj(*(x + i)) * *(x + i));
  }
  return sum;
}

// only for complex types, calculate a dot b
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
SQUEEZE_COMMON_TYPE(Complex<_Tp>, Complex<_Up>)
parallel_dotu(Idx size, const Complex<_Tp>* x, const Complex<_Up>* y) {
  using ValueType = SQUEEZE_COMMON_TYPE(_Tp, _Up);
  ValueType sum[2] = {0, 0};
  #pragma omp parallel
  {
    ValueType sum_div[2] = {0, 0};
    Complex<ValueType> temp;

    #pragma omp for simd aligned(x, y) nowait
    for (Idx i = 0; i < size; i++) {
      temp = *(x + i) * *(y + i);
      sum_div[0] += temp.real();
      sum_div[1] += temp.imag();
    }
    #pragma omp critical
    {
      sum[0] += sum_div[0];
      sum[1] += sum_div[1];
    }
  }
  return Complex<ValueType>(sum[0], sum[1]);
}


/* ----------------------------- parallel_axpy ------------------------------ */
template<class _Tp, class _Up, class _Vp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_axpy(Idx size, const _Tp& a, const _Up* x, _Vp* y) {
  #pragma omp parallel for simd aligned(x, y)
  for (Idx i = 0; i < size; i++) {
    *(y + i) += a * *(x + i);
  }
}


/* ----------------------------- parallel_scal ------------------------------ */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_scal(Idx size, const _Tp& a, _Up* x) {
  #pragma omp parallel for simd aligned(x)
  for (Idx i = 0; i < size; i++) {
    *(x + i) *= a;
  }
}


/* ----------------------------- parallel_nrm2 ------------------------------ */
// for non-complex types
template<class _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Tp parallel_nrm2(Idx size, const _Tp* x) {
  return std::sqrt(parallel_dot(size, x, x));
}

// for complex types
template<class _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Tp parallel_nrm2(Idx size, const Complex<_Tp>* x) {
  return std::sqrt(parallel_dot(size, x));
}


/* ------------------------------ parallel_add ------------------------------ */
template<class _Tp, class _Up, class _Vp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_add(Idx size, const _Tp* x, const _Up* y, _Vp* out) {
  #pragma omp parallel for simd aligned(x, y, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = *(x + i) + *(y + i);
  }
}


/* ------------------------------ parallel_sub ------------------------------ */
template<class _Tp, class _Up, class _Vp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_sub(Idx size, const _Tp* x, const _Up* y, _Vp* out) {
  #pragma omp parallel for simd aligned(x, y, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = *(x + i) - *(y + i);
  }
}


/* ------------------------------ parallel_mul ------------------------------ */
template<class _Tp, class _Up, class _Vp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_mul(Idx size, const _Tp* x, const _Up* y, _Vp* out) {
  #pragma omp parallel for simd aligned(x, y, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = *(x + i) * *(y + i);
  }
}


/* ------------------------------ parallel_div ------------------------------ */
template<class _Tp, class _Up, class _Vp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_div(Idx size, const _Tp* x, const _Up* y, _Vp* out) {
  #pragma omp parallel for simd aligned(x, y, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = *(x + i) / *(y + i);
  }
}


/* ------------------------------ parallel_pow ------------------------------ */
template<class _Tp, class _Up, class _Vp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_pow(Idx size, const _Tp* x, const _Up* y, _Vp* out) {
  #pragma omp parallel for simd aligned(x, y, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::pow(*(x + i), *(y + i));
  }
}


/* ---------------------------- parallel_negate ----------------------------- */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_negate(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = - *(x + i);
  }
}


/* ------------------------------ parallel_exp ------------------------------ */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_exp(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::exp(*(x + i));
  }
}


/* ----------------------------- parallel_exp2 ------------------------------ */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_exp2(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::exp2(*(x + i));
  }
}


/* ----------------------------- parallel_expm1 ----------------------------- */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_expm1(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::expm1(*(x + i));
  }
}


/* ------------------------------ parallel_ln ------------------------------- */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_ln(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::log(*(x + i));
  }
}


/* ----------------------------- parallel_log10 ----------------------------- */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_log10(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::log10(*(x + i));
  }
}


/* ----------------------------- parallel_log2 ------------------------------ */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_log2(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::log2(*(x + i));
  }
}


/* ----------------------------- parallel_log1p ----------------------------- */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_log1p(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::log1p(*(x + i));
  }
}


/* ----------------------------- parallel_sqrt ------------------------------ */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_sqrt(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::sqrt(*(x + i));
  }
}


/* ----------------------------- parallel_cbrt ------------------------------ */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_cbrt(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::cbrt(*(x + i));
  }
}


/* ------------------------------ parallel_sin ------------------------------ */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_sin(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::sin(*(x + i));
  }
}


/* ------------------------------ parallel_cos ------------------------------ */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_cos(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::cos(*(x + i));
  }
}


/* ------------------------------ parallel_tan ------------------------------ */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_tan(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::tan(*(x + i));
  }
}


/* ----------------------------- parallel_asin ------------------------------ */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_asin(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::asin(*(x + i));
  }
}


/* ----------------------------- parallel_acos ------------------------------ */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_acos(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::acos(*(x + i));
  }
}


/* ----------------------------- parallel_atan ------------------------------ */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_atan(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::atan(*(x + i));
  }
}


/* ----------------------------- parallel_sinh ------------------------------ */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_sinh(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::sinh(*(x + i));
  }
}


/* ----------------------------- parallel_cosh ------------------------------ */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_cosh(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::cosh(*(x + i));
  }
}


/* ----------------------------- parallel_tanh ------------------------------ */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_tanh(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::tanh(*(x + i));
  }
}


/* ----------------------------- parallel_asinh ----------------------------- */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_asinh(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::asinh(*(x + i));
  }
}


/* ----------------------------- parallel_acosh ----------------------------- */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_acosh(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::acosh(*(x + i));
  }
}


/* ----------------------------- parallel_atanh ----------------------------- */
template<class _Tp, class _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_atanh(Idx size, const _Tp* x, _Up* out) {
  #pragma omp parallel for simd aligned(x, out)
  for (Idx i = 0; i < size; i++) {
    *(out + i) = std::atanh(*(x + i));
  }
}


/* ----------------------- wrappers to CBLAS library ------------------------ */
#ifdef SQUEEZE_USE_BLAS
#define SQUEEZE_BLAS_USE_FLOAT
  #include "blas.tcc"
#undef SQUEEZE_BLAS_USE_FLOAT

#define SQUEEZE_BLAS_USE_DOUBLE
  #include "blas.tcc"
#undef SQUEEZE_BLAS_USE_DOUBLE
#endif


/* ---------------------- wrappers to MKL VML library ----------------------- */
#ifdef SQUEEZE_USE_MKL
#define SQUEEZE_VML_USE_FLOAT
  #include "vml.tcc"
#undef SQUEEZE_VML_USE_FLOAT

#define SQUEEZE_VML_USE_DOUBLE
  #include "vml.tcc"
#undef SQUEEZE_VML_USE_DOUBLE

#define SQUEEZE_VML_USE_COMPLEX_FLOAT
  #include "vml.tcc"
#undef SQUEEZE_VML_USE_COMPLEX_FLOAT

#define SQUEEZE_VML_USE_COMPLEX_DOUBLE
  #include "vml.tcc"
#undef SQUEEZE_VML_USE_COMPLEX_DOUBLE
#endif

} // namespace internal


// some C++ wrappers for BLAS functions
namespace blas {

/* ------------------------------- blas::copy ------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void copy(Idx size, const _Tp* src, _Up* dest) {
  if (size * std::max(sizeof(_Tp), sizeof(_Up)) < SQUEEZE_NON_PAR_COPY_BYTES) {
    std::copy(src, src + size, dest);
  }
  else {
    internal::parallel_copy(size, src, dest);
  }
}


/* ------------------------------ blas::dot(u) ------------------------------ */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
SQUEEZE_COMMON_TYPE(_Tp, _Up)
dot(Idx size, const _Tp* x, const _Up* y) {
  using ReturnType = SQUEEZE_COMMON_TYPE(_Tp, _Up);

  if (size * sizeof(ReturnType) < SQUEEZE_NON_PAR_CAL_BYTES) {
    return std::inner_product(x, x + size, y, ReturnType(0));
  }
  else {
    return internal::parallel_dot(size, x, y);
  }
}

template<class _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Tp dot(Idx size, const _Tp* x) {
  if (size * sizeof(_Tp) < SQUEEZE_NON_PAR_CAL_BYTES) {
    return std::inner_product(x, x + size, x, _Tp(0));
  }
  else {
    return internal::parallel_dot(size, x, x);
  }
}

template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
SQUEEZE_COMMON_TYPE(Complex<_Tp>, Complex<_Up>)
dot(Idx size, const Complex<_Tp>* x, const Complex<_Up>* y) {
  using ReturnType = SQUEEZE_COMMON_TYPE(Complex<_Tp>, Complex<_Up>);

  if (2 * size * sizeof(ReturnType) < SQUEEZE_NON_PAR_CAL_BYTES) {
    return std::inner_product(x, x + size, y, ReturnType(0),
                              Plus<ReturnType>::run,
                              [&](const Complex<_Tp>& a, const Complex<_Up>& b)
                              { return std::conj(a) * b; }
                             );
  }
  else {
    return internal::parallel_dot(size, x, y);
  }
}

template<class _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Tp dot(Idx size, const Complex<_Tp>* x) {
  if (2 * size * sizeof(_Tp) < SQUEEZE_NON_PAR_CAL_BYTES) {
    return std::inner_product(x, x + size, x, _Tp(0),
                              Plus<_Tp>::run,
                              [&](const Complex<_Tp>& a, const Complex<_Tp>& b)
                              { return std::real(std::conj(a) * b); }
                             );
  }
  else {
    return internal::parallel_dot(size, x);
  }
}

template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
SQUEEZE_COMMON_TYPE(Complex<_Tp>, Complex<_Up>)
dotu(Idx size, const Complex<_Tp>* x, const Complex<_Up>* y) {
  using ReturnType = SQUEEZE_COMMON_TYPE(Complex<_Tp>, Complex<_Up>);

  if (2 * size * sizeof(ReturnType) < SQUEEZE_NON_PAR_CAL_BYTES) {
    return std::inner_product(x, x + size, y, ReturnType(0));
  }
  else {
    return internal::parallel_dotu(size, x, y);
  }
}


/* ------------------------------- blas::axpy ------------------------------- */
template<class _Tp, class _Up = _Tp, class _Vp = _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void axpy(Idx size, const _Tp& a, const _Up* x, _Vp* y) {
  static_assert(std::is_convertible<_Tp, _Vp>::value &&
                std::is_convertible<_Up, _Vp>::value,
                "Type mismatch in blas::axpy!!");

  if (size * sizeof(_Vp) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(y + i) += a * *(x + i);
    }
  }
  else {
    internal::parallel_axpy(size, a, x, y);
  }
}


/* ------------------------------- blas::scal ------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void scal(Idx size, const _Tp& a, _Up* x) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in blas::axpy!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(x + i) *= a;
    }
  }
  else
    internal::parallel_scal(size, a, x);
}


/* ------------------------------- blas::nrm2 ------------------------------- */
template<class _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Tp nrm2(Idx size, const _Tp* x) {
  if (size * sizeof(_Tp) < SQUEEZE_NON_PAR_CAL_BYTES) {
    return std::sqrt(std::inner_product(x, x + size, x, _Tp(0)));
  }
  else {
    return internal::parallel_nrm2(size, x);
  }
}

template<class _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Tp nrm2(Idx size, const Complex<_Tp>* x) {
  if (2 * size * sizeof(_Tp) < SQUEEZE_NON_PAR_CAL_BYTES) {
    return std::sqrt(std::inner_product(
                     x, x + size, x, _Tp(0), Plus<_Tp>::run,
                     [&](const Complex<_Tp>& a, const Complex<_Tp>& b)
                     { return std::real(std::conj(a) * b); })
                    );
  }
  else {
    return internal::parallel_nrm2(size, x);
  }
}

} // namespace blas


// some C++ wrappers for VML functions
namespace vml {

/* -------------------------------- vml::add -------------------------------- */
template<class _Tp, class _Up = _Tp, class _Vp = _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void add(Idx size, const _Tp* x, const _Up* y, _Vp* out) {
  static_assert(std::is_convertible<_Tp, _Vp>::value &&
                std::is_convertible<_Up, _Vp>::value,
                "Type mismatch in vml::add!!");

  if (size * sizeof(_Vp) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = *(x + i) + *(y + i);
    }
  }
  else {
    internal::parallel_add(size, x, y, out);
  }
}


/* -------------------------------- vml::sub -------------------------------- */
template<class _Tp, class _Up = _Tp, class _Vp = _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void sub(Idx size, const _Tp* x, const _Up* y, _Vp* out) {
  static_assert(std::is_convertible<_Tp, _Vp>::value &&
                std::is_convertible<_Up, _Vp>::value,
                "Type mismatch in vml::sub!!");

  if (size * sizeof(_Vp) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = *(x + i) - *(y + i);
    }
  }
  else {
    internal::parallel_sub(size, x, y, out);
  }
}


/* -------------------------------- vml::mul -------------------------------- */
template<class _Tp, class _Up = _Tp, class _Vp = _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void mul(Idx size, const _Tp* x, const _Up* y, _Vp* out) {
  static_assert(std::is_convertible<_Tp, _Vp>::value &&
                std::is_convertible<_Up, _Vp>::value,
                "Type mismatch in vml::mul!!");

  if (size * sizeof(_Vp) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = *(x + i) * *(y + i);
    }
  }
  else {
    internal::parallel_mul(size, x, y, out);
  }
}


/* -------------------------------- vml::div -------------------------------- */
template<class _Tp, class _Up = _Tp, class _Vp = _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void div(Idx size, const _Tp* x, const _Up* y, _Vp* out) {
  static_assert(std::is_convertible<_Tp, _Vp>::value &&
                std::is_convertible<_Up, _Vp>::value,
                "Type mismatch in vml::div!!");

  if (size * sizeof(_Vp) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = *(x + i) / *(y + i);
    }
  }
  else {
    internal::parallel_div(size, x, y, out);
  }
}


/* -------------------------------- vml::pow -------------------------------- */
template<class _Tp, class _Up = _Tp, class _Vp = _Up>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void pow(Idx size, const _Tp* x, const _Up* y, _Vp* out) {
  static_assert(std::is_convertible<_Tp, _Vp>::value &&
                std::is_convertible<_Up, _Vp>::value,
                "Type mismatch in vml::pow!!");

  if (size * sizeof(_Vp) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::pow(*(x + i), *(y + i));
    }
  }
  else {
    internal::parallel_pow(size, x, y, out);
  }
}


/* ------------------------------ vml::negate ------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void negate(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::negate!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = - *(x + i);
    }
  }
  else {
    internal::parallel_negate(size, x, out);
  }
}


/* -------------------------------- vml::exp -------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void exp(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::exp!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::exp(*(x + i));
    }
  }
  else {
    internal::parallel_exp(size, x, out);
  }
}


/* ------------------------------- vml::exp2 -------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void exp2(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::exp2!!");
  static_assert(!internal::IsComplexType<_Up>::value,
                "Vector with complex type has no exp2 function!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::exp2(*(x + i));
    }
  }
  else {
    internal::parallel_exp2(size, x, out);
  }
}


/* ------------------------------- vml::expm1 ------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void expm1(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::expm1!!");
  static_assert(!internal::IsComplexType<_Up>::value,
                "Vector with complex type has no expm1 function!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::expm1(*(x + i));
    }
  }
  else {
    internal::parallel_expm1(size, x, out);
  }
}


/* -------------------------------- vml::ln --------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void ln(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::ln!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::log(*(x + i));
    }
  }
  else {
    internal::parallel_ln(size, x, out);
  }
}


/* ------------------------------- vml::log10 ------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void log10(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::log10!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::log10(*(x + i));
    }
  }
  else {
    internal::parallel_log10(size, x, out);
  }
}


/* ------------------------------- vml::log2 -------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void log2(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::log2!!");
  static_assert(!internal::IsComplexType<_Up>::value,
                "Vector with complex type has no log2 function!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::log2(*(x + i));
    }
  }
  else {
    internal::parallel_log2(size, x, out);
  }
}


/* ------------------------------- vml::log1p ------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void log1p(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::log1p!!");
  static_assert(!internal::IsComplexType<_Up>::value,
                "Vector with complex type has no log1p function!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::log1p(*(x + i));
    }
  }
  else {
    internal::parallel_log1p(size, x, out);
  }
}


/* ------------------------------- vml::sqrt -------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void sqrt(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::sqrt!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::sqrt(*(x + i));
    }
  }
  else {
    internal::parallel_sqrt(size, x, out);
  }
}


/* ------------------------------- vml::cbrt -------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void cbrt(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::cbrt!!");
  static_assert(!internal::IsComplexType<_Up>::value,
                "Vector with complex type has no cbrt function!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::cbrt(*(x + i));
    }
  }
  else {
    internal::parallel_cbrt(size, x, out);
  }
}


/* -------------------------------- vml::sin -------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void sin(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::sin!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::sin(*(x + i));
    }
  }
  else {
    internal::parallel_sin(size, x, out);
  }
}


/* -------------------------------- vml::cos -------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void cos(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::cos!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::cos(*(x + i));
    }
  }
  else {
    internal::parallel_cos(size, x, out);
  }
}


/* -------------------------------- vml::tan -------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void tan(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::tan!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::tan(*(x + i));
    }
  }
  else {
    internal::parallel_tan(size, x, out);
  }
}


/* ------------------------------- vml::asin -------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void asin(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::asin!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::asin(*(x + i));
    }
  }
  else {
    internal::parallel_asin(size, x, out);
  }
}


/* ------------------------------- vml::acos -------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void acos(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::acos!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::acos(*(x + i));
    }
  }
  else {
    internal::parallel_acos(size, x, out);
  }
}


/* ------------------------------- vml::atan -------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void atan(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::atan!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::atan(*(x + i));
    }
  }
  else {
    internal::parallel_atan(size, x, out);
  }
}


/* ------------------------------- vml::sinh -------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void sinh(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::sinh!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::sinh(*(x + i));
    }
  }
  else {
    internal::parallel_sinh(size, x, out);
  }
}


/* ------------------------------- vml::cosh -------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void cosh(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::cosh!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::cosh(*(x + i));
    }
  }
  else {
    internal::parallel_cosh(size, x, out);
  }
}


/* ------------------------------- vml::tanh -------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void tanh(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::tanh!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::tanh(*(x + i));
    }
  }
  else {
    internal::parallel_tanh(size, x, out);
  }
}


/* ------------------------------- vml::asinh ------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void asinh(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::asinh!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::asinh(*(x + i));
    }
  }
  else {
    internal::parallel_asinh(size, x, out);
  }
}


/* ------------------------------- vml::acosh ------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void acosh(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::acosh!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::acosh(*(x + i));
    }
  }
  else {
    internal::parallel_acosh(size, x, out);
  }
}


/* ------------------------------- vml::atanh ------------------------------- */
template<class _Tp, class _Up = _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void atanh(Idx size, const _Tp* x, _Up* out) {
  static_assert(std::is_convertible<_Tp, _Up>::value,
                "Type mismatch in vml::atanh!!");

  if (size * sizeof(_Up) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < size; i++) {
      *(out + i) = std::atanh(*(x + i));
    }
  }
  else {
    internal::parallel_atanh(size, x, out);
  }
}

} // namespace vml


#ifdef SQUEEZE_USE_FFTW
namespace fftw {

static constexpr unsigned flag = FFTW_ESTIMATE|FFTW_PRESERVE_INPUT;

/* ---------------------------- fftw::fft1d_r2r ----------------------------- */
template<class _Vec>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec fft1d_r2r(_Vec& in, Idx n_half_p_1)
{
  _Vec out(n_half_p_1);
  int n = static_cast<int>(n_half_p_1);
  double* in_ptr = in.data();
  double* out_ptr = out.data();

  fftw_plan p = fftw_plan_r2r_1d(n, in_ptr, out_ptr, FFTW_REDFT00, flag);
  fftw_execute(p);
  fftw_destroy_plan(p);

  return out;
}


/* ---------------------------- fftw::fft1d_c2c ----------------------------- */
template<class _Vec>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec fft1d_c2c(_Vec& in, int direction)
{
  _Vec out(in.size());
  int n = in.size();
  fftw_complex* in_ptr = reinterpret_cast<fftw_complex*>(in.data());
  fftw_complex* out_ptr = reinterpret_cast<fftw_complex*>(out.data());

  fftw_plan p = fftw_plan_dft_1d(n, in_ptr, out_ptr, direction, flag);
  fftw_execute(p);
  fftw_destroy_plan(p);

  return out;
}

} // namespace fftw
#endif

} // namespace Squeeze
#endif // include guard
