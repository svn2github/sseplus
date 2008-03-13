//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __SSEPLUS_EMULATION_REF_H__
#define __SSEPLUS_EMULATION_REF_H__

#include "../SSEPlus_base.h"
#include "../number/SSEPlus_number_REF.h"
#include "../arithmetic/SSEPlus_arithmetic_REF.h"
#include <math.h>


/** @defgroup Reference Reference
 *  @{
 *  @name Emulated Instructions{ */

//--------------------------------------
// Multiply Add
//--------------------------------------

/** \IMP5{Reference,_mm_macc_ps,fmaddps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_macc_ps_REF( __m128 a, __m128 b, __m128 c )
{
    ssp_m128 A,B,C;
    A.f = a;
    B.f = b;
    C.f = c;

    A.f32[0] = A.f32[0] * B.f32[0] + C.f32[0];
    A.f32[1] = A.f32[1] * B.f32[1] + C.f32[1];
    A.f32[2] = A.f32[2] * B.f32[2] + C.f32[2];
    A.f32[3] = A.f32[3] * B.f32[3] + C.f32[3];
    return A.f;
}

/** \IMP5{Reference,_mm_macc_pd,fmaddpd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_macc_pd_REF( __m128d a, __m128d b, __m128d c )
{
    ssp_m128 A,B,C;
    A.d = a;
    B.d = b;
    C.d = c;

    A.f64[0] = A.f64[0] * B.f64[0] + C.f64[0];
    A.f64[1] = A.f64[1] * B.f64[1] + C.f64[1]; 
    return A.d;
}

/** \IMP5{Reference,_mm_macc_ss,fmaddss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_macc_ss_REF(__m128 a, __m128 b, __m128 c)   // Assuming SSE5 *_ss semantics are similar to _mm_add_ss. TODO: confirm
{
    ssp_m128 A,B,C;
    A.f = a;
    B.f = b;
    C.f = c;

    A.f32[0] = A.f32[0] * B.f32[0] + C.f32[0];   
    return A.f;
}

/** \IMP5{Reference,_mm_macc_sd,fmaddss,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_macc_sd_REF(__m128d a, __m128d b, __m128d c)   // Assuming SSE5 *_ss semantics are similar to _mm_add_ss. TODO: confirm
{
    ssp_m128 A,B,C;
    A.d = a;
    B.d = b;
    C.d = c;

    A.f64[0] = A.f64[0] * B.f64[0] + C.f64[0];   
    return A.d;
}


//--------------------------------------
// Negative Multiply Add
//--------------------------------------

/** \IMP5{Reference,_mm_nmacc_ps,fnmaddps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_nmacc_ps_REF(__m128 a, __m128 b, __m128 c)
{
    ssp_m128 A,B,C;
    A.f = a;
    B.f = b;
    C.f = c;

    A.f32[0] = -(A.f32[0] * B.f32[0]) + C.f32[0];
    A.f32[1] = -(A.f32[1] * B.f32[1]) + C.f32[1];
    A.f32[2] = -(A.f32[2] * B.f32[2]) + C.f32[2];
    A.f32[3] = -(A.f32[3] * B.f32[3]) + C.f32[3];
    return A.f;
}

/** \IMP5{Reference,_mm_nmacc_pd,fnmaddpd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_nmacc_pd_REF(__m128d a, __m128d b, __m128d c)
{
    ssp_m128 A,B,C;
    A.d = a;
    B.d = b;
    C.d = c;

    A.f64[0] = -(A.f64[0] * B.f64[0]) + C.f64[0];
    A.f64[1] = -(A.f64[1] * B.f64[1]) + C.f64[1]; 
    return A.d;
}

/** \IMP5{Reference,_mm_nmacc_ss,fnmaddss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_nmacc_ss_REF(__m128 a, __m128 b, __m128 c)
{
    ssp_m128 A,B,C;
    A.f = a;
    B.f = b;
    C.f = c;

    A.f32[0] = -(A.f32[0] * B.f32[0]) + C.f32[0];   
    return A.f;
}

/** \IMP{Reference,_mm_nmacc_sd,fnmaddsd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_nmacc_sd_REF(__m128d a, __m128d b, __m128d c)
{
    ssp_m128 A,B,C;
    A.d = a;
    B.d = b;
    C.d = c;

    A.f64[0] = -(A.f64[0] * B.f64[0]) + C.f64[0];   
    return A.d;
}


//--------------------------------------
// Multiply Subtract
//--------------------------------------

/** \IMP5{Reference,_mm_msub_ps,fmsubps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_msub_ps_REF( __m128 a, __m128 b, __m128 c )
{
    ssp_m128 A,B,C;
    A.f = a;
    B.f = b;
    C.f = c;

    A.f32[0] = A.f32[0] * B.f32[0] - C.f32[0];
    A.f32[1] = A.f32[1] * B.f32[1] - C.f32[1];
    A.f32[2] = A.f32[2] * B.f32[2] - C.f32[2];
    A.f32[3] = A.f32[3] * B.f32[3] - C.f32[3];
    return A.f;
}

/** \IMP5{Reference,_mm_msub_pd,fmsubpd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_msub_pd_REF( __m128d a, __m128d b, __m128d c )
{
    ssp_m128 A,B,C;
    A.d = a;
    B.d = b;
    C.d = c;

    A.f64[0] = A.f64[0] * B.f64[0] - C.f64[0];
    A.f64[1] = A.f64[1] * B.f64[1] - C.f64[1]; 
    return A.d;
}

/** \IMP5{Reference,_mm_msub_ss,fmsubss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_msub_ss_REF(__m128 a, __m128 b, __m128 c)   // Assuming SSE5 *_ss semantics are similar to _mm_add_ss. TODO: confirm
{
    ssp_m128 A,B,C;
    A.f = a;
    B.f = b;
    C.f = c;

    A.f32[0] = A.f32[0] * B.f32[0] - C.f32[0];   
    return A.f;
}

/** \IMP5{Reference,_mm_msub_sd,fmsubss,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_msub_sd_REF(__m128d a, __m128d b, __m128d c)   // Assuming SSE5 *_ss semantics are similar to _mm_add_ss. TODO: confirm
{
    ssp_m128 A,B,C;
    A.d = a;
    B.d = b;
    C.d = c;

    A.f64[0] = A.f64[0] * B.f64[0] - C.f64[0];   
    return A.d;
}

//--------------------------------------
// Negative Multiply Subtract
//--------------------------------------

/** \IMP5{Reference,_mm_nmsub_ps,fnmsubps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_nmsub_ps_REF(__m128 a, __m128 b, __m128 c)
{
    ssp_m128 A,B,C;
    A.f = a;
    B.f = b;
    C.f = c;

    A.f32[0] = -(A.f32[0] * B.f32[0]) - C.f32[0];
    A.f32[1] = -(A.f32[1] * B.f32[1]) - C.f32[1];
    A.f32[2] = -(A.f32[2] * B.f32[2]) - C.f32[2];
    A.f32[3] = -(A.f32[3] * B.f32[3]) - C.f32[3];
    return A.f;
}

/** \IMP5{Reference,_mm_nmsub_pd,fnmsubpd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_nmsub_pd_REF(__m128d a, __m128d b, __m128d c)
{
    ssp_m128 A,B,C;
    A.d = a;
    B.d = b;
    C.d = c;

    A.f64[0] = -(A.f64[0] * B.f64[0]) - C.f64[0];
    A.f64[1] = -(A.f64[1] * B.f64[1]) - C.f64[1]; 
    return A.d;
}

/** \IMP5{Reference,_mm_nmsub_ss,fnmsubss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_nmsub_ss_REF(__m128 a, __m128 b, __m128 c)
{
    ssp_m128 A,B,C;
    A.f = a;
    B.f = b;
    C.f = c;

    A.f32[0] = -(A.f32[0] * B.f32[0]) - C.f32[0];   
    return A.f;
}

/** \IMP{Reference,_mm_nmsub_sd,fnmsubsd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_nmsub_sd_REF(__m128d a, __m128d b, __m128d c)
{
    ssp_m128 A,B,C;
    A.d = a;
    B.d = b;
    C.d = c;

    A.f64[0] = -(A.f64[0] * B.f64[0]) - C.f64[0];   
    return A.d;
}



//---------------------------------------
// AddSubtract
//---------------------------------------

/** \IMP{Reference,_mm_addsub_ps,SSE3} */
SSP_FORCEINLINE __m128 ssp_addsub_ps_REF(__m128 a, __m128 b)
{
    ssp_m128 A, B;
    A.f = a;
    B.f = b;

    A.f32[0] -= B.f32[0];
    A.f32[1] += B.f32[1];
    A.f32[2] -= B.f32[2];
    A.f32[3] += B.f32[3];
    return A.f;
}

/** \IMP{Reference,_mm_addsub_pd, SSE3} */
SSP_FORCEINLINE __m128d ssp_addsub_pd_REF(__m128d a, __m128d b)
{
    ssp_m128 A, B;
    A.d = a;
    B.d = b;

    A.f64[0] -= B.f64[0];
    A.f64[1] += B.f64[1];
    return A.d;
}

//---------------------------------------
//Blend
//---------------------------------------

/** \IMP{Reference,_mm_blend_epi16, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_blend_epi16_REF     ( __m128i a, __m128i b, const int mask )
{
    ssp_m128 A, B;
    A.i = a;
    B.i = b;

    A.s16[0] = (mask & 0x01) ? B.s16[0] : A.s16[0];
    A.s16[1] = (mask & 0x02) ? B.s16[1] : A.s16[1];
    A.s16[2] = (mask & 0x04) ? B.s16[2] : A.s16[2];
    A.s16[3] = (mask & 0x08) ? B.s16[3] : A.s16[3];
    A.s16[4] = (mask & 0x10) ? B.s16[4] : A.s16[4];
    A.s16[5] = (mask & 0x20) ? B.s16[5] : A.s16[5];
    A.s16[6] = (mask & 0x40) ? B.s16[6] : A.s16[6];
    A.s16[7] = (mask & 0x80) ? B.s16[7] : A.s16[7];
    return A.i;
}

/** \IMP{Reference,_mm_blend_pd, SSE4.1} */
SSP_FORCEINLINE __m128d ssp_blend_pd_REF        ( __m128d a, __m128d b, const int mask )
{
    ssp_m128 A, B;
    A.d = a;
    B.d = b;

    A.f64[0] = (mask & 0x1) ? B.f64[0] : A.f64[0];
    A.f64[1] = (mask & 0x2) ? B.f64[1] : A.f64[1];
    return A.d;
}

/** \IMP{Reference,_mm_blend_ps, SSE4.1} */
SSP_FORCEINLINE __m128  ssp_blend_ps_REF        ( __m128  a, __m128  b, const int mask )
{
    ssp_m128 A, B;
    A.f = a;
    B.f = b;

    A.f32[0] = (mask & 0x1) ? B.f32[0] : A.f32[0];
    A.f32[1] = (mask & 0x2) ? B.f32[1] : A.f32[1];
    A.f32[2] = (mask & 0x4) ? B.f32[2] : A.f32[2];
    A.f32[3] = (mask & 0x8) ? B.f32[3] : A.f32[3];
    return A.f;
}

/** \IMP{Reference,_mm_blendv_epi8, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_blendv_epi8_REF     ( __m128i a, __m128i b, __m128i mask )
{
    ssp_m128 A, B, Mask;
    A.i = a;
    B.i = b;
    Mask.i = mask;

    A.s8[0]  = (Mask.s8[0]  & 0x80) ? B.s8[0]  : A.s8[0];
    A.s8[1]  = (Mask.s8[1]  & 0x80) ? B.s8[1]  : A.s8[1];
    A.s8[2]  = (Mask.s8[2]  & 0x80) ? B.s8[2]  : A.s8[2];
    A.s8[3]  = (Mask.s8[3]  & 0x80) ? B.s8[3]  : A.s8[3];
    A.s8[4]  = (Mask.s8[4]  & 0x80) ? B.s8[4]  : A.s8[4];
    A.s8[5]  = (Mask.s8[5]  & 0x80) ? B.s8[5]  : A.s8[5];
    A.s8[6]  = (Mask.s8[6]  & 0x80) ? B.s8[6]  : A.s8[6];
    A.s8[7]  = (Mask.s8[7]  & 0x80) ? B.s8[7]  : A.s8[7];
    A.s8[8]  = (Mask.s8[8]  & 0x80) ? B.s8[8]  : A.s8[8];
    A.s8[9]  = (Mask.s8[9]  & 0x80) ? B.s8[9]  : A.s8[9];
    A.s8[10] = (Mask.s8[10] & 0x80) ? B.s8[10] : A.s8[10];
    A.s8[11] = (Mask.s8[11] & 0x80) ? B.s8[11] : A.s8[11];
    A.s8[12] = (Mask.s8[12] & 0x80) ? B.s8[12] : A.s8[12];
    A.s8[13] = (Mask.s8[13] & 0x80) ? B.s8[13] : A.s8[13];
    A.s8[14] = (Mask.s8[14] & 0x80) ? B.s8[14] : A.s8[14];
    A.s8[15] = (Mask.s8[15] & 0x80) ? B.s8[15] : A.s8[15];
    return A.i;
}

/** \IMP{Reference,_mm_blendv_pd, SSE4.1} */
SSP_FORCEINLINE __m128d ssp_blendv_pd_REF       ( __m128d a, __m128d b, __m128d mask )
{
    ssp_m128 A, B, Mask;
    A.d = a;
    B.d = b;
    Mask.d = mask;

    A.f64[0] = (Mask.u64[0] & 0x8000000000000000ll) ? B.f64[0] : A.f64[0];
    A.f64[1] = (Mask.u64[1] & 0x8000000000000000ll) ? B.f64[1] : A.f64[1];
    return A.d;
}

