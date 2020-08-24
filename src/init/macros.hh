/*
    init/macros.hh: Define some fundamental macros for Squeeze.

    Author: Kaixiang Huang <kxhuang@whu.edu.cn>.

    This file is modified from part of Eigen, a lightweight C++ template library
    for linear algebra under MPLv2 license.
*/

#ifndef SQUEEZE_MACROS_HH
#define SQUEEZE_MACROS_HH

#include <cstdlib>

#ifdef SQUEEZE_DEFAULT_TO_ROW_MAJOR
  #define SQUEEZE_DEFAULT_MATRIX_STORAGE_ORDER Squeeze::RowMajor
#else
  #define SQUEEZE_DEFAULT_MATRIX_STORAGE_ORDER Squeeze::ColMajor
#endif

#ifndef SQUEEZE_INDEX_TYPE
  #define SQUEEZE_INDEX_TYPE std::ptrdiff_t
#endif

/** Allows to disable some optimizations
  * which might affect the accuracy of the result.
  * Such optimizations are enabled by default,
  * and set SQUEEZE_FAST_MATH to 0 to disable them.
  * They currently include:
  *   - single precision ArrayBase::sin() and ArrayBase::cos()
  *     for SSE and AVX vectorization.
  */
#ifndef SQUEEZE_FAST_MATH
  #define SQUEEZE_FAST_MATH 1
#endif

#ifndef SQUEEZE_STACK_ALLOCATION_LIMIT
  // 131072 == 128 KB
  #define SQUEEZE_STACK_ALLOCATION_LIMIT 131072
#endif

#ifdef NDEBUG
  #ifdef SQUEEZE_HAS_DEBUG
    #undef SQUEEZE_HAS_DEBUG
  #endif
#endif

//-----------------------------------------------------------------------------
// Compiler identification, SQUEEZE_COMP_*
//-----------------------------------------------------------------------------

/// \internal SQUEEZE_COMP_GNUC set to 1 for all compilers compatible with GCC
#ifdef __GNUC__
  #define SQUEEZE_COMP_GNUC (__GNUC__*10+__GNUC_MINOR__)
#else
  #define SQUEEZE_COMP_GNUC 0
#endif

/// \internal SQUEEZE_COMP_CLANG set to major+minor version
///           (e.g., 307 for clang 3.7) if the compiler is clang
#if defined(__clang__)
  #define SQUEEZE_COMP_CLANG (__clang_major__*100+__clang_minor__)
#else
  #define SQUEEZE_COMP_CLANG 0
#endif


/// \internal SQUEEZE_COMP_LLVM set to 1 if the compiler backend is llvm
#if defined(__llvm__)
  #define SQUEEZE_COMP_LLVM 1
#else
  #define SQUEEZE_COMP_LLVM 0
#endif

/// \internal SQUEEZE_COMP_ICC set to __INTEL_COMPILER
///           if the compiler is Intel compiler, 0 otherwise
#if defined(__INTEL_COMPILER)
  #define SQUEEZE_COMP_ICC __INTEL_COMPILER
#else
  #define SQUEEZE_COMP_ICC 0
#endif

/// \internal SQUEEZE_COMP_MINGW set to 1 if the compiler is mingw
#if defined(__MINGW32__)
  #define SQUEEZE_COMP_MINGW 1
#else
  #define SQUEEZE_COMP_MINGW 0
#endif

/// \internal SQUEEZE_COMP_SUNCC set to 1 if the compiler is Solaris Studio
#if defined(__SUNPRO_CC)
  #define SQUEEZE_COMP_SUNCC 1
#else
  #define SQUEEZE_COMP_SUNCC 0
#endif

/// \internal SQUEEZE_COMP_MSVC set to _MSC_VER
///           if the compiler is Microsoft Visual C++, 0 otherwise.
#if defined(_MSC_VER)
  #define SQUEEZE_COMP_MSVC _MSC_VER
#else
  #define SQUEEZE_COMP_MSVC 0
#endif

