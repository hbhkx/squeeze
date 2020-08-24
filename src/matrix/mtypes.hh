#ifndef SQUEEZE_MTYPES_HH
#define SQUEEZE_MTYPES_HH

#include "../init/type_traits.hh"

namespace Squeeze {

enum Layout : bool { ColMajor = 0, RowMajor = 1 };

// fill mode for triangular / symmetric / hermitian matrices
enum Fill : char { Lower = 0, Upper = 1, Full = 2 };
#ifdef SQUEEZE_USE_MKL
namespace internal {

template<Fill uplo = Full>
struct MKL_FILL_MODE
{
  static constexpr sparse_fill_mode_t value = SPARSE_FILL_MODE_FULL;
};
template<>
struct MKL_FILL_MODE<Upper>
{
  static constexpr sparse_fill_mode_t value = SPARSE_FILL_MODE_UPPER;
};
template<>
struct MKL_FILL_MODE<Lower>
{
  static constexpr sparse_fill_mode_t value = SPARSE_FILL_MODE_LOWER;
};
template<>
struct MKL_FILL_MODE<Full>
{
  static constexpr sparse_fill_mode_t value = SPARSE_FILL_MODE_FULL;
};

} // namespace internal
#endif
#define DEFAULT_UPLO SQUEEZE_DEFAULT_MATRIX_STORAGE_ORDER ? Upper : Lower

// unit or non-unit diagonal
enum Diag : bool { NonUnit = 0, Unit = 1 };
#ifdef SQUEEZE_USE_MKL
  #define MKL_DIAG_MODE(diag) (diag) ? SPARSE_DIAG_UNIT : SPARSE_DIAG_NON_UNIT
#endif

/* ----------------------------- general matrix ----------------------------- */
struct General
{
#ifdef SQUEEZE_USE_MKL
  static constexpr matrix_descr m_descr_mkl{SPARSE_MATRIX_TYPE_GENERAL,
                                            SPARSE_FILL_MODE_FULL,
                                            SPARSE_DIAG_NON_UNIT};
#endif
};

/* ------------------------------ half storage ------------------------------ */
// triangular matrix with only upper or lower part and can be unitriangle
template<Fill _uplo = DEFAULT_UPLO, Diag _diag = NonUnit>
struct Triangular
{
#ifdef SQUEEZE_USE_MKL
  static constexpr matrix_descr m_descr_mkl{SPARSE_MATRIX_TYPE_TRIANGULAR,
                                  internal::MKL_FILL_MODE<_uplo>::value,
                                            MKL_DIAG_MODE(_diag)};
#endif
};

// real symmetric matrix with only upper or lower part
template<Fill _uplo = DEFAULT_UPLO, Diag _diag = NonUnit>
struct Symmetric
{
#ifdef SQUEEZE_USE_MKL
  static constexpr matrix_descr m_descr_mkl{SPARSE_MATRIX_TYPE_SYMMETRIC,
                                  internal::MKL_FILL_MODE<_uplo>::value,
                                            MKL_DIAG_MODE(_diag)};
#endif
};

// complex hermitian matrix with only upper or lower part
template<Fill _uplo = DEFAULT_UPLO, Diag _diag = NonUnit>
struct Hermitian
{
#ifdef SQUEEZE_USE_MKL
  static constexpr matrix_descr m_descr_mkl{SPARSE_MATRIX_TYPE_HERMITIAN,
                                  internal::MKL_FILL_MODE<_uplo>::value,
                                            MKL_DIAG_MODE(_diag)};
#endif
  template<class _Tp>
  SQUEEZE_DEVICE_FUNC static constexpr void check_matrix() {
    static_assert(internal::IsComplexType<_Tp>::value,
                  "Hermitian matrix is only for complex types");
  }
};

/* --------------------- half part with packed storage ---------------------- */
// triangular packed matrix
template<Fill _uplo = DEFAULT_UPLO, Diag _diag = NonUnit>
struct TriangularPacked;
// real symmetric packed matrix
template<Fill _uplo = DEFAULT_UPLO, Diag _diag = NonUnit>
struct SymmetricPacked;
// complex hermitian packed matrix
template<Fill _uplo = DEFAULT_UPLO, Diag _diag = NonUnit>
struct HermitianPacked;

/* ------------------------------ band storage ------------------------------ */
// general band matrix with _ku superdiagonals and _kl subdiagonals
template<Idx _ku = Dynamic, Idx _kl = _ku, Diag _diag = NonUnit>
struct GeneralBand;
// triangular band matrix with _k super- or sub-diagonals
template<Fill _uplo = DEFAULT_UPLO, Idx _k = Dynamic, Diag _diag = NonUnit>
struct TriangularBand;
// symmetric band matrix with _ku superdiagonals and _kl subdiagonals
template<Fill _uplo = DEFAULT_UPLO, Idx _k = Dynamic, Diag _diag = NonUnit>
struct SymmetricBand;
// hermitian band matrix with _ku superdiagonals and _kl subdiagonals
template<Fill _uplo = DEFAULT_UPLO, Idx _k = Dynamic, Diag _diag = NonUnit>
struct HermitianBand;

/* ---------------------------- diagonal matrix ----------------------------- */
template<Diag _diag = NonUnit>
struct Diagonal : public GeneralBand<0, 0, _diag>
{
#ifdef SQUEEZE_USE_MKL
  static constexpr matrix_descr m_descr_mkl{SPARSE_MATRIX_TYPE_DIAGONAL,
                                            SPARSE_FILL_MODE_FULL,
                                            MKL_DIAG_MODE(_diag)};
#endif
};

// an alias for identity matrix
using Identity = Diagonal<Unit>;

#undef DEFAULT_UPLO
#ifdef SQUEEZE_USE_MKL
  #undef MKL_DIAG_MODE
#endif


namespace internal { // This part can be reduced using `Concept` of C++20.

template<class _MType>
struct IsMatrixType : public std::false_type { };
template<class _MType>
struct IsSparseMatrixType : public std::false_type { };

template<>
struct IsMatrixType<General> : public std::true_type { };
template<>
struct IsSparseMatrixType<General> : public std::true_type { };

template<Fill _uplo, Diag _diag>
struct IsMatrixType<Triangular<_uplo, _diag>> : public std::true_type { };
template<Fill _uplo, Diag _diag>
struct IsSparseMatrixType<Triangular<_uplo, _diag>> : public std::true_type { };

template<Fill _uplo, Diag _diag>
struct IsMatrixType<Symmetric<_uplo, _diag>> : public std::true_type { };
template<Fill _uplo, Diag _diag>
struct IsSparseMatrixType<Symmetric<_uplo, _diag>> : public std::true_type { };

template<Fill _uplo, Diag _diag>
struct IsMatrixType<Hermitian<_uplo, _diag>> : public std::true_type { };
template<Fill _uplo, Diag _diag>
struct IsSparseMatrixType<Hermitian<_uplo, _diag>> : public std::true_type { };

template<Fill _uplo, Diag _diag>
struct IsMatrixType<TriangularPacked<_uplo, _diag>> : public std::true_type{ };

template<Fill _uplo, Diag _diag>
struct IsMatrixType<SymmetricPacked<_uplo, _diag>> : public std::true_type { };

template<Fill _uplo, Diag _diag>
struct IsMatrixType<HermitianPacked<_uplo, _diag>> : public std::true_type { };

template<Idx _ku, Idx _kl, Diag _diag>
struct IsMatrixType<GeneralBand<_ku, _kl, _diag>> : public std::true_type { };

template<Fill _uplo, Idx _k, Diag _diag>
struct IsMatrixType<TriangularBand<_uplo, _k, _diag>>
: public std::true_type { };

template<Fill _uplo, Idx _k, Diag _diag>
struct IsMatrixType<SymmetricBand<_uplo, _k, _diag>>
: public std::true_type { };

template<Fill _uplo, Idx _k, Diag _diag>
struct IsMatrixType<HermitianBand<_uplo, _k, _diag>>
: public std::true_type { };

template<Diag _diag>
struct IsSparseMatrixType<Diagonal<_diag>> : public std::true_type { };

struct IsMatrixType<Identity> : public std::true_type { };

} // namespace internal

} // namespace Squeeze

#endif // include guard
