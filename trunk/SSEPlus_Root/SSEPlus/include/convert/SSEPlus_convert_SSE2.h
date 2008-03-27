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


SSP_FORCEINLINE 
void ssp_convert_3c_3p_epi8_SSE2( __m128i *rgb1, __m128i *rgb2, __m128i *rgb3)
{
    __m128i temp1, temp2;
                                                            // RGB1 =         r5 , b4  g4  r4 , b3  g3  r3 , b2  g2  r2 , b1  g1  r1 , b0  g0 r0
                                                            // RGB2 =     g10 r10, b9  g9  r9 , b8  g8  r8 , b7  g7  r7 , b6  g6  r6 , b5  g5   
                                                            // RGB3 = b15 g15 r15, b14 g14 r14, b13 g13 r13, b12 g12 r12, b11 g11 r11, b10 


    *rgb2 = _mm_shuffle_epi32(*rgb2, _MM_SHUFFLE(1,0,3,2));	// b7, g7, r7, b6, g6, r6, b5, g5,g10,r10, b9, g9, r9, b8, g8, r8
    temp1 = _mm_unpacklo_epi8(*rgb1, *rgb2);				//g10, g2,r10, r2, b9, b1, g9, g1, r9, r1, b8, b0, g8, g0, r8, r0
    temp2 = _mm_unpackhi_epi8(*rgb2, *rgb3);				//b15, b7,g15, g7,r15, r7,b14, b6,g14, g6,r14, r6,b13, b5,g13, g5
    *rgb3 = _mm_slli_si128   (*rgb3, 8    );				//r13,b12,g12,r12,b11,g11,r11,b10,  0,  0,  0,  0,  0,  0,  0,  0
    *rgb2 = _mm_unpackhi_epi8(*rgb1, *rgb3);				//r13, r5,b12, b4,g12, g4,r12, r4,b11, b3,g11, g3,r11, r3,b10, b2

    *rgb3 = _mm_shuffle_epi32(*rgb2, _MM_SHUFFLE(1,0,3,2));	//b11, b3,g11, g3,r11, r3,b10, b2,r13, r5,b12, b4,g12, g4,r12, r4
    *rgb1 = _mm_unpacklo_epi8(temp1, *rgb3);				//r13, r9, r5, r1,b12, b8, b4, b0,g12, g8, g4, g0,r12, r8, r4, r0
    temp1 = _mm_srli_si128   (temp1, 8    );				//  0,  0,  0,  0,  0,  0,  0,  0,g10, g2,r10, r2, b9, b1, g9, g1
    temp1 = _mm_unpacklo_epi8(temp1, temp2);				//g14,g10, g6, g2,r14,r10, r6, r2,b13, b9, b5, b1,g13, g9, g5, g1
    temp2 = _mm_unpackhi_epi8(*rgb3, temp2);				//b15,b11, b7, b3,g15,g11, g7, g3,r15,r11, r7, r3,b14,b10, b6, b2

    temp1 = _mm_shuffle_epi32(temp1, _MM_SHUFFLE(1,0,3,2)); //b13, b9, b5, b1,g13, g9, g5, g1,g14,g10, g6, g2,r14,r10, r6, r2
    *rgb3 = _mm_unpackhi_epi8(temp1, temp2);				//b15,b13,b11, b9, b7, b5, b3, b1,g15,g13,g11, g9, g7, g5, g3, g1
    temp2 = _mm_slli_si128   (temp2, 8    );				//r15,r11, r7, r3,b14,b10, b6, b2,  0,  0,  0,  0,  0,  0,  0,  0
    temp2 = _mm_unpackhi_epi8(*rgb1, temp2);				//r15,r13,r11, r9, r7, r5, r3, r1,b14,b12,b10, b8, b6, b4, b2, b0
    temp1 = _mm_unpacklo_epi8(*rgb1, temp1);				//g14,g12,g10, g8, g6, g4, g2, g0,r14,r12,r10, r8, r6, r4, r2, r0

    temp2 = _mm_shuffle_epi32(temp2, _MM_SHUFFLE(1,0,3,2)); //b14,b12,b10, b8, b6, b4, b2, b0,r15,r13,r11, r9, r7, r5, r3, r1
    *rgb1 = _mm_unpacklo_epi8(temp1, temp2);				//r15,r14,r13,r12,r11,r10, r9, r8, r7, r6, r5, r4, r3, r2, r1, r0	
    temp1 = _mm_srli_si128   (temp1, 8    );				//  0,  0,  0,  0,  0,  0,  0,  0,g14,g12,g10, g8, g6, g4, g2, g0
    *rgb2 = _mm_unpacklo_epi8(temp1, *rgb3);				//g15,g14,g13,g12,g11,g10, g9, g8, g7, g6, g5, g4, g3, g2, g1, g0	
    *rgb3 = _mm_unpackhi_epi8(temp2, *rgb3);				//b15,b14,b13,b12,b11,b10, b9, b8, b7, b6, b5, b4, b3, b2, b1, b0	
}


