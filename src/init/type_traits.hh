#ifndef SQUEEZE_TYPE_TRAITS_HH
#define SQUEEZE_TYPE_TRAITS_HH

#include <type_traits>
#include "macros.hh"


namespace Squeeze { namespace internal {

// check if _Tp is Complex type, specialization is in complex.hh
template<class _Tp>
struct IsComplexType : public std::false_type { };


// arithmetic types in Squeeze means general scalar types and Complex types
// specialization for Complex types is in complex.hh
template<class _Tp>
struct SupportedType : public std::is_arithmetic<_Tp> { };


// check if _Obj is Vector type, specialization is in vector.hh
template<class _Obj>
struct IsVector : public std::false_type { };


// check if _Obj is Matrix type, specialization is in matrix.hh
template<class _Obj>
struct IsMatrix : public std::false_type { };


// check if _Obj is SparseMatrix type, specialization is in sparsematrix.hh
template<class _Obj>
struct IsSpMat : public std::false_type { };


#define SQUEEZE_ENABLE_IF(expr, T) typename std::enable_if<expr, T>::type

// for SFINAE purpose: Idx type if it's scalar type, otherwise null
template<class _Sca>
using IdxIfSca = SQUEEZE_ENABLE_IF(std::is_arithmetic<_Sca>::value, Idx);

// for SFINAE purpose: void if _Tp is arithmetic type, otherwise null
template<class _Tp>
using VoidIfAri = SQUEEZE_ENABLE_IF(
  SupportedType<typename std::remove_reference<_Tp>::type>::value, void);

// for SFINAE purpose: Idx if _Tp is arithmetic type, otherwise null
template<class _Tp>
using IdxIfAri = SQUEEZE_ENABLE_IF(SupportedType<_Tp>::value, Idx);

// for SFINAE purpose: void if _Obj is not arithmetic type, otherwise null
template<class _Obj>
using VoidIfNotAri = SQUEEZE_ENABLE_IF(
    !SupportedType<typename std::remove_reference<_Obj>::type>::value, void);

// for SFINAE purpose: Idx if _Obj is not arithmetic type, otherwise null
template<class _Obj>
using IdxIfNotAri = SQUEEZE_ENABLE_IF(!SupportedType<_Obj>::value, Idx);

// for SFINAE purpose: void if _Vec is Vector type, otherwise null
template<class _Vec>
using VoidIfVec = SQUEEZE_ENABLE_IF(IsVector<_Vec>::value, void);

// for SFINAE purpose: Idx if _Vec is Vector type, otherwise null
template<class _Vec>
using IdxIfVec = SQUEEZE_ENABLE_IF(IsVector<_Vec>::value, Idx);

// for SFINAE purpose: Idx if _Mat is Matrix type, otherwise null
template<class _Mat>
using IdxIfMatrix = SQUEEZE_ENABLE_IF(IsMatrix<_Mat>::value, Idx);

// for SFINAE purpose: Idx if _SpMat is SparseMatrix type, otherwise null
template<class _SpMat>
using IdxIfSpMat = SQUEEZE_ENABLE_IF(IsSpMat<_SpMat>::value, Idx);


// Arithmetic type that an object contains, specializations are in their files
template<class _Obj, typename _Sfinae = void>
struct ValueType;

// real arithmetic types
template<class _Tp>
struct ValueType<_Tp, VoidIfAri<_Tp>>
{
  using type = _Tp;
};

// object types
template<class _Obj>
struct ValueType<_Obj, VoidIfNotAri<_Obj>>
{
  using type = typename _Obj::ValueType;
};

}} // namespace Squeeze::internal

#endif // include guard
