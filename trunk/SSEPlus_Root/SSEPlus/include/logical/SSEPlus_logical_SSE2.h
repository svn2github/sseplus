//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __SSEPLUS_LOGICAL_SSE2_H__
#define __SSEPLUS_LOGICAL_SSE2_H__

#include "../native/SSEPlus_native_SSE2.h"

/** @defgroup SSE2 SSE2 Optimized
 *  @{
 *  @name Logical Operations */


SSP_FORCEINLINE __m128i ssp_logical_cmplt_epu16_SSE2( __m128i a, __m128i b )
{
    __m128i signMask, mask;

    mask     = _mm_cmplt_epi16( a, b );              // FFFF where a < b (signed)
    signMask = _mm_xor_si128  ( a, b );              // Signbit is 1 where signs differ 
    signMask = _mm_srai_epi16 ( signMask, 15 );      // fill all fields with sign bit     
    mask     = _mm_xor_si128  ( mask, signMask );    // Invert output where signs differed
    return mask;
}

SSP_FORCEINLINE __m128i ssp_logical_cmpgt_epu16_SSE2( __m128i a, __m128i b )
{
    __m128i signMask, mask;

    mask     = _mm_cmpgt_epi16( a, b );              // FFFF where a > b (signed)
    signMask = _mm_xor_si128  ( a, b );              // Signbit is 1 where signs differ 
    signMask = _mm_srai_epi16 ( signMask, 15 );      // fill all fields with sign bit     
    mask     = _mm_xor_si128  ( mask, signMask );    // Invert output where signs differed
    return mask;
}

SSP_FORCEINLINE __m128i ssp_logical_cmplt_epu32_SSE2( __m128i a, __m128i b )
{
    __m128i signMask, mask;

    mask     = _mm_cmplt_epi32( a, b );              // FFFF where a < b (signed)
    signMask = _mm_xor_si128  ( a, b );              // Signbit is 1 where signs differ 
    signMask = _mm_srai_epi32 ( signMask, 31 );      // fill all fields with sign bit     
    mask     = _mm_xor_si128  ( mask, signMask );    // Invert output where signs differed
    return mask;
}

SSP_FORCEINLINE __m128i ssp_logical_cmpgt_epu32_SSE2( __m128i a, __m128i b )
{
    __m128i signMask, mask;

    mask     = _mm_cmpgt_epi32( a, b );              // FFFF where a < b (signed)
    signMask = _mm_xor_si128  ( a, b );              // Signbit is 1 where signs differ 
    signMask = _mm_srai_epi32 ( signMask, 31 );      // fill all fields with sign bit     
    mask     = _mm_xor_si128  ( mask, signMask );    // Invert output where signs differed
    return mask;
}



SSP_FORCEINLINE __m128i ssp_logical_bitwise_choose_SSE2( __m128i a, __m128i b, __m128i mask )   // Bitwise (mask ? a : b) 
{
    a = _mm_and_si128   ( a,    mask );                                 // clear a where mask = 0
    b = _mm_andnot_si128( mask, b    );                                 // clear b where mask = 1
    a = _mm_or_si128    ( a,    b    );                                 // a = a OR b                         
    return a; 
}


//SSP_FORCEINLINE
//__m128i ssp_generate_mask_imm8_to_epi16_SSE2( int mask )
//{
//    __m128i screen;
//    const static __m128i mulShiftImm = SSP_CONST_SET_16I( 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000 ); // Shift mask multiply moves all bits to left, becomes MSB
//    screen = _mm_set1_epi16  ( mask                );   // Load the mask into register
//    screen = _mm_mullo_epi16 ( screen, mulShiftImm );   // Shift bits to MSB
//    screen = _mm_srai_epi16  ( screen, 15          );   // Shift bits to obtain 0xFFFF or 0x0000
//    return screen;
//}

SSP_FORCEINLINE
__m128i ssp_movmask_imm8_to_epi32_SSE2( int mask )
{
    __m128i screen;
    const static __m128i mulShiftImm = SSP_CONST_SET_16I( 0x1000, 0x0000, 0x2000, 0x0000, 0x4000, 0x0000, 0x8000, 0x0000 ); // Shift mask multiply moves all bits to left, becomes MSB
    screen = _mm_set1_epi16 ( mask                );   // Load the mask into register
    screen = _mm_mullo_epi16( screen, mulShiftImm );   // Shift bits to MSB
    screen = _mm_srai_epi32 ( screen, 31          );   // Shift bits to obtain all F's or all 0's
    return screen;
}

/**

 r_:= (a_<=b_) ? 0xff : 0x0
*/
SSP_FORCEINLINE
__m128i ssp_logical_cmplte_epi8( __m128i a, __m128i b )
{
    a = _mm_cmpgt_epi8( a, b );
    a = _mm_xor_si128 ( a, _mm_set1_epi8( (char)0xFF) );
    return a;
}

/**

 r_:= (a_>=b_) ? 0xff : 0x0
*/
SSP_FORCEINLINE
__m128i ssp_logical_cmpgte_epi8( __m128i a, __m128i b )
{
    a = _mm_cmplt_epi8( a, b );
    a = _mm_xor_si128 ( a, _mm_set1_epi8( (char)0xFF) );
    return a;
}


//@}
//@}

#endif // __SSEPLUS_LOGICAL_SSE2_H__