//a: 9  6 3 0    3  2  1 0               
//b: 10 7 4 1 -> 7  6  5 4       
//c: 11 8 5 2    11 10 9 8
SSP_FORCEINLINE
void ssp_convert_reverse_transpose_SSE2( __m128i *a, __m128i *b, __m128i *c )
{
    ssp_m128 A, B, C, T1, T2, T3;
    A.i = *a;   
    B.i = *b;   
    C.i = *c;  

    T1.f = _mm_shuffle_ps( C.f,  A.f,  _MM_SHUFFLE( 3,1,2,0) ); // 9  3  8  2
    T2.f = _mm_shuffle_ps( B.f,  A.f,  _MM_SHUFFLE( 2,0,2,0) ); // 6  0  7  1
    T3.f = _mm_shuffle_ps( C.f,  B.f,  _MM_SHUFFLE( 3,1,3,1) ); // 10 4  11 5

    A.f  = _mm_shuffle_ps( T2.f, T1.f, _MM_SHUFFLE( 2,0,0,2 ) ); //3  2  1  0  
    B.f  = _mm_shuffle_ps( T3.f, T2.f, _MM_SHUFFLE( 1,3,0,2 ) ); //7  6  5  4  
    C.f  = _mm_shuffle_ps( T1.f, T3.f, _MM_SHUFFLE( 1,3,3,1 ) ); //11 10 9  8   

    *a = A.i;
    *b = B.i;
    *c = C.i; 
}


SSP_FORCEINLINE
void ssp_convert_3p_3c_epi8_SSE2( __m128i *r, __m128i *g, __m128i *b )
{
    const static __m128i odd_8  = SSP_CONST_SET_8I(   0xFF,0,0xFF,0,0xFF,0,0xFF,0,0xFF,0,0xFF,0,0xFF,0,0xFF,0 );
    const static __m128i even_8 = SSP_CONST_SET_8I( 0,0xFF,0,0xFF,0,0xFF,0,0xFF,0,0xFF,0,0xFF,0,0xFF,0,0xFF   );

    const static __m128i odd_16  = SSP_CONST_SET_16I(   0xFFFF,0,0xFFFF,0,0xFFFF,0,0xFFFF,0 );
    const static __m128i even_16 = SSP_CONST_SET_16I( 0,0xFFFF,0,0xFFFF,0,0xFFFF,0,0xFFFF   );    

   ssp_m128 T, RG, GB, BR, RGBR, GBRG, BRGB;
   ssp_m128 A, B, C;
    
     RG.i = _mm_and_si128 (     *r, even_8  );  // Mask out the odd r bits
      T.i = _mm_slli_epi16(     *g, 8       );  // Move the even g bits to the odd position
     RG.i = _mm_or_si128  (   RG.i, T.i     );  // G14 R14 ... G2 R2 G0 R0

     GB.i = _mm_srli_epi16(     *g, 8       );      
      T.i = _mm_and_si128 (     *b, odd_8   );
     GB.i = _mm_or_si128  (   GB.i, T.i     );

     BR.i = _mm_and_si128 (     *b, even_8  );
      T.i = _mm_and_si128 (     *r, odd_8   );
     BR.i = _mm_or_si128  (   BR.i, T.i     );

   RGBR.i = _mm_and_si128 (   RG.i, even_16 );
      T.i = _mm_slli_epi32(   BR.i, 16      );
   RGBR.i = _mm_or_si128  ( RGBR.i, T.i     );

   GBRG.i = _mm_and_si128 (   GB.i, even_16 );
      T.i = _mm_and_si128 (   RG.i, odd_16  );
   GBRG.i = _mm_or_si128  ( GBRG.i, T.i     );

   BRGB.i = _mm_srli_epi32(   BR.i, 16      );
      T.i = _mm_and_si128 (   GB.i, odd_16  );
   BRGB.i = _mm_or_si128  ( BRGB.i, T.i     );

   ssp_convert_reverse_transpose_SSE2( &RGBR.i, &GBRG.i, &BRGB.i );

   *r = RGBR.i;
   *g = GBRG.i;
   *b = BRGB.i; 
}


