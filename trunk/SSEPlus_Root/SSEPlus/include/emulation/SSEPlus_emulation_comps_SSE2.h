//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __SSEPLUS_EMULATION_COMPS_SSE2_H__
#define __SSEPLUS_EMULATION_COMPS_SSE2_H__

#include "../SSEPlus_SSE2.h"


/** @addtogroup emulated_SSE2   
 *  @{ 
 *  @name SSE[3,4A,...,5] implemented in SSE2
 */


/** \SSE5{SSE2,_mm_comeq_ps, comps } */
SSP_FORCEINLINE __m128 ssp_comeq_ps_SSE2(__m128 a, __m128 b)
{
    a = _mm_cmpeq_ps( a, b );
    return a;
}

/** \SSE5{SSE2,_mm_comlt_ps, comps } */
SSP_FORCEINLINE __m128 ssp_comlt_ps_SSE2(__m128 a, __m128 b)
{
    a = _mm_cmplt_ps( a, b );
    return a;
}

/** \SSE5{SSE2,_mm_comneq_ps, comps } */
SSP_FORCEINLINE __m128 ssp_comneq_ps_SSE2(__m128 a, __m128 b)
{
    a = _mm_cmpneq_ps( a, b );
    return a;
}


/** \SSE5{SSE2,_mm_comueq_ps, comps } */
SSP_FORCEINLINE __m128 ssp_comueq_ps_SSE2(__m128 a, __m128 b)
{
    const static __m128i mask_i = SSP_CONST_SET_32I( 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF );

    __m128 t;
    ssp_m128 mask_f;
    mask_f.i = mask_i;

    t = _mm_cmplt_ps( a, b );
    a = _mm_cmplt_ps( b, a );
    a = _mm_or_ps   ( a, t );
    a = _mm_xor_ps  ( a, mask_f.f );

   return a;
}


/** \SSE5{SSE2,_mm_comeq_pd, compd }*/
SSP_FORCEINLINE __m128d ssp_comeq_pd_SSE2(__m128d a, __m128d b)
{
    a = _mm_cmpeq_pd( a, b );
    return a;
}



/** \SSE5{SSE2,_mm_comneq_pd, compd }*/
SSP_FORCEINLINE __m128d ssp_comneq_pd_SSE2(__m128d a, __m128d b)
{
    a = _mm_cmpneq_pd( a, b );
    return a;
}




/** \SSE5{SSE2,_mm_comoneq_ps, comps } */
SSP_FORCEINLINE __m128 ssp_comoneq_ps_SSE2(__m128 a, __m128 b)
{
    __m128 t = _mm_cmplt_ps( a, b );
           a = _mm_cmplt_ps( b, a );
           a = _mm_or_ps   ( a, t );
   return a;
}



/** \SSE5{SSE2,_mm_comfalse_epi16, pcomw } */
SSP_FORCEINLINE __m128i ssp_comfalse_epi16_SSE2(__m128i a, __m128i b)
{
	return _mm_setzero_si128();
}

/** \SSE5{SSE2,_mm_comfalse_epi32, pcomd } */
SSP_FORCEINLINE __m128i ssp_comfalse_epi32_SSE2(__m128i a, __m128i b)
{
	return _mm_setzero_si128();
}

/** \SSE5{SSE2,_mm_comfalse_epi64, pcomq } */
SSP_FORCEINLINE __m128i ssp_comfalse_epi64_SSE2(__m128i a, __m128i b)
{
	return _mm_setzero_si128();
}

/** \SSE5{SSE2,_mm_comfalse_epi8, pcomb } */
SSP_FORCEINLINE __m128i ssp_comfalse_epi8_SSE2(__m128i a, __m128i b)
{
	return _mm_setzero_si128();
}

/** \SSE5{SSE2,_mm_comfalse_epu16, pcomuw } */
SSP_FORCEINLINE __m128i ssp_comfalse_epu16_SSE2(__m128i a, __m128i b)
{
	return _mm_setzero_si128();
}

/** \SSE5{SSE2,_mm_comfalse_epu32, pcomud } */
SSP_FORCEINLINE __m128i ssp_comfalse_epu32_SSE2(__m128i a, __m128i b)
{
	return _mm_setzero_si128();
}

/** \SSE5{SSE2,_mm_comfalse_epu64, pcomuq } */
SSP_FORCEINLINE __m128i ssp_comfalse_epu64_SSE2(__m128i a, __m128i b)
{
	return _mm_setzero_si128();
}

/** \SSE5{SSE2,_mm_comfalse_epu8, pcomub } */
SSP_FORCEINLINE __m128i ssp_comfalse_epu8_SSE2(__m128i a, __m128i b)
{
	return _mm_setzero_si128();
}