/** \IMP{Reference,_mm_blendv_epi8, SSE4.1} */
SSP_FORCEINLINE __m128  ssp_blendv_ps_REF       ( __m128  a, __m128  b, __m128 mask )     
{
    ssp_m128 A, B, Mask;
    A.f = a;
    B.f = b;
    Mask.f = mask;

    A.f32[0] = (Mask.u32[0] & 0x80000000) ? B.f32[0] : A.f32[0];
    A.f32[1] = (Mask.u32[1] & 0x80000000) ? B.f32[1] : A.f32[1];
    A.f32[2] = (Mask.u32[2] & 0x80000000) ? B.f32[2] : A.f32[2];
    A.f32[3] = (Mask.u32[3] & 0x80000000) ? B.f32[3] : A.f32[3];
    return A.f;
}


//---------------------------------------
//Compare
//---------------------------------------
/** \IMP{Reference,_mm_cmpeq_epi64, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_cmpeq_epi64_REF( __m128i a, __m128i b )                       
{
    ssp_m128 A, B;
    A.i = a;
    B.i = b;

    if( A.s64[0] == B.s64[0] )
        A.s64[0] = 0xFFFFFFFFFFFFFFFFll;
    else
        A.s64[0] = 0x0ll;

    if( A.s64[1] == B.s64[1] )
        A.s64[1] = 0xFFFFFFFFFFFFFFFFll;
    else
        A.s64[1] = 0x0ll;
    return A.i;
}

//---------------------------------------
// Dot Product
//---------------------------------------
/** \IMP{Reference,_mm_dp_pd, SSE4.1} */
SSP_FORCEINLINE __m128d ssp_dp_pd_REF( __m128d a, __m128d b, const int mask )             
{
    ssp_f64 tmp[3];
    ssp_m128 A, B;
    A.d = a;
    B.d = b;

    tmp[0] = (mask & 0x10) ? (A.f64[0] * B.f64[0]) : 0.0;
    tmp[1] = (mask & 0x20) ? (A.f64[1] * B.f64[1]) : 0.0;

    tmp[2] = tmp[0] + tmp[1];

    A.f64[0] = (mask & 0x1) ? tmp[2] : 0.0;
    A.f64[1] = (mask & 0x2) ? tmp[2] : 0.0;
    return A.d;
}

/** \IMP{Reference,_mm_dp_ps, SSE4.1} */
SSP_FORCEINLINE __m128 ssp_dp_ps_REF( __m128 a, __m128 b, const int mask )                
{
    ssp_f32 tmp[5];
    ssp_m128 A, B;
    A.f = a;
    B.f = b;

    tmp[0] = (mask & 0x10) ? (A.f32[0] * B.f32[0]) : 0.0f;
    tmp[1] = (mask & 0x20) ? (A.f32[1] * B.f32[1]) : 0.0f;
    tmp[2] = (mask & 0x40) ? (A.f32[2] * B.f32[2]) : 0.0f;
    tmp[3] = (mask & 0x80) ? (A.f32[3] * B.f32[3]) : 0.0f;

    tmp[4] = tmp[0] + tmp[1] + tmp[2] + tmp[3];

    A.f32[0] = (mask & 0x1) ? tmp[4] : 0.0f;
    A.f32[1] = (mask & 0x2) ? tmp[4] : 0.0f;
    A.f32[2] = (mask & 0x4) ? tmp[4] : 0.0f;
    A.f32[3] = (mask & 0x8) ? tmp[4] : 0.0f;
    return A.f;
}

#define SSP_SATURATION(a, pos_limit, neg_limit) (a>0) ? ((a>pos_limit)?pos_limit:a) : ((a<neg_limit)?neg_limit:a)

/** \IMP{Reference,_mm_maddubs_epi16, SSSE3} */
SSP_FORCEINLINE __m128i ssp_maddubs_epi16_REF( __m128i a,  __m128i b)
{
    ssp_m128 A, B, C;
	int tmp[8];
    A.i = a;
    B.i = b;

	// a is 8 bit unsigned integer, b is signed integer
	tmp[0] = A.u8[0] * B.s8[0] +  A.u8[1] * B.s8[1];
	C.s16[0] = (ssp_s16)(SSP_SATURATION(tmp[0], 32767, -32768));

	tmp[1] = A.u8[2] * B.s8[2] +  A.u8[3] * B.s8[3];
	C.s16[1] = (ssp_s16)(SSP_SATURATION(tmp[1], 32767, -32768));

	tmp[2] = A.u8[4] * B.s8[4] +  A.u8[5] * B.s8[5];
	C.s16[2] = (ssp_s16)(SSP_SATURATION(tmp[2], 32767, -32768));

	tmp[3] = A.u8[6] * B.s8[6] +  A.u8[7] * B.s8[7];
	C.s16[3] = (ssp_s16)(SSP_SATURATION(tmp[3], 32767, -32768));

	tmp[4] = A.u8[8] * B.s8[8] +  A.u8[9] * B.s8[9];
	C.s16[4] = (ssp_s16)(SSP_SATURATION(tmp[4], 32767, -32768));

	tmp[5] = A.u8[10] * B.s8[10] +  A.u8[11] * B.s8[11];
	C.s16[5] = (ssp_s16)(SSP_SATURATION(tmp[5], 32767, -32768));

	tmp[6] = A.u8[12] * B.s8[12] +  A.u8[13] * B.s8[13];
	C.s16[6] = (ssp_s16)(SSP_SATURATION(tmp[6], 32767, -32768));

	tmp[7] = A.u8[14] * B.s8[14] +  A.u8[15] * B.s8[15];
	C.s16[7] = (ssp_s16)(SSP_SATURATION(tmp[7], 32767, -32768));

	return C.i;
}

/** \IMP{Reference,_mm_maddubs_pi16, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
 */
//__m64 _mm_maddubs_pi16( __m64 a,  __m64 b); [SSSE3]
SSP_FORCEINLINE __m64 ssp_maddubs_pi16_REF( __m64 a,  __m64 b)
{
    ssp_m64 A, B, C;
	int tmp[8];
    A.m64 = a;
    B.m64 = b;

	// a is 8 bit unsigned integer, b is signed integer
	tmp[0] = A.u8[0] * B.s8[0] +  A.u8[1] * B.s8[1];
	C.s16[0] = (ssp_s16)(SSP_SATURATION(tmp[0], 32767, -32768));

	tmp[1] = A.u8[2] * B.s8[2] +  A.u8[3] * B.s8[3];
	C.s16[1] = (ssp_s16)(SSP_SATURATION(tmp[1], 32767, -32768));

	tmp[2] = A.u8[4] * B.s8[4] +  A.u8[5] * B.s8[5];
	C.s16[2] = (ssp_s16)(SSP_SATURATION(tmp[2], 32767, -32768));

	tmp[3] = A.u8[6] * B.s8[6] +  A.u8[7] * B.s8[7];
	C.s16[3] = (ssp_s16)(SSP_SATURATION(tmp[3], 32767, -32768));

	return C.m64;
}

//__m128i _mm_mulhrs_epi16( __m128i a,  __m128i b);
/** \IMP{Reference,_mm_mulhrs_epi16, SSSE3} */
SSP_FORCEINLINE __m128i ssp_mulhrs_epi16_REF( __m128i a, __m128i b )
{
    ssp_m128 A,B;
    A.i = a;
    B.i = b;

	A.s16[0] = (ssp_s16) ((A.s16[0] * B.s16[0] + 0x4000) >> 15);
	A.s16[1] = (ssp_s16) ((A.s16[1] * B.s16[1] + 0x4000) >> 15);
	A.s16[2] = (ssp_s16) ((A.s16[2] * B.s16[2] + 0x4000) >> 15);
	A.s16[3] = (ssp_s16) ((A.s16[3] * B.s16[3] + 0x4000) >> 15);
	A.s16[4] = (ssp_s16) ((A.s16[4] * B.s16[4] + 0x4000) >> 15);
	A.s16[5] = (ssp_s16) ((A.s16[5] * B.s16[5] + 0x4000) >> 15);
	A.s16[6] = (ssp_s16) ((A.s16[6] * B.s16[6] + 0x4000) >> 15);
	A.s16[7] = (ssp_s16) ((A.s16[7] * B.s16[7] + 0x4000) >> 15);

    return A.i;
}

//__m64 _mm_mulhrs_epi16( __m64 a,  __m64 b);
/** \IMP{Reference,_mm_mulhrs_pi16, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSP_FORCEINLINE __m64 ssp_mulhrs_pi16_REF( __m64 a, __m64 b )
{
    ssp_m64 A,B;
    A.m64 = a;
    B.m64 = b;

	A.s16[0] = (ssp_s16) ((A.s16[0] * B.s16[0] + 0x4000) >> 15);
	A.s16[1] = (ssp_s16) ((A.s16[1] * B.s16[1] + 0x4000) >> 15);
	A.s16[2] = (ssp_s16) ((A.s16[2] * B.s16[2] + 0x4000) >> 15);
	A.s16[3] = (ssp_s16) ((A.s16[3] * B.s16[3] + 0x4000) >> 15);

    return A.m64;
}

//---------------------------------------
//Extract
//---------------------------------------

// TODO PHS: Test the actual intrinsic to deterine what value is returned if he ndx/imm is a large number.
//           ie.  for _mm_extract_epi8, what is returned if ndx = 20 [since 20=0x14 > 0x0F]?
//           Repeat procedures for other extract functions.
/** \IMP{Reference,_mm_extract_epi8, SSE4.1} */
SSP_FORCEINLINE int ssp_extract_epi8_REF( __m128i a, const int ndx )                       
{
    ssp_m128 A;
    A.i = a;
    return (int)A.u8[ndx&0xF];
}

/** \IMP{Reference,_mm_extract_epi32, SSE4.1} */
SSP_FORCEINLINE int ssp_extract_epi32_REF( __m128i a, const int imm )                            
{
    ssp_m128 A;
    A.i = a;
    return (int)A.u32[imm&0x3];
}

/** \IMP{Reference,_mm_extract_epi64, SSE4.1} */
SSP_FORCEINLINE ssp_s64 ssp_extract_epi64_REF( __m128i a, const int ndx )                  
{
    ssp_m128 A;
    A.i = a;
    return A.s64[ndx & 0x1];
}

/** \IMP{Reference,_mm_extract_ps, SSE4.1} */
SSP_FORCEINLINE int ssp_extract_ps_REF( __m128 a, const int ndx )                          
{
    ssp_m128 A;
    A.f = a;
    return (int)A.s32[ndx&0x3];
}


/**  \IMP{Reference,_mm_extract_si64,SSE4a} 
\n  NOTE: The upper 64-bit of the destination register are undefined.
*/
SSP_FORCEINLINE __m128i ssp_extract_si64_REF( __m128i a ,__m128i b )        
{
    ssp_u32 len, ndx;
    ssp_s64 mask;
    ssp_m128 A, B;
    A.i = a;
    B.i = b;
    ndx = (ssp_u32)((B.u64[0] & 0x3F00) >> 8);    // Mask ndx field.
    len = (ssp_u32)((B.u64[0] & 0x003F));         // Mask len field.

    len = (len) ? len : 64;    
    if( (ndx+len) > 64 )               // If the sum of ndx and length is greater than 64, the results are undefined.
        return a;                      // If index = 0 and length = 0/64, extract all lower bits.
    mask = ~(-1 << len);
    A.u64[0] = A.u64[0] >> ndx;
    A.u64[0] = A.u64[0] & mask;
    return A.i;
}
/**  \IMP{Reference,_mm_extracti_si64,SSE4a}
\n  NOTE: The upper 64-bits of the destination register are undefined.
*/
SSP_FORCEINLINE __m128i ssp_extracti_si64_REF( __m128i a, int len, int ndx )   
{
    ssp_s64 mask;
    ssp_m128 A;
    A.i = a;
    ndx = ndx & 0x3F; // ndx % 64
    len = len & 0x3F; // len % 64

    len = (len) ? len : 64;    
    if( (ndx+len) > 64 )               // If the sum of ndx and length is greater than 64, the results are undefined.
        return a;                      // If index = 0 and length = 0/64, extract all lower bits.
    mask = ~(-1 << len);
    A.u64[0] = A.u64[0] >> ndx;
    A.u64[0] = A.u64[0] & mask;
    return A.i;
}