#if defined(__NVCC__)
#if defined(__CUDACC_VER_MAJOR__) && (__CUDACC_VER_MAJOR__ >= 9)
  #define SQUEEZE_COMP_NVCC  ((__CUDACC_VER_MAJOR__ * 10000) + \
                              (__CUDACC_VER_MINOR__ * 100))
#elif defined(__CUDACC_VER__)
  #define SQUEEZE_COMP_NVCC __CUDACC_VER__
#else
  #error "NVCC did not define compiler version."
#endif
#else
  #define SQUEEZE_COMP_NVCC 0
#endif

// For the record, here is a table summarizing
// the possible values for SQUEEZE_COMP_MSVC:
//  name        ver   MSC_VER
//  2015        14      1900
//  "15"        15      1900
//  2017-14.1   15.0    1910
//  2017-14.11  15.3    1911
//  2017-14.12  15.5    1912
//  2017-14.13  15.6    1913
//  2017-14.14  15.7    1914
//  2019-14.20  16.7    1920
//  2019-14.21  16.1    1921
//  2019-14.22  16.2    1922
//  2019-14.23  16.3    1923

/// \internal SQUEEZE_COMP_MSVC_LANG set to _MSVC_LANG
///           if the compiler is Microsoft Visual C++, 0 otherwise.
#if defined(_MSVC_LANG)
  #define SQUEEZE_COMP_MSVC_LANG _MSVC_LANG
#else
  #define SQUEEZE_COMP_MSVC_LANG 0
#endif

// For the record, here is a table summarizing
// the possible values for SQUEEZE_COMP_MSVC_LANG:
// MSVC option                          Standard  MSVC_LANG
// /std:c++14 (default as of VS 2019)   C++14     201402L
// /std:c++17                           C++17     201703L
// /std:c++latest                       >C++17    >201703L

/// \internal SQUEEZE_COMP_MSVC_STRICT set to 1
///           if the compiler is really Microsoft Visual C++
///           and not, e.g., ICC or clang-cl
#if SQUEEZE_COMP_MSVC && !(SQUEEZE_COMP_ICC || SQUEEZE_COMP_LLVM || \
                           SQUEEZE_COMP_CLANG)
  #define SQUEEZE_COMP_MSVC_STRICT _MSC_VER
#else
  #define SQUEEZE_COMP_MSVC_STRICT 0
#endif

/// \internal SQUEEZE_COMP_IBM set to xlc version if the compiler is IBM XL C++
// XLC   version
// 3.1   0x0301
// 4.5   0x0405
// 5.0   0x0500
// 12.1  0x0C01
#if defined(__IBMCPP__) || defined(__xlc__) || defined(__ibmxl__)
  #define SQUEEZE_COMP_IBM __xlC__
#else
  #define SQUEEZE_COMP_IBM 0
#endif

/// \internal SQUEEZE_COMP_PGI set to PGI version
///           if the compiler is Portland Group Compiler
#if defined(__PGI)
  #define SQUEEZE_COMP_PGI (__PGIC__*100+__PGIC_MINOR__)
#else
  #define SQUEEZE_COMP_PGI 0
#endif

/// \internal SQUEEZE_COMP_ARM set to 1 if the compiler is ARM Compiler
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
  #define SQUEEZE_COMP_ARM 1
#else
  #define SQUEEZE_COMP_ARM 0
#endif

/// \internal SQUEEZE_COMP_ARM set to 1 if the compiler is ARM Compiler
#if defined(__EMSCRIPTEN__)
  #define SQUEEZE_COMP_EMSCRIPTEN 1
#else
  #define SQUEEZE_COMP_EMSCRIPTEN 0
#endif


/// \internal SQUEEZE_GNUC_STRICT set to 1 if the compiler is really GCC
///           and not a compatible compiler (e.g., ICC, clang, mingw, etc.)
#if SQUEEZE_COMP_GNUC && !(SQUEEZE_COMP_CLANG || SQUEEZE_COMP_ICC || \
    SQUEEZE_COMP_PGI || SQUEEZE_COMP_IBM || SQUEEZE_COMP_ARM ||      \
    SQUEEZE_COMP_EMSCRIPTEN)
  #define SQUEEZE_COMP_GNUC_STRICT 1
#else
  #define SQUEEZE_COMP_GNUC_STRICT 0
