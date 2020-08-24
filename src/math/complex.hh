#ifndef SQUEEZE_COMPLEX_HH
#define SQUEEZE_COMPLEX_HH

#include <complex>
#include "../init/type_traits.hh"

// #define CAST_STL(X)        reinterpret_cast<std::complex<_Tp>>(X)
// #define CAST_STL_CONST(X)  reinterpret_cast<const std::complex<_Tp>>(X)
// #define CAST_BACK(X)       reinterpret_cast<Complex<_Tp>>(X)

namespace Squeeze {

// TODO: implement our own Complex types using SIMD
// now we are using std::complex temporarily
template<typename _Tp>
using Complex = std::complex<_Tp>;


// /* Class for imaginary unit */
// struct __I { };
// /* Class for negative imaginary unit */
// struct __In { };

constexpr static const Complex<Idx> I(0, 1);


namespace internal {

/* --------------------- helper classes for type_traits --------------------- */
template<class _Tp>
struct IsComplexType<Complex<_Tp>> : public std::true_type { };

template<class _Tp>
struct SupportedType<Complex<_Tp>> : public SupportedType<_Tp> { };

} // namespace internal


// template<typename _Tp>
// struct Complex {
//   static_assert(std::is_arithmetic<_Tp>::value, "Unsupported type!!!");
//  protected:
//   _Tp _M_real;
//   _Tp _M_imag;

//  public:
//   using value_type = _Tp;

//   // Default constructor.  First parameter is re, second parameter is im.
//   // Unspecified parameters default to 0.
//   constexpr Complex(const _Tp& __r = _Tp(), const _Tp& __i = _Tp())
//       : _M_real(__r), _M_imag(__i) { }

//   // Let the compiler synthesize the copy constructor and move constructor.
//   constexpr Complex(const Complex&) = default;
//   constexpr Complex(Complex&&) = default;

//   // Cast from std::complex.
//   constexpr Complex(const std::complex<_Tp>& __z)
//       : _M_real(__z.real()), _M_imag(__z.imag()) { }
//   // Cast from imaginary unit
//   constexpr Complex(__I) : _M_real(0), _M_imag(1) { }
//   // Cast from nagative imaginary unit
//   constexpr Complex(__In) : _M_real(0), _M_imag(-1) { }

//   // Converting constructor.
//   template<typename _Up> constexpr Complex(const Complex<_Up>& __z)
//       : _M_real(__z.real()), _M_imag(__z.imag()) { }

//   // Return real part of complex number.
//   constexpr _Tp real() const { return _M_real; }
//   // Return imaginary part of complex number.
//   constexpr _Tp imag() const { return _M_imag; }

//   SQUEEZE_CONSTEXPR14 void real(_Tp __val) { _M_real = __val; }
//   SQUEEZE_CONSTEXPR14 void imag(_Tp __val) { _M_imag = __val; }

//   // Assign a scalar to this complex number.
//   SQUEEZE_CONSTEXPR14 Complex<_Tp>& operator=(const _Tp& __t) {
//     _M_real = __t;
//     _M_imag = 0;
//     return *this;
//   }
//   // Add a scalar to this complex number.
//   SQUEEZE_CONSTEXPR14 Complex<_Tp>& operator+=(const _Tp& __t) {
//     _M_real += __t;
//     return *this;
//   }
//   // Subtract a scalar to this complex number.
//   SQUEEZE_CONSTEXPR14 Complex<_Tp>& operator-=(const _Tp& __t) {
//     _M_real -= __t;
//     return *this;
//   }
//   // Multiply this complex number by a scalar.
//   SQUEEZE_CONSTEXPR14 Complex<_Tp>& operator*=(const _Tp& __t) {
//     _M_real *= __t;
//     _M_imag *= __t;
//     return *this;
//   }
//   // Divide this complex number by a scalar.
//   SQUEEZE_CONSTEXPR14 Complex<_Tp>& operator/=(const _Tp& __t) {
//     _M_real /= __t;
//     _M_imag /= __t;
//     return *this;
//   }

//   // Let the compiler synthesize the copy/move assignment operator.
//   constexpr Complex& operator=(const Complex&) = default;
//   constexpr Complex& operator=(Complex&&) = default;

//   // Assign another complex number to this one.
//   template<typename _Up>
//   SQUEEZE_CONSTEXPR14 Complex<_Tp>& operator=(const Complex<_Up>& __z) {
//     _M_real = __z._M_real;
//     _M_imag = __z._M_imag;
//     return *this;
//   }
//   // Add another complex number to this one.
//   template<typename _Up>
//   SQUEEZE_CONSTEXPR14 Complex<_Tp>& operator+=(const Complex<_Up>& __z) {
//     _M_real += __z._M_real;
//     _M_imag += __z._M_imag;
//     return *this;
//   }
//   // Subtract another complex number from this one.
//   template<typename _Up>
//   SQUEEZE_CONSTEXPR14 Complex<_Tp>& operator-=(const Complex<_Up>& __z) {
//     _M_real -= __z._M_real;
//     _M_imag -= __z._M_imag;
//     return *this;
//   }
//   // Multiply this complex number by another.
//   template<typename _Up>
//   SQUEEZE_CONSTEXPR14 Complex<_Tp>& operator*=(const Complex<_Up>& __z) {
//     const _Tp __r = _M_real * __z.real() - _M_imag * __z.imag();
//     _M_imag = _M_real * __z.imag() + _M_imag * __z.real();
//     _M_real = __r;
//     return *this;
//   }
//   // Divide this complex number by another.
//   template<typename _Up>
//   SQUEEZE_CONSTEXPR14 Complex<_Tp>& operator/=(const Complex<_Up>& __z) {
//     const _Tp __r =  _M_real * __z.real() + _M_imag * __z.imag();
//     const _Tp __n = __z.real() * __z.real() + __z.imag() * __z.imag();
//     _M_imag = (_M_imag * __z.real() - _M_real * __z.imag()) / __n;
//     _M_real = __r / __n;
//     return *this;
//   }
// };

// // Operators:
// //@{
// // Return new complex value @a x plus @a y.
// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14 Complex<_Tp>
// operator+(const Complex<_Tp>& __x, const Complex<_Tp>& __y) {
//   Complex<_Tp> out = __x;
//   out += __y;
//   return out;
// }

// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14 Complex<_Tp>
// operator+(const Complex<_Tp>& __x, const _Tp& __y) {
//   Complex<_Tp> out = __x;
//   out += __y;
//   return out;
// }

// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14 Complex<_Tp>
// operator+(const _Tp& __x, const Complex<_Tp>& __y) {
//   Complex<_Tp> out = __y;
//   out += __x;
//   return out;
// }
// //@}

// //@{
// // Return new complex value @a x minus @a y.
// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14 Complex<_Tp>
// operator-(const Complex<_Tp>& __x, const Complex<_Tp>& __y) {
//   Complex<_Tp> out = __x;
//   out -= __y;
//   return out;
// }

// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14 Complex<_Tp>
// operator-(const Complex<_Tp>& __x, const _Tp& __y) {
//   Complex<_Tp> out = __x;
//   out -= __y;
//   return out;
// }

// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14 Complex<_Tp>
// operator-(const _Tp& __x, const Complex<_Tp>& __y) {
//   Complex<_Tp> out = -__y;
//   out += __x;
//   return out;
// }
// //@}

// //@{
// // Return new complex value @a x times @a y.
// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14 Complex<_Tp>
// operator*(const Complex<_Tp>& __x, const Complex<_Tp>& __y) {
//   Complex<_Tp> out = __x;
//   out *= __y;
//   return out;
// }

// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14 Complex<_Tp>
// operator*(const Complex<_Tp>& __x, const _Tp& __y) {
//   Complex<_Tp> out = __x;
//   out *= __y;
//   return out;
// }

// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14 Complex<_Tp>
// operator*(const _Tp& __x, const Complex<_Tp>& __y) {
//   Complex<_Tp> out = __y;
//   out *= __x;
//   return out;
// }
// //@}

// //@{
// // Return new complex value @a x divided by @a y.
// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14 Complex<_Tp>
// operator/(const Complex<_Tp>& __x, const Complex<_Tp>& __y) {
//   Complex<_Tp> out = __x;
//   out /= __y;
//   return out;
// }

// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14 Complex<_Tp>
// operator/(const Complex<_Tp>& __x, const _Tp& __y) {
//   Complex<_Tp> out = __x;
//   out /= __y;
//   return out;
// }

// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14 Complex<_Tp>
// operator/(const _Tp& __x, const Complex<_Tp>& __y) {
//   const _Tp __r = -__x * __y.imag();
//   const _Tp __i =  __x * __y.real();
//   const _Tp __n = __y.real() * __y.real() + __y.imag() * __y.imag();
//   return Complex<_Tp>(__r / __n, __i / __n);
// }
// //@}

// // Return @a x.
// template<typename _Tp>
// inline constexpr Complex<_Tp>
// operator+(const Complex<_Tp>& __x) { return __x; }

// // Return complex negation of @a x.
// template<typename _Tp>
// inline constexpr Complex<_Tp>
// operator-(const Complex<_Tp>& __x) {
//   return Complex<_Tp>(-__x.real(), -__x.imag());
// }

// //@{
// // Return true if @a x is equal to @a y.
// template<typename _Tp>
// inline constexpr bool
// operator==(const Complex<_Tp>& __x, const Complex<_Tp>& __y) {
//   return __x.real() == __y.real() && __x.imag() == __y.imag();
// }

// template<typename _Tp>
// inline constexpr bool
// operator==(const Complex<_Tp>& __x, const _Tp& __y) {
//   return __x.real() == __y && __x.imag() == _Tp();
// }

// template<typename _Tp>
// inline constexpr bool
// operator==(const _Tp& __x, const Complex<_Tp>& __y) {
//   return __x == __y.real() && _Tp() == __y.imag();
// }
// //@}

// //@{
// // Return false if @a x is equal to @a y.
// template<typename _Tp>
// inline constexpr bool
// operator!=(const Complex<_Tp>& __x, const Complex<_Tp>& __y) {
//   return __x.real() != __y.real() || __x.imag() != __y.imag();
// }

// template<typename _Tp>
// inline constexpr bool
// operator!=(const Complex<_Tp>& __x, const _Tp& __y) {
//   return __x.real() != __y || __x.imag() != _Tp();
// }

// template<typename _Tp>
// inline constexpr bool
// operator!=(const _Tp& __x, const Complex<_Tp>& __y) {
//   return __x != __y.real() || _Tp() != __y.imag();
// }
// //@}

// // Extraction operator for complex values.
// template<typename _Tp, typename _CharT, class _Traits>
// std::basic_istream<_CharT, _Traits>& operator>>(
//     std::basic_istream<_CharT, _Traits>& __is, Complex<_Tp>& __x) {
//   bool __fail = true;
//   _CharT __ch;
//   if (__is >> __ch) {
//     if (_Traits::eq(__ch, __is.widen('('))) {
//       _Tp __u;
//       if (__is >> __u >> __ch) {
//         const _CharT __rparen = __is.widen(')');
//         if (_Traits::eq(__ch, __rparen)) {
//           __x = __u;
//           __fail = false;
//         }
//         else if (_Traits::eq(__ch, __is.widen(','))) {
//           _Tp __v;
//           if (__is >> __v >> __ch) {
//             if (_Traits::eq(__ch, __rparen)) {
//               __x = Complex<_Tp>(__u, __v);
//               __fail = false;
//             } else { __is.putback(__ch); }
//           }
//         } else { __is.putback(__ch); }
//       }
//     } else {
//       __is.putback(__ch);
//       _Tp __u;
//       if (__is >> __u) {
//         __x = __u;
//         __fail = false;
//       }
//     }
//   }
//   if (__fail) { __is.setstate(std::ios_base::failbit); }

//   return __is;
// }

// // Insertion operator for complex values.
// template<typename _Tp, typename _CharT, class _Traits>
// std::basic_ostream<_CharT, _Traits>& operator<<(
//     std::basic_ostream<_CharT, _Traits>& __os, const Complex<_Tp>& __x) {
//   std::basic_ostringstream<_CharT, _Traits> __s;
//   __s.flags(__os.flags());
//   __s.imbue(__os.getloc());
//   __s.precision(__os.precision());
//   __s << '(' << __x.real() << ',' << __x.imag() << ')';
//   return __os << __s.str();
// }

// template<typename _Tp>
// inline constexpr _Tp real(const Complex<_Tp>& __z) { return __z.real(); }

// template<typename _Tp>
// inline constexpr _Tp imag(const Complex<_Tp>& __z) { return __z.imag(); }

// template<typename _Tp>
// inline _Tp abs(const Complex<_Tp>& __z) {
//   return std::abs(CAST_STL_CONST(__z));
// }

// template<typename _Tp>
// inline _Tp arg(const Complex<_Tp>& __z) {
//   return std::arg(CAST_STL_CONST(__z));
// }

// template<typename _Tp>
// inline constexpr _Tp norm(const Complex<_Tp>& __z) {
//   return __z.real() * __z.real() + __z.imag() * __z.imag();
// }

// template<typename _Tp>
// inline constexpr Complex<_Tp> conj(const Complex<_Tp>& __z) {
//   return Complex<_Tp>(__z.real(), -__z.imag());
// }

// template<typename _Tp>
// inline Complex<_Tp> proj(const Complex<_Tp>& __z) {
//   return CAST_BACK(std::proj(CAST_STL_CONST(__z)));
// }

// template<typename _Tp>
// inline Complex<_Tp> polar(const _Tp& __rho, const _Tp& __theta = 0) {
//   return CAST_BACK(std::polar(__rho, __theta));
// }

// template<typename _Tp>
// inline Complex<_Tp> exp(const Complex<_Tp>& __z) {
//   return CAST_BACK(std::exp(CAST_STL_CONST(__z)));
// }

// template<typename _Tp>
// inline Complex<_Tp> log(const Complex<_Tp>& __z) {
//   return CAST_BACK(std::log(CAST_STL_CONST(__z)));
// }

// template<typename _Tp>
// inline Complex<_Tp> log10(const Complex<_Tp>& __z) {
//   return CAST_BACK(std::log10(CAST_STL_CONST(__z)));
// }

// template<typename _Tp>
// inline Complex<_Tp> pow(const Complex<_Tp>& __z, int __n) {
//   return CAST_BACK(std::pow(CAST_STL_CONST(__z), __n));
// }

// template<typename _Tp>
// inline Complex<_Tp> pow(const Complex<_Tp>& __x, const _Tp& __y) {
//   return CAST_BACK(std::pow(CAST_STL_CONST(__x), __y));
// }

// template<typename _Tp>
// inline Complex<_Tp> pow(const Complex<_Tp>& __x, const Complex<_Tp>& __y) {
//   return CAST_BACK(std::pow(CAST_STL_CONST(__x), CAST_STL_CONST(__y)));
// }

// template<typename _Tp>
// inline Complex<_Tp> pow(const _Tp& __x, const Complex<_Tp>& __y) {
//   return CAST_BACK(std::pow(__x, CAST_STL_CONST(__y)));
// }

// template<typename _Tp>
// inline Complex<_Tp> sqrt(const Complex<_Tp>& __z) {
//   return CAST_BACK(std::sqrt(CAST_STL_CONST(__z)));
// }

// template<typename _Tp>
// inline Complex<_Tp> sin(const Complex<_Tp>& __z) {
//   return CAST_BACK(std::sin(CAST_STL_CONST(__z)));
// }

// template<typename _Tp>
// inline Complex<_Tp> cos(const Complex<_Tp>& __z) {
//   return CAST_BACK(std::cos(CAST_STL_CONST(__z)));
// }

// template<typename _Tp>
// inline Complex<_Tp> tan(const Complex<_Tp>& __z) {
//   return CAST_BACK(std::tan(CAST_STL_CONST(__z)));
// }

// template<typename _Tp>
// inline Complex<_Tp> asin(const Complex<_Tp>& __z) {
//   return CAST_BACK(std::asin(CAST_STL_CONST(__z)));
// }

// template<typename _Tp>
// inline Complex<_Tp> acos(const Complex<_Tp>& __z) {
//   return CAST_BACK(std::acos(CAST_STL_CONST(__z)));
// }

// template<typename _Tp>
// inline Complex<_Tp> atan(const Complex<_Tp>& __z) {
//   return CAST_BACK(std::atan(CAST_STL_CONST(__z)));
// }

// template<typename _Tp>
// inline Complex<_Tp> sinh(const Complex<_Tp>& __z) {
//   return CAST_BACK(std::sinh(CAST_STL_CONST(__z)));
// }

// template<typename _Tp>
// inline Complex<_Tp> cosh(const Complex<_Tp>& __z) {
//   return CAST_BACK(std::cosh(CAST_STL_CONST(__z)));
// }

// template<typename _Tp>
// inline Complex<_Tp> tanh(const Complex<_Tp>& __z) {
//   return CAST_BACK(std::tanh(CAST_STL_CONST(__z)));
// }

// template<typename _Tp>
// inline Complex<_Tp> asinh(const Complex<_Tp>& __z) {
//   return CAST_BACK(std::asinh(CAST_STL_CONST(__z)));
// }

// template<typename _Tp>
// inline Complex<_Tp> acosh(const Complex<_Tp>& __z) {
//   return CAST_BACK(std::acosh(CAST_STL_CONST(__z)));
// }

// template<typename _Tp>
// inline Complex<_Tp> atanh(const Complex<_Tp>& __z) {
//   return CAST_BACK(std::atanh(CAST_STL_CONST(__z)));
// }


/* -------------------- Class for pure imaginary number. -------------------- */
template<typename _Tp>
struct Imag : public Complex<_Tp>
{
  constexpr Imag(const _Tp __i): Complex<_Tp>::Complex(_Tp(0), __i) { }