//---------------------------------------
// Horizontal Add
//---------------------------------------
/** \IMP{Reference,_mm_hadd_epi16, SSSE3} */
SSP_FORCEINLINE __m128i ssp_hadd_epi16_REF ( __m128i a, __m128i b )                       
{
    ssp_m128 A, B;
    A.i = a;
    B.i = b;

    A.s16[0] = A.s16[0] + A.s16[1];
    A.s16[1] = A.s16[2] + A.s16[3];
    A.s16[2] = A.s16[4] + A.s16[5];
    A.s16[3] = A.s16[6] + A.s16[7];
    A.s16[4] = B.s16[0] + B.s16[1];
    A.s16[5] = B.s16[2] + B.s16[3];
    A.s16[6] = B.s16[4] + B.s16[5];
    A.s16[7] = B.s16[6] + B.s16[7];
    return A.i;
}

/** \IMP{Reference,_mm_hadd_epi32, SSSE3} */
SSP_FORCEINLINE __m128i ssp_hadd_epi32_REF ( __m128i a, __m128i b )                        
{
    ssp_m128 A, B;
    A.i = a;
    B.i = b;

    A.s32[0] = A.s32[0] + A.s32[1];
    A.s32[1] = A.s32[2] + A.s32[3];
    A.s32[2] = B.s32[0] + B.s32[1];
    A.s32[3] = B.s32[2] + B.s32[3];

    return A.i;
}

/** \IMP{Reference,_mm_hadd_pi16, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSP_FORCEINLINE __m64 ssp_hadd_pi16_REF ( __m64 a, __m64 b )                        
{
    ssp_m64 A, B;
    A.m64 = a;
    B.m64 = b;

    A.s16[0] = A.s16[0] + A.s16[1];
    A.s16[1] = A.s16[2] + A.s16[3];
    A.s16[2] = B.s16[0] + B.s16[1];
    A.s16[3] = B.s16[2] + B.s16[3];

    return A.m64;
}

/** \IMP{Reference,_mm_add_pi32, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSP_FORCEINLINE __m64 ssp_hadd_pi32_REF ( __m64 a, __m64 b )                        
{
    ssp_m64 A, B;
    A.m64 = a;
    B.m64 = b;

    A.s32[0] = A.s32[0] + A.s32[1];
    A.s32[1] = B.s32[0] + B.s32[1];

    return A.m64;
}

/** \IMP{Reference,_mm_hadds_epi16, SSSE3} */
SSP_FORCEINLINE __m128i ssp_hadds_epi16_REF ( __m128i a, __m128i b )                         
{
    ssp_m128 A, B;
	int answer[8];
    A.i = a;
    B.i = b;

	answer[0] = A.s16[0] + A.s16[1];
    A.s16[0]  = (ssp_s16) (SSP_SATURATION(answer[0], 32767, -32768));
	answer[1] = A.s16[2] + A.s16[3];
    A.s16[1]  = (ssp_s16) (SSP_SATURATION(answer[1], 32767, -32768));
	answer[2] = A.s16[4] + A.s16[5];
    A.s16[2]  = (ssp_s16) (SSP_SATURATION(answer[2], 32767, -32768));
	answer[3] = A.s16[6] + A.s16[7];
    A.s16[3]  = (ssp_s16) (SSP_SATURATION(answer[3], 32767, -32768));
	answer[4] = B.s16[0] + B.s16[1];
    A.s16[4]  = (ssp_s16) (SSP_SATURATION(answer[4], 32767, -32768));
	answer[5] = B.s16[2] + B.s16[3];
    A.s16[5]  = (ssp_s16) (SSP_SATURATION(answer[5], 32767, -32768));
	answer[6] = B.s16[4] + B.s16[5];
    A.s16[6]  = (ssp_s16) (SSP_SATURATION(answer[6], 32767, -32768));
	answer[7] = B.s16[6] + B.s16[7];
    A.s16[7]  = (ssp_s16) (SSP_SATURATION(answer[7], 32767, -32768));

	return A.i;
}

/** \IMP{Reference,_mm_hadds_pi16, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSP_FORCEINLINE __m64 ssp_hadds_pi16_REF ( __m64 a, __m64 b )                         
{
    ssp_m64 A, B;
	int answer[4];
    A.m64 = a;
    B.m64 = b;

	answer[0] = A.s16[0] + A.s16[1];
    A.s16[0]  = (ssp_s16) (SSP_SATURATION(answer[0], 32767, -32768));
	answer[1] = A.s16[2] + A.s16[3];
    A.s16[1]  = (ssp_s16) (SSP_SATURATION(answer[1], 32767, -32768));
	answer[2] = B.s16[0] + B.s16[1];
    A.s16[2]  = (ssp_s16) (SSP_SATURATION(answer[2], 32767, -32768));
	answer[3] = B.s16[2] + B.s16[3];
    A.s16[3]  = (ssp_s16) (SSP_SATURATION(answer[3], 32767, -32768));

	return A.m64;
}

/** \IMP{Reference,_mm_hadd_ps, SSSE3} */
SSP_FORCEINLINE __m128 ssp_hadd_ps_REF(__m128 a, __m128 b)                                 
{
    ssp_m128 A, B;
    A.f = a;
    B.f = b;

    A.f32[0] = A.f32[0] + A.f32[1];
    A.f32[1] = A.f32[2] + A.f32[3];
    A.f32[2] = B.f32[0] + B.f32[1];
    A.f32[3] = B.f32[2] + B.f32[3];
    return A.f;
}

/** \IMP{Reference,_mm_hadd_pd, SSSE3} */
SSP_FORCEINLINE __m128d ssp_hadd_pd_REF(__m128d a, __m128d b)                               
{
    ssp_m128 A, B;
    A.d = a;
    B.d = b;

    A.f64[0] = A.f64[0] + A.f64[1];
    A.f64[1] = B.f64[0] + B.f64[1];
    return A.d;
}


//---------------------------------------
// Horizontal Subtract
//---------------------------------------
/** \IMP{Reference,_mm_hsub_epi16, SSSE3} */
SSP_FORCEINLINE __m128i ssp_hsub_epi16_REF ( __m128i a, __m128i b )                        
{
    ssp_m128 A, B;
    A.i = a;
    B.i = b;

    A.s16[0] = A.s16[0] - A.s16[1];
    A.s16[1] = A.s16[2] - A.s16[3];
    A.s16[2] = A.s16[4] - A.s16[5];
    A.s16[3] = A.s16[6] - A.s16[7];
    A.s16[4] = B.s16[0] - B.s16[1];
    A.s16[5] = B.s16[2] - B.s16[3];
    A.s16[6] = B.s16[4] - B.s16[5];
    A.s16[7] = B.s16[6] - B.s16[7];

	return A.i;
}

/** \IMP{Reference,_mm_hsub_epi32, SSSE3} */
SSP_FORCEINLINE __m128i ssp_hsub_epi32_REF ( __m128i a, __m128i b )                        
{
    ssp_m128 A, B;
    A.i = a;
    B.i = b;

    A.s32[0] = A.s32[0] - A.s32[1];
    A.s32[1] = A.s32[2] - A.s32[3];
    A.s32[2] = B.s32[0] - B.s32[1];
    A.s32[3] = B.s32[2] - B.s32[3];

    return A.i;
}

/** \IMP{Reference,_mm_hsub_pi16, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSP_FORCEINLINE __m64 ssp_hsub_pi16_REF ( __m64 a, __m64 b )                         
{
    ssp_m64 A, B;
    A.m64 = a;
    B.m64 = b;

    A.s16[0] = A.s16[0] - A.s16[1];
    A.s16[1] = A.s16[2] - A.s16[3];
    A.s16[2] = B.s16[0] - B.s16[1];
    A.s16[3] = B.s16[2] - B.s16[3];

	return A.m64;
}

/** \IMP{Reference,_mm_hsub_pi32, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSP_FORCEINLINE __m64 ssp_hsub_pi32_REF ( __m64 a, __m64 b )                         
{
    ssp_m64 A, B;
    A.m64 = a;
    B.m64 = b;

    A.s32[0] = A.s32[0] - A.s32[1];
    A.s32[1] = B.s32[0] - B.s32[1];

    return A.m64;
}

/** \IMP{Reference,_mm_hsubs_epi16, SSSE3} */
SSP_FORCEINLINE __m128i ssp_hsubs_epi16_REF ( __m128i a, __m128i b )                 
{
    ssp_m128 A, B;
	int answer[8];
    A.i = a;
    B.i = b;

	answer[0] = A.s16[0] - A.s16[1];
    A.s16[0]  = (ssp_s16) (SSP_SATURATION(answer[0], 32767, -32768));
	answer[1] = A.s16[2] - A.s16[3];
    A.s16[1]  = (ssp_s16) (SSP_SATURATION(answer[1], 32767, -32768));
	answer[2] = A.s16[4] - A.s16[5];
    A.s16[2]  = (ssp_s16) (SSP_SATURATION(answer[2], 32767, -32768));
	answer[3] = A.s16[6] - A.s16[7];
    A.s16[3]  = (ssp_s16) (SSP_SATURATION(answer[3], 32767, -32768));
	answer[4] = B.s16[0] - B.s16[1];
    A.s16[4]  = (ssp_s16) (SSP_SATURATION(answer[4], 32767, -32768));
	answer[5] = B.s16[2] - B.s16[3];
    A.s16[5]  = (ssp_s16) (SSP_SATURATION(answer[5], 32767, -32768));
	answer[6] = B.s16[4] - B.s16[5];
    A.s16[6]  = (ssp_s16) (SSP_SATURATION(answer[6], 32767, -32768));
	answer[7] = B.s16[6] - B.s16[7];
    A.s16[7]  = (ssp_s16) (SSP_SATURATION(answer[7], 32767, -32768));

	return A.i;
}

/** \IMP{Reference,_mm_hsubs_pi16, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSP_FORCEINLINE __m64 ssp_hsubs_pi16_REF ( __m64 a, __m64 b )                        
{
    ssp_m64 A, B;
	int answer[4];
    A.m64 = a;
    B.m64 = b;

	answer[0] = A.s16[0] - A.s16[1];
    A.s16[0]  = (ssp_s16) (SSP_SATURATION(answer[0], 32767, -32768));
	answer[1] = A.s16[2] - A.s16[3];
    A.s16[1]  = (ssp_s16) (SSP_SATURATION(answer[1], 32767, -32768));
	answer[2] = B.s16[0] - B.s16[1];
    A.s16[2]  = (ssp_s16) (SSP_SATURATION(answer[2], 32767, -32768));
	answer[3] = B.s16[2] - B.s16[3];
    A.s16[3]  = (ssp_s16) (SSP_SATURATION(answer[3], 32767, -32768));

	return A.m64;
}

/** \IMP{Reference,_mm_hsub_ps, SSSE3} */
SSP_FORCEINLINE __m128 ssp_hsub_ps_REF(__m128 a, __m128 b)                           
{
    ssp_m128 A, B;
    A.f = a;
    B.f = b;

    A.f32[0] = A.f32[0] - A.f32[1];
    A.f32[1] = A.f32[2] - A.f32[3];
    A.f32[2] = B.f32[0] - B.f32[1];
    A.f32[3] = B.f32[2] - B.f32[3];
    return A.f;
}

/** \IMP{Reference,_mm_hsub_pd, SSSE3} */
SSP_FORCEINLINE __m128d ssp_hsub_pd_REF(__m128d a, __m128d b)                        
{
    ssp_m128 A, B;
    A.d = a;
    B.d = b;

    A.f64[0] = A.f64[0] - A.f64[1];
    A.f64[1] = B.f64[0] - B.f64[1];
    return A.d;
}