#endif


//-----------------------------------------------------------------------------
// Architecture identification, SQUEEZE_ARCH_*
//-----------------------------------------------------------------------------


#if defined(__x86_64__) || defined(_M_X64) || defined(__amd64)
  #define SQUEEZE_ARCH_x86_64 1
#else
  #define SQUEEZE_ARCH_x86_64 0
#endif

#if defined(__i386__) || defined(_M_IX86) || defined(_X86_) || defined(__i386)
  #define SQUEEZE_ARCH_i386 1
#else
  #define SQUEEZE_ARCH_i386 0
#endif

#if SQUEEZE_ARCH_x86_64 || SQUEEZE_ARCH_i386
  #define SQUEEZE_ARCH_i386_OR_x86_64 1
#else
  #define SQUEEZE_ARCH_i386_OR_x86_64 0
#endif

/// \internal SQUEEZE_ARCH_ARM set to 1 if the architecture is ARM
#if defined(__arm__)
  #define SQUEEZE_ARCH_ARM 1
#else
  #define SQUEEZE_ARCH_ARM 0
#endif

/// \internal SQUEEZE_ARCH_ARM64 set to 1 if the architecture is ARM64
#if defined(__aarch64__)
  #define SQUEEZE_ARCH_ARM64 1
#else
  #define SQUEEZE_ARCH_ARM64 0
#endif

#if SQUEEZE_ARCH_ARM || SQUEEZE_ARCH_ARM64
  #define SQUEEZE_ARCH_ARM_OR_ARM64 1
#else
  #define SQUEEZE_ARCH_ARM_OR_ARM64 0
#endif

/// \internal SQUEEZE_ARCH_MIPS set to 1 if the architecture is MIPS
#if defined(__mips__) || defined(__mips)
  #define SQUEEZE_ARCH_MIPS 1
#else
  #define SQUEEZE_ARCH_MIPS 0
#endif

/// \internal SQUEEZE_ARCH_SPARC set to 1 if the architecture is SPARC
#if defined(__sparc__) || defined(__sparc)
  #define SQUEEZE_ARCH_SPARC 1
#else
  #define SQUEEZE_ARCH_SPARC 0
#endif

/// \internal SQUEEZE_ARCH_IA64 set to 1 if the architecture is Intel Itanium
#if defined(__ia64__)
  #define SQUEEZE_ARCH_IA64 1
#else
  #define SQUEEZE_ARCH_IA64 0
#endif

/// \internal SQUEEZE_ARCH_PPC set to 1 if the architecture is PowerPC
#if defined(__powerpc__) || defined(__ppc__) || defined(_M_PPC)
  #define SQUEEZE_ARCH_PPC 1
#else
  #define SQUEEZE_ARCH_PPC 0
#endif



//-----------------------------------------------------------------------------
// Operating system identification, SQUEEZE_OS_*
//-----------------------------------------------------------------------------

/// \internal SQUEEZE_OS_UNIX set to 1 if the OS is a unix variant
#if defined(__unix__) || defined(__unix)
  #define SQUEEZE_OS_UNIX 1
#else
  #define SQUEEZE_OS_UNIX 0
#endif

/// \internal SQUEEZE_OS_LINUX set to 1 if the OS is based on Linux kernel
#if defined(__linux__)
  #define SQUEEZE_OS_LINUX 1
#else
  #define SQUEEZE_OS_LINUX 0
#endif

/// \internal SQUEEZE_OS_ANDROID set to 1 if the OS is Android
// note: ANDROID is defined when using ndk_build,
//       __ANDROID__ is defined when using a standalone toolchain.
#if defined(__ANDROID__) || defined(ANDROID)
  #define SQUEEZE_OS_ANDROID 1
#else
  #define SQUEEZE_OS_ANDROID 0
#endif

/// \internal SQUEEZE_OS_GNULINUX set to 1 if the OS is GNU Linux
#if defined(__gnu_linux__)
  #define SQUEEZE_OS_GNULINUX 1
#else
  #define SQUEEZE_OS_GNULINUX 0
#endif

