//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __SSEPLUS_CONVERT_REF_H__
#define __SSEPLUS_CONVERT_REF_H__


/** @defgroup REF Reference
 *  @{
 *  @name Convert Operations */


//a: 9  6 3 0    3  2  1 0               
//b: 10 7 4 1 -> 7  6  5 4       
//c: 11 8 5 2    11 10 9 8
SSP_FORCEINLINE
void ssp_convert_reverse_transpose_REF( __m128i *a, __m128i *b, __m128i *c )
{
    ssp_m128 Ai, Ao, Bi, Bo, Ci, Co;
    Ai.i = *a;   
    Bi.i = *b;   
    Ci.i = *c;   

    Ao.u32[ 0 ] = Ai.u32[ 0 ];
    Ao.u32[ 1 ] = Bi.u32[ 0 ];
    Ao.u32[ 2 ] = Ci.u32[ 0 ];
    Ao.u32[ 3 ] = Ai.u32[ 1 ];

    Bo.u32[ 0 ] = Bi.u32[ 1 ];
    Bo.u32[ 1 ] = Ci.u32[ 1 ];
    Bo.u32[ 2 ] = Ai.u32[ 2 ];
    Bo.u32[ 3 ] = Bi.u32[ 2 ];

    Co.u32[ 0 ] = Ci.u32[ 2 ];
    Co.u32[ 1 ] = Ai.u32[ 3 ];
    Co.u32[ 2 ] = Bi.u32[ 3 ];
    Co.u32[ 3 ] = Ci.u32[ 3 ];

    *a = Ao.i;
    *b = Bo.i;
    *c = Co.i;
}


SSP_FORCEINLINE 
void ssp_convert_3c_3p_epi8_REF( __m128i *rgb1, __m128i *rgb2, __m128i *rgb3)
{
    ssp_m128 RGB1, RGB2, RGB3;
    ssp_m128 R,G,B;

    RGB1.i = *rgb1;
    RGB2.i = *rgb2;
    RGB3.i = *rgb3;
    
    R.u8[0 ] = RGB1.u8[0 ];  //RED
    R.u8[1 ] = RGB1.u8[3 ];
    R.u8[2 ] = RGB1.u8[6 ];
    R.u8[3 ] = RGB1.u8[9 ];
    R.u8[4 ] = RGB1.u8[12];
    R.u8[5 ] = RGB1.u8[15];
    R.u8[6 ] = RGB2.u8[2 ];
    R.u8[7 ] = RGB2.u8[5 ];
    R.u8[8 ] = RGB2.u8[8 ];
    R.u8[9 ] = RGB2.u8[11];
    R.u8[10] = RGB2.u8[14];
    R.u8[11] = RGB3.u8[1 ];
    R.u8[12] = RGB3.u8[4 ];
    R.u8[13] = RGB3.u8[7 ];
    R.u8[14] = RGB3.u8[10];
    R.u8[15] = RGB3.u8[13];

    G.u8[0 ] = RGB1.u8[1 ];  //GREEN
    G.u8[1 ] = RGB1.u8[4 ];
    G.u8[2 ] = RGB1.u8[7 ];
    G.u8[3 ] = RGB1.u8[10];
    G.u8[4 ] = RGB1.u8[13];
    G.u8[5 ] = RGB2.u8[0 ];
    G.u8[6 ] = RGB2.u8[3 ];
    G.u8[7 ] = RGB2.u8[6 ];
    G.u8[8 ] = RGB2.u8[9 ];
    G.u8[9 ] = RGB2.u8[12];
    G.u8[10] = RGB2.u8[15];
    G.u8[11] = RGB3.u8[2 ];
    G.u8[12] = RGB3.u8[5 ];
    G.u8[13] = RGB3.u8[8 ];
    G.u8[14] = RGB3.u8[11];
    G.u8[15] = RGB3.u8[14];

    B.u8[0 ] = RGB1.u8[2 ];  //BLUE
    B.u8[1 ] = RGB1.u8[5 ];
    B.u8[2 ] = RGB1.u8[8 ];
    B.u8[3 ] = RGB1.u8[11];
    B.u8[4 ] = RGB1.u8[14];
    B.u8[5 ] = RGB2.u8[1 ];
    B.u8[6 ] = RGB2.u8[4 ];
    B.u8[7 ] = RGB2.u8[7 ];
    B.u8[8 ] = RGB2.u8[10];
    B.u8[9 ] = RGB2.u8[13];
    B.u8[10] = RGB3.u8[0 ];
    B.u8[11] = RGB3.u8[3 ];
    B.u8[12] = RGB3.u8[6 ];
    B.u8[13] = RGB3.u8[9 ];
    B.u8[14] = RGB3.u8[12];
    B.u8[15] = RGB3.u8[15];
   

    *rgb1 = R.i;
    *rgb2 = G.i;
    *rgb3 = B.i;   
}


