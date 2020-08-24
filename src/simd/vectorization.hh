// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2008-2018 Gael Guennebaud <gael.guennebaud@inria.fr>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SQUEEZE_VECTORIZATION_HH
#define SQUEEZE_VECTORIZATION_HH

#include "../init/macros.hh"

//-----------------------------------------------------------------------------
// Static and dynamic alignment control
//
// The main purpose of this section is to define SQUEEZE_MAX_ALIGN_BYTES and SQUEEZE_MAX_STATIC_ALIGN_BYTES
// as the maximal boundary in bytes on which dynamically and statically allocated data may be alignment respectively.
// The values of SQUEEZE_MAX_ALIGN_BYTES and SQUEEZE_MAX_STATIC_ALIGN_BYTES can be specified by the user. If not,
// a default value is automatically computed based on architecture, compiler, and OS.
//
// This section also defines macros alignas(N) and the shortcuts SQUEEZE_ALIGN{8,16,32,_MAX}
// to be used to declare statically aligned buffers.
//-----------------------------------------------------------------------------

#ifdef __AVX512F__
  // 64 bytes static alignment is preferred only if really required
  #define SQUEEZE_IDEAL_MAX_ALIGN_BYTES 64
#elif defined(__AVX__)
  // 32 bytes static alignment is preferred only if really required
  #define SQUEEZE_IDEAL_MAX_ALIGN_BYTES 32
#else
  #define SQUEEZE_IDEAL_MAX_ALIGN_BYTES 16
#endif


// SQUEEZE_MIN_ALIGN_BYTES defines the minimal value for which the notion of explicit alignment makes sense
#define SQUEEZE_MIN_ALIGN_BYTES 16

#ifndef SQUEEZE_MAX_STATIC_ALIGN_BYTES

  // Try to automatically guess what is the best default value for SQUEEZE_MAX_STATIC_ALIGN_BYTES

  // 16 byte alignment is only useful for vectorization. Since it affects the ABI, we need to enable
  // 16 byte alignment on all platforms where vectorization might be enabled. In theory we could always
  // enable alignment, but it can be a cause of problems on some platforms, so we just disable it in
  // certain common platform (compiler+architecture combinations) to avoid these problems.
  // Only static alignment is really problematic (relies on nonstandard compiler extensions),
  // try to keep heap alignment even when we have to disable static alignment.
  #if SQUEEZE_COMP_GNUC && !(SQUEEZE_ARCH_i386_OR_x86_64 || SQUEEZE_ARCH_ARM_OR_ARM64 || SQUEEZE_ARCH_PPC || SQUEEZE_ARCH_IA64 || SQUEEZE_ARCH_MIPS)
  #define SQUEEZE_GCC_AND_ARCH_DOESNT_WANT_STACK_ALIGNMENT 1
  #else
  #define SQUEEZE_GCC_AND_ARCH_DOESNT_WANT_STACK_ALIGNMENT 0
  #endif

  // static alignment is completely disabled with GCC 3, Sun Studio, and QCC/QNX
  #if !SQUEEZE_GCC_AND_ARCH_DOESNT_WANT_STACK_ALIGNMENT && \
      !SQUEEZE_COMP_SUNCC && !SQUEEZE_OS_QNX
    #define SQUEEZE_ARCH_WANTS_STACK_ALIGNMENT 1
  #else
    #define SQUEEZE_ARCH_WANTS_STACK_ALIGNMENT 0
  #endif

  #if SQUEEZE_ARCH_WANTS_STACK_ALIGNMENT
    #define SQUEEZE_MAX_STATIC_ALIGN_BYTES SQUEEZE_IDEAL_MAX_ALIGN_BYTES
  #else
    #define SQUEEZE_MAX_STATIC_ALIGN_BYTES 0
  #endif

#endif

// If SQUEEZE_MAX_ALIGN_BYTES is defined, then it is considered as an upper bound for SQUEEZE_MAX_STATIC_ALIGN_BYTES
#if defined(SQUEEZE_MAX_ALIGN_BYTES) && SQUEEZE_MAX_ALIGN_BYTES<SQUEEZE_MAX_STATIC_ALIGN_BYTES
#undef SQUEEZE_MAX_STATIC_ALIGN_BYTES
#define SQUEEZE_MAX_STATIC_ALIGN_BYTES SQUEEZE_MAX_ALIGN_BYTES
#endif