  // Let the compiler synthesize the copy constructor and move constructor.
  constexpr Imag(const Imag&) = default;
  constexpr Imag(Imag&&) = default;

//   // Assign another imaginary number to this one.
//   template<typename _Up>
//   SQUEEZE_CONSTEXPR14 Imag<_Tp>& operator=(const Imag<_Up>& __z) {
//     _M_imag = __z._M_imag;
//     return *this;
//   }
//   // Add another imaginary number to this one.
//   template<typename _Up>
//   SQUEEZE_CONSTEXPR14 Imag<_Tp>& operator+=(const Imag<_Up>& __z) {
//     _M_imag += __z._M_imag;
//     return *this;
//   }
//   // Subtract another complex number from this one.
//   template<typename _Up>
//   SQUEEZE_CONSTEXPR14 Imag<_Tp>& operator-=(const Imag<_Up>& __z) {
//     _M_imag -= __z._M_imag;
//     return *this;
//   }
//   // Multiply this imaginary number by a scalar.
//   SQUEEZE_CONSTEXPR14 Imag<_Tp>& operator*=(const _Tp& __t) {
//     _M_imag *= __t;
//     return *this;
//   }
//   // Divide this imaginary number by a scalar.
//   SQUEEZE_CONSTEXPR14 Imag<_Tp>& operator/=(const _Tp& __t) {
//     _M_imag /= __t;
//     return *this;
//   }

//   // Let the compiler synthesize the copy/move assignment operator.
//   constexpr Imag& operator=(const Imag&) = default;
//   constexpr Imag& operator=(Imag&&) = default;
};

// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14
// Imag<_Tp> operator+(const Imag<_Tp>& __x, const Imag<_Tp>& __y) {
//   Imag<_Tp> out = __x;
//   out += __y;
//   return out;
// }

// template<typename _Tp>
// inline constexpr
// Imag<_Tp> operator+(const Imag<_Tp> __i) {
//   return __i;
// }

// template<typename _Tp>
// inline constexpr
// Imag<_Tp> operator-(const Imag<_Tp> __i) {
//   return -__i;
// }

// template<typename _Tp>
// inline constexpr
// Complex<_Tp> operator+(const _Tp& __r, const Imag<_Tp>& __i) {
//   return Complex<_Tp>(__r, __i);
// }

// template<typename _Tp>
// inline constexpr
// Complex<_Tp> operator+(const Imag<_Tp>& __i, const _Tp& __r) {
//   return Complex<_Tp>(__r, __i);
// }

// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14
// Imag<_Tp> operator-(const Imag<_Tp>& __x, const Imag<_Tp>& __y) {
//   Imag<_Tp> out = __x;
//   out -= __y;
//   return out;
// }

// template<typename _Tp>
// inline constexpr
// Complex<_Tp> operator-(const _Tp& __r, const Imag<_Tp>& __i) {
//   return Complex<_Tp>(__r, -__i);
// }

// template<typename _Tp>
// inline constexpr
// Complex<_Tp> operator-(const Imag<_Tp>& __i, const _Tp& __r) {
//   return Complex<_Tp>(-__r, __i);
// }

// template<typename _Tp>
// inline constexpr
// _Tp operator*(const Imag<_Tp>& __x, const Imag<_Tp>& __y) {
//   return -__x.imag() * __y.imag();
// }

// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14
// Imag<_Tp> operator*(const _Tp& __r, const Imag<_Tp>& __i) {
//   Imag<_Tp> out = __i;
//   out *= __r;
//   return out;
// }

// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14
// Imag<_Tp> operator*(const Imag<_Tp>& __i, const _Tp& __r) {
//   Imag<_Tp> out = __i;
//   out *= __r;
//   return out;
// }

// template<typename _Tp>
// inline constexpr
// _Tp operator/(const Imag<_Tp>& __x, const Imag<_Tp>& __y) {
//   return __x.imag() / __y.imag();
// }

// template<typename _Tp>
// inline constexpr
// Imag<_Tp> operator/(const _Tp& __r, const Imag<_Tp>& __i) {
//   return Imag<_Tp>(-__r / __i.imag());
// }

// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14
// Imag<_Tp> operator/(const Imag<_Tp>& __i, const _Tp& __r) {
//   Imag<_Tp> out = __i;
//   out /= __r;
//   return out;
// }

// inline constexpr
// __I operator+(__I i) { return i; }

// inline constexpr
// __In operator+(__In i) { return i; }

// inline constexpr
// __In operator-(__I) { return __In(); }

// inline constexpr
// __I operator-(__In) { return __I(); }

// template<typename _Tp>
// inline constexpr
// Imag<_Tp> operator*(const _Tp& __r, __I) {
//   return Imag<_Tp>(__r);
// }

// template<typename _Tp>
// inline constexpr
// Imag<_Tp> operator*(const _Tp& __r, __In) {
//   return Imag<_Tp>(-__r);
// }

// template<typename _Tp>
// inline constexpr
// Imag<_Tp> operator*(__I, const _Tp& __r) {
//   return Imag<_Tp>(__r);
// }

// template<typename _Tp>
// inline constexpr
// Imag<_Tp> operator*(__In, const _Tp& __r) {
//   return Imag<_Tp>(-__r);
// }

// template<typename _Tp>
// inline constexpr
// _Tp operator*(const Imag<_Tp>& __i, __I) {
//   return -__i.imag();
// }

// template<typename _Tp>
// inline constexpr
// _Tp operator*(const Imag<_Tp>& __i, __In) {
//   return __i.imag();
// }

// template<typename _Tp>
// inline constexpr
// _Tp operator*(__I, const Imag<_Tp>& __i) {
//   return -__i.imag();
// }

// template<typename _Tp>
// inline constexpr
// _Tp operator*(__In, const Imag<_Tp>& __i) {
//   return __i.imag();
// }

// template<typename _Tp>
// inline constexpr
// Complex<_Tp> operator*(__I, const Complex<_Tp>& __x) {
//   return Complex<_Tp>(-__x.imag(), __x.real());
// }

// template<typename _Tp>
// inline constexpr
// Complex<_Tp> operator*(__In, const Complex<_Tp>& __x) {
//   return Complex<_Tp>(__x.imag(), -__x.real());
// }

// template<typename _Tp>
// inline constexpr
// Complex<_Tp> operator*(const Complex<_Tp>& __x, __I) {
//   return Complex<_Tp>(-__x.imag(), __x.real());
// }

// template<typename _Tp>
// inline constexpr
// Complex<_Tp> operator*(const Complex<_Tp>& __x, __In) {
//   return Complex<_Tp>(__x.imag(), -__x.real());
// }

// template<typename _Tp>
// inline constexpr
// Imag<_Tp> operator/(const _Tp& __r, __I) {
//   return Imag<_Tp>(-__r);
// }

// template<typename _Tp>
// inline constexpr
// Imag<_Tp> operator/(const _Tp& __r, __In) {
//   return Imag<_Tp>(__r);
// }

// template<typename _Tp>
// inline constexpr
// Imag<_Tp> operator/(__I, const _Tp& __r) {
//   return Imag<_Tp>(_Tp(1)/__r);
// }

// template<typename _Tp>
// inline constexpr
// Imag<_Tp> operator/(__In, const _Tp& __r) {
//   return Imag<_Tp>(-_Tp(1)/__r);
// }

// template<typename _Tp>
// inline constexpr
// _Tp operator/(const Imag<_Tp>& __i, __I) {
//   return __i.imag();
// }

// template<typename _Tp>
// inline constexpr
// _Tp operator/(const Imag<_Tp>& __i, __In) {
//   return -__i.imag();
// }

// template<typename _Tp>
// inline constexpr
// _Tp operator/(__I, const Imag<_Tp>& __i) {
//   return _Tp(1) / __i.imag();
// }

// template<typename _Tp>
// inline constexpr
// _Tp operator/(__In, const Imag<_Tp>& __i) {
//   return -_Tp(1) / __i.imag();
// }

// template<typename _Tp>
// inline constexpr
// Complex<_Tp> operator/(const Complex<_Tp>& __x, __I) {
//   return Complex<_Tp>(__x.imag(), -__x.real());
// }

// template<typename _Tp>
// inline constexpr
// Complex<_Tp> operator/(const Complex<_Tp>& __x, __In) {
//   return Complex<_Tp>(-__x.imag(), __x.real());
// }

// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14
// Complex<_Tp> operator/(__I, const Complex<_Tp>& __x) {
//   Complex<_Tp> out = Imag<_Tp>(1);
//   out /= __x;
//   return out;
// }

// template<typename _Tp>
// inline SQUEEZE_CONSTEXPR14
// Complex<_Tp> operator/(__In, const Complex<_Tp>& __x) {
//   Complex<_Tp> out = Imag<_Tp>(-1);
//   out /= __x;
//   return out;
// }


// /*********** specializations ************/
// template<>
// alignas(16) class Complex<double> {
//  private:
//   double _M_value[2];

//  public:
//   using value_type = double;

//   // Default constructor.  First parameter is re, second parameter is im.
//   // Unspecified parameters default to 0.
//   constexpr Complex(double __r = 0, double __i = 0) : _M_value{__r, __i} { }

//   // Let the compiler synthesize the copy constructor and move constructor.
//   constexpr Complex(const Complex&) = default;
//   constexpr Complex(Complex&&) = default;

//   // Cast from std::complex.
//   constexpr Complex(const std::complex<double>& __z)
//       : _M_value{__z.real(), __z.imag()} { }
//   // Cast from imaginary unit
//   constexpr Complex(__I) : _M_value{0, 1} { }
//   // Cast from nagative imaginary unit
//   constexpr Complex(__In) : _M_value{0, -1} { }

//   // Converting constructor.
//   template<typename _Up> constexpr Complex(const Complex<_Up>& __z)
//       : _M_value{__z.real(), __z.imag()} { }

//   // Return real part of complex number.
//   constexpr double real() const { return _M_value[0]; }
//   // Return imaginary part of complex number.
//   constexpr double imag() const { return _M_value[1]; }

//   SQUEEZE_CONSTEXPR14 void real(double __val) { _M_value[0] = __val; }
//   SQUEEZE_CONSTEXPR14 void imag(double __val) { _M_value[1] = __val; }

//   // Assign a scalar to this complex number.
//   SQUEEZE_CONSTEXPR14 Complex<double>& operator=(double __t) {
//     _M_value[0] = __t;
//     return *this;
//   }
//   // Add a scalar to this complex number.
//   SQUEEZE_CONSTEXPR14 Complex<double>& operator+=(double __t) {
//     _M_value[0] += __t;
//     return *this;
//   }
//   // Subtract a scalar to this complex number.
//   SQUEEZE_CONSTEXPR14 Complex<double>& operator-=(double __t) {
//     _M_value[0] -= __t;
//     return *this;
//   }
//   // Multiply this complex number by a scalar.
//   SQUEEZE_CONSTEXPR14 Complex<double>& operator*=(double __t) {
//     _M_value[0] *= __t;
//     _M_value[1] *= __t;
//     return *this;
//   }
//   // Divide this complex number by a scalar.
//   SQUEEZE_CONSTEXPR14 Complex<double>& operator/=(double __t) {
//     _M_value[0] /= __t;
//     _M_value[1] /= __t;
//     return *this;
//   }

//   // Let the compiler synthesize the copy/move assignment operator.
//   constexpr Complex& operator=(const Complex&) = default;
//   constexpr Complex& operator=(Complex&&) = default;

//   // Assign another complex number to this one.
//   template<typename _Up>
//   SQUEEZE_CONSTEXPR14 Complex<double>& operator=(const Complex<_Up>& __z) {
//     _M_value[0] = __z._M_value[0];
//     _M_value[1] = __z._M_value[1];
//     return *this;
//   }
//   // Add another complex number to this one.
//   template<typename _Up>
//   SQUEEZE_CONSTEXPR14 Complex<double>& operator+=(const Complex<_Up>& __z) {
//     _M_value[0] += __z._M_value[0];
//     _M_value[1] += __z._M_value[1];
//     return *this;
//   }
//   // Subtract another complex number from this one.
//   template<typename _Up>
//   SQUEEZE_CONSTEXPR14 Complex<double>& operator-=(const Complex<_Up>& __z) {
//     _M_value[0] -= __z._M_value[0];
//     _M_value[1] -= __z._M_value[1];
//     return *this;
//   }
//   // Multiply this complex number by another.
//   template<typename _Up>
//   SQUEEZE_CONSTEXPR14 Complex<double>& operator*=(const Complex<_Up>& __z) {
//     const double __r = _M_value[0] * __z.real() - _M_value[1] * __z.imag();
//     _M_value[1] = _M_value[0] * __z.imag() + _M_value[1] * __z.real();
//     _M_value[0] = __r;
//     return *this;
//   }
//   // Divide this complex number by another.
//   template<typename _Up>
//   SQUEEZE_CONSTEXPR14 Complex<double>& operator/=(const Complex<_Up>& __z) {
//     const double __r =  _M_value[0] * __z.real() + _M_value[1] * __z.imag();
//     const double __n = __z.real() * __z.real() + __z.imag() * __z.imag();
//     _M_value[1] = (_M_value[1] * __z.real() - _M_value[0] * __z.imag())
//                  / __n;
//     _M_value[0] = __r / __n;
//     return *this;
//   }
// };


/* ------- operators between complex and scalar with defferent types -------- */
template<class _Sca, class _Tp, internal::IdxIfSca<_Sca> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
Complex<_Tp> operator+(const _Sca& a, const Complex<_Tp>& c) {
  return static_cast<_Tp>(a) + c;
}

template<class _Tp, class _Sca, internal::IdxIfSca<_Sca> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
Complex<_Tp> operator+(const Complex<_Tp>& c, const _Sca& a) {
  return c + static_cast<_Tp>(a);
}

template<class _Sca, class _Tp, internal::IdxIfSca<_Sca> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
Complex<_Tp> operator-(const _Sca& a, const Complex<_Tp>& c) {
  return static_cast<_Tp>(a) - c;
}

template<class _Tp, class _Sca, internal::IdxIfSca<_Sca> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
Complex<_Tp> operator-(const Complex<_Tp>& c, const _Sca& a) {
  return c - static_cast<_Tp>(a);
}

template<class _Sca, class _Tp, internal::IdxIfSca<_Sca> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
Complex<_Tp> operator*(const _Sca& a, const Complex<_Tp>& c) {
  return static_cast<_Tp>(a) * c;
}

template<class _Tp, class _Sca, internal::IdxIfSca<_Sca> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
Complex<_Tp> operator*(const Complex<_Tp>& c, const _Sca& a) {
  return c * static_cast<_Tp>(a);
}

template<class _Sca, class _Tp, internal::IdxIfSca<_Sca> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
Complex<_Tp> operator/(const _Sca& a, const Complex<_Tp>& c) {
  return static_cast<_Tp>(a) / c;
}

template<class _Tp, class _Sca, internal::IdxIfSca<_Sca> = 0>
SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE
Complex<_Tp> operator/(const Complex<_Tp>& c, const _Sca& a) {
  return c / static_cast<_Tp>(a);
}


/* ------------------------- output in format a+bi -------------------------- */
template<class _Tp>
std::ostream& operator<<(std::ostream& os, const Complex<_Tp>& c) {
  return os << c.real() << (c.imag() < 0 ? '-' : '+') << c.imag() << 'i';
}


// #undef CAST_STL
// #undef CAST_STL_CONST
// #undef CAST_BACK
} // namespace Squeeze
#endif // include guard
