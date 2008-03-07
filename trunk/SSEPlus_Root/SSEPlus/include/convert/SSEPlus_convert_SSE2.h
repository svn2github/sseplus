//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __SSEPLUS_CONVERT_SSE2_H__
#define __SSEPLUS_CONVERT_SSE2_H__

#include "../native/SSEPlus_native_SSE2.h"

/** @defgroup SSE2 SSE2 Optimized
 *  @{
 *  @name Convert Operations */

/** \IMP{SSE2,ssp_convert_odd_even_epi16_SSE2,custom} */
SSP_FORCEINLINE
void ssp_convert_odd_even_epi16_SSE2( __m128i *a, __m128i *b )
{
    // IN
    // a = a7,a6,a5,a4,a3,a2,a1,a0
    // b = b7,b6,b5,b4,b3,b2,b1,b0

    // OUT
    // a = b6,b4,b2,b0,a6,a4,a2,a0  // even
    // b = b7,b5,b3,b1,a7,a5,a3,a1  // odd

    __m128i A = *a;
    __m128i B = *b;
    __m128i ta, tb, odd, even;

    ta   = _mm_srai_epi32 ( A, 16 );    // sign,a7,sign,a5,sign,a3,sign,a1
    tb   = _mm_srai_epi32 ( B, 16 );    // sign,b7,sign,b5,sign,b3,sign,b1
    odd  = _mm_packs_epi32( ta, tb );   //   b7,b5,  b3,b1,  a7,a5,  a3,a1

    A    = _mm_slli_si128 ( A, 2 );     //   a6, 0,  a4, 0,  a2, 0,  a0, 0
    B    = _mm_slli_si128 ( B, 2 );     //   b6, 0,  b4, 0,  b2, 0,  b0, 0
    A    = _mm_srai_epi32 ( A, 16 );    // sign,a6,sign,a4,sign,a2,sign,a0
    B    = _mm_srai_epi32 ( B, 16 );    // sign,b6,sign,b4,sign,b2,sign,b0                                        
    even = _mm_packs_epi32( A, B );     //   b6,b4,  b2,b0,  a6,a4,  a2,a0

    *a = even;
    *b = odd;
}


/** \IMP{SSE2,ssp_convert_odd_even_epi32_SSE2,custom} */
SSP_FORCEINLINE
void ssp_convert_odd_even_ps_SSE2( __m128 *a, __m128 *b )
{
    // IN
    // a = a3,a2,a1,a0
    // b = b3,b2,b1,b0

    // OUT
    // a = b2,b0,a2,a0  // even
    // b = b3,b1,a3,a1  // odd
    
    __m128 c, d;  
    c = _mm_shuffle_ps( *a, *b, _MM_SHUFFLE(3,1,3,1) );
    d = _mm_shuffle_ps( *a, *b, _MM_SHUFFLE(2,0,2,0) );
    *a = c;
    *b = d;     
}

/** \IMP{SSE2,ssp_convert_odd_even_epi32_SSE2,custom} */
SSP_FORCEINLINE
void ssp_convert_odd_even_epi32_SSE2( __m128i *a, __m128i *b )
{
    // IN
    // a = a3,a2,a1,a0
    // b = b3,b2,b1,b0

    // OUT
    // a = b2,b0,a2,a0  // even
    // b = b3,b1,a3,a1  // odd
    
    ssp_m128 A,B;
    A.i = *a;
    B.i = *b;  

    ssp_convert_odd_even_ps_SSE2( &A.f, &B.f );

    *a = A.i;
    *b = B.i;       
}


//@}
//@}

#endif // __SSEPLUS_CONVERT_SSE2_H__
