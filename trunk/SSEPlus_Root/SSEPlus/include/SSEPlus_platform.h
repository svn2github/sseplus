//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#if     defined( _MSC_VER )

#define SSEPLUS_MSVC
#define SSEPLUS_FORCEINLINE __forceinline

#elif   defined( __GNUC__ )

#define SSEPLUS_GNUC
#define SSEPLUS_FORCEINLINE __inline__

#endif

#ifdef SSEPLUS_MSVC
#if _MSC_VER >= 1500 
#define SSEPLUS_SSSE3_SSE4A_SSE41_SSE42
#endif
#endif

#ifdef SSEPLUS_GNUC
#if __GNUC__ >= 4
#if __GNUC_MINOR__ >= 3
#define SSEPLUS_SSSE3_SSE4A_SSE41_SSE42
#endif
#endif
#endif

#endif // __PLATFORM_H__
