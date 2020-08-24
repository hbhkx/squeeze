#ifndef SQUEEZE_SPARSEMATRIX_HH
#define SQUEEZE_SPARSEMATRIX_HH

#include "../vector/vector.hh"
#include "mtypes.hh"

namespace Squeeze {

/* ------------------------------ sparse types ------------------------------ */
struct Coo { };
struct Csr { };
struct Csc { };
// struct Bsr { };

namespace internal {

template<class _SparseType>
struct IsSparseType : public std::false_type { };

template<>
struct IsSparseType<Coo> : public std::true_type { };

template<>
struct IsSparseType<Csr> : public std::true_type { };

template<>
struct IsSparseType<Csc> : public std::true_type { };

// template<>
// struct IsSparseType<Bsr> : public std::true_type { };

} // namespace internal


template<class _Tp, Idx _rows = Dynamic, Idx _cols = _rows,
         class _SparseType = Coo, class _MatrixType = General>
class SparseMatrix
{
  static_assert(internal::IsSparseType<_SparseType>::value,
                "Wrong sparse type!!");
  static_assert(internal::IsSparseMatrixType<_MatrixType>::value,
                "Wrong type!!");
  static_assert(_rows != _cols, "Square matrix is needed but sizes are not!");
};


namespace internal {

template<class _Tp, Idx _rows, Idx _cols, class _SparseType, class _MatrixType>
struct IsSpMat<SparseMatrix<_Tp, _rows, _cols, _SparseType, _MatrixType>>
: public std::true_type { };

}


/* --------------------- specialization for Coo Matrix ---------------------- */
// template<class _Tp, Idx _rows, Idx _cols, class _MatrixType>
// class SparseMatrix<_Tp, _rows, _cols, Coo, _MatrixType>
// {
//   static_assert((_rows == Dynamic || _rows >= 0) &&
//                 (_cols == Dynamic || _cols >= 0), "Invalid size!!");
// private:
// #ifdef SQUEEZE_USE_MKL
//   sparse_matrix_t m_matrix_mkl;
//   static constexpr matrix_descr m_descr_mkl{_MatrixType::type,
//                                             _MatrixType::mode,
//                                             _MatrixType::diag};
// #endif
//   Vector<Idx> m_i;
//   Vector<Idx> m_j;
//   Vector<_Tp> m_data;
// };


/* --------------------- specialization for Csr Matrix ---------------------- */
template<class _Tp, Idx _rows, Idx _cols, class _MatrixType>
class SparseMatrix<_Tp, _rows, _cols, Csr, _MatrixType>
{
  static_assert((_rows == Dynamic || _rows >= 0) &&
                (_cols == Dynamic || _cols >= 0), "Invalid size!!");
private:
#ifdef SQUEEZE_USE_MKL
  sparse_matrix_t m_matrix_mkl;
  using _MatrixType::m_descr_mkl;
#endif
  Idx m_rows = _rows == Dynamic ? 0 : _rows;
  Idx m_cols = _cols == Dynamic ? 0 : _cols;
  Vector<Idx> m_indptr;
  Vector<Idx> m_indices;
  Vector<_Tp> m_data;
public:
  using ValueType = _Tp;

  // SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE SparseMatrix(Idx rows, Idx cols)
  // : m_rows(rows), m_cols(cols), m_indptr(rows + 1)
  // {}

  // SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE SparseMatrix(Idx order)
  // : m_rows(order), m_cols(order), m_indptr(order + 1)
  // {}

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  SparseMatrix(const Vector<Idx>& indptr, const Vector<Idx>& indices,
               const Vector<_Tp>& data)
  : m_indptr(indptr), m_indices(indices), m_data(data)
  {
#ifdef SQUEEZE_USE_MKL
    mkl_sparse_z_create_csr(&m_matrix_mkl, SPARSE_INDEX_BASE_ZERO,
                            n_rows, n_cols, indptr.data(), &indptr[1],
                            indices.data(), data.data());
#endif
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  SparseMatrix(Vector<Idx>&& indptr, Vector<Idx>&& indices, Vector<_Tp>&& data)
  : m_indptr(std::move(indptr))
  , m_indices(std::move(indices))
  , m_data(std::move(data))
  {
#ifdef SQUEEZE_USE_MKL
    mkl_sparse_z_create_csr(&m_matrix_mkl, SPARSE_INDEX_BASE_ZERO,
                            n_rows, n_cols, indptr.data(), &indptr[1],
                            indices.data(), data.data());
#endif
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE ~SparseMatrix() {
#ifdef SQUEEZE_USE_MKL
    mkl_sparse_destroy(m_matrix_mkl);
#endif
    ~m_data;
    ~m_indices;
    ~m_indptr;
  }

  SQUEEZE_DEVICE_FUNC constexpr Idx rows() const { return m_rows; }
  SQUEEZE_DEVICE_FUNC constexpr Idx cols() const { return m_cols; }
  SQUEEZE_DEVICE_FUNC constexpr Idx nnz() const { return m_indices.size(); }

  SQUEEZE_DEVICE_FUNC constexpr
  const Vector<Idx>& indptr() const { return m_indptr; }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  Vector<Idx>& indptr() { return m_indptr; }

  SQUEEZE_DEVICE_FUNC constexpr
  const Vector<Idx>& indices() const { return m_indices; }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  Vector<Idx>& indices() { return m_indices; }

  SQUEEZE_DEVICE_FUNC constexpr
  const Vector<_Tp>& data() const { return m_data; }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  Vector<_Tp>& data() { return m_data; }
#ifdef SQUEEZE_USE_MKL
  SQUEEZE_DEVICE_FUNC constexpr
  sparse_matrix_t mkl() const { return m_matrix_mkl; }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  sparse_matrix_t mkl() { return m_matrix_mkl; }

  SQUEEZE_DEVICE_FUNC static constexpr
  matrix_descr descr() { return m_descr_mkl; }
#endif
};


namespace spblas {

/* ----------------------------- spblas::csr_mv ----------------------------- */
template<class _SpMat, class _Vec>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec csr_mv(const _SpMat& m, const _Vec& v) {
  _Vec out(v.size());
#ifdef SQUEEZE_USE_MKL
  mkl_sparse_z_mv(SPARSE_OPERATION_NON_TRANSPOSE, 1, m.mkl(),
                  m.descr(), v.data(), 0, out.data());
#else
  const Vector<Idx>& indptr = m.indptr();
  const Vector<Idx>& indices = m.indices();
  const _Vec data = m.data();
  #pragma omp parallel for \
          if (v.size() * sizeof(ValueType<_Vec>) > SQUEEZE_NON_PAR_CAL_BYTES)
  for (Idx i = 0; i < size; i++) {
    out[i] = 0;
    for (Idx j = indptr[i]; j < indptr[i + 1]; j++) {
        out[i] += data[j] * v[indices[j]];
    }
  }
#endif
  return out;
}


/* ---------------------------- spblas::csr_amv ----------------------------- */
template<class _SpMat, class _Vec, class _Ari = ValueType<_Vec>>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec csr_amv(const _Ari& a, const _SpMat& m, const _Vec& v) {
  _Vec out(v.size());
#ifdef SQUEEZE_USE_MKL
  mkl_sparse_z_mv(SPARSE_OPERATION_NON_TRANSPOSE, a, m.mkl(),
                  m.descr(), v.data(), 0, out.data());
#else
  const Vector<Idx>& indptr = m.indptr();
  const Vector<Idx>& indices = m.indices();
  const _Vec data = m.data();
  #pragma omp parallel for \
          if (v.size() * sizeof(ValueType<_Vec>) >= SQUEEZE_NON_PAR_CAL_BYTES)
  for (Idx i = 0; i < size; i++) {
    out[i] = 0;
    for (Idx j = indptr[i]; j < indptr[i + 1]; j++) {
        out[i] += data[j] * v[indices[j]];
    }
    out[i] *= a;
  }
#endif
  return out;
}


/* ---------------------------- spblas::csr_mvpy ---------------------------- */
template<class _SpMat, class _Vec>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& csr_mvpy(const _SpMat& m, const _Vec& v, _Vec& y) {
#ifdef SQUEEZE_USE_MKL
  mkl_sparse_z_mv(SPARSE_OPERATION_NON_TRANSPOSE, 1, m.mkl(),
                  m.descr(), v.data(), 1, y.data());
#else
  const Vector<Idx>& indptr = m.indptr();
  const Vector<Idx>& indices = m.indices();
  const _Vec data = m.data();
  #pragma omp parallel for \
          if (v.size() * sizeof(ValueType<_Vec>) >= SQUEEZE_NON_PAR_CAL_BYTES)
  for (Idx i = 0; i < size; i++) {
    for (Idx j = indptr[i]; j < indptr[i + 1]; j++) {
        y[i] += data[j] * v[indices[j]];
    }
  }
#endif
  return y;
}


/* --------------------------- spblas::csr_mvpby ---------------------------- */
template<class _SpMat, class _Vec, class _Ari = ValueType<_Vec>>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& csr_amv(const _SpMat& m, const _Vec& v, const _Ari& b, _Vec& y) {
#ifdef SQUEEZE_USE_MKL
  mkl_sparse_z_mv(SPARSE_OPERATION_NON_TRANSPOSE, 1, m.mkl(),
                  m.descr(), v.data(), b, y.data());
#else
  const Vector<Idx>& indptr = m.indptr();
  const Vector<Idx>& indices = m.indices();
  const _Vec data = m.data();
  #pragma omp parallel for \
          if (v.size() * sizeof(ValueType<_Vec>) >= SQUEEZE_NON_PAR_CAL_BYTES)
  for (Idx i = 0; i < size; i++) {
    ValueType<_Vec> temp = 0;
    for (Idx j = indptr[i]; j < indptr[i + 1]; j++) {
        temp += data[j] * v[indices[j]];
    }
    y[i] = temp + b * y[i];
  }
#endif
  return y;
}


/* --------------------------- spblas::csr_amvpy ---------------------------- */
template<class _SpMat, class _Vec, class _Ari = ValueType<_Vec>>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& csr_amv(const _Ari& a, const _SpMat& m, const _Vec& v, _Vec& y) {
#ifdef SQUEEZE_USE_MKL
  mkl_sparse_z_mv(SPARSE_OPERATION_NON_TRANSPOSE, a, m.mkl(),
                  m.descr(), v.data(), 1, y.data());
#else
  const Vector<Idx>& indptr = m.indptr();
  const Vector<Idx>& indices = m.indices();
  const _Vec data = m.data();
  #pragma omp parallel for \
          if (v.size() * sizeof(ValueType<_Vec>) >= SQUEEZE_NON_PAR_CAL_BYTES)
  for (Idx i = 0; i < size; i++) {
    ValueType<_Vec> temp = 0;
    for (Idx j = indptr[i]; j < indptr[i + 1]; j++) {
        temp += data[j] * v[indices[j]];
    }
    y[i] += a * temp;
  }
#endif
  return y;
}


/* --------------------------- spblas::csr_amvpby --------------------------- */
template<class _SpMat, class _Vec, class _Ari = ValueType<_Vec>>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
_Vec& csr_amv(const _Ari& a, const _SpMat& m, const _Vec& v,
              const _Ari& b, _Vec& y) {
#ifdef SQUEEZE_USE_MKL
  mkl_sparse_z_mv(SPARSE_OPERATION_NON_TRANSPOSE, a, m.mkl(),
                  m.descr(), v.data(), b, y.data());
#else
  const Vector<Idx>& indptr = m.indptr();
  const Vector<Idx>& indices = m.indices();
  const _Vec data = m.data();
  #pragma omp parallel for \
          if (v.size() * sizeof(ValueType<_Vec>) >= SQUEEZE_NON_PAR_CAL_BYTES)
  for (Idx i = 0; i < size; i++) {
    ValueType<_Vec> temp = 0;
    for (Idx j = indptr[i]; j < indptr[i + 1]; j++) {
        temp += data[j] * v[indices[j]];
    }
    y[i] = a * temp + b * y[i];
  }
#endif
  return y;
}

} // namespace spblas

} // namespace Squeeze

#endif // include guard