/// \internal SQUEEZE_OS_BSD set to 1 if the OS is a BSD variant
#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || \
    defined(__bsdi__) || defined(__DragonFly__)
  #define SQUEEZE_OS_BSD 1
#else
  #define SQUEEZE_OS_BSD 0
#endif

/// \internal SQUEEZE_OS_MAC set to 1 if the OS is MacOS
#if defined(__APPLE__)
  #define SQUEEZE_OS_MAC 1
#else
  #define SQUEEZE_OS_MAC 0
#endif

/// \internal SQUEEZE_OS_QNX set to 1 if the OS is QNX
#if defined(__QNX__)
  #define SQUEEZE_OS_QNX 1
#else
  #define SQUEEZE_OS_QNX 0
#endif

/// \internal SQUEEZE_OS_WIN set to 1 if the OS is Windows based
#if defined(_WIN32)
  #define SQUEEZE_OS_WIN 1
#else
  #define SQUEEZE_OS_WIN 0
#endif

/// \internal SQUEEZE_OS_WIN64 set to 1 if the OS is Windows 64bits
#if defined(_WIN64)
  #define SQUEEZE_OS_WIN64 1
#else
  #define SQUEEZE_OS_WIN64 0
#endif

/// \internal SQUEEZE_OS_WINCE set to 1 if the OS is Windows CE
#if defined(_WIN32_WCE)
  #define SQUEEZE_OS_WINCE 1
#else
  #define SQUEEZE_OS_WINCE 0
#endif

/// \internal SQUEEZE_OS_CYGWIN set to 1 if the OS is Windows/Cygwin
#if defined(__CYGWIN__)
  #define SQUEEZE_OS_CYGWIN 1
#else
  #define SQUEEZE_OS_CYGWIN 0
#endif

/// \internal SQUEEZE_OS_WIN_STRICT set to 1
///           if the OS is really Windows and not some variants
#if SQUEEZE_OS_WIN && !( SQUEEZE_OS_WINCE || SQUEEZE_OS_CYGWIN )
  #define SQUEEZE_OS_WIN_STRICT 1
#else
  #define SQUEEZE_OS_WIN_STRICT 0
#endif

/// \internal SQUEEZE_OS_SUN set to __SUNPRO_C if the OS is SUN
#if (defined(sun) || defined(__sun)) && !(defined(__SVR4) || defined(__svr4__))
  #define SQUEEZE_OS_SUN __SUNPRO_C
#else
  #define SQUEEZE_OS_SUN 0
#endif

/// \internal SQUEEZE_OS_SOLARIS set to 1 if the OS is Solaris
#if (defined(sun) || defined(__sun)) && (defined(__SVR4) || defined(__svr4__))
  #define SQUEEZE_OS_SOLARIS 1
#else
  #define SQUEEZE_OS_SOLARIS 0
#endif


//-----------------------------------------------------------------------------
// Detect GPU compilers and architectures
//-----------------------------------------------------------------------------

// NVCC is not supported as the target platform for HIPCC
// Note that this also makes SQUEEZE_CUDACC and SQUEEZE_HIPCC mutually exclusive
#if defined(__NVCC__) && defined(__HIPCC__)
  #error "NVCC as the target platform for HIPCC is currently not supported."
#endif

#if defined(__CUDACC__) && !defined(SQUEEZE_NO_CUDA)
  // Means the compiler is either nvcc or clang with CUDA enabled
  #define SQUEEZE_CUDACC __CUDACC__
#endif

#if defined(__CUDA_ARCH__) && !defined(SQUEEZE_NO_CUDA)
  // Means we are generating code for the device
  #define SQUEEZE_CUDA_ARCH __CUDA_ARCH__
#endif

#if defined(SQUEEZE_CUDACC)
#include <cuda.h>
  #define SQUEEZE_CUDA_SDK_VER (CUDA_VERSION * 10)
#else
  #define SQUEEZE_CUDA_SDK_VER 0
#endif