// At this stage, SQUEEZE_MAX_STATIC_ALIGN_BYTES>0 is the true test whether we want to align arrays on the stack or not.
// It takes into account both the user choice to explicitly enable/disable alignment (by setting SQUEEZE_MAX_STATIC_ALIGN_BYTES)
// and the architecture config (SQUEEZE_ARCH_WANTS_STACK_ALIGNMENT).
// Henceforth, only SQUEEZE_MAX_STATIC_ALIGN_BYTES should be used.


// Shortcuts to alignas
#if SQUEEZE_MAX_STATIC_ALIGN_BYTES>0
  #define SQUEEZE_ALIGN_MAX alignas(SQUEEZE_MAX_STATIC_ALIGN_BYTES)
#else
  #define SQUEEZE_ALIGN_MAX
#endif


// Dynamic alignment control

#if SQUEEZE_MAX_STATIC_ALIGN_BYTES==0
  #if defined(SQUEEZE_MAX_ALIGN_BYTES) && SQUEEZE_MAX_ALIGN_BYTES>0
    #error SQUEEZE_MAX_STATIC_ALIGN_BYTES==0 but SQUEEZE_MAX_ALIGN_BYTES!=0
  #elif !defined(SQUEEZE_MAX_ALIGN_BYTES)
    #define SQUEEZE_MAX_ALIGN_BYTES 0
  #endif
#endif

#ifndef SQUEEZE_MAX_ALIGN_BYTES
  #define SQUEEZE_MAX_ALIGN_BYTES SQUEEZE_IDEAL_MAX_ALIGN_BYTES
#endif

#ifndef SQUEEZE_DONT_ALIGN
  #if SQUEEZE_IDEAL_MAX_ALIGN_BYTES > SQUEEZE_MAX_ALIGN_BYTES
    #define SQUEEZE_DEFAULT_ALIGN_BYTES SQUEEZE_IDEAL_MAX_ALIGN_BYTES
  #else
    #define SQUEEZE_DEFAULT_ALIGN_BYTES SQUEEZE_MAX_ALIGN_BYTES
  #endif
#else
  #define SQUEEZE_DEFAULT_ALIGN_BYTES 0
#endif


#ifndef SQUEEZE_UNALIGNED_VECTORIZE
#define SQUEEZE_UNALIGNED_VECTORIZE 1
#endif

//----------------------------------------------------------------------

// if alignment is disabled, then disable vectorization. Note: SQUEEZE_MAX_ALIGN_BYTES is the proper check, it takes into
// account both the user's will (SQUEEZE_MAX_ALIGN_BYTES,SQUEEZE_DONT_ALIGN) and our own platform checks
#if SQUEEZE_MAX_ALIGN_BYTES==0 && !defined(SQUEEZE_DONT_ALIGN)
  #define SQUEEZE_DONT_ALIGN
#endif


// The following (except #include <malloc.h> and _M_IX86_FP ??) can likely be
// removed as gcc 4.1 and msvc 2008 are not supported anyways.
#if SQUEEZE_COMP_MSVC
  #include <malloc.h> // for _aligned_malloc -- need it regardless of whether vectorization is enabled
  // a user reported that in 64-bit mode, MSVC doesn't care to define _M_IX86_FP.
  #if (defined(_M_IX86_FP) && (_M_IX86_FP >= 2)) || SQUEEZE_ARCH_x86_64
    #define SQUEEZE_SSE2_ON_MSVC_2008_OR_LATER
  #endif
#else
  #if (defined __SSE2__) && ( (!SQUEEZE_COMP_GNUC) || SQUEEZE_COMP_ICC )
    #define SQUEEZE_SSE2_ON_NON_MSVC_BUT_NOT_OLD_GCC
  #endif
#endif


