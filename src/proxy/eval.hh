#ifndef SQUEEZE_EVAL_HH
#define SQUEEZE_EVAL_HH

#include "../math/functional.hh"
#include "../math/math.hh"
#include "proxy.hh"

namespace Squeeze {

/* ----------------------- final evaluation for proxy ----------------------- */
// general case
template<class _Proxy, class _Vec, internal::IdxIfProxy<_Proxy> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const _Proxy& from, _Vec& to) {
  if (from.size() * sizeof(_Proxy::ValueType) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < from.size(); i++) {
      to[i] = from[i];
    }
  }
  else {
    #pragma omp parallel for simd
    for (Idx i = 0; i < from.size(); i++) {
      to[i] = from[i];
    }
  }
  return to;
}

// a single scalar
template<class _Ari, class _Vec, internal::IdxIfAri<_Ari> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const _Ari& from, _Vec& to) {
  if (to.size() * sizeof(_Vec::ValueType) < SQUEEZE_NON_PAR_CAL_BYTES) {
    for (Idx i = 0; i < to.size(); i++) {
      to[i] = from;
    }
  }
  else {
    #pragma omp parallel for simd
    for (Idx i = 0; i < to.size(); i++) {
      to[i] = from;
    }
  }
  return to;
}

// evaluate only vec1 + vec2, using vml::add
template<class _Vec1, class _Vec2, class _Vec,
         internal::IdxIfVec<_Vec1> = 0, internal::IdxIfVec<_Vec2> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_BINPROXY(Plus, _Vec1, _Vec2)& from, _Vec& to)
{
  vml::add(from.size(), from.vec1.data(), from.vec2.data(), to.data());
  return to;
}

// evaluate only vec1 - vec2, using vml::sub
template<class _Vec1, class _Vec2, class _Vec,
         internal::IdxIfVec<_Vec1> = 0, internal::IdxIfVec<_Vec2> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_BINPROXY(Minus, _Vec1, _Vec2)& from, _Vec& to)
{
  vml::sub(from.size(), from.vec1.data(), from.vec2.data(), to.data());
  return to;
}

// evaluate only vec1 * vec2, using vml::mul
template<class _Vec1, class _Vec2, class _Vec,
         internal::IdxIfVec<_Vec1> = 0, internal::IdxIfVec<_Vec2> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_BINPROXY(Multiplies, _Vec1, _Vec2)& from, _Vec& to)
{
  vml::mul(from.size(), from.vec1.data(), from.vec2.data(), to.data());
  return to;
}

// evaluate only vec1 / vec2, using vml::div
template<class _Vec1, class _Vec2, class _Vec,
         internal::IdxIfVec<_Vec1> = 0, internal::IdxIfVec<_Vec2> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_BINPROXY(Divides, _Vec1, _Vec2)& from, _Vec& to)
{
  vml::div(from.size(), from.vec1.data(), from.vec2.data(), to.data());
  return to;
}

// evaluate only pow(vec1, vec2), using vml::pow
template<class _Vec1, class _Vec2, class _Vec,
         internal::IdxIfVec<_Vec1> = 0, internal::IdxIfVec<_Vec2> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_BINPROXY(Pow, _Vec1, _Vec2)& from, _Vec& to)
{
  vml::pow(from.size(), from.vec1.data(), from.vec2.data(), to.data());
  return to;
}

