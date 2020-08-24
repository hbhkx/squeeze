#ifndef SQUEEZE_MATRIX_HH
#define SQUEEZE_MATRIX_HH

#include "../vector/vector.hh"
#include "mtypes.hh"

namespace Squeeze {

template<class _Tp, Idx _rows = Dynamic, Idx _cols = _rows,
         Layout _is_row_major = SQUEEZE_DEFAULT_MATRIX_STORAGE_ORDER,
         class _MatrixType = General,
         StdUIdx _alignment = SQUEEZE_DEFAULT_ALIGN_BYTES>
class Matrix
{
  static_assert(internal::IsMatrixType<_MatrixType>::value, "Wrong type!!");
  static_assert(_rows != _cols, "Square matrix is needed but sizes are not!");
};


/* ------------------- specialization for General Matrix ------------------- */
#define GET_SIZE(rows, cols) rows * cols
#define CONDITIONAL_SIZE(rows, cols) (rows == Dynamic || cols == Dynamic) ? \
                                     Dynamic : GET_SIZE(rows, cols)
#define GET_INDEX(i, j) (_is_row_major) ? (i*m_cols + j) : (j*m_rows + i)

template<class _Tp, Idx _rows, Idx _cols, Layout _is_row_major,
         StdUIdx _alignment>
class Matrix<_Tp, _rows, _cols, _is_row_major, General, _alignment>
{
#ifdef SQUEEZE_DONT_ALIGN
  static_assert(_alignment == 0,
    "Why use non-zero alignment while SQUEEZE_DONT_ALIGN is specified?");
#endif
  static_assert((_rows == Dynamic || _rows >= 0) &&
                (_cols == Dynamic || _cols >= 0), "Invalid size!!");
  Vector<_Tp, CONDITIONAL_SIZE(_rows, _cols), _alignment> m_data;
  Idx m_rows = _rows == Dynamic ? 0 : _rows;
  Idx m_cols = _cols == Dynamic ? 0 : _cols;
public:
  SQUEEZE_DEVICE_FUNC constexpr Matrix() = default;

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE Matrix(Idx rows, Idx cols)
  : m_data(GET_SIZE(rows, cols)), m_rows(rows), m_cols(cols)
  {
    if (rows < 0 || cols < 0)
      throw std::length_error("rows and cols cannot be negative!!");
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE Matrix(Idx order)
  : m_data(GET_SIZE(order, order)), m_rows(order), m_cols(order)
  {
    if (order < 0)
      throw std::length_error("rows and cols cannot be negative!!");
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Matrix& operator=(const Matrix&) = default;

  // This hetero copy constructor is to be specialized later
  template<class _T, Idx _r, Idx _c,
           Layout _row_major, class _MType, StdUIdx _align>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Matrix& operator=(const Matrix<_T, _r, _c, _row_major, _MType, _align>&);

  template<class _T, StdUIdx _align>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Matrix& operator=(const Matrix<_T, _rows, _cols,
                                 _is_row_major, General, _align>& other)
  {
    m_data = other.m_data;
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    return *this;
  }

  SQUEEZE_DEVICE_FUNC constexpr Idx rows() const { return m_rows; }
  SQUEEZE_DEVICE_FUNC constexpr Idx cols() const { return m_cols; }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR20
  void swap(Matrix& other) noexcept {
    m_data.swap(other.m_data);
    std::swap(m_rows, other.m_rows);
    std::swap(m_cols, other.m_cols);
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  void resize(Idx rows, Idx cols) {
    m_data.resize(GET_SIZE(rows, cols));
    m_rows = rows;
    m_cols = cols;
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  void resize(Idx order) {
    m_data.resize(GET_SIZE(order, order));
    m_rows = order;
    m_cols = order;
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR17
  const _Tp* data() const { return m_data.data(); }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR17 _Tp* data() { return m_data.data(); }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  const _Tp& operator()(Idx i, Idx j) const {
#ifdef SQUEEZE_HAS_DEBUG
    if (i < 0 || j < 0 || i >= m_rows || j >= m_cols)
      throw std::out_of_range("Invalid index!!");
#endif
    return m_data[GET_INDEX(i, j)];
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR17 _Tp& operator()(Idx i, Idx j) {
#ifdef SQUEEZE_HAS_DEBUG
    if (i < 0 || j < 0 || i >= m_rows || j >= m_cols)
      throw std::out_of_range("Invalid index!!");
#endif
      return m_data[GET_INDEX(i, j)];
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  _Tp get(Idx i, Idx j) const {
    if (i < 0 || j < 0 || i >= m_rows || j >= m_cols)
      throw std::out_of_range("Invalid index!!");

    return m_data[GET_INDEX(i, j)];
  }
};
#undef GET_SIZE
#undef CONDITIONAL_SIZE
#undef GET_INDEX


/* ------------------ specialization for Triangular Matrix ------------------ */
#define GET_SIZE(order) order * order
#define CONDITIONAL_SIZE(order) (order == Dynamic) ? Dynamic : GET_SIZE(order)
#define GET_INDEX(i, j) (_is_row_major) ? (i*m_order + j) : (j*m_order + i)

template<class _Tp, Idx _order, Layout _is_row_major,
         StdUIdx _alignment, Fill _uplo, Diag _diag>
class Matrix<_Tp, _order, _order,
             _is_row_major, Triangular<_uplo, _diag>, _alignment>
{
#ifdef SQUEEZE_DONT_ALIGN
  static_assert(_alignment == 0,
    "Why use non-zero alignment while SQUEEZE_DONT_ALIGN is specified?");
#endif
  static_assert((_order == Dynamic || _order >= 0),
                "Invalid size for square matrix!!");
  Vector<_Tp, CONDITIONAL_SIZE(_order), _alignment> m_data;
  Idx m_order = (_order == Dynamic) ? 0 : _order;

public:
  SQUEEZE_DEVICE_FUNC constexpr Matrix() = default;

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE Matrix(Idx rows, Idx cols)
  : m_data(GET_SIZE(rows)), m_order(rows)
  {
    if (rows != cols || rows < 0)
      throw std::length_error("square matrix needed!!");
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE Matrix(Idx order)
  : m_data(GET_SIZE(order)), m_order(order)
  {
    if (order < 0)
      throw std::length_error("order cannot be negative!!");
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Matrix& operator=(const Matrix&) = default;

  // This hetero copy constructor is to be specialized later
  template<class _T, Idx _ord,
           Layout _row_major, class _MType, StdUIdx _align>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Matrix& operator=(const Matrix<_T, _ord, _ord, _row_major, _MType, _align>&);

  SQUEEZE_DEVICE_FUNC constexpr Idx rows() const { return m_order; }
  SQUEEZE_DEVICE_FUNC constexpr Idx cols() const { return m_order; }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR20
  void swap(Matrix& other) noexcept {
    m_data.swap(other.m_data);
    std::swap(m_order, other.m_order);
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  void resize(Idx rows, Idx cols) {
    if (rows != cols)
      throw std::length_error("square matrix needed!!");

    m_data.resize(GET_SIZE(rows));
    m_order = rows;
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  void resize(Idx order) {
    m_data.resize(GET_SIZE(order));
    m_order = order;
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR17
  const _Tp* data() const { return m_data.data(); }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR17 _Tp* data() { return m_data.data(); }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  const _Tp& operator()(Idx i, Idx j) const {
#ifdef SQUEEZE_HAS_DEBUG
    if (_uplo) {
      if (i < 0 || j < i || j >= m_order)
        throw std::out_of_range("Invalid index!!");
    }
    else {
      if (j < 0 || i < j || i >= m_order)
        throw std::out_of_range("Invalid index!!");
    }
#endif
    return m_data[GET_INDEX(i, j)];
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR17 _Tp& operator()(Idx i, Idx j) {
#ifdef SQUEEZE_HAS_DEBUG
    if (_uplo) {
      if (i < 0 || j < i || j >= m_order)
        throw std::out_of_range("Invalid index!!");
    }
    else {
      if (j < 0 || i < j || i >= m_order)
        throw std::out_of_range("Invalid index!!");
    }
#endif
    return m_data[GET_INDEX(i, j)];
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  _Tp get(Idx i, Idx j) const {
    if (i < 0 || j < 0 || i >= m_order || j >= m_order)
      throw std::out_of_range("Invalid index!!");

    if (_uplo) {
      if (i <= j)
        return m_data[GET_INDEX(i, j)];
      else
        return _Tp(0);
    }
    else {
      if (j <= i)
        return m_data[GET_INDEX(i, j)];
      else
        return _Tp(0);
    }
  }
};
#undef GET_SIZE
#undef CONDITIONAL_SIZE


/* ------------------ specialization for Symmetric Matrix ------------------ */
template<class _Tp, Idx _order, Layout _is_row_major,
         StdUIdx _alignment, Fill _uplo, Diag _diag>
class Matrix<_Tp, _order, _order,
             _is_row_major, Symmetric<_uplo, _diag>, _alignment>
: public Matrix<_Tp, _order, _order,
                _is_row_major, Triangular<_uplo, _diag>, _alignment>
{
#ifdef SQUEEZE_DONT_ALIGN
  static_assert(_alignment == 0,
    "Why use non-zero alignment while SQUEEZE_DONT_ALIGN is specified?");
#endif
  static_assert((_order == Dynamic || _order >= 0),
                "Invalid size for square matrix!!");

  // inherit the constructor
  using Matrix<_Tp, _order, _order,
                _is_row_major, Triangular<_uplo, _diag>, _alignment>::Matrix;

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  _Tp get(Idx i, Idx j) const {
    if (i < 0 || j < 0 || i >= m_order || j >= m_order)
      throw std::out_of_range("Invalid index!!");

    if (_uplo) {
      if (i <= j)
        return m_data[GET_INDEX(i, j)];
      else
        return m_data[GET_INDEX(j, i)];
    }
    else {
      if (j <= i)
        return m_data[GET_INDEX(i, j)];
      else
        return m_data[GET_INDEX(j, i)];
    }
  }
};


/* ------------------ specialization for Hermitian Matrix ------------------- */
template<class _Tp, Idx _order, Layout _is_row_major,
         StdUIdx _alignment, Fill _uplo, Diag _diag>
class Matrix<_Tp, _order, _order,
             _is_row_major, Hermitian<_uplo, _diag>, _alignment>
: public Matrix<_Tp, _order, _order,
                _is_row_major, Triangular<_uplo, _diag>, _alignment>
{
  static_assert(internal::IsComplexType<_Tp>::value,
                "Hermitian matrix is only for complex types");
#ifdef SQUEEZE_DONT_ALIGN
  static_assert(_alignment == 0,
    "Why use non-zero alignment while SQUEEZE_DONT_ALIGN is specified?");
#endif
  static_assert((_order == Dynamic || _order >= 0),
                "Invalid size for square matrix!!");

  // inherit the constructor
  using Matrix<_Tp, _order, _order,
                _is_row_major, Triangular<_uplo, _diag>, _alignment>::Matrix;

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  _Tp get(Idx i, Idx j) const {
    if (i < 0 || j < 0 || i >= m_order || j >= m_order)
      throw std::out_of_range("Invalid index!!");

    if (_uplo) {
      if (i <= j)
        return m_data[GET_INDEX(i, j)];
      else
        return std::conj(m_data[GET_INDEX(j, i)]);
    }
    else {
      if (j <= i)
        return m_data[GET_INDEX(i, j)];
      else
        return std::conj(m_data[GET_INDEX(j, i)]);
    }
  }
};
#undef GET_INDEX


/* --------------- specialization for TriangularPacked Matrix --------------- */
#define GET_SIZE(order) order * (order + 1) / 2
#define CONDITIONAL_SIZE(order) (order == Dynamic) ? Dynamic : GET_SIZE(order)
#define GET_INDEX_UP(i, j) \
  (_is_row_major) ? (j + i*(2*m_order+1-i)/2) : (i + j*(j+1)/2)
#define GET_INDEX_LO(i, j) \
  (_is_row_major) ? (j + i*(i+1)/2) : (i + j*(2*m_order+1-j)/2)

template<class _Tp, Idx _order, Layout _is_row_major,
         StdUIdx _alignment, Fill _uplo, Diag _diag>
class Matrix<_Tp, _order, _order,
             _is_row_major, TriangularPacked<_uplo, _diag>, _alignment>
{
#ifdef SQUEEZE_DONT_ALIGN
  static_assert(_alignment == 0,
    "Why use non-zero alignment while SQUEEZE_DONT_ALIGN is specified?");
#endif
  static_assert((_order == Dynamic || _order >= 0),
                "Invalid size for square matrix!!");
  Vector<_Tp, CONDITIONAL_SIZE(_order), _alignment> m_data;
  Idx m_order = _order == Dynamic ? 0 : _order;
public:
  SQUEEZE_DEVICE_FUNC constexpr Matrix() = default;

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE Matrix(Idx rows, Idx cols)
  : m_data(GET_SIZE(rows)), m_order(rows)
  {
    if (rows != cols || rows < 0)
      throw std::length_error("square matrix needed!!");
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE Matrix(Idx order)
  : m_data(GET_SIZE(order)), m_order(order)
  {
    if (order < 0)
      throw std::length_error("matrix order cannot be negative!!");
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Matrix& operator=(const Matrix&) = default;

  // This hetero copy constructor is to be specialized later
  template<class _T, Idx _order,
           Layout _row_major, class _MType, StdUIdx _align>
  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  Matrix& operator=(const Matrix<_T, _order, _order,
                                 _row_major, _MType, _align>&);

  SQUEEZE_DEVICE_FUNC constexpr Idx rows() const { return m_order; }
  SQUEEZE_DEVICE_FUNC constexpr Idx cols() const { return m_order; }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR20
  void swap(Matrix& other) noexcept {
    m_data.swap(other.m_data);
    std::swap(m_order, other.m_order);
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  void resize(Idx rows, Idx cols) {
    if (rows != cols)
      throw std::length_error("square matrix needed!!");

    m_data.resize(GET_SIZE(rows));
    m_order = rows;
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
  void resize(Idx order) {
    m_data.resize(GET_SIZE(order));
    m_order = order;
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR17
  const _Tp* data() const { return m_data.data(); }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR17 _Tp* data() { return m_data.data(); }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  const _Tp& operator()(Idx i, Idx j) const {
#ifdef SQUEEZE_HAS_DEBUG
    if (_uplo) {
      if (i < 0 || j < i || j >= m_order)
        throw std::out_of_range("Invalid index!!");
    }
    else {
      if (j < 0 || i < j || i >= m_order)
        throw std::out_of_range("Invalid index!!");
    }
#endif
    if (_uplo)
      return m_data[GET_INDEX_UP(i, j)];
    else
      return m_data[GET_INDEX_LO(i, j)];
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR17 _Tp& operator()(Idx i, Idx j) {
#ifdef SQUEEZE_HAS_DEBUG
    if (_uplo) {
      if (i < 0 || j < i || j >= m_order)
        throw std::out_of_range("Invalid index!!");
    }
    else {
      if (j < 0 || i < j || i >= m_order)
        throw std::out_of_range("Invalid index!!");
    }
#endif
    if (_uplo)
      return m_data[GET_INDEX_UP(i, j)];
    else
      return m_data[GET_INDEX_LO(i, j)];
  }

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  _Tp get(Idx i, Idx j) const {
    if (i < 0 || j < 0 || i >= m_order || j >= m_order)
      throw std::out_of_range("Invalid index!!");

    if (_uplo) {
      if (i <= j)
        return m_data[GET_INDEX_UP(i, j)];
      else
        return _Tp(0);
    }
    else {
      if (j <= i)
        return m_data[GET_INDEX_LO(i, j)];
      else
        return _Tp(0);
    }
  }
};
#undef GET_SIZE
#undef CONDITIONAL_SIZE


/* --------------- specialization for SymmetricPacked Matrix ---------------- */
template<class _Tp, Idx _order, Layout _is_row_major,
         StdUIdx _alignment, Fill _uplo, Diag _diag>
class Matrix<_Tp, _order, _order,
             _is_row_major, SymmetricPacked<_uplo, _diag>, _alignment>
: public Matrix<_Tp, _order, _order,
                _is_row_major, TriangularPacked<_uplo, _diag>, _alignment>
{
#ifdef SQUEEZE_DONT_ALIGN
  static_assert(_alignment == 0,
    "Why use non-zero alignment while SQUEEZE_DONT_ALIGN is specified?");
#endif
  static_assert((_order == Dynamic || _order >= 0),
                "Invalid size for square matrix!!");

  // inherit the constructor
  using Matrix<_Tp, _order, _order, _is_row_major,
               TriangularPacked<_uplo, _diag>, _alignment>::Matrix;

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  _Tp get(Idx i, Idx j) const {
    if (i < 0 || j < 0 || i >= m_order || j >= m_order)
      throw std::out_of_range("Invalid index!!");

    if (_uplo) {
      if (i <= j)
        return m_data[GET_INDEX_UP(i, j)];
      else
        return m_data[GET_INDEX_UP(j, i)];
    }
    else {
      if (j <= i)
        return m_data[GET_INDEX_LO(i, j)];
      else
        return m_data[GET_INDEX_LO(j, i)];
    }
  }
};


/* ---------------- specialization for HermitianPacked Matrix --------------- */
template<class _Tp, Idx _order, Layout _is_row_major,
         StdUIdx _alignment, Fill _uplo, Diag _diag>
class Matrix<_Tp, _order, _order,
             _is_row_major, HermitianPacked<_uplo, _diag>, _alignment>
: public Matrix<_Tp, _order, _order,
                _is_row_major, TriangularPacked<_uplo, _diag>, _alignment>
{
  static_assert(internal::IsComplexType<_Tp>::value,
                "Hermitian matrix is only for complex types");
#ifdef SQUEEZE_DONT_ALIGN
  static_assert(_alignment == 0,
    "Why use non-zero alignment while SQUEEZE_DONT_ALIGN is specified?");
#endif
  static_assert((_order == Dynamic || _order >= 0),
                "Invalid size for square matrix!!");

  // inherit the constructor
  using Matrix<_Tp, _order, _order, _is_row_major,
               TriangularPacked<_uplo, _diag>, _alignment>::Matrix;

  SQUEEZE_DEVICE_FUNC SQUEEZE_CONSTEXPR14
  _Tp get(Idx i, Idx j) const {
    if (i < 0 || j < 0 || i >= m_order || j >= m_order)
      throw std::out_of_range("Invalid index!!");

    if (_uplo) {
      if (i <= j)
        return m_data[GET_INDEX_UP(i, j)];
      else
        return std::conj(m_data[GET_INDEX_UP(j, i)]);
    }
    else {
      if (j <= i)
        return m_data[GET_INDEX_LO(i, j)];
      else
        return std::conj(m_data[GET_INDEX_LO(j, i)]);
    }
  }
};
#undef GET_INDEX_UP
#undef GET_INDEX_LO


#ifdef SQUEEZE_USE_LAPACK
namespace lapack {

template<bool _eigen_vectors = 0, class _Tp = double,
         Idx _order = Dynamic, Layout _is_row_major = ColMajor,
         StdUIdx _alignment = SQUEEZE_DEFAULT_ALIGN_BYTES, Fill _uplo = Lower>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
Vector<_Tp, _order, _alignment> eigen_values(Matrix<Complex<_Tp>,
                                                    _order, _order,
                                                    _is_row_major,
                                                    Hermitian<_uplo, NonUnit>,
                                                    _alignment>& mat)
{
  constexpr int layout = (_is_row_major) ? LAPACK_ROW_MAJOR : LAPACK_COL_MAJOR;
  constexpr char jobz  = (_eigen_vectors) ? 'V' : 'N';
  constexpr char range = 'A';
  constexpr char uplo  = (_uplo) ? 'U' : 'L';
  Idx n = mat.rows(), m;
  Vector<_Tp, _order, _alignment> out(n);

  LAPACKE_zheevr(layout, jobz, range, uplo, n, mat.data(), n,
                 0.0, 0.0, 0, 0, 0.0, &m, out.data(), nullptr, 1, nullptr);

  return out;
}

} // namespace lapack
#endif

} // namespace Squeeze

#endif // include guard