#if !(defined(SQUEEZE_DONT_ALIGN) || defined(SQUEEZE_GPUCC))

  #if defined (SQUEEZE_SSE2_ON_NON_MSVC_BUT_NOT_OLD_GCC)

    // Defines symbols for compile-time detection of which instructions are
    // used.
    // SQUEEZE_VECTORIZE_YY is defined if and only if the instruction set YY is used
    #define SQUEEZE_VECTORIZE
    #define SQUEEZE_VECTORIZE_SSE
    #define SQUEEZE_VECTORIZE_SSE2

    // Detect sse3/ssse3/sse4:
    // gcc and icc defines __SSE3__, ...
    // there is no way to know about this on msvc. You can define SQUEEZE_VECTORIZE_SSE* if you
    // want to force the use of those instructions with msvc.
    #ifdef __SSE3__
      #define SQUEEZE_VECTORIZE_SSE3
    #endif
    #ifdef __SSSE3__
      #define SQUEEZE_VECTORIZE_SSSE3
    #endif
    #ifdef __SSE4_1__
      #define SQUEEZE_VECTORIZE_SSE4_1
    #endif
    #ifdef __SSE4_2__
      #define SQUEEZE_VECTORIZE_SSE4_2
    #endif
    #ifdef __AVX__
      #define SQUEEZE_VECTORIZE_AVX
      #define SQUEEZE_VECTORIZE_SSE3
      #define SQUEEZE_VECTORIZE_SSSE3
      #define SQUEEZE_VECTORIZE_SSE4_1
      #define SQUEEZE_VECTORIZE_SSE4_2
    #endif
    #ifdef __AVX2__
      #define SQUEEZE_VECTORIZE_AVX2
      #define SQUEEZE_VECTORIZE_AVX
      #define SQUEEZE_VECTORIZE_SSE3
      #define SQUEEZE_VECTORIZE_SSSE3
      #define SQUEEZE_VECTORIZE_SSE4_1
      #define SQUEEZE_VECTORIZE_SSE4_2
    #endif
    #if defined(__FMA__) || (SQUEEZE_COMP_MSVC && defined(__AVX2__))
      // MSVC does not expose a switch dedicated for FMA
      // For MSVC, AVX2 => FMA
      #define SQUEEZE_VECTORIZE_FMA
    #endif
    #if defined(__AVX512F__)
      #ifndef SQUEEZE_VECTORIZE_FMA
      #if SQUEEZE_COMP_GNUC
      #error Please add -mfma to your compiler flags: compiling with -mavx512f alone without SSE/AVX FMA is not supported.
      #else
      #error Please enable FMA in your compiler flags (e.g. -mfma): compiling with AVX512 alone without SSE/AVX FMA is not supported.
      #endif
      #endif
      #define SQUEEZE_VECTORIZE_AVX512
      #define SQUEEZE_VECTORIZE_AVX2
      #define SQUEEZE_VECTORIZE_AVX
      #define SQUEEZE_VECTORIZE_FMA
      #define SQUEEZE_VECTORIZE_SSE3
      #define SQUEEZE_VECTORIZE_SSSE3
      #define SQUEEZE_VECTORIZE_SSE4_1
      #define SQUEEZE_VECTORIZE_SSE4_2
      #ifdef __AVX512DQ__
        #define SQUEEZE_VECTORIZE_AVX512DQ
      #endif
      #ifdef __AVX512ER__
        #define SQUEEZE_VECTORIZE_AVX512ER
      #endif
    #endif

    // include files

    // This extern "C" works around a MINGW-w64 compilation issue
    // https://sourceforge.net/tracker/index.php?func=detail&aid=3018394&group_id=202880&atid=983354
    // In essence, intrin.h is included by windows.h and also declares intrinsics (just as emmintrin.h etc. below do).
    // However, intrin.h uses an extern "C" declaration, and g++ thus complains of duplicate declarations
    // with conflicting linkage.  The linkage for intrinsics doesn't matter, but at that stage the compiler doesn't know;
    // so, to avoid compile errors when windows.h is included after Eigen/Core, ensure intrinsics are extern "C" here too.
    // notice that since these are C headers, the extern "C" is theoretically needed anyways.
    extern "C" {
      // In theory we should only include immintrin.h and not the other *mmintrin.h header files directly.
      // Doing so triggers some issues with ICC. However old gcc versions seems to not have this file, thus:
      #ifdef SQUEEZE_COMP_ICC
        #include <immintrin.h>
      #else
        #include <mmintrin.h>
        #include <emmintrin.h>
        #include <xmmintrin.h>
        #ifdef  SQUEEZE_VECTORIZE_SSE3
        #include <pmmintrin.h>
        #endif
        #ifdef SQUEEZE_VECTORIZE_SSSE3
        #include <tmmintrin.h>
        #endif
        #ifdef SQUEEZE_VECTORIZE_SSE4_1
        #include <smmintrin.h>
        #endif
        #ifdef SQUEEZE_VECTORIZE_SSE4_2
        #include <nmmintrin.h>
        #endif
        #if defined(SQUEEZE_VECTORIZE_AVX) || defined(SQUEEZE_VECTORIZE_AVX512)
        #include <immintrin.h>
        #endif
      #endif
    } // end extern "C"

  #elif defined __VSX__

    #define SQUEEZE_VECTORIZE
    #define SQUEEZE_VECTORIZE_VSX
    #include <altivec.h>
    // We need to #undef all these ugly tokens defined in <altivec.h>
    // => use __vector instead of vector
    #undef bool
    #undef vector
    #undef pixel

  #elif defined __ALTIVEC__

    #define SQUEEZE_VECTORIZE
    #define SQUEEZE_VECTORIZE_ALTIVEC
    #include <altivec.h>
    // We need to #undef all these ugly tokens defined in <altivec.h>
    // => use __vector instead of vector
    #undef bool
    #undef vector
    #undef pixel

  #elif (defined  __ARM_NEON) || (defined __ARM_NEON__)

    #define SQUEEZE_VECTORIZE
    #define SQUEEZE_VECTORIZE_NEON
    #include <arm_neon.h>

  #elif (defined __s390x__ && defined __VEC__)

    #define SQUEEZE_VECTORIZE
    #define SQUEEZE_VECTORIZE_ZVECTOR
    #include <vecintrin.h>

  #elif defined __mips_msa

    // Limit MSA optimizations to little-endian CPUs for now.
    // TODO: Perhaps, eventually support MSA optimizations on big-endian CPUs?
    #if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
      #if defined(__LP64__)
        #define SQUEEZE_MIPS_64
      #else
        #define SQUEEZE_MIPS_32
      #endif
      #define SQUEEZE_VECTORIZE
      #define SQUEEZE_VECTORIZE_MSA
      #include <msa.h>
    #endif

  #endif
