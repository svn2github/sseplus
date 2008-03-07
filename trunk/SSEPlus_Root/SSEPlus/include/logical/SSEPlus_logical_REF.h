//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __SSEPLUS_LOGICAL_REF_H__
#define __SSEPLUS_LOGICAL_REF_H__

#include "../SSEPlus_base.h"


/** @defgroup Reference Reference
 *  @{
 *  @name Logical Operations */

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


//@}
//@}


#endif // __SSEPLUS_LOGICAL_REF_H__