#if defined(__HIPCC__) && !defined(SQUEEZE_NO_HIP)
  // Means the compiler is HIPCC (analogous to SQUEEZE_CUDACC, but for HIP)
  #define SQUEEZE_HIPCC __HIPCC__

  // We need to include hip_runtime.h here because it pulls in
  // ++ hip_common.h which contains the define for  __HIP_DEVICE_COMPILE__
  // ++ host_defines.h which contains the defines for __host__ and __device__
  #include <hip/hip_runtime.h>

  #if defined(__HIP_DEVICE_COMPILE__)
    // analogous to SQUEEZE_CUDA_ARCH, but for HIP
    #define SQUEEZE_HIP_DEVICE_COMPILE __HIP_DEVICE_COMPILE__
  #endif
#endif

// Unify CUDA/HIPCC

#if defined(SQUEEZE_CUDACC) || defined(SQUEEZE_HIPCC)
//
// If either SQUEEZE_CUDACC or SQUEEZE_HIPCC is defined,
// then define SQUEEZE_GPUCC
//
#define SQUEEZE_GPUCC
//
// SQUEEZE_HIPCC implies the HIP compiler
// and is used to tweak Squeeze code for use in HIP kernels
// SQUEEZE_CUDACC implies the CUDA compiler
// and is used to tweak Squeeze code for use in CUDA kernels
//
// In most cases the same tweaks are required to the Squeeze code
// to enable in both the HIP and CUDA kernels.
// For those cases, the corresponding code should be guarded with
//      #if defined(SQUEEZE_GPUCC)
// instead of
//      #if defined(SQUEEZE_CUDACC) || defined(SQUEEZE_HIPCC)
//
// For cases where the tweak is specific to HIP, the code should be guarded with
//      #if defined(SQUEEZE_HIPCC)
//
// For cases where the tweak is specific to CUDA,
// the code should be guarded with
//      #if defined(SQUEEZE_CUDACC)
//
#endif

#if defined(SQUEEZE_CUDA_ARCH) || defined(SQUEEZE_HIP_DEVICE_COMPILE)
//
// If either SQUEEZE_CUDA_ARCH or SQUEEZE_HIP_DEVICE_COMPILE is defined,
// then define SQUEEZE_GPU_COMPILE_PHASE
//
#define SQUEEZE_GPU_COMPILE_PHASE
//
// GPU compilers (HIPCC, NVCC) typically do two passes over the source code,
//   + one to compile the source for the "host" (ie CPU)
//   + another to compile the source for the "device" (ie. GPU)
//
// Code that needs to enabled only during
// either the "host" or "device" compilation phase
// needs to be guarded with a macro that indicates the current compilation phase
//
// SQUEEZE_HIP_DEVICE_COMPILE implies the device compilation phase in HIP
// SQUEEZE_CUDA_ARCH implies the device compilation phase in CUDA
//
// In most cases, the "host" / "device" specific code is the same
// for both HIP and CUDA
// For those cases, the code should be guarded with
//       #if defined(SQUEEZE_GPU_COMPILE_PHASE)
// instead of
//       #if defined(SQUEEZE_CUDA_ARCH) || defined(SQUEEZE_HIP_DEVICE_COMPILE)
//
// For cases where the tweak is specific to HIP, the code should be guarded with
//      #if defined(SQUEEZE_HIP_DEVICE_COMPILE)
//
// For cases where the tweak is specific to CUDA,
// the code should be guarded with
//      #if defined(SQUEEZE_CUDA_ARCH)
//
#endif

#if defined(SQUEEZE_USE_SYCL) && defined(__SYCL_DEVICE_ONLY__)
// SQUEEZE_USE_SYCL is a user-defined macro
// while __SYCL_DEVICE_ONLY__ is a compiler-defined macro.
// In most cases we want to check if both macros are defined
// which can be done using the define below.
#define SYCL_DEVICE_ONLY
#endif

//-----------------------------------------------------------------------------
// Preprocessor programming helpers
//-----------------------------------------------------------------------------

#define SQUEEZE_DEBUG_VAR(x) std::cerr << #x << " = " << x << std::endl;