//---------------------------------------
//Insert
//---------------------------------------
/** \IMP{Reference,_mm_insert_epi8, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_insert_epi8_REF( __m128i a, int b, const int ndx )       // Verify behavior on Intel Hardware
{
    ssp_m128 A;
    A.i = a;

    A.s8[ndx & 0xF] = (ssp_s8)b;
    return A.i;
}

/** \IMP{Reference,_mm_insert_epi32, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_insert_epi32_REF( __m128i a, int b, const int ndx )      // Verify behavior on Intel Hardware
{
    ssp_m128 A;
    A.i = a;

    A.s32[ndx & 0x3] = b;
    return A.i;
}

/** \IMP{Reference,_mm_insert_epi64, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_insert_epi64_REF( __m128i a, ssp_s64 b, const int ndx )  // Verify behavior on Intel Hardware
{
    ssp_m128 A;
    A.i = a;

    A.s64[ndx & 0x1] = b;
    return A.i;
}

/** \IMP{Reference,_mm_insert_ps, SSE4.1} */
SSP_FORCEINLINE __m128 ssp_insert_ps_REF( __m128 a, __m128 b, const int sel )          // Verify behavior on Intel Hardware
{
    ssp_f32 tmp;
    int count_d,zmask;

    ssp_m128 A,B;
    A.f = a;
    B.f = b;

    tmp     = B.f32[(sel & 0xC0)>>6];   // 0xC0 = sel[7:6]
    count_d = (sel & 0x30)>>4;          // 0x30 = sel[5:4]
    zmask   = sel & 0x0F;               // 0x0F = sel[3:0]

    A.f32[count_d] = tmp;

    A.f32[0] = (zmask & 0x1) ? 0 : A.f32[0];
    A.f32[1] = (zmask & 0x2) ? 0 : A.f32[1];
    A.f32[2] = (zmask & 0x4) ? 0 : A.f32[2];
    A.f32[3] = (zmask & 0x8) ? 0 : A.f32[3];
    return A.f;
}

/** \IMP{Reference,_mm_insert_si64, SSE4a} */
SSP_FORCEINLINE __m128i ssp_insert_si64_REF( __m128i a, __m128i b )
{
    ssp_u32  ndx, len;
    ssp_s64  mask;
    ssp_m128 A, B;
    B.i = b;
    ndx = (ssp_u32)((B.u64[1] & 0x3F00) >> 8);    // Mask length field.
    len = (ssp_u32)((B.u64[1] & 0x003F));         // Mask ndx field.

    if( ( (ndx + len) > 64 ) ||
        ( (len == 0) && (ndx > 0) ) )
        return a;

    A.i = a;
    if( (len == 0 ) && (ndx == 0) )
    {
        A.u64[0] = B.u64[0];
        return A.i;
    }

    len = (len) ? len : 64;         // A value of zero for field length is interpreted as 64.
    mask = ~(-1 << len);
    B.u64[0]  = B.u64[0] & mask;
    B.u64[0]  = B.u64[0] << ndx;
    mask      = ~(mask << ndx);
    A.u64[0]  = A.u64[0] & mask;
    A.u64[0] |= B.u64[0];
    return A.i;
}

/** \IMP{Reference,_mm_inserti_si64, SSE4a} */
SSP_FORCEINLINE __m128i ssp_inserti_si64_REF( __m128i a, __m128i b, int len, int ndx )
{
    ssp_s64 mask;
    ssp_m128 A, B;
    A.i = a;
    ndx = ndx & 0x3F; // ndx % 64
    len = len & 0x3F; // len % 64

    if( ( (ndx + len) > 64 ) ||
        ( (len == 0) && (ndx > 0) ) )
        return a;

    B.i = b;
    if( (len == 0 ) && (ndx == 0) )
    {
        A.u64[0] = B.u64[0];
        return A.i;
    }

    len = (len) ? len : 64;         // A value of zero for field length is interpreted as 64.
    mask = ~(-1 << len);
    B.u64[0]  = B.u64[0] & mask;
    B.u64[0]  = B.u64[0] << ndx;
    mask      = ~(mask << ndx);
    A.u64[0]  = A.u64[0] & mask;
    A.u64[0] |= B.u64[0];
    return A.i;
}



//---------------------------------------
// Load
//---------------------------------------
/** \IMP{Reference,_mm_loaddup_pd, SSE3} */
SSP_FORCEINLINE __m128d ssp_loaddup_pd_REF(double const * dp)                               
{
    ssp_m128 a;
    a.f64[0] = *dp;
    a.f64[1] = *dp;
    return a.d;
}

/** \IMP{Reference,_mm_lddqu_si128, SSE3} */
SSP_FORCEINLINE __m128i ssp_lddqu_si128_REF(__m128i const *p)                               
{
    return *p;
}

/** \IMP{Reference,_mm_stream_load_si128, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_stream_load_si128_REF( __m128i *p )                             
{
    return *p;
}


//---------------------------------------
// Min / Max
//---------------------------------------

#define SSP_SET_MIN( sd, s) sd=(sd<s)?sd:s;
#define SSP_SET_MAX( sd, s) sd=(sd>s)?sd:s;

//8 bit min/max
/** \IMP{Reference,_mm_min_epi8, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_min_epi8_REF( __m128i a, __m128i b )
{
    ssp_m128 A,B;
    A.i = a;
    B.i = b;

    SSP_SET_MIN( A.s8[ 0], B.s8[ 0] );
    SSP_SET_MIN( A.s8[ 1], B.s8[ 1] );
    SSP_SET_MIN( A.s8[ 2], B.s8[ 2] );
    SSP_SET_MIN( A.s8[ 3], B.s8[ 3] );
    SSP_SET_MIN( A.s8[ 4], B.s8[ 4] );
    SSP_SET_MIN( A.s8[ 5], B.s8[ 5] );
    SSP_SET_MIN( A.s8[ 6], B.s8[ 6] );
    SSP_SET_MIN( A.s8[ 7], B.s8[ 7] );
    SSP_SET_MIN( A.s8[ 8], B.s8[ 8] );
    SSP_SET_MIN( A.s8[ 9], B.s8[ 9] );
    SSP_SET_MIN( A.s8[10], B.s8[10] );
    SSP_SET_MIN( A.s8[11], B.s8[11] );
    SSP_SET_MIN( A.s8[12], B.s8[12] );
    SSP_SET_MIN( A.s8[13], B.s8[13] );
    SSP_SET_MIN( A.s8[14], B.s8[14] );
    SSP_SET_MIN( A.s8[15], B.s8[15] );
    return A.i;
}

/** \IMP{Reference,_mm_max_epi8, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_max_epi8_REF( __m128i a, __m128i b )
{
    ssp_m128 A,B;
    A.i = a;
    B.i = b;

    SSP_SET_MAX( A.s8[ 0], B.s8[ 0] );
    SSP_SET_MAX( A.s8[ 1], B.s8[ 1] );
    SSP_SET_MAX( A.s8[ 2], B.s8[ 2] );
    SSP_SET_MAX( A.s8[ 3], B.s8[ 3] );
    SSP_SET_MAX( A.s8[ 4], B.s8[ 4] );
    SSP_SET_MAX( A.s8[ 5], B.s8[ 5] );
    SSP_SET_MAX( A.s8[ 6], B.s8[ 6] );
    SSP_SET_MAX( A.s8[ 7], B.s8[ 7] );
    SSP_SET_MAX( A.s8[ 8], B.s8[ 8] );
    SSP_SET_MAX( A.s8[ 9], B.s8[ 9] );
    SSP_SET_MAX( A.s8[10], B.s8[10] );
    SSP_SET_MAX( A.s8[11], B.s8[11] );
    SSP_SET_MAX( A.s8[12], B.s8[12] );
    SSP_SET_MAX( A.s8[13], B.s8[13] );
    SSP_SET_MAX( A.s8[14], B.s8[14] );
    SSP_SET_MAX( A.s8[15], B.s8[15] );
    return A.i;
}

//16 bit min/max
/** \IMP{Reference,_mm_min_epu16, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_min_epu16_REF ( __m128i a, __m128i b )
{
    ssp_m128 A,B;
    A.i = a;
    B.i = b;

    SSP_SET_MIN( A.u16[ 0], B.u16[ 0] );
    SSP_SET_MIN( A.u16[ 1], B.u16[ 1] );
    SSP_SET_MIN( A.u16[ 2], B.u16[ 2] );
    SSP_SET_MIN( A.u16[ 3], B.u16[ 3] );
    SSP_SET_MIN( A.u16[ 4], B.u16[ 4] );
    SSP_SET_MIN( A.u16[ 5], B.u16[ 5] );
    SSP_SET_MIN( A.u16[ 6], B.u16[ 6] );
    SSP_SET_MIN( A.u16[ 7], B.u16[ 7] );
    return A.i;
}

/** \IMP{Reference,_mm_max_epu16, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_max_epu16_REF ( __m128i a, __m128i b )
{
    ssp_m128 A,B;
    A.i = a;
    B.i = b;

    SSP_SET_MAX( A.u16[ 0], B.u16[ 0] );
    SSP_SET_MAX( A.u16[ 1], B.u16[ 1] );
    SSP_SET_MAX( A.u16[ 2], B.u16[ 2] );
    SSP_SET_MAX( A.u16[ 3], B.u16[ 3] );
    SSP_SET_MAX( A.u16[ 4], B.u16[ 4] );
    SSP_SET_MAX( A.u16[ 5], B.u16[ 5] );
    SSP_SET_MAX( A.u16[ 6], B.u16[ 6] );
    SSP_SET_MAX( A.u16[ 7], B.u16[ 7] );
    return A.i;
}

//32 bit min/max
/** \IMP{Reference,_mm_min_epi32, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_min_epi32_REF( __m128i a, __m128i b )                     
{
    ssp_m128 A,B;
    A.i = a;
    B.i = b;

    SSP_SET_MIN( A.s32[ 0], B.s32[ 0] );
    SSP_SET_MIN( A.s32[ 1], B.s32[ 1] );
    SSP_SET_MIN( A.s32[ 2], B.s32[ 2] );
    SSP_SET_MIN( A.s32[ 3], B.s32[ 3] );
    return A.i;
}

/** \IMP{Reference,_mm_max_epi32, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_max_epi32_REF( __m128i a, __m128i b )                     
{
    ssp_m128 A,B;
    A.i = a;
    B.i = b;

    SSP_SET_MAX( A.s32[ 0], B.s32[ 0] );
    SSP_SET_MAX( A.s32[ 1], B.s32[ 1] );
    SSP_SET_MAX( A.s32[ 2], B.s32[ 2] );
    SSP_SET_MAX( A.s32[ 3], B.s32[ 3] );
    return A.i;
}

/** \IMP{Reference,_mm_min_epu32, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_min_epu32_REF ( __m128i a, __m128i b )                    
{
    ssp_m128 A,B;
    A.i = a;
    B.i = b;

    SSP_SET_MIN( A.u32[ 0], B.u32[ 0] );
    SSP_SET_MIN( A.u32[ 1], B.u32[ 1] );
    SSP_SET_MIN( A.u32[ 2], B.u32[ 2] );
    SSP_SET_MIN( A.u32[ 3], B.u32[ 3] );
    return A.i;
}

/** \IMP{Reference,_mm_max_epu32, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_max_epu32_REF ( __m128i a, __m128i b )                    
{
    ssp_m128 A,B;
    A.i = a;
    B.i = b;

    SSP_SET_MAX( A.u32[ 0], B.u32[ 0] );
    SSP_SET_MAX( A.u32[ 1], B.u32[ 1] );
    SSP_SET_MAX( A.u32[ 2], B.u32[ 2] );
    SSP_SET_MAX( A.u32[ 3], B.u32[ 3] );
    return A.i;
}

#undef SSP_SET_MIN
#undef SSP_SET_MAX

/** \IMP{Reference,_mm_minpos_epu16, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_minpos_epu16_REF( __m128i shortValues )                   
{
    ssp_m128 ShortValues;
    ShortValues.i = shortValues;

    if( ShortValues.u16[1] < ShortValues.u16[0] )
    {
        ShortValues.u16[0] = ShortValues.u16[1];
        ShortValues.u16[1] = 1;
    }
    else
        ShortValues.u16[1] = 0;


#define FN( I )                                     \
    if( ShortValues.u16[I] < ShortValues.u16[0] )   \
    {                                               \
        ShortValues.u16[0] = ShortValues.u16[I];    \
        ShortValues.u16[1] = I;                     \
    }

    FN( 2 );
    FN( 3 );
    FN( 4 );
    FN( 5 );
    FN( 6 );
    FN( 7 );

    ShortValues.u32[1] = 0;
    ShortValues.u64[1] = 0;

#undef FN

    return ShortValues.i;
}

/** \IMP{Reference,_mm_minpos_epu16, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_minpos_epu16_REFb( __m128i shortValues )                   
{
    ssp_m128 ShortValues;
    ssp_u32 i;
    ssp_u16 pos = 0;
    ssp_u16 minVal;
    ShortValues.i = shortValues;
    minVal = ShortValues.u16[0];

    for( i=1; i<8; ++i )
    {
        if( ShortValues.u16[i] < minVal )
        {
            minVal = ShortValues.u16[i];
            pos    = i;
        }

        ShortValues.u16[i] = 0;
    }

    ShortValues.u16[0] = minVal;
    ShortValues.u16[1] = pos;
    return ShortValues.i;
}


//---------------------------------------
// Move
//---------------------------------------
/** \IMP{Reference,_mm_movehdup_ps, SSE3} */
SSP_FORCEINLINE __m128 ssp_movehdup_ps_REF(__m128 a)                                   
{
    ssp_m128 A;
    A.f = a;

    A.f32[0] = A.f32[1];
    A.f32[2] = A.f32[3];
    return A.f;
}

