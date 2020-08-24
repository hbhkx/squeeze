/* // for debug only
#include "math.hh"
#include <mkl_cblas.h>
// #define SQUEEZE_BLAS_USE_FLOAT
#define SQUEEZE_BLAS_USE_DOUBLE

namespace Squeeze { namespace internal {
*/

#ifdef SQUEEZE_BLAS_USE_DOUBLE
  #define TYPE double
  #define R_FUNC(func)  cblas_ ## d  ## func
  #define C_FUNC(func)  cblas_ ## z  ## func
  #define CR_FUNC(func) cblas_ ## zd ## func
  #define RC_FUNC(func) cblas_ ## dz ## func
#elif defined SQUEEZE_BLAS_USE_FLOAT
  #define TYPE float
  #define R_FUNC(func)  cblas_ ## s  ## func
  #define C_FUNC(func)  cblas_ ## c  ## func
  #define CR_FUNC(func) cblas_ ## cs ## func
  #define RC_FUNC(func) cblas_ ## sc ## func
#endif


template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
TYPE parallel_dot(Idx size, const TYPE* x, const TYPE* y) {
  return R_FUNC(dot)(size, x, 1, y, 1);
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
Complex<TYPE> parallel_dot(Idx size,
                           const Complex<TYPE>* x,
                           const Complex<TYPE>* y)
{
  Complex<TYPE> result;
  C_FUNC(dotc_sub)(size, x, 1, y, 1, &result);
  return result;
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
Complex<TYPE> parallel_dotu(Idx size,
                            const Complex<TYPE>* x,
                            const Complex<TYPE>* y)
{
  Complex<TYPE> result;
  C_FUNC(dotu_sub)(size, x, 1, y, 1, &result);
  return result;
}

template<class _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_axpy(Idx size, const _Tp& a, const TYPE* x, TYPE* y) {
  TYPE b = a;
  R_FUNC(axpy)(size, b, x, 1, y, 1);
}

template<class _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_axpy(Idx size,
                   const _Tp& a,
                   const Complex<TYPE>* x,
                   Complex<TYPE>* y)
{
  Complex<TYPE> b = a;
  C_FUNC(axpy)(size, &b, x, 1, y, 1);
}

template<class _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_scal(Idx size, const _Tp& a, TYPE* x) {
  TYPE b = a;
  R_FUNC(scal)(size, b, x, 1);
}

template<class _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_scal(Idx size, const _Tp& a, Complex<TYPE>* x) {
  TYPE b = a;
  CR_FUNC(scal)(size, b, x, 1);
}

template<class _Tp>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
void parallel_scal(Idx size, const Complex<_Tp>& a, Complex<TYPE>* x) {
  Complex<TYPE> b = a;
  C_FUNC(scal)(size, &b, x, 1);
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
TYPE parallel_nrm2(Idx size, const TYPE* x) {
  return R_FUNC(nrm2)(size, x, 1);
}

template<>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
TYPE parallel_nrm2(Idx size, const Complex<TYPE>* x) {
  return RC_FUNC(nrm2)(size, x, 1);
}

#undef TYPE
#undef R_FUNC
#undef C_FUNC
#undef CR_FUNC
#undef RC_FUNC


/* // for debug only
}}
*/