// SQUEEZE_STRONG_INLINE is a stronger version of the inline,
// using __forceinline on MSVC, but it still doesn't use GCC's always_inline.
// This is useful in (common) situations where MSVC needs forceinline
// but GCC is still doing fine with just inline.
#ifndef SQUEEZE_STRONG_INLINE
  #if SQUEEZE_COMP_ICC
    #define SQUEEZE_STRONG_INLINE __forceinline
  #else
    #define SQUEEZE_STRONG_INLINE inline
  #endif
#endif

// SQUEEZE_ALWAYS_INLINE is the strongest,
// it has the effect of making the function inline and adding every possible
// attribute to maximize inlining.
// This should only be used when really necessary: in particular,
// it uses __attribute__((always_inline)) on GCC,
// which most of the time is useless and can severely harm compile times.
#if SQUEEZE_COMP_GNUC && !defined(SYCL_DEVICE_ONLY)
  #define SQUEEZE_ALWAYS_INLINE __attribute__((always_inline)) inline
#else
  #define SQUEEZE_ALWAYS_INLINE SQUEEZE_STRONG_INLINE
#endif

#if SQUEEZE_COMP_GNUC
  #define SQUEEZE_DONT_INLINE __attribute__((noinline))
#elif SQUEEZE_COMP_MSVC
  #define SQUEEZE_DONT_INLINE __declspec(noinline)
#else
  #define SQUEEZE_DONT_INLINE
#endif


#if (defined(__cplusplus) && (__cplusplus >= 201402L) || \
     SQUEEZE_COMP_MSVC >= 1910)
  #define SQUEEZE_CONSTEXPR14 constexpr
#else
  #define SQUEEZE_CONSTEXPR14 SQUEEZE_ALWAYS_INLINE
#endif

#if (defined(__cplusplus) && (__cplusplus >= 201703L) || \
     SQUEEZE_COMP_MSVC >= 1914)
  #define SQUEEZE_CONSTEXPR17 constexpr
  #define SQUEEZE_HAS_FOLD_EXPR 1
  #ifdef __USE_ISOC11
    #define SQUEEZE_HAS_ALIGNED_ALLOC 1
  #else
    #define SQUEEZE_HAS_ALIGNED_ALLOC 0
  #endif
#else
  #define SQUEEZE_CONSTEXPR17 SQUEEZE_ALWAYS_INLINE
  #define SQUEEZE_HAS_FOLD_EXPR 0
  #define SQUEEZE_HAS_ALIGNED_ALLOC 0
#endif

#if __cplusplus > 201703L
  #define SQUEEZE_CONSTEXPR20 constexpr
#else
  #define SQUEEZE_CONSTEXPR20 SQUEEZE_STRONG_INLINE
#endif
#if (defined(__cplusplus) && (__cplusplus < 201103L) || \
     (SQUEEZE_COMP_MSVC != 0 && SQUEEZE_COMP_MSVC < 1900) )
  #error Squeeze only supports C++ standard >= C++11 !!
#endif

#if defined(SQUEEZE_CUDACC) && SQUEEZE_HAS_CONSTEXPR
  // While available already with c++11,
  // this is useful mostly starting with c++14 and relaxed constexpr rules
  #if defined(__NVCC__)
    // nvcc considers constexpr functions as __host__ __device__
    // with the option --expt-relaxed-constexpr
    #ifdef __CUDACC_RELAXED_CONSTEXPR__
      #define SQUEEZE_CONSTEXPR_ARE_DEVICE_FUNC
    #endif
  #elif defined(__clang__) && defined(__CUDA__) && \
        __has_feature(cxx_relaxed_constexpr)
    // clang++ always considers constexpr functions
    // as implicitly __host__ __device__
    #define SQUEEZE_CONSTEXPR_ARE_DEVICE_FUNC
  #endif
#endif


// GPU stuff

// Disable some features when compiling with GPU compilers
// (NVCC/clang-cuda/SYCL/HIPCC)
#if defined(SQUEEZE_CUDACC) || defined(SYCL_DEVICE_ONLY) || \
    defined(SQUEEZE_HIPCC)
  // Do not try asserts on device code
  #ifndef SQUEEZE_NO_DEBUG
    #define SQUEEZE_NO_DEBUG
  #endif

  #ifdef SQUEEZE_INTERNAL_DEBUGGING
    #undef SQUEEZE_INTERNAL_DEBUGGING
  #endif

  #ifdef SQUEEZE_EXCEPTIONS
    #undef SQUEEZE_EXCEPTIONS
  #endif
