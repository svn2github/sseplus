//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __SSEPLUS_NATIVE_SSE3_H__
#define __SSEPLUS_NATIVE_SSE3_H__

#include "../SSEPlus_base.h"

#ifdef SSEPLUS_GNUC
#include <pmmintrin.h> //SSE3
#else
#include <intrin.h>    //SSE3
#endif

/** @defgroup SSE3 SSE3 Optimized
 *  @{
 *  @name Native Instructions */

/** \IMP{SSE3 Native,_mm_addsub_ps,SSE3} */ 
SSEPLUS_FORCEINLINE __m128 ssp_addsub_ps_SSE3(__m128 a, __m128 b)                              
{
    return _mm_addsub_ps( a, b );
}
/** \IMP{SSE3 Native,_mm_addsub_pd,SSE3} */ 
SSEPLUS_FORCEINLINE __m128d ssp_addsub_pd_SSE3( __m128d a, __m128d b)
{
    return _mm_addsub_pd( a, b );
}
/** \IMP{SSE3 Native,_mm_hadd_pd,SSE3} */ 
SSEPLUS_FORCEINLINE __m128d ssp_hadd_pd_SSE3( __m128d a, __m128d b)
{
    return _mm_hadd_pd(a, b );
}
/** \IMP{SSE3 Native,_mm_hadd_ps,SSE3} */ 
SSEPLUS_FORCEINLINE __m128 ssp_hadd_ps_SSE3( __m128 a, __m128 b)
{
    return _mm_hadd_ps( a, b);    
}
/** \IMP{SSE3 Native,_mm_hsub_pd,SSE3} */ 
SSEPLUS_FORCEINLINE __m128d ssp_hsub_pd_SSE3( __m128d a, __m128d b)
{
    return _mm_hsub_pd (a, b);
}
/** \IMP{SSE3 Native,_mm_hsub_ps,SSE3} */ 
SSEPLUS_FORCEINLINE __m128 ssp_hsub_ps_SSE3( __m128 a, __m128 b)
{
    return _mm_hsub_ps (a, b);
}
/** \IMP{SSE3 Native,_mm_lddqu_si128,SSE3} */ 
SSEPLUS_FORCEINLINE __m128i ssp_lddqu_si128_SSE3( __m128i const *p)
{
    return _mm_lddqu_si128 (p);    
}
/** \IMP{SSE3 Native,_mm_loaddup_pd,SSE3} */ 
SSEPLUS_FORCEINLINE __m128d ssp_loaddup_pd_SSE3 (double const * dp)
{
    return _mm_loaddup_pd (dp);
}
/** \IMP{SSE3 Native,_mm_movedup_pd,SSE3} */ 
SSEPLUS_FORCEINLINE __m128d ssp_movedup_pd_SSE3( __m128d a)
{
    return _mm_movedup_pd (a);    
}
/** \IMP{SSE3 Native,_mm_movehdup_ps,SSE3} */ 
SSEPLUS_FORCEINLINE __m128 ssp_movehdup_ps_SSE3( __m128 a)
{
    return _mm_movehdup_ps (a);
}
/** \IMP{SSE3 Native,_mm_moveldup_ps,SSE3} */ 
SSEPLUS_FORCEINLINE __m128 ssp_moveldup_ps_SSE3( __m128 a)
{
    return _mm_moveldup_ps (a);
}

//@}
//@}

#endif // __SSEPLUS_NATIVE_SSE3_H__