SSP_FORCEINLINE
void ssp_convert_3p_3c_epi8_a_SSE2( __m128i *r, __m128i *g, __m128i *b )
{
    __m128i temp;                                           // R = r15,r14,r13,r12,r11,r10,r9,r8,r7,r6,r5,r4,r3,r2,r1,r0
                                                            // G = g15,g14,g13,g12,g11,g10,g9,g8,g7,g6,g5,g4,g3,g2,g1,g0
                                                            // B = b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0

   
                                        

                                                            // R =         r5 , b4  g4  r4 , b3  g3  r3 , b2  g2  r2 , b1  g1  r1 , b0  g0 r0
                                                            // G =     g10 r10, b9  g9  r9 , b8  g8  r8 , b7  g7  r7 , b6  g6  r6 , b5  g5   
                                                            // B = b15 g15 r15, b14 g14 r14, b13 g13 r13, b12 g12 r12, b11 g11 r11, b10 


    temp = _mm_srli_si128     (*r, 8);			            //  0,  0,  0,  0,  0,  0,  0,  0,r15,r14,r13,r12,r11,r10, r9, r8
    *r   = _mm_unpacklo_epi8  (*r, temp);		            //r15, r7,r14, r6,r13, r5,r12, r4,r11, r3,r10, r2, r9, r1, r8, r0
    temp = _mm_srli_si128     (*r, 8);			            //  0,  0,  0,  0,  0,  0,  0,  0,r15, r7,r14, r6,r13, r5,r12, r4 	
    *r   = _mm_unpacklo_epi8  (*r, temp);		            //r15,r11, r7, r3,r14,r10, r6, r2,r13, r9, r5, r1,r12, r8, r4, r0
    temp = _mm_srli_si128     (*r, 8);			            //  0,  0,  0,  0,  0,  0,  0,  0,r15,r11, r7, r3,r14,r10, r6, r2
    *r   = _mm_unpacklo_epi8  (*r, temp);		            //r15,r13,r11, r9, r7, r5, r3, r1,r14,r12,r10, r8, r6, r4, r2, r0

    temp = _mm_srli_si128     (*g, 8);			            //  0,  0,  0,  0,  0,  0,  0,  0,g15,g14,g13,g12,g11,g10, g9, g8
    *g   = _mm_unpacklo_epi8  (*g, temp);		            //g15, g7,g14, g6,g13, g5,g12, g4,g11, g3,g10, g2, g9, g1, g8, g0
    temp = _mm_srli_si128     (*g, 8);			            //  0,  0,  0,  0,  0,  0,  0,  0,g15, g7,g14, g6,g13, g5,g12, g4 
    *g   = _mm_unpacklo_epi8  (*g, temp);		            //g15,g11, g7, g3,g14,g10, g6, g2,g13, g9, g5, g1,g12, g8, g4, g0
    temp = _mm_srli_si128     (*g, 8);			            //  0,  0,  0,  0,  0,  0,  0,  0,g15,g11, g7, g3,g14,g10, g6, g2
    *g   = _mm_unpacklo_epi8  (*g, temp);		            //g15,g13,g11, g9, g7, g5, g3, g1,g14,g12,g10, g8, g6, g4, g2, g0

    temp = _mm_srli_si128     (*b, 8);			            //  0,  0,  0,  0,  0,  0,  0,  0,b15,b14,b13,b12,b11,b10, b9, b8
    *b   = _mm_unpacklo_epi8  (*b, temp);		            //b15, b7,b14, b6,b13, b5,b12, b4,b11, b3,b10, b2, b9, b1, b8, b0
    temp = _mm_srli_si128     (*b, 8);			            //  0,  0,  0,  0,  0,  0,  0,  0,b15, b7,b14, b6,b13, b5,b12, b4 
    *b   = _mm_unpacklo_epi8  (*b, temp);		            //b15,b11, b7, b3,b14,b10, b6, b2,b13, b9, b5, b1,b12, b8, b4, b0
    temp = _mm_srli_si128     (*b, 8);			            //  0,  0,  0,  0,  0,  0,  0,  0,b15,b11, b7, b3,b14,b10, b6, b2
    *b   = _mm_unpacklo_epi8  (*b, temp);		            //b15,b13,b11, b9, b7, b5, b3, b1,b14,b12,b10, b8, b6, b4, b2, b0

    temp = _mm_unpacklo_epi8  (*r, *g);			            //g14,r14,g12,r12,g10,r10, g8, r8, g6, r6, g4, r4, g2, r2, g0, r0
    *g   = _mm_unpackhi_epi8  (*g, *b);			            //b15,g15,b13,g13,b11,g11, b9, g9, b7, g7, b5, g5, b3, g3, b1, g1
    *r   = _mm_srli_si128     (*r, 8);			            //  0,  0,  0,  0,  0,  0,  0,  0,r15,r13,r11, r9, r7, r5, r3, r1
    *b   = _mm_unpacklo_epi8  (*b,*r);			            //r15,b14,r13,b12,r11,b10, r9, b8, r7, b6, r5, b4, r3, b2, r1, b0

    *r   = _mm_srli_si128     (temp, 8);			        //  0,  0,  0,  0,  0,  0,  0,  0,g14,r14,g12,r12,g10,r10, g8, r8
    temp = _mm_unpacklo_epi16 (temp, *r);		            //g14,r14, g6, r6,g12,r12, g4, r4,g10,r10, g2, r2, g8, r8, g0, r0
    *r   = _mm_srli_si128     (temp, 8);			        //  0,  0,  0,  0,  0,  0,  0,  0,g14,r14, g6, r6,g12,r12, g4, r4
    temp = _mm_unpacklo_epi16 (temp, *r);		            //g14,g10,r14,r10, g6, g2, r6, r2,g12, g8,r12, r8, g4, g0, r4, r0

    *r   = _mm_srli_si128     (*g, 8);			            //  0,  0,  0,  0,  0,  0,  0,  0,b15,g15,b13,g13,b11,g11, b9, g9
    *g   = _mm_unpacklo_epi16 (*g, *r);		                //b15,g15, b7, g7,b13,g13, b5, g5,b11,g11, b3, g3, b9, g9, b1, g1
    *r   = _mm_srli_si128     (*g, 8);			            //  0,  0,  0,  0,  0,  0,  0,  0,b15,g15, b7, g7,b13,g13, b5, g5
    *g   = _mm_unpacklo_epi16 (*g, *r);		                //b15,g15,b11,g11, b7, g7, b3, g3,b13,g13, b9, g9, b5, g5, b1, g1

    *r   = _mm_srli_si128     (*b, 8);			            //  0,  0,  0,  0,  0,  0,  0,  0,r15,b14,r13,b12,r11,b10, r9, b8
    *b   = _mm_unpacklo_epi16 (*b, *r);		                //r15,b14, r7, b6,r13,b12, r5, b4,r11,b10, r3, b2, r9, b8, r1, b0
    *r   = _mm_srli_si128     (*b, 8);			            //  0,  0,  0,  0,  0,  0,  0,  0,r15,b14, r7, b6,r13,b12, r5, b4
    *b   = _mm_unpacklo_epi16 (*b, *r);		                //r15,b14,r11,b10, r7, b6, r3, b2,r13,b12, r9, b8, r5, b4, r1, b0

    *r   = _mm_unpacklo_epi16 (temp, *g);		            //b13,g13,g12,r12, b9, g9, g8, r8, b5, g5, g4, r4, b1, g1, g0, r0
    *g   = _mm_unpackhi_epi16 (*b, *g);		                //b15,g15,r15,b14,b11,g11,r11,b10, b7, g7, r7, b6, b3, g3, r3, b2
    temp = _mm_srli_si128     (temp, 8);			        //  0,  0,  0,  0,  0,  0,  0,  0,g14,r14,g10,r10, g6, r6, g2, r2
    *b   = _mm_unpacklo_epi16 (*b, temp);		            //g14,r14,r13,b12,g10,r10, r9, b8, g6, r6, r5, b4, g2, r2, r1, b0

    temp = _mm_unpacklo_epi16 (*r, *b);		                // g6, r6, b5, g5, r5, b4, g4, r4, g2, r2, b1, g1, r1, b0, g0, r0
    *b   = _mm_unpackhi_epi16 (*r, *b);		                //g14,r14,b13,g13,r13,b12,g12,r12,g10,r10, b9, g9, r9, b8, g8, r8

    *r   = _mm_unpacklo_epi64 (temp, *b);		            //g10,r10, b9, g9, r9, b8, g8, r8, g2, r2, b1, g1, r1, b0, g0, r0
    *b   = _mm_unpackhi_epi32 (*g, *b);		                //g14,r14,b13,g13,b15,g15,r15,b14,r13,b12,g12,r12,b11,g11,r11,b10
    *b   = _mm_shufflehi_epi16(*b, _MM_SHUFFLE(1,0,3,2));   //b15,g15,r15,b14,g14,r14,b13,g13,r13,b12,g12,r12,b11,g11,r11,b10

    temp = _mm_srli_si128     (temp, 8);			        //  0,  0,  0,  0,  0,  0,  0,  0, g6, r6, b5, g5, r5, b4, g4, r4
    temp = _mm_unpacklo_epi32 (*g, temp);		            // g6, r6, b5, g5, b7, g7, r7, b6, r5, b4, g4, r4, b3, g3, r3, b2
    temp = _mm_shufflehi_epi16(temp, _MM_SHUFFLE(1,0,3,2)); //b7,g7,r7,b6,g6,r6,b5,g5,r5,b4,g4,r4,b3,g3,r3,b2

    *g   = _mm_unpackhi_epi64 (temp, *r);		            //g10,r10, b9, g9, r9, b8, g8, r8, b7, g7, r7, b6, g6, r6, b5, g5
    *r   = _mm_unpacklo_epi64 (*r, temp);		            // r5, b4, g4, r4, b3, g3, r3, b2, g2, r2, b1, g1, r1, b0, g0, r0
}


//@}
//@}

#endif // __SSEPLUS_CONVERT_SSE2_H__