#endif

#if defined(SYCL_DEVICE_ONLY)
  #ifndef SQUEEZE_DONT_VECTORIZE
    #define SQUEEZE_DONT_VECTORIZE
  #endif
  #define SQUEEZE_DEVICE_FUNC __attribute__((always_inline))
// All functions callable from CUDA/HIP code must be qualified with __device__
#elif defined(SQUEEZE_GPUCC)
    #define SQUEEZE_DEVICE_FUNC __host__ __device__
#else
  #define SQUEEZE_DEVICE_FUNC
#endif


// this macro allows to get rid of linking errors
// about multiply defined functions.
//  - static is not very good because it prevents
//    definitions from different object files to be merged.
//    So static causes the resulting linked executable to be bloated
//    with multiple copies of the same function.
//  - inline is not perfect either as it unwantedly
//    hints the compiler toward inlining the function.
#define SQUEEZE_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS \
  SQUEEZE_DEVICE_FUNC
#define SQUEEZE_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS \
  SQUEEZE_DEVICE_FUNC inline

#if SQUEEZE_COMP_GNUC
  #define SQUEEZE_UNUSED __attribute__((unused))
#else
  #define SQUEEZE_UNUSED
#endif

// Suppresses 'unused variable' warnings.
namespace Squeeze {
  namespace internal {
    template<class _T>
    SQUEEZE_DEVICE_FUNC SQUEEZE_STRONG_INLINE constexpr
    void ignore_unused_variable(const _T&) {}
  }
}
#define SQUEEZE_UNUSED_VARIABLE(var)              \
  Squeeze::internal::ignore_unused_variable(var);


// When compiling CUDA/HIP device code with NVCC or HIPCC
// pull in math functions from the global namespace.
// In host mode, and when device code is compiled with clang,
// use the std versions.
#if (defined(SQUEEZE_CUDA_ARCH) && defined(__NVCC__)) || \
     defined(SQUEEZE_HIP_DEVICE_COMPILE)
  #define SQUEEZE_USING_STD_MATH(FUNC) using ::FUNC;
#else
  #define SQUEEZE_USING_STD_MATH(FUNC) using std::FUNC;
#endif


// When compiling HIP device code with HIPCC, certain functions
// from the stdlib need to be pulled in from the global namespace
// (as opposed to from the std:: namespace). This is because HIPCC
// does not natively support all the std:: routines in device code.
// Instead it contains header files that declare the corresponding
// routines in the global namespace such they can be used in device code.
#if defined(SQUEEZE_HIP_DEVICE_COMPILE)
  #define SQUEEZE_USING_STD(FUNC) using ::FUNC;
#else
  #define SQUEEZE_USING_STD(FUNC) using std::FUNC;
#endif

// Wrapping #pragma unroll in a macro since it is required for SYCL
#if defined(SYCL_DEVICE_ONLY)
  #if defined(_MSC_VER)
    #define SQUEEZE_UNROLL_LOOP __pragma(unroll)
  #else
    #define SQUEEZE_UNROLL_LOOP _Pragma("unroll")
  #endif
#else
  #define SQUEEZE_UNROLL_LOOP
#endif

#ifdef SQUEEZE_USE_MKL
  #ifndef SQUEEZE_USE_BLAS
    #define SQUEEZE_USE_BLAS
  #endif
  #ifndef SQUEEZE_USE_LAPACK
    #define SQUEEZE_USE_LAPACK
  #endif
  #ifndef SQUEEZE_USE_FFTW
    #define SQUEEZE_USE_FFTW
  #endif
#endif


#define SQUEEZE_COMMON_TYPE(typ1, typ2)       \
  typename std::common_type<typ1, typ2>::type

// rename index type
namespace Squeeze {

using StdUIdx = std::size_t;
using Idx     = SQUEEZE_INDEX_TYPE;

constexpr static Idx Dynamic = static_cast<Idx>(-1);

} // namespace Squeeze

#endif // include guard