/** \IMP{Reference,_mm_moveldup_ps, SSE3} */
SSP_FORCEINLINE __m128 ssp_moveldup_ps_REF(__m128 a)                                   
{
    ssp_m128 A;
    A.f = a;

    A.f32[1] = A.f32[0];
    A.f32[3] = A.f32[2];
    return A.f;
}

/** \IMP{Reference,_mm_movedup_pd, SSE3} */
SSP_FORCEINLINE __m128d ssp_movedup_pd_REF(__m128d a)                                  
{
    ssp_m128 A;
    A.d = a;

    A.f64[1] = A.f64[0];
    return A.d;
}

//---------------------------------------
// Multiply
//---------------------------------------
/** \IMP{Reference,_mm_mul_epi32, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_mul_epi32_REF( __m128i a, __m128i b )                      
{
    ssp_m128 A,B;
    A.i = a;
    B.i = b;

    A.s64[0] = A.s32[0] * B.s32[0];
    A.s64[1] = A.s32[2] * B.s32[2];
    return A.i;
}

/** \IMP{Reference,_mm_mullo_epi32, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_mullo_epi32_REF( __m128i a, __m128i b )                    
{
    ssp_m128 A,B;
    A.i = a;
    B.i = b;

    A.s32[0] = A.s32[0] + B.s32[0];
    A.s32[1] = A.s32[1] + B.s32[1];
    A.s32[2] = A.s32[2] + B.s32[2];
    A.s32[3] = A.s32[3] + B.s32[3];
    return A.i;
}

/** \IMP{Reference,_mm_mpsadbw_epu8, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_mpsadbw_epu8_REF ( __m128i a,   __m128i b,   const int msk  ) 
{
	ssp_u8 Abyte[11], Bbyte[4], tmp[4];
	ssp_u8 Boffset, Aoffset;
	int i;

    ssp_m128 A,B;
    A.i = a;
    B.i = b;

	Boffset = (msk & 0x3) << 2; // *32/8,   for byte size count
	Aoffset = (msk & 0x4);      // *32/8/4, for byte size count and shift msk to bit 2

	for (i=0; i<11; i++)
	{
		Abyte[i] = A.u8[i+Aoffset];
	}
	
	Bbyte[0] = B.u8[Boffset  ];
	Bbyte[1] = B.u8[Boffset+1];
	Bbyte[2] = B.u8[Boffset+2];
	Bbyte[3] = B.u8[Boffset+3];

	for (i=0; i<8; i++)
	{
		tmp[0] = (Abyte[i  ] > Bbyte[0]) ? (Abyte[i  ] - Bbyte[0]) :  (Bbyte[0] - Abyte[i  ]);        //abs diff
		tmp[1] = (Abyte[i+1] > Bbyte[1]) ? (Abyte[i+1] - Bbyte[1]) :  (Bbyte[1] - Abyte[i+1]);
		tmp[2] = (Abyte[i+2] > Bbyte[2]) ? (Abyte[i+2] - Bbyte[2]) :  (Bbyte[2] - Abyte[i+2]);
		tmp[3] = (Abyte[i+3] > Bbyte[3]) ? (Abyte[i+3] - Bbyte[3]) :  (Bbyte[3] - Abyte[i+3]);

		A.u16[i] = tmp[0] + tmp[1] + tmp[2] + tmp[3];
	}

	return A.i;
}

//---------------------------------------
// Pack
//---------------------------------------
/** \IMP{Reference,_mm_packus_epi32, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_packus_epi32_REF( __m128i a, __m128i b )                       
{
    ssp_m128 A,B;
    A.i = a;
    B.i = b;

    if( A.s32[0] < 0 )
        A.u16[0] = 0;
    else
        if( A.s32[0] > 0xFFFF )
            A.u16[0] = 0xFFFF;
        else
            A.s16[0] = (ssp_u16)A.s32[0];

    if( A.s32[1] < 0 )
        A.u16[1] = 0;
    else
        if( A.s32[1] > 0xFFFF )
            A.u16[1] = 0xFFFF;
        else
            A.s16[1] = (ssp_u16)A.s32[1];

    if( A.s32[2] < 0 )
        A.u16[2] = 0;
    else
        if( A.s32[2] > 0xFFFF )
            A.u16[2] = 0xFFFF;
        else
            A.s16[2] = (ssp_u16)A.s32[2];


    if( A.s32[3] < 0 )
        A.u16[3] = 0;
    else
        if( A.s32[3] > 0xFFFF )
            A.u16[3] = 0xFFFF;
        else
            A.s16[3] = (ssp_u16)A.s32[3];

    if( B.s32[0] < 0 )
        A.u16[4] = 0;
    else
        if( B.s32[0] > 0xFFFF )
            A.u16[4] = 0xFFFF;
        else
            A.s16[4] = (ssp_u16)B.s32[0];

    if( B.s32[1] < 0 )
        A.u16[5] = 0;
    else
        if( B.s32[1] > 0xFFFF )
            A.u16[5] = 0xFFFF;
        else
            A.s16[5] = (ssp_u16)B.s32[1];

    if( B.s32[2] < 0 )
        A.u16[6] = 0;
    else
        if( B.s32[2] > 0xFFFF )
            A.u16[6] = 0xFFFF;
        else
            A.s16[6] = (ssp_u16)B.s32[2];


    if( B.s32[3] < 0 )
        A.u16[7] = 0;
    else
        if( B.s32[3] > 0xFFFF )
            A.u16[7] = 0xFFFF;
        else
            A.s16[7] = (ssp_u16)B.s32[3];

    return A.i;
}


//---------------------------------------
// Round
//---------------------------------------
/** \IMP{Reference,_mm_ceil_pd, SSE4.1} */
SSP_FORCEINLINE __m128d ssp_ceil_pd_REF( __m128d a )                                        
{
    ssp_m128 A;
    A.d = a;    

    A.f64[0] = ceil( A.f64[0] );
    A.f64[1] = ceil( A.f64[1] );
    return A.d;
}

/** \IMP{Reference,_mm_ceil_ps, SSE4.1} */
SSP_FORCEINLINE __m128 ssp_ceil_ps_REF( __m128 a )                                          
{
    ssp_m128 A;
    A.f = a;

    A.f32[0] = (ssp_f32)ceil( A.f32[0] );
    A.f32[1] = (ssp_f32)ceil( A.f32[1] );
    A.f32[2] = (ssp_f32)ceil( A.f32[2] );
    A.f32[3] = (ssp_f32)ceil( A.f32[3] );
    return A.f;
}

/** \IMP{Reference,_mm_ceil_sd, SSE4.1} */
SSP_FORCEINLINE __m128d ssp_ceil_sd_REF( __m128d a, __m128d b)                              
{
    ssp_m128 A,B;
    A.d = a;
    B.d = b;

    A.f64[0] = ceil( B.f64[0] );
    return A.d;
}

/** \IMP{Reference,_mm_ceil_ss, SSE4.1} */
SSP_FORCEINLINE __m128 ssp_ceil_ss_REF( __m128  a, __m128  b)                               
{
    ssp_m128 A,B;
    A.f = a;
    B.f = b;

    A.f32[0] = (ssp_f32)ceil( B.f32[0] );
    return A.f;
}

/** \IMP{Reference,_mm_floor_pd, SSE4.1} */
SSP_FORCEINLINE __m128d ssp_floor_pd_REF( __m128d a )                                       
{
    ssp_m128 A;
    A.d = a;

    A.f64[0] = floor( A.f64[0] );
    A.f64[1] = floor( A.f64[1] );
    return A.d;
}

/** \IMP{Reference,_mm_floor_ps, SSE4.1} */
SSP_FORCEINLINE __m128 ssp_floor_ps_REF( __m128 a )                                         
{
    ssp_m128 A;
    A.f = a;

    A.f32[0] = (float)floor( A.f32[0] );
    A.f32[1] = (float)floor( A.f32[1] );
    A.f32[2] = (float)floor( A.f32[2] );
    A.f32[3] = (float)floor( A.f32[3] );
    return A.f;
}

/** \IMP{Reference,_mm_floor_sd, SSE4.1} */
SSP_FORCEINLINE __m128d ssp_floor_sd_REF( __m128d a, __m128d b )                            
{
    ssp_m128 A,B;
    A.d = a;
    B.d = b;

    A.f64[0] = floor( B.f64[0] );
    return A.d;
}

/** \IMP{Reference,_mm_floor_ss, SSE4.1} */
SSP_FORCEINLINE __m128  ssp_floor_ss_REF( __m128  a, __m128  b )                            
{
    ssp_m128 A,B;
    A.f = a;
    B.f = b;

    A.f32[0] = (float)floor( B.f32[0] );
    return A.f;
}

/** \IMP{Reference,_mm_round_pd, SSE4.1 and SSE5} */
SSP_FORCEINLINE __m128d ssp_round_pd_REF( __m128d val, int iRoundMode )                     
{
    ssp_s64 *valPtr;
    ssp_m128 Val;
    Val.d = val;

    switch( iRoundMode & 0x3 )
    {
    case SSP_FROUND_CUR_DIRECTION:
        break;
    case SSP_FROUND_TO_ZERO:
        valPtr = (ssp_s64*)(&Val.f64[0]);
        if( ssp_number_isValidNumber_F64_REF( valPtr ) )
            Val.f64[0] = (ssp_f64)( (ssp_s64)Val.f64[0] );

        valPtr = (ssp_s64*)(&Val.f64[1]);
        if( ssp_number_isValidNumber_F64_REF( valPtr ) )
            Val.f64[1] = (ssp_f64)( (ssp_s64)Val.f64[1] );
        break;
    case SSP_FROUND_TO_POS_INF:
        valPtr = (ssp_s64*)(&Val.f64[0]);
        if( ssp_number_isValidNumber_F64_REF( valPtr ) )
            Val.f64[0] = ceil( Val.f64[0] );

        valPtr = (ssp_s64*)(&Val.f64[1]);
        if( ssp_number_isValidNumber_F64_REF( valPtr ) )
            Val.f64[1] = ceil( Val.f64[1] );
        break;
    case SSP_FROUND_TO_NEG_INF:
        valPtr = (ssp_s64*)(&Val.f64[0]);
        if( ssp_number_isValidNumber_F64_REF( valPtr ) )
            Val.f64[0] = floor( Val.f64[0] );

        valPtr = (ssp_s64*)(&Val.f64[1]);
        if( ssp_number_isValidNumber_F64_REF( valPtr ) )
            Val.f64[1] = floor( Val.f64[1] );
        break;
    default: // SSP_FROUND_TO_NEAREST_INT
        valPtr = (ssp_s64*)(&Val.f64[0]);
        if( ssp_number_isValidNumber_F64_REF( valPtr ) )
            Val.f64[0] = (ssp_f64)( (Val.f64[0]>0) ? (ssp_s64)(Val.f64[0]+0.5) : (ssp_s64)(Val.f64[0]-0.5) );
        else
            Val.f64[0] = ssp_number_changeSNanToQNaN_F64_REF( valPtr );

        valPtr = (ssp_s64*)(&Val.f64[1]);
        if( ssp_number_isValidNumber_F64_REF( valPtr ) )
            Val.f64[1] = (ssp_f64)( (Val.f64[1]>0) ? (ssp_s64)(Val.f64[1]+0.5) : (ssp_s64)(Val.f64[1]-0.5) );
        else
            Val.f64[1] = ssp_number_changeSNanToQNaN_F64_REF( valPtr );
    }
    return Val.d;
}

