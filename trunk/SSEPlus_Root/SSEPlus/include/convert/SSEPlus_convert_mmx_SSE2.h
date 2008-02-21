//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __SSEPLUS_CONVERT_MMX_SSE2_H__
#define __SSEPLUS_CONVERT_MMX_SSE2_H__

#include "../native/SSEPlus_native_SSE2.h"

/** @defgroup SSE2 SSE2 Optimized
 *  @{
 *  @name Convert operations on MMX registers */


/** \IMP{SSE2,ssp_convert_load_m64_m64,custom} */
SSEPLUS_FORCEINLINE
__m128 ssp_convert_load_m64_m64( __m64 a, __m64 b )
{
    ssp_m128 A,B;   

    A.i = _mm_movpi64_epi64( a );
    B.i = _mm_movpi64_epi64( b );
    A.f = _mm_movelh_ps( A.f, B.f );  

    return A.f;
}


//@}
//@}

#endif // __SSEPLUS_CONVERT_MMX_SSE2_H__