#endif

#if defined(__F16C__) && (!defined(SQUEEZE_COMP_CLANG) || SQUEEZE_COMP_CLANG>=380)
  // We can use the optimized fp16 to float and float to fp16 conversion routines
  #define SQUEEZE_HAS_FP16_C

  #if defined(SQUEEZE_COMP_CLANG)
    // Workaround for clang: The FP16C intrinsics for clang are included by
    // immintrin.h, as opposed to emmintrin.h as suggested by Intel:
    // https://software.intel.com/sites/landingpage/IntrinsicsGuide/#othertechs=FP16C&expand=1711
    #include <immintrin.h>
  #endif
#endif

#if defined SQUEEZE_CUDACC
  #define SQUEEZE_VECTORIZE_GPU
  #include <vector_types.h>
  #if SQUEEZE_CUDA_SDK_VER >= 70500
    #define SQUEEZE_HAS_CUDA_FP16
  #endif
#endif

#if defined(SQUEEZE_HAS_CUDA_FP16)
  #include <cuda_runtime_api.h>
  #include <cuda_fp16.h>
#endif

#if defined(SQUEEZE_HIPCC)
  #define SQUEEZE_VECTORIZE_GPU
  #include <hip/hip_vector_types.h>
#endif

#if defined(SQUEEZE_HIP_DEVICE_COMPILE)
  #define SQUEEZE_HAS_HIP_FP16
  #include <hip/hip_fp16.h>
#endif

#endif // include guard