SSP_FORCEINLINE
void ssp_convert_3p_3c_epi8_REF( __m128i *r, __m128i *g, __m128i *b )
{
    ssp_m128 R,G,B;
    ssp_m128 RGB1, RGB2, RGB3;
    
    R.i = *r;
    G.i = *g;
    B.i = *b;

    RGB1.u8[0 ] = R.u8[0 ];  
    RGB1.u8[1 ] = G.u8[0 ];
    RGB1.u8[2 ] = B.u8[0 ];
    RGB1.u8[3 ] = R.u8[1 ];
    RGB1.u8[4 ] = G.u8[1 ];
    RGB1.u8[5 ] = B.u8[1 ];
    RGB1.u8[6 ] = R.u8[2 ];
    RGB1.u8[7 ] = G.u8[2 ];
    RGB1.u8[8 ] = B.u8[2 ];
    RGB1.u8[9 ] = R.u8[3 ];
    RGB1.u8[10] = G.u8[3 ];
    RGB1.u8[11] = B.u8[3 ];
    RGB1.u8[12] = R.u8[4 ];
    RGB1.u8[13] = G.u8[4 ];
    RGB1.u8[14] = B.u8[4 ];
    RGB1.u8[15] = R.u8[5 ];

    RGB2.u8[0 ] = G.u8[5 ];  
    RGB2.u8[1 ] = B.u8[5 ];
    RGB2.u8[2 ] = R.u8[6 ];
    RGB2.u8[3 ] = G.u8[6 ];
    RGB2.u8[4 ] = B.u8[6 ];
    RGB2.u8[5 ] = R.u8[7 ];
    RGB2.u8[6 ] = G.u8[7 ];
    RGB2.u8[7 ] = B.u8[7 ];
    RGB2.u8[8 ] = R.u8[8 ];
    RGB2.u8[9 ] = G.u8[8 ];
    RGB2.u8[10] = B.u8[8 ];
    RGB2.u8[11] = R.u8[9 ];
    RGB2.u8[12] = G.u8[9 ];
    RGB2.u8[13] = B.u8[9 ];
    RGB2.u8[14] = R.u8[10];
    RGB2.u8[15] = G.u8[10];

    RGB3.u8[0 ] = B.u8[10];  
    RGB3.u8[1 ] = R.u8[11];
    RGB3.u8[2 ] = G.u8[11];
    RGB3.u8[3 ] = B.u8[11];
    RGB3.u8[4 ] = R.u8[12];
    RGB3.u8[5 ] = G.u8[12];
    RGB3.u8[6 ] = B.u8[12];
    RGB3.u8[7 ] = R.u8[13];
    RGB3.u8[8 ] = G.u8[13];
    RGB3.u8[9 ] = B.u8[13];
    RGB3.u8[10] = R.u8[14];
    RGB3.u8[11] = G.u8[14];
    RGB3.u8[12] = B.u8[14];
    RGB3.u8[13] = R.u8[15];
    RGB3.u8[14] = G.u8[15];
    RGB3.u8[15] = B.u8[15];

    *r = RGB1.i;
    *g = RGB2.i;
    *b = RGB3.i;
}


//@}
//@}

#endif // __SSEPLUS_CONVERT_REF_H__