// evaluate only -vec, using vml::negate
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(Negate, _Vec0)& from,
           _Vec& to)
{
  vml::negate(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::exp(vec), using vml::exp
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(Exp, _Vec0)& from, _Vec& to)
{
  vml::exp(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::exp2(vec), using vml::exp2
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(Exp2, _Vec0)& from, _Vec& to)
{
  vml::exp2(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::expm1(vec), using vml::expm1
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(Expm1, _Vec0)& from, _Vec& to)
{
  vml::expm1(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::ln(vec), using vml::ln
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(Ln, _Vec0)& from, _Vec& to)
{
  vml::ln(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::log10(vec), using vml::log10
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(Log10, _Vec0)& from, _Vec& to)
{
  vml::log10(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::log2(vec), using vml::log2
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(Log2, _Vec0)& from, _Vec& to)
{
  vml::log2(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::log1p(vec), using vml::log1p
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(Log1p, _Vec0)& from, _Vec& to)
{
  vml::log1p(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::sqrt(vec), using vml::sqrt
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(Sqrt, _Vec0)& from, _Vec& to)
{
  vml::sqrt(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::cbrt(vec), using vml::cbrt
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(Cbrt, _Vec0)& from, _Vec& to)
{
  vml::cbrt(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::sin(vec), using vml::sin
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(Sin, _Vec0)& from, _Vec& to)
{
  vml::sin(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::cos(vec), using vml::cos
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(Cos, _Vec0)& from, _Vec& to)
{
  vml::cos(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::tan(vec), using vml::tan
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(Tan, _Vec0)& from, _Vec& to)
{
  vml::tan(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::asin(vec), using vml::asin
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(ASin, _Vec0)& from, _Vec& to)
{
  vml::asin(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::acos(vec), using vml::acos
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(ACos, _Vec0)& from, _Vec& to)
{
  vml::acos(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::atan(vec), using vml::atan
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(ATan, _Vec0)& from, _Vec& to)
{
  vml::atan(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::sinh(vec), using vml::sinh
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(Sinh, _Vec0)& from, _Vec& to)
{
  vml::sinh(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::cosh(vec), using vml::cosh
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(Cosh, _Vec0)& from, _Vec& to)
{
  vml::cosh(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::tanh(vec), using vml::tanh
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(Tanh, _Vec0)& from, _Vec& to)
{
  vml::tanh(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::asinh(vec), using vml::asinh
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(ASinh, _Vec0)& from, _Vec& to)
{
  vml::asinh(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::acosh(vec), using vml::acosh
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(ACosh, _Vec0)& from, _Vec& to)
{
  vml::acosh(from.size(), from.vec.data(), to.data());
  return to;
}

// evaluate only std::atanh(vec), using vml::atanh
template<class _Vec0, class _Vec, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_UNAPROXY(ATanh, _Vec0)& from, _Vec& to)
{
  vml::atanh(from.size(), from.vec.data(), to.data());
  return to;
}


// evaluate only spmat_csr * vec, using spblas::csr_mv
template<class _SpMat, class _Vec0, class _Vec,
         internal::IdxIfSpMat<_SpMat> = 0, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const SQUEEZE_BINPROXY(Multiplies, _SpMat, _Vec0)& from, _Vec& to)
{
  to = spblas::csr_mv(from.vec1, from.vec2);
  return to;
}


// evaluate only spmat_csr * vec0 + vec, using spblas::csr_mvpy
template<class _SpMat, class _Vec0, class _Vec,
         internal::IdxIfSpMat<_SpMat> = 0, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const BinProxy<Plus<SQUEEZE_COMMON_TYPE(typename _SpMat::ValueType,
                                                   typename _Vec0::ValueType),
                               typename _Vec::ValueType>,
                          BinProxy<Multiplies<typename _SpMat::ValueType,
                                              typename _Vec0::ValueType>,
                                   _SpMat, _Vec0>,
                          _Vec>& from,
           _Vec& to)
{
  to = spblas::csr_mvpy(from.vec1.vec1, from.vec1.vec2,
                        const_cast<_Vec&>(from.vec2));
  return to;
}


// evaluate only ari * spmat_csr * vec, using spblas::csr_amv
template<class _Ari, class _SpMat, class _Vec0, class _Vec,
         internal::IdxIfAri<_Ari> = 0,
         internal::IdxIfSpMat<_SpMat> = 0, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const BinProxy<Multiplies<
                            SQUEEZE_COMMON_TYPE(_Ari,
                                                typename _SpMat::ValueType),
                            typename _Vec0::ValueType>,
                          BinProxy<Multiplies<_Ari, typename _SpMat::ValueType>,
                                   _Ari, _SpMat>,
                          _Vec0>& from,
           _Vec& to)
{
  to = spblas::csr_amv(from.vec1.ari, from.vec1.vec, from.vec2);
  return to;
}


// evaluate only ari * (spmat_csr * vec), using spblas::csr_amv
template<class _Ari, class _SpMat, class _Vec0, class _Vec,
         internal::IdxIfAri<_Ari> = 0,
         internal::IdxIfSpMat<_SpMat> = 0, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const BinProxy<Multiplies<_Ari,
                            SQUEEZE_COMMON_TYPE(typename _SpMat::ValueType,
                                                typename _Vec0::ValueType)>,
                          _Ari,
                          BinProxy<Multiplies<typename _SpMat::ValueType,
                                              typename _Vec0::ValueType>,
                                   _SpMat, _Vec0>>& from,
           _Vec& to)
{
  to = spblas::csr_amv(from.ari, from.vec.vec1, from.vec.vec2);
  return to;
}


// evaluate only ari * spmat_csr * vec0 + vec, using spblas::csr_amvpy
template<class _Ari, class _SpMat, class _Vec0, class _Vec,
         internal::IdxIfAri<_Ari> = 0,
         internal::IdxIfSpMat<_SpMat> = 0, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const BinProxy<Plus<SQUEEZE_COMMON_TYPE(
                              SQUEEZE_COMMON_TYPE(_Ari,
                                                  typename _SpMat::ValueType),
                              typename _Vec0::ValueType),
                            typename _Vec::ValueType>,
                          BinProxy<Multiplies<
                              SQUEEZE_COMMON_TYPE(_Ari,
                                                  typename _SpMat::ValueType),
                              typename _Vec0::ValueType>,
                            BinProxy<Multiplies<_Ari,
                                                typename _SpMat::ValueType>,
                                     _Ari, _SpMat>,
                            _Vec0>,
                          _Vec>& from,
           _Vec& to)
{
  to = spblas::csr_amvpy(from.vec1.vec1.ari, from.vec1.vec1.vec, from.vec1.vec2,
                         const_cast<_Vec&>(from.vec2));
  return to;
}


// evaluate only ari * (spmat_csr * vec0) + vec, using spblas::csr_amvpy
template<class _Ari, class _SpMat, class _Vec0, class _Vec,
         internal::IdxIfAri<_Ari> = 0,
         internal::IdxIfSpMat<_SpMat> = 0, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const BinProxy<Plus<SQUEEZE_COMMON_TYPE(_Ari,
                                 SQUEEZE_COMMON_TYPE(typename _SpMat::ValueType,
                                   typename _Vec0::ValueType)),
                            typename _Vec::ValueType>,
                          BinProxy<Multiplies<_Ari,
                              SQUEEZE_COMMON_TYPE(typename _SpMat::ValueType,
                                                 typename _Vec0::ValueType)>,
                            _Ari,
                            BinProxy<Multiplies<typename _SpMat::ValueType,
                                                typename _Vec0::ValueType>,
                                     _SpMat, _Vec0>>,
                          _Vec>& from,
           _Vec& to)
{
  to = spblas::csr_amvpy(from.vec1.ari, from.vec1.vec.vec1, from.vec1.vec.vec2,
                         const_cast<_Vec&>(from.vec2));
  return to;
}


// evaluate only ari1 * spmat_csr * vec0 + ari2 * vec, using spblas::csr_amvpby
template<class _Ari1, class _SpMat, class _Vec0, class _Ari2, class _Vec,
         internal::IdxIfAri<_Ari1> = 0, internal::IdxIfAri<_Ari2> = 0,
         internal::IdxIfSpMat<_SpMat> = 0, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const BinProxy<Plus<SQUEEZE_COMMON_TYPE(
                              SQUEEZE_COMMON_TYPE(_Ari1,
                                                  typename _SpMat::ValueType),
                              typename _Vec0::ValueType),
                            SQUEEZE_COMMON_TYPE(_Ari2,
                                                typename _Vec::ValueType)>,
                          BinProxy<Multiplies<
                              SQUEEZE_COMMON_TYPE(_Ari1,
                                                  typename _SpMat::ValueType),
                              typename _Vec0::ValueType>,
                            BinProxy<Multiplies<_Ari1,
                                                typename _SpMat::ValueType>,
                                     _Ari1, _SpMat>,
                            _Vec0>,
                          BinProxy<Multiplies<_Ari2, typename _Vec::ValueType>,
                            _Ari2, _Vec>>& from,
           _Vec& to)
{
  to = spblas::csr_amvpby(from.vec1.vec1.ari, from.vec1.vec1.vec,
                          from.vec1.vec2, from.vec2.ari,
                          const_cast<_Vec&>(from.vec2.vec));
  return to;
}


// evaluate only ari1*(spmat_csr * vec0) + ari2 * vec, using spblas::csr_amvpby
template<class _Ari1, class _SpMat, class _Vec0, class _Ari2, class _Vec,
         internal::IdxIfAri<_Ari1> = 0, internal::IdxIfAri<_Ari2> = 0,
         internal::IdxIfSpMat<_SpMat> = 0, internal::IdxIfVec<_Vec0> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& eval(const BinProxy<Plus<SQUEEZE_COMMON_TYPE(_Ari1,
                                SQUEEZE_COMMON_TYPE(typename _SpMat::ValueType,
                                                    typename _Vec0::ValueType)),
                            SQUEEZE_COMMON_TYPE(_Ari2,
                                                typename _Vec::ValueType)>,
                          BinProxy<Multiplies<_Ari1,
                              SQUEEZE_COMMON_TYPE(typename _SpMat::ValueType,
                                                  typename _Vec0::ValueType)>,
                            _Ari1,
                            BinProxy<Multiplies<typename _SpMat::ValueType,
                                                typename _Vec0::ValueType>,
                                     _SpMat, _Vec0>>,
                          BinProxy<Multiplies<_Ari2, typename _Vec::ValueType>,
                            _Ari2, _Vec>>& from,
           _Vec& to)
{
  to = spblas::csr_amvpby(from.vec1.ari, from.vec1.vec.vec1,
                          from.vec1.vec.vec2, from.vec2.ari,
                          const_cast<_Vec&>(from.vec2.vec));
  return to;
}

} // namespace Squeeze
#endif // include guard
