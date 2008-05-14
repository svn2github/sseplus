//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __SSEPLUS_LOGICAL_REF_H__
#define __SSEPLUS_LOGICAL_REF_H__

#include "../SSEPlus_base.h"


/** @addtogroup supplimental_REF   
 *  @{ 
 *  @name Logical Operations
 */

SSP_FORCEINLINE __m128i ssp_logical_cmplt_epu16_REF( __m128i a, __m128i b )
{
    ssp_m128 A, B;
    A.i = a;
    B.i = b;

    A.u16[0] = A.u16[0] < B.u16[0] ? 0xFFFF : 0;
    A.u16[1] = A.u16[1] < B.u16[1] ? 0xFFFF : 0;
    A.u16[2] = A.u16[2] < B.u16[2] ? 0xFFFF : 0;
    A.u16[3] = A.u16[3] < B.u16[3] ? 0xFFFF : 0;
    A.u16[4] = A.u16[4] < B.u16[4] ? 0xFFFF : 0;
    A.u16[5] = A.u16[5] < B.u16[5] ? 0xFFFF : 0;
    A.u16[6] = A.u16[6] < B.u16[6] ? 0xFFFF : 0;
    A.u16[7] = A.u16[7] < B.u16[7] ? 0xFFFF : 0; 
    return A.i;
}

SSP_FORCEINLINE __m128i ssp_logical_cmpgt_epu16_REF( __m128i a, __m128i b )
{
    ssp_m128 A, B;
    A.i = a;
    B.i = b;

    A.u16[0] = A.u16[0] > B.u16[0] ? 0xFFFF : 0;
    A.u16[1] = A.u16[1] > B.u16[1] ? 0xFFFF : 0;
    A.u16[2] = A.u16[2] > B.u16[2] ? 0xFFFF : 0;
    A.u16[3] = A.u16[3] > B.u16[3] ? 0xFFFF : 0;
    A.u16[4] = A.u16[4] > B.u16[4] ? 0xFFFF : 0;
    A.u16[5] = A.u16[5] > B.u16[5] ? 0xFFFF : 0;
    A.u16[6] = A.u16[6] > B.u16[6] ? 0xFFFF : 0;
    A.u16[7] = A.u16[7] > B.u16[7] ? 0xFFFF : 0; 
    return A.i;
}



SSP_FORCEINLINE __m128i ssp_logical_cmplt_epu32_REF( __m128i a, __m128i b )
{
    ssp_m128 A, B;
    A.i = a;
    B.i = b;

    A.u32[0] = A.u32[0] < B.u32[0] ? 0xFFFFFFFF : 0;
    A.u32[1] = A.u32[1] < B.u32[1] ? 0xFFFFFFFF : 0;
    A.u32[2] = A.u32[2] < B.u32[2] ? 0xFFFFFFFF : 0;
    A.u32[3] = A.u32[3] < B.u32[3] ? 0xFFFFFFFF : 0;   
    return A.i;
}

SSP_FORCEINLINE __m128i ssp_logical_cmpgt_epu32_REF( __m128i a, __m128i b )
{
    ssp_m128 A, B;
    A.i = a;
    B.i = b;

    A.u32[0] = A.u32[0] > B.u32[0] ? 0xFFFFFFFF : 0;
    A.u32[1] = A.u32[1] > B.u32[1] ? 0xFFFFFFFF : 0;
    A.u32[2] = A.u32[2] > B.u32[2] ? 0xFFFFFFFF : 0;
    A.u32[3] = A.u32[3] > B.u32[3] ? 0xFFFFFFFF : 0;   
    return A.i;
}

/**
  r_:= a_ << b; (logical left shift)
*/
SSP_FORCEINLINE __m128i ssp_slli_epi8_REF(__m128i a, const int b)
{
    int n;
    ssp_m128 A;
    A.i = a;
    for( n = 0; n < 16; n++ )
    {
        A.u8[n] = A.u8[n] << b;
    }
    return A.i;
}

/**
  r_:= a_ >> b; (logical right shift)
*/
SSP_FORCEINLINE __m128i ssp_srli_epi8_REF(__m128i a, const int b)
{                                            //  a = VfVeVdVcVbVaV9V8V7V6V5V4V3V2V1V0
    int n;
    ssp_m128 A;
    A.i = a;
    for( n = 0; n < 16; n++ )
    {
        A.u8[n] = A.u8[n] >> b;
    }
    return A.i;
}

/** @} 
 *  @}
 */


#endif // __SSEPLUS_LOGICAL_REF_H__