/** \SSE5{SSE2,_mm_comfalse_pd, compd } */
SSP_FORCEINLINE __m128d ssp_comfalse_pd_SSE2(__m128d a, __m128d b)
{
	return _mm_setzero_pd();
}

/** \SSE5{SSE2,_mm_comfalse_ps, comps } */
SSP_FORCEINLINE __m128 ssp_comfalse_ps_SSE2(__m128 a, __m128 b)
{
	return _mm_setzero_ps();
}

/** \SSE5{SSE2,_mm_comfalse_sd, comsd } */
SSP_FORCEINLINE __m128d ssp_comfalse_sd_SSE2(__m128d a, __m128d b)
{
	ssp_m128 B;
	B.i = _mm_set_epi32(0xFFFFFFFF, 0xFFFFFFFF, 0, 0);
	return _mm_and_pd(a, B.d);
}

/** \SSE5{SSE2,_mm_comfalse_ss, comss } */
SSP_FORCEINLINE __m128 ssp_comfalse_ss_SSE2(__m128 a, __m128 b)
{
	ssp_m128 B;
	B.i = _mm_set_epi32(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0);
	return _mm_and_ps(a, B.f);
}

/** \SSE5{SSE2,_mm_comtrue_epi16, pcomw } */
SSP_FORCEINLINE __m128i ssp_comtrue_epi16_SSE2(__m128i a, __m128i b)
{
	return _mm_set1_epi32(0xFFFFFFFF);
}

/** \SSE5{SSE2,_mm_comtrue_epi32, pcomd } */
SSP_FORCEINLINE __m128i ssp_comtrue_epi32_SSE2(__m128i a, __m128i b)
{
	return _mm_set1_epi32(0xFFFFFFFF);
}

/** \SSE5{SSE2,_mm_comtrue_epi64, pcomq } */
SSP_FORCEINLINE __m128i ssp_comtrue_epi64_SSE2(__m128i a, __m128i b)
{
	return _mm_set1_epi32(0xFFFFFFFF);
}

/** \SSE5{SSE2,_mm_comtrue_epi8, pcomb } */
SSP_FORCEINLINE __m128i ssp_comtrue_epi8_SSE2(__m128i a, __m128i b)
{
	return _mm_set1_epi32(0xFFFFFFFF);
}

/** \SSE5{SSE2,_mm_comtrue_epu16, pcomuw } */
SSP_FORCEINLINE __m128i ssp_comtrue_epu16_SSE2(__m128i a, __m128i b)
{
	return _mm_set1_epi32(0xFFFFFFFF);
}

/** \SSE5{SSE2,_mm_comtrue_epu32, pcomud } */
SSP_FORCEINLINE __m128i ssp_comtrue_epu32_SSE2(__m128i a, __m128i b)
{
	return _mm_set1_epi32(0xFFFFFFFF);
}

/** \SSE5{SSE2,_mm_comtrue_epu64, pcomuq } */
SSP_FORCEINLINE __m128i ssp_comtrue_epu64_SSE2(__m128i a, __m128i b)
{
	return _mm_set1_epi32(0xFFFFFFFF);
}

/** \SSE5{SSE2,_mm_comtrue_epu8, pcomub } */
SSP_FORCEINLINE __m128i ssp_comtrue_epu8_SSE2(__m128i a, __m128i b)
{
	return _mm_set1_epi32(0xFFFFFFFF);
}

/** \SSE5{SSE2,_mm_comtrue_pd, compd } */
SSP_FORCEINLINE __m128d ssp_comtrue_pd_SSE2(__m128d a, __m128d b)
{
	ssp_m128 B;
	B.i = _mm_set1_epi32(0xFFFFFFFF);
	return B.d;
}

/** \SSE5{SSE2,_mm_comtrue_ps, comps } */
SSP_FORCEINLINE __m128 ssp_comtrue_ps_SSE2(__m128 a, __m128 b)
{
	ssp_m128 B;
	B.i = _mm_set1_epi32(0xFFFFFFFF);
	return B.f;
}

/** \SSE5{SSE2,_mm_comtrue_sd, comsd } */
SSP_FORCEINLINE __m128d ssp_comtrue_sd_SSE2(__m128d a, __m128d b)
{
	ssp_m128 B;
	B.i = _mm_set_epi32(0, 0, 0xFFFFFFFF, 0xFFFFFFFF);
	return _mm_or_pd(a, B.d);
}

/** \SSE5{SSE2,_mm_comtrue_ss, comss } */
SSP_FORCEINLINE __m128 ssp_comtrue_ss_SSE2(__m128 a, __m128 b)
{
	ssp_m128 B;
	B.i = _mm_set_epi32(0, 0, 0, 0xFFFFFFFF);
	return _mm_or_ps(a, B.f);
}



/** @} 
 *  @}
 */


#endif // __SSEPLUS_EMULATION_COMPS_SSE2_H__