/** \IMP{Reference,_mm_round_ps, SSE4.1 and SSE5} */
SSP_FORCEINLINE __m128  ssp_round_ps_REF( __m128  val, int iRoundMode )                     
{
    ssp_s32 *valPtr;
    ssp_m128 Val;
    Val.f = val;

    switch( iRoundMode & 0x3 )
    {
    case SSP_FROUND_CUR_DIRECTION:
        break;
    case SSP_FROUND_TO_ZERO:
        valPtr = (ssp_s32*)(&Val.f32[0]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
        {
            if( Val.f32[0] >= 0 )
                Val.f32[0] = (ssp_f32)( (ssp_s32)Val.f32[0] );
            else
            {
                Val.f32[0] = (ssp_f32)( (ssp_s32)Val.f32[0] );
                //Val.s32[0] = Val.s32[0] | 0x80000000;
            }
        }

        valPtr = (ssp_s32*)(&Val.f32[1]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
        {
            if( Val.f32[1] >= 0 )
                Val.f32[1] = (ssp_f32)( (ssp_s32)Val.f32[1] );
            else
            {
                Val.f32[1] = (ssp_f32)( (ssp_s32)Val.f32[1] );
                //Val.s32[1] = Val.s32[1] | 0x80000000;
            }
        }

        valPtr = (ssp_s32*)(&Val.f32[2]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
        {
            if( Val.f32[2] >= 0 )
                Val.f32[2] = (ssp_f32)( (ssp_s32)Val.f32[2] );
            else
            {
                Val.f32[2] = (ssp_f32)( (ssp_s32)Val.f32[2] );
                //Val.s32[2] = Val.s32[2] | 0x80000000;
            }
        }

        valPtr = (ssp_s32*)(&Val.f32[3]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
        {
            if( Val.f32[3] >= 0 )
                Val.f32[3] = (ssp_f32)( (ssp_s32)Val.f32[3] );
            else
            {
                Val.f32[3] = (ssp_f32)( (ssp_s32)Val.f32[3] );
                //Val.s32[3] = Val.s32[3] | 0x80000000;
            }
        }
        break;
    case SSP_FROUND_TO_POS_INF:
        valPtr = (ssp_s32*)(&Val.f32[0]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
            Val.f32[0] = (ssp_f32)ceil( Val.f32[0] );

        valPtr = (ssp_s32*)(&Val.f32[1]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
            Val.f32[1] = (ssp_f32)ceil( Val.f32[1] );

        valPtr = (ssp_s32*)(&Val.f32[2]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
            Val.f32[2] = (ssp_f32)ceil( Val.f32[2] );

        valPtr = (ssp_s32*)(&Val.f32[3]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
            Val.f32[3] = (ssp_f32)ceil( Val.f32[3] );
        break;
    case SSP_FROUND_TO_NEG_INF:
        valPtr = (ssp_s32*)(&Val.f32[0]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
            Val.f32[0] = (ssp_f32)floor( Val.f32[0] );

        valPtr = (ssp_s32*)(&Val.f32[1]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
            Val.f32[1] = (ssp_f32)floor( Val.f32[1] );

        valPtr = (ssp_s32*)(&Val.f32[2]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
            Val.f32[2] = (ssp_f32)floor( Val.f32[2] );

        valPtr = (ssp_s32*)(&Val.f32[3]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
            Val.f32[3] = (ssp_f32)floor( Val.f32[3] );
        break;
    default: // SSP_FROUND_TO_NEAREST_INT
        valPtr = (ssp_s32*)(&Val.f32[0]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
            Val.f32[0] = (ssp_f32)( (Val.f32[0]>0) ? (ssp_s32)(Val.f32[0]+0.5) : (ssp_s32)(Val.f32[0]-0.5) );
        else
            Val.f32[0] = ssp_number_changeSNanToQNaN_F32_REF( valPtr );

        valPtr = (ssp_s32*)(&Val.f32[1]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
            Val.f32[1] = (ssp_f32)( (Val.f32[1]>0) ? (ssp_s32)(Val.f32[1]+0.5) : (ssp_s32)(Val.f32[1]-0.5) );
        else
            Val.f32[1] = ssp_number_changeSNanToQNaN_F32_REF( valPtr );

        valPtr = (ssp_s32*)(&Val.f32[2]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
            Val.f32[2] = (ssp_f32)( (Val.f32[2]>0) ? (ssp_s32)(Val.f32[2]+0.5) : (ssp_s32)(Val.f32[2]-0.5) );
        else
            Val.f32[2] = ssp_number_changeSNanToQNaN_F32_REF( valPtr );

        valPtr = (ssp_s32*)(&Val.f32[3]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
            Val.f32[3] = (ssp_f32)( (Val.f32[3]>0) ? (ssp_s32)(Val.f32[3]+0.5) : (ssp_s32)(Val.f32[3]-0.5) );
        else
            Val.f32[3] = ssp_number_changeSNanToQNaN_F32_REF( valPtr );
    }

    if( -0.0f == Val.f32[0] ) Val.f32[0]=+0.0f;
    if( -0.0f == Val.f32[1] ) Val.f32[1]=+0.0f;
    if( -0.0f == Val.f32[2] ) Val.f32[2]=+0.0f;
    if( -0.0f == Val.f32[3] ) Val.f32[3]=+0.0f;

    return Val.f;
}

/** \IMP{Reference,_mm_round_sd, SSE4.1 and SSE5} */
SSP_FORCEINLINE __m128d ssp_round_sd_REF( __m128d dst, __m128d val, int iRoundMode )        
{
    ssp_s64 *valPtr;
    ssp_m128 Dst, Val;
    Dst.d = dst;
    Val.d = val;

    switch( iRoundMode & 0x3 )
    {
    case SSP_FROUND_CUR_DIRECTION:
        break;
    case SSP_FROUND_TO_ZERO:
        valPtr = (ssp_s64*)(&Val.f64[0]);
        if( ssp_number_isValidNumber_F64_REF( valPtr ) )
            Dst.f64[0] = (ssp_f64)( (ssp_s64)Val.f64[0] );
        break;
    case SSP_FROUND_TO_POS_INF:
        valPtr = (ssp_s64*)(&Val.f64[0]);
        if( ssp_number_isValidNumber_F64_REF( valPtr ) )
            Val.f64[0] = ceil( Val.f64[0] );
        break;
    case SSP_FROUND_TO_NEG_INF:
        valPtr = (ssp_s64*)(&Val.f64[0]);
        if( ssp_number_isValidNumber_F64_REF( valPtr ) )
            Val.f64[0] = floor( Val.f64[0] );
        break;
    default: // SSP_FROUND_TO_NEAREST_INT
        valPtr = (ssp_s64*)(&Val.f64[0]);
        if( ssp_number_isValidNumber_F64_REF( valPtr ) )
            Val.f64[0] = (ssp_f64)( (Val.f64[0]>0) ? (ssp_s64)(Val.f64[0]+0.5) : (ssp_s64)(Val.f64[0]-0.5) );
        else
            Val.f64[0] = ssp_number_changeSNanToQNaN_F64_REF( valPtr );
    }
    return Dst.d;
}

/** \IMP{Reference,_mm_round_ss, SSE4.1 and SSE5} */
SSP_FORCEINLINE __m128  ssp_round_ss_REF( __m128  dst, __m128  val, int iRoundMode )        //_mm_round_ss
{
    ssp_s32 *valPtr;
    ssp_m128 Dst, Val;
    Dst.f = dst;
    Val.f = val;

    switch( iRoundMode & 0x3 )
    {
    case SSP_FROUND_CUR_DIRECTION:
        break;
    case SSP_FROUND_TO_ZERO:
        valPtr = (ssp_s32*)(&Val.f32[0]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
        {
            Dst.f32[0] = (ssp_f32)( (ssp_s32)Val.f32[0] );
            if( Val.f32[0] <= -0 )
                Dst.s32[0] = Dst.s32[0] | 0x80000000;
        }
        break;
    case SSP_FROUND_TO_POS_INF:
        valPtr = (ssp_s32*)(&Val.f32[0]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
            Dst.f32[0] = (ssp_f32)ceil( Val.f32[0] );
        break;
    case SSP_FROUND_TO_NEG_INF:
        valPtr = (ssp_s32*)(&Val.f32[0]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
            Dst.f32[0] = (ssp_f32)floor( Val.f32[0] );
        break;
    default: // SSP_FROUND_TO_NEAREST_INT
        valPtr = (ssp_s32*)(&Val.f32[0]);
        if( ssp_number_isValidNumber_F32_REF( valPtr ) )
            Dst.f32[0] = (ssp_f32)( (Val.f32[0]>0) ? (ssp_s32)(Val.f32[0]+0.5) : (ssp_s32)(Val.f32[0]-0.5) );
        else
            Dst.f32[0] = ssp_number_changeSNanToQNaN_F32_REF( valPtr );
    }
    return Dst.f;
}

//---------------------------------------
// Test
//---------------------------------------
/** \IMP{Reference,_mm_testc_si128, SSE4.1 and SSE5} */
SSP_FORCEINLINE int ssp_testc_si128_REF( __m128i a, __m128i b)                              
{
    ssp_m128 A,B;
    A.i = a;
    B.i = b;

    return ( (A.s64[0] & B.s64[0]) == A.s64[0] ) &&
           ( (A.s64[1] & B.s64[1]) == A.s64[1] ) ;
}

/** \IMP{Reference,_mm_testz_si128, SSE4.1 and SSE5} */
SSP_FORCEINLINE int ssp_testz_si128_REF( __m128i a, __m128i b)                              
{
    ssp_m128 A,B;
    A.i = a;
    B.i = b;

    return ( (A.s64[0] & B.s64[0]) == 0 ) &&
           ( (A.s64[1] & B.s64[1]) == 0 ) ;
}

/** \IMP{Reference,_mm_testnzc_si128, SSE4.1 and SSE5} */
SSP_FORCEINLINE int ssp_testnzc_si128_REF( __m128i a, __m128i b)                            
{
    int zf, cf;
    ssp_m128 A,B;
    A.i = a;
    B.i = b;

    zf = ssp_testz_si128_REF( A.i, B.i);

    cf = ( (~A.s64[0] & B.s64[0]) == 0 ) &&
         ( (~A.s64[1] & B.s64[1]) == 0 ) ;
    return ((int)!zf & (int)!cf);
}

//---------------------------------------
// Type Conversion
//---------------------------------------
/** \IMP{Reference,_mm_cvtepi8_epi16, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_cvtepi8_epi16_REF ( __m128i a)                                  
{
    ssp_m128 A;
    A.i = a;

	A.s16[7] = A.s8[7];
	A.s16[6] = A.s8[6];
	A.s16[5] = A.s8[5];
	A.s16[4] = A.s8[4];
	A.s16[3] = A.s8[3];
	A.s16[2] = A.s8[2];
	A.s16[1] = A.s8[1];
	A.s16[0] = A.s8[0];
	return A.i;
}

/** \IMP{Reference,_mm_cvtepi8_epi32, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_cvtepi8_epi32_REF ( __m128i a)                                  
{
    ssp_m128 A;
    A.i = a;

	A.s32[3] = A.s8[3];
	A.s32[2] = A.s8[2];
	A.s32[1] = A.s8[1];
	A.s32[0] = A.s8[0];
	return A.i;
}

/** \IMP{Reference,_mm_cvtepi8_epi64, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_cvtepi8_epi64_REF ( __m128i a)                                  
{
    ssp_m128 A;
    A.i = a;

	A.s64[1] = A.s8[1];
	A.s64[0] = A.s8[0];
	return A.i;
}

/** \IMP{Reference,_mm_cvtepi16_epi32, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_cvtepi16_epi32_REF ( __m128i a)                                 
{
    ssp_m128 A;
    A.i = a;

	A.s32[3] = A.s16[3];
	A.s32[2] = A.s16[2];
	A.s32[1] = A.s16[1];
	A.s32[0] = A.s16[0];
	return A.i;
}

/** \IMP{Reference,_mm_cvtepi16_epi64, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_cvtepi16_epi64_REF ( __m128i a)                                 
{
    ssp_m128 A;
    A.i = a;

	A.s64[1] = A.s16[1];
	A.s64[0] = A.s16[0];
	return A.i;
}

/** \IMP{Reference,_mm_cvtepi32_epi64, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_cvtepi32_epi64_REF ( __m128i a)                                 
{
    ssp_m128 A;
    A.i = a;

	A.s64[1] = A.s32[1];
    A.s64[0] = A.s32[0];
	return A.i;
}

/** \IMP{Reference,_mm_cvtepu8_epi16, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_cvtepu8_epi16_REF ( __m128i a)                                  
{
    ssp_m128 A;
    A.i = a;

	A.s16[7] = A.u8[7];
	A.s16[6] = A.u8[6];
	A.s16[5] = A.u8[5];
	A.s16[4] = A.u8[4];
	A.s16[3] = A.u8[3];
	A.s16[2] = A.u8[2];
	A.s16[1] = A.u8[1];
	A.s16[0] = A.u8[0];
	return A.i;
}

/** \IMP{Reference,_mm_cvtepu8_epi32, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_cvtepu8_epi32_REF ( __m128i a)                                  
{
    ssp_m128 A;
    A.i = a;

	A.s32[3] = A.u8[3];
	A.s32[2] = A.u8[2];
	A.s32[1] = A.u8[1];
	A.s32[0] = A.u8[0];
	return A.i;
}

/** \IMP{Reference,_mm_cvtepu8_epi64, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_cvtepu8_epi64_REF ( __m128i a)                                  
{
    ssp_m128 A;
    A.i = a;

	A.s64[1] = A.u8[1];
	A.s64[0] = A.u8[0];
	return A.i;
}

/** \IMP{Reference,_mm_cvtepu16_epi32, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_cvtepu16_epi32_REF ( __m128i a)                                 
{
    ssp_m128 A;
    A.i = a;

	A.s32[3] = A.u16[3];
	A.s32[2] = A.u16[2];
	A.s32[1] = A.u16[1];
	A.s32[0] = A.u16[0];
	return A.i;
}

/** \IMP{Reference,_mm_cvtepu16_epi64, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_cvtepu16_epi64_REF ( __m128i a)                                 
{
    ssp_m128 A;
    A.i = a;

	A.s64[1] = A.u16[1];
	A.s64[0] = A.u16[0];
	return A.i;
}

/** \IMP{Reference,_mm_cvtepu32_epi64, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_cvtepu32_epi64_REF ( __m128i a)                                 
{
    ssp_m128 A;
    A.i = a;

	A.s64[1] = A.u32[1];
	A.s64[0] = A.u32[0];
	return A.i;
}

//SSSE3
//__m128i _mm_abs_epi8(__m128i a);
/** \IMP{Reference,_mm_abs_epi8, SSSE3} */
SSP_FORCEINLINE __m128i ssp_abs_epi8_REF (__m128i a)
{
    ssp_m128 A;
    A.i = a;

	A.s8[0]  = (A.s8[0] < 0) ? -A.s8[0]  : A.s8[0];
	A.s8[1]  = (A.s8[1] < 0) ? -A.s8[1]  : A.s8[1];
	A.s8[2]  = (A.s8[2] < 0) ? -A.s8[2]  : A.s8[2];
	A.s8[3]  = (A.s8[3] < 0) ? -A.s8[3]  : A.s8[3];
	A.s8[4]  = (A.s8[4] < 0) ? -A.s8[4]  : A.s8[4];
	A.s8[5]  = (A.s8[5] < 0) ? -A.s8[5]  : A.s8[5];
	A.s8[6]  = (A.s8[6] < 0) ? -A.s8[6]  : A.s8[6];
	A.s8[7]  = (A.s8[7] < 0) ? -A.s8[7]  : A.s8[7];
	A.s8[8]  = (A.s8[8] < 0) ? -A.s8[8]  : A.s8[8];
	A.s8[9]  = (A.s8[9] < 0) ? -A.s8[9]  : A.s8[9];
	A.s8[10] = (A.s8[10]< 0) ? -A.s8[10] : A.s8[10];
	A.s8[11] = (A.s8[11]< 0) ? -A.s8[11] : A.s8[11];
	A.s8[12] = (A.s8[12]< 0) ? -A.s8[12] : A.s8[12];
	A.s8[13] = (A.s8[13]< 0) ? -A.s8[13] : A.s8[13];
	A.s8[14] = (A.s8[14]< 0) ? -A.s8[14] : A.s8[14];
	A.s8[15] = (A.s8[15]< 0) ? -A.s8[15] : A.s8[15];

	return A.i;
}

//__m128i _mm_abs_epi16(__m128i a);
/** \IMP{Reference,_mm_abs_epi16, SSSE3} */
SSP_FORCEINLINE __m128i ssp_abs_epi16_REF (__m128i a)
{
    ssp_m128 A;
    A.i = a;

	A.s16[0]  = (A.s16[0] < 0) ? -A.s16[0]  : A.s16[0];
	A.s16[1]  = (A.s16[1] < 0) ? -A.s16[1]  : A.s16[1];
	A.s16[2]  = (A.s16[2] < 0) ? -A.s16[2]  : A.s16[2];
	A.s16[3]  = (A.s16[3] < 0) ? -A.s16[3]  : A.s16[3];
	A.s16[4]  = (A.s16[4] < 0) ? -A.s16[4]  : A.s16[4];
	A.s16[5]  = (A.s16[5] < 0) ? -A.s16[5]  : A.s16[5];
	A.s16[6]  = (A.s16[6] < 0) ? -A.s16[6]  : A.s16[6];
	A.s16[7]  = (A.s16[7] < 0) ? -A.s16[7]  : A.s16[7];

	return A.i;
}

/**  \IMP{Reference,_mm_abs_epi32,SSSE3} */
SSP_FORCEINLINE __m128i ssp_abs_epi32_REF (__m128i a)
{
    ssp_m128 A;
    A.i = a;

	A.s32[0]  = (A.s32[0] < 0) ? -A.s32[0]  : A.s32[0];
	A.s32[1]  = (A.s32[1] < 0) ? -A.s32[1]  : A.s32[1];
	A.s32[2]  = (A.s32[2] < 0) ? -A.s32[2]  : A.s32[2];
	A.s32[3]  = (A.s32[3] < 0) ? -A.s32[3]  : A.s32[3];

	return A.i;
}

/** \IMP{Reference,_mm_abs_pi8,SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
 */
SSP_FORCEINLINE __m64 ssp_abs_pi8_REF (__m64 a)
{
    ssp_m64 A;
    A.m64 = a;

	A.s8[0]  = (A.s8[0] < 0) ? -A.s8[0]  : A.s8[0];
	A.s8[1]  = (A.s8[1] < 0) ? -A.s8[1]  : A.s8[1];
	A.s8[2]  = (A.s8[2] < 0) ? -A.s8[2]  : A.s8[2];
	A.s8[3]  = (A.s8[3] < 0) ? -A.s8[3]  : A.s8[3];
	A.s8[4]  = (A.s8[4] < 0) ? -A.s8[4]  : A.s8[4];
	A.s8[5]  = (A.s8[5] < 0) ? -A.s8[5]  : A.s8[5];
	A.s8[6]  = (A.s8[6] < 0) ? -A.s8[6]  : A.s8[6];
	A.s8[7]  = (A.s8[7] < 0) ? -A.s8[7]  : A.s8[7];

	return A.m64;
}

//__m64 _mm_abs_pi16( __m64 a);
/** \IMP{Reference,_mm_abs_pi16, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSP_FORCEINLINE __m64 ssp_abs_pi16_REF (__m64 a)
{
    ssp_m64 A;
    A.m64 = a;

	A.s16[0]  = (A.s16[0] < 0) ? -A.s16[0]  : A.s16[0];
	A.s16[1]  = (A.s16[1] < 0) ? -A.s16[1]  : A.s16[1];
	A.s16[2]  = (A.s16[2] < 0) ? -A.s16[2]  : A.s16[2];
	A.s16[3]  = (A.s16[3] < 0) ? -A.s16[3]  : A.s16[3];

	return A.m64;
}

//__m64 _mm_abs_pi32( __m64 a);
/** \IMP{Reference,_mm_abs_pi32, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSP_FORCEINLINE __m64 ssp_abs_pi32_REF (__m64 a)
{
    ssp_m64 A;
    A.m64 = a;

	A.s32[0]  = (A.s32[0] < 0) ? -A.s32[0]  : A.s32[0];
	A.s32[1]  = (A.s32[1] < 0) ? -A.s32[1]  : A.s32[1];

	return A.m64;
}

// bit manipulation
//__m128i _mm_alignr_epi8(__m128i a, __m128i b, const int ralign);
/**  \IMP{Reference,_mm_alignr_epi8,SSSE3} */
SSP_FORCEINLINE __m128i ssp_alignr_epi8_REF (__m128i a, __m128i b, const int ralign)
{
    ssp_m128 C[3];
	ssp_s8 * tmp;
	int i, j;

	if (ralign <0) return b; //only shift to right, no negative
	C[2].i = _mm_setzero_si128();
	if (ralign > 32) return C[2].i;
    C[1].i = a;
	C[0].i = b;
	tmp = & (C[0].s8[0]);

	for (i=ralign+15, j=15; i >=ralign; i--, j--) {
		C[2].s8[j] = tmp[i];
	}

	return C[2].i;
}

/**  \IMP{Reference,_mm_alignr_pi8,SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSP_FORCEINLINE __m64 ssp_alignr_pi8_REF (__m64 a, __m64 b, const int ralign)
{
    ssp_m64 C[3];
	ssp_s8 * tmp;
	int i, j;

	if (ralign <0) return b; //only shift to right, no negative
	C[2].u32[0] = 0;
	C[2].u32[1] = 0;
	if (ralign > 16) return C[2].m64;
    C[1].m64 = a;
	C[0].m64 = b;
	tmp = & (C[0].s8[0]);

	for (i=ralign+7, j=7; i >=ralign; i--, j--) {
		C[2].s8[j] = tmp[i];
	}

	return C[2].m64;
}

//__m128i _mm_shuffle_epi8( __m128i a, __m128i mask);
/**  \IMP{Reference,_mm_shuffle_epi8,SSSE3} */
SSP_FORCEINLINE __m128i ssp_shuffle_epi8_REF (__m128i a, __m128i mask)
{
    ssp_m128 A, MSK, B;
	A.i = a;
	MSK.i = mask;

	B.s8[0]  = (MSK.s8[0]  & 0x80) ? 0 : A.s8[(MSK.s8[0]  & 0xf)];
	B.s8[1]  = (MSK.s8[1]  & 0x80) ? 0 : A.s8[(MSK.s8[1]  & 0xf)];
	B.s8[2]  = (MSK.s8[2]  & 0x80) ? 0 : A.s8[(MSK.s8[2]  & 0xf)];
	B.s8[3]  = (MSK.s8[3]  & 0x80) ? 0 : A.s8[(MSK.s8[3]  & 0xf)];
	B.s8[4]  = (MSK.s8[4]  & 0x80) ? 0 : A.s8[(MSK.s8[4]  & 0xf)];
	B.s8[5]  = (MSK.s8[5]  & 0x80) ? 0 : A.s8[(MSK.s8[5]  & 0xf)];
	B.s8[6]  = (MSK.s8[6]  & 0x80) ? 0 : A.s8[(MSK.s8[6]  & 0xf)];
	B.s8[7]  = (MSK.s8[7]  & 0x80) ? 0 : A.s8[(MSK.s8[7]  & 0xf)];
	B.s8[8]  = (MSK.s8[8]  & 0x80) ? 0 : A.s8[(MSK.s8[8]  & 0xf)];
	B.s8[9]  = (MSK.s8[9]  & 0x80) ? 0 : A.s8[(MSK.s8[9]  & 0xf)];
	B.s8[10] = (MSK.s8[10] & 0x80) ? 0 : A.s8[(MSK.s8[10] & 0xf)];
	B.s8[11] = (MSK.s8[11] & 0x80) ? 0 : A.s8[(MSK.s8[11] & 0xf)];
	B.s8[12] = (MSK.s8[12] & 0x80) ? 0 : A.s8[(MSK.s8[12] & 0xf)];
	B.s8[13] = (MSK.s8[13] & 0x80) ? 0 : A.s8[(MSK.s8[13] & 0xf)];
	B.s8[14] = (MSK.s8[14] & 0x80) ? 0 : A.s8[(MSK.s8[14] & 0xf)];
	B.s8[15] = (MSK.s8[15] & 0x80) ? 0 : A.s8[(MSK.s8[15] & 0xf)];

	return B.i;
}

/**  \IMP{Reference,_mm_shuffle_pi8,SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSP_FORCEINLINE __m64 ssp_shuffle_pi8_REF (__m64 a, __m64 mask)
{
    ssp_m64 A, MSK, B;
	A.m64 = a;
	MSK.m64 = mask;

	B.s8[0]  = (MSK.s8[0]  & 0x80) ? 0 : A.s8[(MSK.s8[0]  & 0xf)];
	B.s8[1]  = (MSK.s8[1]  & 0x80) ? 0 : A.s8[(MSK.s8[1]  & 0xf)];
	B.s8[2]  = (MSK.s8[2]  & 0x80) ? 0 : A.s8[(MSK.s8[2]  & 0xf)];
	B.s8[3]  = (MSK.s8[3]  & 0x80) ? 0 : A.s8[(MSK.s8[3]  & 0xf)];
	B.s8[4]  = (MSK.s8[4]  & 0x80) ? 0 : A.s8[(MSK.s8[4]  & 0xf)];
	B.s8[5]  = (MSK.s8[5]  & 0x80) ? 0 : A.s8[(MSK.s8[5]  & 0xf)];
	B.s8[6]  = (MSK.s8[6]  & 0x80) ? 0 : A.s8[(MSK.s8[6]  & 0xf)];
	B.s8[7]  = (MSK.s8[7]  & 0x80) ? 0 : A.s8[(MSK.s8[7]  & 0xf)];

	return B.m64;
}

//Negate the number
//__m128i _mm_sign_epi8( __m128i a, __m128i b);
/**  \IMP{Reference,_mm_sign_epi8, SSSE3} */
SSP_FORCEINLINE __m128i ssp_sign_epi8_REF (__m128i a, __m128i b)
{
    ssp_m128 A, B;
	A.i = a;
	B.i = b;

	A.s8[0]  = (B.s8[0]<0)  ? (-A.s8[0])  :((B.s8[0]==0) ? 0: A.s8[0]);
	A.s8[1]  = (B.s8[1]<0)  ? (-A.s8[1])  :((B.s8[1]==0) ? 0: A.s8[1]);
	A.s8[2]  = (B.s8[2]<0)  ? (-A.s8[2])  :((B.s8[2]==0) ? 0: A.s8[2]);
	A.s8[3]  = (B.s8[3]<0)  ? (-A.s8[3])  :((B.s8[3]==0) ? 0: A.s8[3]);
	A.s8[4]  = (B.s8[4]<0)  ? (-A.s8[4])  :((B.s8[4]==0) ? 0: A.s8[4]);
	A.s8[5]  = (B.s8[5]<0)  ? (-A.s8[5])  :((B.s8[5]==0) ? 0: A.s8[5]);
	A.s8[6]  = (B.s8[6]<0)  ? (-A.s8[6])  :((B.s8[6]==0) ? 0: A.s8[6]);
	A.s8[7]  = (B.s8[7]<0)  ? (-A.s8[7])  :((B.s8[7]==0) ? 0: A.s8[7]);
	A.s8[8]  = (B.s8[8]<0)  ? (-A.s8[8])  :((B.s8[8]==0) ? 0: A.s8[8]);
	A.s8[9]  = (B.s8[9]<0)  ? (-A.s8[9])  :((B.s8[9]==0) ? 0: A.s8[9]);
	A.s8[10] = (B.s8[10]<0) ? (-A.s8[10]) :((B.s8[10]==0)? 0: A.s8[10]);
	A.s8[11] = (B.s8[11]<0) ? (-A.s8[11]) :((B.s8[11]==0)? 0: A.s8[11]);
	A.s8[12] = (B.s8[12]<0) ? (-A.s8[12]) :((B.s8[12]==0)? 0: A.s8[12]);
	A.s8[13] = (B.s8[13]<0) ? (-A.s8[13]) :((B.s8[13]==0)? 0: A.s8[13]);
	A.s8[14] = (B.s8[14]<0) ? (-A.s8[14]) :((B.s8[14]==0)? 0: A.s8[14]);
	A.s8[15] = (B.s8[15]<0) ? (-A.s8[15]) :((B.s8[15]==0)? 0: A.s8[15]);

	return A.i;
}

//__m128i _mm_sign_epi16( __m128i a, __m128i b);
/**  \IMP{Reference,_mm_sign_epi16, SSSE3} */
SSP_FORCEINLINE __m128i ssp_sign_epi16_REF (__m128i a, __m128i b)
{
    ssp_m128 A, B;
	A.i = a;
	B.i = b;

	A.s16[0]  = (B.s16[0]<0)  ? (-A.s16[0])  :((B.s16[0]==0) ? 0: A.s16[0]);
	A.s16[1]  = (B.s16[1]<0)  ? (-A.s16[1])  :((B.s16[1]==0) ? 0: A.s16[1]);
	A.s16[2]  = (B.s16[2]<0)  ? (-A.s16[2])  :((B.s16[2]==0) ? 0: A.s16[2]);
	A.s16[3]  = (B.s16[3]<0)  ? (-A.s16[3])  :((B.s16[3]==0) ? 0: A.s16[3]);
	A.s16[4]  = (B.s16[4]<0)  ? (-A.s16[4])  :((B.s16[4]==0) ? 0: A.s16[4]);
	A.s16[5]  = (B.s16[5]<0)  ? (-A.s16[5])  :((B.s16[5]==0) ? 0: A.s16[5]);
	A.s16[6]  = (B.s16[6]<0)  ? (-A.s16[6])  :((B.s16[6]==0) ? 0: A.s16[6]);
	A.s16[7]  = (B.s16[7]<0)  ? (-A.s16[7])  :((B.s16[7]==0) ? 0: A.s16[7]);

	return A.i;
}

//__m128i _mm_sign_epi32( __m128i a, __m128i b);
/**  \IMP{Reference,_mm_sign_epi32, SSSE3} */
SSP_FORCEINLINE __m128i ssp_sign_epi32_REF (__m128i a, __m128i b)
{
    ssp_m128 A, B;
	A.i = a;
	B.i = b;

	A.s32[0]  = (B.s32[0]<0)  ? (-A.s32[0])  :((B.s32[0]==0) ? 0: A.s32[0]);
	A.s32[1]  = (B.s32[1]<0)  ? (-A.s32[1])  :((B.s32[1]==0) ? 0: A.s32[1]);
	A.s32[2]  = (B.s32[2]<0)  ? (-A.s32[2])  :((B.s32[2]==0) ? 0: A.s32[2]);
	A.s32[3]  = (B.s32[3]<0)  ? (-A.s32[3])  :((B.s32[3]==0) ? 0: A.s32[3]);

	return A.i;
}

//__m64 _mm_sign_pi8( __m64 a, __m64 b);
/**  \IMP{Reference,_mm_sign_pi8, SSSE3} */
SSP_FORCEINLINE __m64 ssp_sign_pi8_REF (__m64 a, __m64 b)
{
    ssp_m64 A, B;
	A.m64 = a;
	B.m64 = b;

	A.s8[0]  = (B.s8[0]<0)  ? (-A.s8[0])  :((B.s8[0]==0) ? 0: A.s8[0]);
	A.s8[1]  = (B.s8[1]<0)  ? (-A.s8[1])  :((B.s8[1]==0) ? 0: A.s8[1]);
	A.s8[2]  = (B.s8[2]<0)  ? (-A.s8[2])  :((B.s8[2]==0) ? 0: A.s8[2]);
	A.s8[3]  = (B.s8[3]<0)  ? (-A.s8[3])  :((B.s8[3]==0) ? 0: A.s8[3]);
	A.s8[4]  = (B.s8[4]<0)  ? (-A.s8[4])  :((B.s8[4]==0) ? 0: A.s8[4]);
	A.s8[5]  = (B.s8[5]<0)  ? (-A.s8[5])  :((B.s8[5]==0) ? 0: A.s8[5]);
	A.s8[6]  = (B.s8[6]<0)  ? (-A.s8[6])  :((B.s8[6]==0) ? 0: A.s8[6]);
	A.s8[7]  = (B.s8[7]<0)  ? (-A.s8[7])  :((B.s8[7]==0) ? 0: A.s8[7]);

	return A.m64;
}

//__m64 _mm_sign_pi16( __m64 a, __m64 b);
/**  \IMP{Reference,_mm_sign_pi16, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSP_FORCEINLINE __m64 ssp_sign_pi16_REF (__m64 a, __m64 b)
{
    ssp_m64 A, B;
	A.m64 = a;
	B.m64 = b;

	A.s16[0]  = (B.s16[0]<0)  ? (-A.s16[0])  :((B.s16[0]==0) ? 0: A.s16[0]);
	A.s16[1]  = (B.s16[1]<0)  ? (-A.s16[1])  :((B.s16[1]==0) ? 0: A.s16[1]);
	A.s16[2]  = (B.s16[2]<0)  ? (-A.s16[2])  :((B.s16[2]==0) ? 0: A.s16[2]);
	A.s16[3]  = (B.s16[3]<0)  ? (-A.s16[3])  :((B.s16[3]==0) ? 0: A.s16[3]);

	return A.m64;
}

//__m64 _mm_sign_pi32( __m64 a, __m64 b);
/**  \IMP{Reference,_mm_sign_pi32, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSP_FORCEINLINE __m64 ssp_sign_pi32_REF (__m64 a, __m64 b)
{
    ssp_m64 A, B;
	A.m64 = a;
	B.m64 = b;

	A.s32[0]  = (B.s32[0]<0)  ? (-A.s32[0])  :((B.s32[0]==0) ? 0: A.s32[0]);
	A.s32[1]  = (B.s32[1]<0)  ? (-A.s32[1])  :((B.s32[1]==0) ? 0: A.s32[1]);

	return A.m64;
}

/** \IMP{Reference,_mm_stream_sd,SSE4a} */ 
SSP_FORCEINLINE void ssp_stream_sd_REF( double *dst ,__m128d src )
{
    ssp_m128 SRC;
    SRC.d = src;
    *dst = SRC.f64[0];
}

/** \IMP{Reference,_mm_stream_ss,SSE4a} */ 
SSP_FORCEINLINE void ssp_stream_ss_REF( float *dst, __m128 src )
{
    ssp_m128 SRC;
    SRC.f = src;
    *dst = SRC.f32[0];
}

//---------------------------------------
// Leading Zeros Count
//---------------------------------------
/** \IMP{Reference,__lzcnt16,SSE4a} */ 
SSP_FORCEINLINE unsigned short ssp_lzcnt16_REF( unsigned short val )
{
    
    if( !val )
        return 16;
    // Binary Search Tree of possible output values
    else if( val > 0x00FF )
    {
        if( val > 0x0FFF )
        {
            if( val > 0x3FFF )
            {
                if( val > 0x7FFF )
                    return 0;
                else
                    return 1;
            }
            else // val < 0x3FFF
            {
                if( val > 0x1FFF )
                    return 2;
                else
                    return 3;
            }
        }
        else // val < 0x0FFF
        {
            if( val > 0x03FF )
            {
                if( val > 0x07FF )
                    return 4;
                else
                    return 5;
            }
            else // val < 0x03FF
            {
                if( val > 0x01FF )
                    return 6;
                else
                    return 7;
            }
        }
    }
    else // val < 0x00FF
    {
        if( val > 0x000F )
        {
            if( val > 0x003F  )
            {
                if( val > 0x007F  )
                    return 8;
                else
                    return 9;
            }
            else // val < 0x003F
            {
                if( val > 0x001F)
                    return 10;
                else
                    return 11;
            }
        }
        else // val < 0x000F
        {
            if( val > 0x0003  )
            {
                if( val > 0x0007  )
                    return 12;
                else
                    return 13;
            }
            else // val < 0x0003
            {
                if( val > 0x0001)
                    return 14;
                else
                    return 15;
            }
        }
    }
}
/** \IMP{Reference,__lzcnt,SSE4a} */ 
SSP_FORCEINLINE unsigned int ssp_lzcnt_REF( unsigned int val )
{
    ssp_u32 cnt;
    cnt = ssp_lzcnt16_REF( (ssp_u16)(val>>16) );
    if( cnt == 16 )
        cnt += ssp_lzcnt16_REF( (ssp_u16)(val & 0x0000FFFF) );
    return cnt;
}
/** \IMP{Reference,__lzcnt64,SSE4a} */ 
SSP_FORCEINLINE ssp_u64 ssp_lzcnt64_REF( ssp_u64 val )
{
    ssp_u64 cnt;
    cnt = ssp_lzcnt_REF( (ssp_u32)(val>>32) );
    if( cnt == 32 )
        cnt += ssp_lzcnt_REF( (ssp_u32)(val & 0x00000000FFFFFFFF) );
    return cnt;
}

//---------------------------------------
// Population Count
//---------------------------------------
/** \IMP{SSE4a Native,__popcnt16,SSE4a} */ 
SSP_FORCEINLINE unsigned short ssp_popcnt16_REF( unsigned short val )
{
    int i;
    ssp_u16 cnt=0;
    for( i=0; i<15, val; ++i, val = val>>1 )
        cnt += val & 0x1;
    return cnt;
}
/** \IMP{SSE4a Native,__popcnt,SSE4a} */ 
SSP_FORCEINLINE unsigned int ssp_popcnt_REF( unsigned int val )
{
    int i;
    ssp_u32 cnt = 0;
    for( i=0; i<31, val; ++i, val = val>>1 )
        cnt += val & 0x1;
    return cnt;
}
/** \IMP{SSE4a Native,__popcnt64,SSE4a} */ 
SSP_FORCEINLINE ssp_u64 ssp_popcnt64_REF( ssp_u64 val )
{
    int i;
    ssp_u64 cnt = 0;
    for( i=0; i<63, val; ++i, val = val>>1 )
        cnt += val & 0x1;
    return cnt;
}

//@}
//@}

#endif // __SSP_EMULATION_REF_H__
