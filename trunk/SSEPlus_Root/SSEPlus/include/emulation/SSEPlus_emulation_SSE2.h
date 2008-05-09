//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __SSEPLUS_EMULATION_SSE2_H__
#define __SSEPLUS_EMULATION_SSE2_H__

#include "../SSEPlus_SSE2.h"
#include "../native/SSEPlus_native_SSE2.h"
#include "../logical/SSEPlus_logical_SSE2.h"
#include "../convert/SSEPlus_convert_SSE2.h"
#include "../arithmetic/SSEPlus_arithmetic_SSE2.h"


/** @addtogroup emulated_SSE2   
 *  @{ 
 *  @name SSE[3,4A,...,5] implemented in SSE2
 */


//
// Multiply Add
//
/** \SSE5{SSE2,_mm_macc_epi16, pmacsww } */ 
SSP_FORCEINLINE __m128i ssp_macc_epi16_SSE2( __m128i a, __m128i b, __m128i c )
{
    a = _mm_mullo_epi16( a, b );
    a = _mm_add_epi16( a, c );
    return a;
}

/** \SSE5{SSE2,_mm_macc_epi32, pmacsdd } */ 
SSP_FORCEINLINE __m128i ssp_macc_epi32_SSE2( __m128i a, __m128i b, __m128i c )
{
	//from Framewave CBL
	__m128i a1, b1, c1, d, x, y, LO;
	__m128i dstlo, dsthi, dst1;

	a1 = _mm_srai_epi32(a,16);
	b1 = _mm_slli_epi32(a,16);
	b1 = _mm_srli_epi32(b1,16);

	c1 = _mm_srai_epi32(b,16);
	d = _mm_slli_epi32(b,16);
	d = _mm_srli_epi32(d,16);

	dstlo =  _mm_mullo_epi16(b1,d);
	dsthi =  _mm_mulhi_epu16(b1,d);

	dst1 =_mm_unpacklo_epi16(dstlo,dsthi); 
	dsthi =_mm_unpackhi_epi16(dstlo,dsthi); 

	dstlo =_mm_unpacklo_epi32(dst1,dsthi); 
	dsthi =_mm_unpackhi_epi32(dst1,dsthi); 
	
	LO = _mm_unpacklo_epi32(dstlo,dsthi);

	dstlo =  _mm_mullo_epi16(a1,d);
	dsthi =  _mm_mulhi_epi16(a1,d);

	dst1 =_mm_unpacklo_epi16(dstlo,dsthi); 
	dsthi =_mm_unpackhi_epi16(dstlo,dsthi); 

	dstlo =_mm_unpacklo_epi32(dst1,dsthi); 
	dsthi =_mm_unpackhi_epi32(dst1,dsthi); 
	
	x = _mm_unpacklo_epi32(dstlo,dsthi);

	dstlo =  _mm_mullo_epi16(c1,b1);
	dsthi =  _mm_mulhi_epu16(c1,b1);

	dst1 =_mm_unpacklo_epi16(dstlo,dsthi); 
	dsthi =_mm_unpackhi_epi16(dstlo,dsthi); 

	dstlo =_mm_unpacklo_epi32(dst1,dsthi); 
	dsthi =_mm_unpackhi_epi32(dst1,dsthi); 
	
	y = _mm_unpacklo_epi32(dstlo,dsthi);

	x = _mm_add_epi32(x,y);

	y = _mm_srli_epi32(LO,16);

	y = _mm_add_epi32(y,x);
	
	y = _mm_slli_epi32(y,16);

	LO = _mm_slli_epi32(LO,16);
	LO = _mm_srli_epi32(LO,16);

	LO = _mm_or_si128(LO,y);

	return _mm_add_epi32(LO,c);
}

/** \SSE5{SSE2,_mm_macc_pd,fmaddpd} */ 
SSP_FORCEINLINE __m128d ssp_macc_pd_SSE2(__m128d a, __m128d b, __m128d c)
{
    a = _mm_mul_pd( a, b );
    a = _mm_add_pd( a, c );
    return a;
}
/** \SSE5{SSE2,_mm_macc_ps,fmaddps} */ 
SSP_FORCEINLINE __m128 ssp_macc_ps_SSE2( __m128 a, __m128 b, __m128 c )
{
    a = _mm_mul_ps( a, b );
    a = _mm_add_ps( a, c );
    return a;
}
/** \SSE5{SSE2,_mm_macc_sd,fmaddsd} */ 
SSP_FORCEINLINE __m128d ssp_macc_sd_SSE2(__m128d a, __m128d b, __m128d c)
{
    const static __m128i mask = SSP_CONST_SET_32I( SSP_ALL_SET_32I, SSP_ALL_SET_32I, 0, 0 );

    ssp_m128 A,B;
    A.d = a;
    B.d = b;
    B.d = ssp_macc_pd_SSE2( A.d, B.d, c );
    B.i = ssp_logical_bitwise_select_SSE2( A.i, B.i, mask ); // This was faster than using 2 shuffles
    return B.d;
}
/** \SSE5{SSE2,_mm_macc_ss,fmaddss} */ 
SSP_FORCEINLINE __m128 ssp_macc_ss_SSE2(__m128 a, __m128 b, __m128 c)   // Assuming SSE5 *_ss semantics are similar to _mm_add_ss. TODO: confirm
{
    const static __m128i mask = SSP_CONST_SET_32I( SSP_ALL_SET_32I, SSP_ALL_SET_32I, SSP_ALL_SET_32I, 0 );

    ssp_m128 A,B;
    A.f = a;
    B.f = b;
    B.f = ssp_macc_ps_SSE2( A.f, B.f, c );
    B.i = ssp_logical_bitwise_select_SSE2( A.i, B.i, mask ); // This was faster than using 2 shuffles
    return B.f;
}



//
// Negative Multiply Add
//

/** \SSE5{SSE2,_mm_nmacc_ps,fnmaddps} */ 
SSP_FORCEINLINE __m128 ssp_nmacc_ps_SSE2( __m128 a, __m128 b, __m128 c )
{
    const static __m128 neg1 = SSP_CONST_SET_32F( -1.0f, -1.0f, -1.0f, -1.0f );

    a = _mm_mul_ps( a, b    );
    a = _mm_mul_ps( a, neg1 );
    a = _mm_add_ps( a, c    );
    return a;
}

/** \SSE5{SSE2,_mm_nmacc_pd,fnmaddpd} */ 
SSP_FORCEINLINE __m128d ssp_nmacc_pd_SSE2(__m128d a, __m128d b, __m128d c)
{
    const static __m128d neg1 = SSP_CONST_SET_64F( -1.0, -1.0 );

    a = _mm_mul_pd( a, b    );
    a = _mm_mul_pd( a, neg1 );
    a = _mm_add_pd( a, c    );
    return a;
}

/** \SSE5{SSE2,_mm_nmacc_ss,fnmaddss} */ 
SSP_FORCEINLINE __m128 ssp_nmacc_ss_SSE2(__m128 a, __m128 b, __m128 c)   // Assuming SSE5 *_ss semantics are similar to _mm_add_ss. TODO: confirm
{
    const static __m128i mask = SSP_CONST_SET_32I( SSP_ALL_SET_32I, SSP_ALL_SET_32I, SSP_ALL_SET_32I, 0 );

    ssp_m128 A,B;
    A.f = a;
    B.f = b;
    B.f = ssp_nmacc_ps_SSE2( A.f, B.f, c );
    B.i = ssp_logical_bitwise_select_SSE2( A.i, B.i, mask ); // This was faster than using 2 shuffles
    return B.f;
}

/** \SSE5{SSE2,_mm_nmacc_sd,fnmaddsd} */ 
SSP_FORCEINLINE __m128d ssp_nmacc_sd_SSE2(__m128d a, __m128d b, __m128d c)
{
    const static __m128i mask = SSP_CONST_SET_32I( SSP_ALL_SET_32I, SSP_ALL_SET_32I, 0, 0 );

    ssp_m128 A,B;
    A.d = a;
    B.d = b;
    B.d = ssp_nmacc_pd_SSE2( A.d, B.d, c );
    B.i = ssp_logical_bitwise_select_SSE2( A.i, B.i, mask ); // This was faster than using 2 shuffles
    return B.d;
}

//
// Multiply Subtract
//

/** \SSE5{SSE2,_mm_msub_ps,fmsubps} */ 
SSP_FORCEINLINE __m128 ssp_msub_ps_SSE2(__m128 a, __m128 b, __m128 c)
{
    a = _mm_mul_ps( a, b );
    a = _mm_sub_ps( a, c );
    return a;
}

/** \SSE5{SSE2,_mm_msub_pd,fmsubpd} */ 
SSP_FORCEINLINE __m128d ssp_msub_pd_SSE2(__m128d a, __m128d b, __m128d c)
{
    a = _mm_mul_pd( a, b );
    a = _mm_sub_pd( a, c );
    return a;
}

/** \SSE5{SSE2,_mm_msub_ss,fmsubss} */ 
SSP_FORCEINLINE __m128 ssp_msub_ss_SSE2(__m128 a, __m128 b, __m128 c)
{
    const static __m128i mask = SSP_CONST_SET_32I( SSP_ALL_SET_32I, SSP_ALL_SET_32I, SSP_ALL_SET_32I, 0 );

    ssp_m128 A,B;
    A.f = a;
    B.f = b;
    B.f = ssp_msub_ps_SSE2( A.f, B.f, c );
    B.i = ssp_logical_bitwise_select_SSE2( A.i, B.i, mask ); // This was faster than using 2 shuffles
    return B.f;
}

/** \SSE5{SSE2,_mm_msub_sd,fmsubsd} */ 
SSP_FORCEINLINE __m128d ssp_msub_sd_SSE2(__m128d a, __m128d b, __m128d c)
{
    const static __m128i mask = SSP_CONST_SET_32I( SSP_ALL_SET_32I, SSP_ALL_SET_32I, 0, 0 );

    ssp_m128 A,B;
    A.d = a;
    B.d = b;
    B.d = ssp_msub_pd_SSE2( A.d, B.d, c );
    B.i = ssp_logical_bitwise_select_SSE2( A.i, B.i, mask ); // This was faster than using 2 shuffles
    return B.d;
}

//
// Negative Multiply Subtract
//

/** \SSE5{SSE2,_mm_nmsub_ps,fnmsubps} */ 
SSP_FORCEINLINE __m128 ssp_nmsub_ps_SSE2(__m128 a, __m128 b, __m128 c)
{
    const static __m128 neg1 = SSP_CONST_SET_32F( -1.0f, -1.0f, -1.0f, -1.0f );

    a = _mm_mul_ps( a, b    );
    a = _mm_mul_ps( a, neg1 );
    a = _mm_sub_ps( a, c    );
    return a;
}

/** \SSE5{SSE2,_mm_nmsub_pd,fnmsubpd} */ 
SSP_FORCEINLINE __m128d ssp_nmsub_pd_SSE2(__m128d a, __m128d b, __m128d c)
{
    const static __m128d neg1 = SSP_CONST_SET_64F( -1.0, -1.0 );

    a = _mm_mul_pd( a, b    );
    a = _mm_mul_pd( a, neg1 );
    a = _mm_sub_pd( a, c    );
    return a;
}

/** \SSE5{SSE2,_mm_nmsub_ss,fnmsubss} */ 
SSP_FORCEINLINE __m128 ssp_nmsub_ss_SSE2(__m128 a, __m128 b, __m128 c)
{
    const static __m128i mask = SSP_CONST_SET_32I( SSP_ALL_SET_32I, SSP_ALL_SET_32I, SSP_ALL_SET_32I, 0 );

    ssp_m128 A,B;
    A.f = a;
    B.f = b;
    B.f = ssp_nmsub_ps_SSE2( A.f, B.f, c );
    B.i = ssp_logical_bitwise_select_SSE2( A.i, B.i, mask ); // This was faster than using 2 shuffles
    return B.f;
}

/** \SSE5{SSE2,_mm_nmsub_sd,fnmsubsd} */ 
SSP_FORCEINLINE __m128d ssp_nmsub_sd_SSE2(__m128d a, __m128d b, __m128d c)
{
    const static __m128i mask = SSP_CONST_SET_32I( SSP_ALL_SET_32I, SSP_ALL_SET_32I, 0, 0 );

    ssp_m128 A,B;
    A.d = a;
    B.d = b;
    B.d = ssp_nmsub_pd_SSE2( A.d, B.d, c );
    B.i = ssp_logical_bitwise_select_SSE2( A.i, B.i, mask ); // This was faster than using 2 shuffles
    return B.d;
}

//
// Abs
//


/** \IMP{SSE2,_mm_abs_epi8,SSSE3} */
SSP_FORCEINLINE
__m128i ssp_abs_epi8_SSE2 (__m128i a)
{
    __m128i mask = _mm_cmplt_epi8( a, _mm_setzero_si128() );  // FFFF   where a < 0
	__m128i one  = _mm_set1_epi8(1);
    a    = _mm_xor_si128 ( a, mask  );                        // Invert where a < 0
    mask = _mm_and_si128 ( mask, one );                       // 0001   where a < 0
    a    = _mm_add_epi8  ( a, mask  );                        // Add 1  where a < 0 
    return a;
}

/** \IMP{SSE2,_mm_abs_epi16,SSSE3} */
SSP_FORCEINLINE
__m128i ssp_abs_epi16_SSE2 (__m128i a)
{
    __m128i mask = _mm_cmplt_epi16( a, _mm_setzero_si128() ); // FFFF   where a < 0
    a    = _mm_xor_si128 ( a, mask  );                        // Invert where a < 0
    mask = _mm_srli_epi16( mask, 15 );                        // 0001   where a < 0
    a    = _mm_add_epi16 ( a, mask  );                        // Add 1  where a < 0
    return a;
}

/** \IMP{SSE2,_mm_abs_epi32,SSSE3} */
SSP_FORCEINLINE
__m128i ssp_abs_epi32_SSE2 (__m128i a)
{
    __m128i mask = _mm_cmplt_epi32( a, _mm_setzero_si128() ); // FFFF   where a < 0
    a    = _mm_xor_si128 ( a, mask );                         // Invert where a < 0
    mask = _mm_srli_epi32( mask, 31 );                        // 0001   where a < 0
    a = _mm_add_epi32( a, mask );                             // Add 1  where a < 0
	return a;
}


/** \IMP{SSE2,_mm_addsub_ps,SSE3} */
SSP_FORCEINLINE
__m128 ssp_addsub_ps_SSE2(__m128 a, __m128 b)
{
    const static __m128 neg = SSP_CONST_SET_32F(  1, -1, 1, -1 );

    b = _mm_mul_ps( b, neg );
    a = _mm_add_ps( a, b   );
    return a;
}

/** \IMP{SSE2,_mm_addsub_ps,SSE3} */
SSP_FORCEINLINE
__m128d ssp_addsub_pd_SSE2(__m128d a, __m128d b)
{
    const static __m128d const_addSub_pd_neg = SSP_CONST_SET_64F( 1, -1 );

    b = _mm_mul_pd( b, const_addSub_pd_neg );
    a = _mm_add_pd( a, b   );
    return a;
}

//
// Blend
//

/** \IMP{SSE2,_mm_blend_epi16,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_blend_epi16_SSE2( __m128i a, __m128i b, const int mask )
{
    __m128i screen;
    const static __m128i mulShiftImm = SSP_CONST_SET_16I( 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000 ); // Shift mask multiply moves all bits to left, becomes MSB

    screen = _mm_set1_epi16  ( mask                );   // Load the mask into register
    screen = _mm_mullo_epi16 ( screen, mulShiftImm );   // Shift bits to MSB
    screen = _mm_srai_epi16  ( screen, 15          );   // Shift bits to obtain 0xFFFF or 0x0000
    b      = _mm_and_si128   ( screen,  b          );   // Mask out the correct values from b
    a      = _mm_andnot_si128( screen,  a          );   // Mask out the correct values from a (invert the mask)
    a      = _mm_or_si128    (      a,  b          );   // Or the 2 results.
    return a;
}

/** \IMP{SSE2,_mm_blend_pd,SSE4.1} */
SSP_FORCEINLINE
__m128d ssp_blend_pd_SSE2(  __m128d a, __m128d b, const int mask )
{
    __m128d screen;
    screen = _mm_set_pd(  (mask&0x2)>>1,    mask&0x1 );
    b      = _mm_mul_pd(              b,      screen );
    screen = _mm_set_pd( (~mask&0x2)>>1, (~mask&0x1) );
    a      = _mm_mul_pd(              a,      screen );
    a      = _mm_or_pd (              a,           b );
    return a;
}

/** \IMP{SSE2,_mm_blend_ps,SSE4.1} */
SSP_FORCEINLINE
__m128  ssp_blend_ps_SSE2( __m128  a, __m128  b, const int mask )               // _mm_blend_ps [SSE4.1]
{
    ssp_m128 screen, A, B;
    A.f = a;
    B.f = b;
    screen.i = ssp_movmask_imm8_to_epi32_SSE2( mask );
    screen.i = ssp_logical_bitwise_select_SSE2( B.i, A.i, screen.i );
    return screen.f;
}

/** \IMP{SSE2,_mm_blendv_epi8,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_blendv_epi8_SSE2( __m128i a, __m128i b, __m128i mask )
{
    __m128i mHi, mLo;
    __m128i zero = _mm_setzero_si128 ();

    mHi = _mm_unpacklo_epi8( zero, mask );
    mHi = _mm_srai_epi16   (  mHi,   15 );
    mHi = _mm_srli_epi16   (  mHi,    1 );

    mLo = _mm_unpackhi_epi8( zero, mask );
    mLo = _mm_srai_epi16   (  mLo,   15 );
    mLo = _mm_srli_epi16   (  mLo,    1 );

    mHi = _mm_packus_epi16  ( mHi,  mLo );

    b   = _mm_and_si128     (    b, mHi  );
    a   = _mm_andnot_si128  (  mHi,  a   );
    a   = _mm_or_si128      (    a,  b   );
    return a;
}

/** \IMP{SSE2,_mm_blendv_pd, SSE4.1} */
SSP_FORCEINLINE __m128d ssp_blendv_pd_SSE2( __m128d a, __m128d b, __m128d mask )
{
    ssp_m128 A, B, Mask;
    A.d = a;
    B.d = b;
    Mask.d = mask;

    Mask.i = _mm_shuffle_epi32( Mask.i, _MM_SHUFFLE(3, 3, 1, 1) );
    Mask.i = _mm_srai_epi32   ( Mask.i, 31                      );

    B.i = _mm_and_si128( B.i, Mask.i );
    A.i = _mm_andnot_si128( Mask.i, A.i );
    A.i = _mm_or_si128( A.i, B.i );
    return A.d;
}
/** \IMP{SSE2,_mm_blendv_epi8, SSE4.1} */
SSP_FORCEINLINE __m128  ssp_blendv_ps_SSE2( __m128  a, __m128  b, __m128 mask )     
{
    ssp_m128 A, B, Mask;
    A.f = a;
    B.f = b;
    Mask.f = mask;

    Mask.i = _mm_srai_epi32( Mask.i, 31 );
    B.i = _mm_and_si128( B.i, Mask.i );
    A.i = _mm_andnot_si128( Mask.i, A.i );
    A.i = _mm_or_si128( A.i, B.i );
    return A.f;
}

//
// Compare
//

/** \IMP{SSE2,_mm_cmpeq_epi64,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_cmpeq_epi64_SSE2( __m128i a, __m128i b )
{
    const static __m128i const_mask = SSP_CONST_SET_32I( 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFE );

    a = _mm_cmpeq_epi32( a, b );
    a = _mm_slli_epi64 ( a, 1 );
    a = _mm_cmpeq_epi32( a, const_mask ); // Values only equal if shifting by 1 results in FFFFFFFF FFFFFFFE
    return a;
}


//
// Horizontal Operations
//

/** \IMP{SSE2,_mm_hadd_epi16,SSE3} */
SSP_FORCEINLINE
__m128i ssp_hadd_epi16_SSE2( __m128i a, __m128i b )
{
    ssp_convert_odd_even_epi16_SSE2( &a, &b );
    a = _mm_add_epi16( a, b );     
    return a;
}

/** \IMP{SSE2,_mm_hadds_epi16, SSSE3} */
SSP_FORCEINLINE __m128i ssp_hadds_epi16_SSE2 ( __m128i a, __m128i b )                     
{
    ssp_convert_odd_even_epi16_SSE2( &a, &b );
    a = _mm_adds_epi16( a, b );    
    return a;
}


/** \IMP{SSE2,_mm_hsub_epi16,SSE3} */
SSP_FORCEINLINE
__m128i ssp_hsub_epi16_SSE2 ( __m128i a, __m128i b )
{
    ssp_convert_odd_even_epi16_SSE2( &a, &b ); 
    a = _mm_sub_epi16( a, b );     
    return a;  
}

/** \IMP{SSE2,_mm_hsub_epi16,SSE3} */
SSP_FORCEINLINE
__m128i ssp_hsubs_epi16_SSE2 ( __m128i a, __m128i b )
{
    ssp_convert_odd_even_epi16_SSE2( &a, &b ); 
    a = _mm_subs_epi16( a, b );     
    return a;  
}



/** \IMP{SSE2,_mm_hadd_epi32, SSSE3} */
SSP_FORCEINLINE __m128i ssp_hadd_epi32_SSE2( __m128i a, __m128i b )                        
{
   ssp_convert_odd_even_epi32_SSE2( &a, &b );
   a = _mm_add_epi32( a, b );
   return a; 
}

/** \IMP{SSE2,_mm_hsub_epi32, SSSE3} */
SSP_FORCEINLINE __m128i ssp_hsub_epi32_SSE2 ( __m128i a, __m128i b )                        
{
   ssp_convert_odd_even_epi32_SSE2( &a, &b );
   a = _mm_sub_epi32( b, a );
   return a;
}


/** \IMP{SSE2,_mm_hadd_ps,SSE3} */
SSP_FORCEINLINE
__m128 ssp_hadd_ps_SSE2(__m128 a, __m128 b)
{
    ssp_convert_odd_even_ps_SSE2( &a, &b );
    a = _mm_add_ps( a, b );
    return a;
}

/** \IMP{SSE2,_mm_hsub_ps,SSE3} */
SSP_FORCEINLINE
__m128 ssp_hsub_ps_SSE2(__m128 a, __m128 b)
{
    ssp_convert_odd_even_ps_SSE2( &a, &b );
    a = _mm_sub_ps( b, a );
    return a;
}


/** \IMP{SSE2,_mm_hadd_pd,SSE3} */
SSP_FORCEINLINE
__m128d ssp_hadd_pd_SSE2(__m128d a, __m128d b)
{
    ssp_m128 A,B,C;
    A.d = a;
    C.d = a;
    B.d = b;

    A.f = _mm_movelh_ps( A.f, B.f );
    B.f = _mm_movehl_ps( B.f, C.f );
    A.d = _mm_add_pd   ( A.d, B.d );
    return A.d;
}

/** \IMP{SSE2,_mm_hsub_pd,SSE3} */
SSP_FORCEINLINE
__m128d ssp_hsub_pd_SSE2(__m128d a, __m128d b)
{
    ssp_m128 A,B,C;
    A.d = a;
    C.d = a;
    B.d = b;

    A.f = _mm_movelh_ps( A.f, B.f );
    B.f = _mm_movehl_ps( B.f, C.f );
    A.d = _mm_sub_pd   ( A.d, B.d );
    return A.d;
}


//__m128i _mm_mulhrs_epi16( __m128i a,  __m128i b);
/** \IMP{SSE2,_mm_mulhrs_epi16, SSSE3} */
SSP_FORCEINLINE __m128i ssp_mulhrs_epi16_SSE2( __m128i a, __m128i b )
{
    const static __m128i VAL = SSP_CONST_SET_32I( 0x4000, 0x4000, 0x4000, 0x4000 );
    __m128i c,d;   

    c = _mm_mullo_epi16( a, b );
    d = _mm_mulhi_epi16( a, b );
   
    a = _mm_unpackhi_epi16( c, d );
    b = _mm_unpacklo_epi16( c, d );

    a = _mm_add_epi32( a, VAL );
    b = _mm_add_epi32( b, VAL );

    a = _mm_srai_epi32( a, 15 );
    b = _mm_srai_epi32( b, 15 );

    a = _mm_packs_epi32( b, a );
    return a;
}


/** \IMP{SSE2,_mm_insert_epi32,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_insert_epi32_SSE2( __m128i a, int b, const int ndx )            // TODO: Verify behavior on Intel Hardware
{
    switch( ndx & 0x3 )
    {
    case 0: a = _mm_insert_epi16( a, b    , 0 );
            a = _mm_insert_epi16( a, b<<16, 1 ); break;
    case 1: a = _mm_insert_epi16( a, b    , 2 );
            a = _mm_insert_epi16( a, b<<16, 3 ); break;
    case 2: a = _mm_insert_epi16( a, b    , 4 );
            a = _mm_insert_epi16( a, b<<16, 5 ); break;
    case 3: a = _mm_insert_epi16( a, b    , 6 );
            a = _mm_insert_epi16( a, b<<16, 7 ); break;
    }
    return a;
}

//
// Min / Max
//

/** \IMP{SSE2,_mm_min_epi8, SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_min_epi8_SSE2( __m128i a, __m128i b )
{
    __m128i mask  = _mm_cmplt_epi8( a, b );                             // FFFFFFFF where a < b
    a = ssp_logical_bitwise_select_SSE2( a, b, mask );
    return a;
}

/** \IMP{SSE2,_mm_max_epi8, SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_max_epi8_SSE2( __m128i a, __m128i b )
{
    __m128i mask  = _mm_cmpgt_epi8( a, b );                             // FFFFFFFF where a > b
    a = ssp_logical_bitwise_select_SSE2( a, b, mask );
    return a;
}

/** \IMP{SSE2,_mm_min_epu16, SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_min_epu16_SSE2( __m128i a, __m128i b )
{
    __m128i mask = ssp_logical_cmplt_epu16_SSE2( a, b );
    a = ssp_logical_bitwise_select_SSE2( a, b, mask );
    return a;
}

/** \IMP{SSE2,_mm_max_epu16, SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_max_epu16_SSE2( __m128i a, __m128i b )
{
    __m128i mask = ssp_logical_cmpgt_epu16_SSE2( a, b );
    a = ssp_logical_bitwise_select_SSE2( a, b, mask );
    return a;
}

/** \IMP{SSE2,_mm_min_epi32, SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_min_epi32_SSE2( __m128i a, __m128i b )
{
    __m128i mask  = _mm_cmplt_epi32( a, b );                            // FFFFFFFF where a < b
    a = ssp_logical_bitwise_select_SSE2( a, b, mask );
    return a;
}

/** \IMP{SSE2,_mm_max_epi32, SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_max_epi32_SSE2( __m128i a, __m128i b )
{
    __m128i mask  = _mm_cmpgt_epi32( a, b );                            // FFFFFFFF where a > b
    a = ssp_logical_bitwise_select_SSE2( a, b, mask );
    return a;
}

/** \IMP{SSE2,_mm_min_epu32,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_min_epu32_SSE2 ( __m128i a, __m128i b )
{
    __m128i mask = ssp_logical_cmplt_epu32_SSE2( a, b );
    a = ssp_logical_bitwise_select_SSE2( a, b, mask );
    return a;
}

/** \IMP{SSE2,_mm_max_epu32,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_max_epu32_SSE2 ( __m128i a, __m128i b )
{
   __m128i mask = ssp_logical_cmpgt_epu32_SSE2( a, b );
    a = ssp_logical_bitwise_select_SSE2( a, b, mask );
    return a;
}


/** \IMP{SSE2,_mm_maddubs_epi16, SSSE3} 

in:  2 registers x 16 x 8 bit values (a is unsigned, b is signed)
out: 1 register  x 8  x 16 bit values

r0 := SATURATE_16((a0 * b0) + (a1 * b1))

*/
SSP_FORCEINLINE __m128i ssp_maddubs_epi16_SSE2( __m128i a,  __m128i b)
{
    const static __m128i EVEN_8 = SSP_CONST_SET_8I( 0,0xFF,0,0xFF,0,0xFF,0,0xFF,0,0xFF,0,0xFF,0,0xFF,0,0xFF);
    __m128i Aodd, Aeven, Beven, Bodd;

    // Convert the 8 bit inputs into 16 bits by dropping every other value
    Aodd  = _mm_srli_epi16( a, 8 );             // A is unsigned  
    Bodd  = _mm_srai_epi16( b, 8 );             // B is signed

    Aeven = _mm_and_si128 ( a, EVEN_8 );        // A is unsigned   
    Beven = _mm_slli_si128( b,     1  );        // B is signed
    Beven = _mm_srai_epi16( Beven, 8  );

    a = _mm_mullo_epi16( Aodd , Bodd  );        // Will always fit in lower 16
    b = _mm_mullo_epi16( Aeven, Beven );  
    a = _mm_adds_epi16 ( a, b );
	return a;
}



/** \IMP{SSE2,_mm_mpsadbw_epu8, SSE4.?} */
SSP_FORCEINLINE
__m128i ssp_mpsadbw_epu8_SSE2 ( __m128i a, __m128i b, const int msk  ) // _mm_mpsadbw_epu8
{
    const static __m128i MASK_BITS04 = SSP_CONST_SET_16I( 0,0,0,0xFFFF,0,0,0,0xFFFF );
    const static __m128i MASK_BITS15 = SSP_CONST_SET_16I( 0,0,0xFFFF,0,0,0,0xFFFF,0 );
    const static __m128i MASK_BITS26 = SSP_CONST_SET_16I( 0,0xFFFF,0,0,0,0xFFFF,0,0 );
    const static __m128i MASK_BITS37 = SSP_CONST_SET_16I( 0xFFFF,0,0,0,0xFFFF,0,0,0 );

    ssp_m128 A,B,A16,tmp,out;
    A.i = a;
    B.i = b;

    switch( msk & 0x4 )         // Possible values: 0, 4
    {
    case 4: A.i = _mm_srli_si128( A.i, 4 );
    }

    switch( (msk & 0x3) * 4 )   // Possible values: 0, 4, 8, 12
    {
    case 0:     B.i = _mm_shuffle_epi32( B.i, _MM_SHUFFLE(0,0,0,0) ); break;
    case 4:     B.i = _mm_shuffle_epi32( B.i, _MM_SHUFFLE(1,1,1,1) ); break;
    case 8:     B.i = _mm_shuffle_epi32( B.i, _MM_SHUFFLE(2,2,2,2) ); break;
    case 12:    B.i = _mm_shuffle_epi32( B.i, _MM_SHUFFLE(3,3,3,3) ); break;
    //default: ASSERT( false );
    }

    // out[0,4]
    B.i   = _mm_unpacklo_epi8( B.i, _mm_setzero_si128() );          // 1 2 3 4 | 1 2 3 4
    A16.i = _mm_unpacklo_epi8( A.i, _mm_setzero_si128() );          // a b c d | e f g h
    tmp.i = _mm_subs_epi16                 ( A16.i, B.i );          // a-1,b-2,c-3,d-4 | e-1,f-2,g-3,h-4
    tmp.i = ssp_abs_epi16_SSE2             ( tmp.i    );            // abs(a-1),abs(b-2),...,abs(h-4) | ...
    tmp.i = ssp_arithmetic_hadd4_epi16_SSE2( tmp.i, 0 );            // x,x,x,abs(a-1)+abs(b-2)+abs(c-3)+abs(d-4) | ...
    tmp.i = _mm_and_si128                  ( tmp.i, MASK_BITS04 );  // 0,0,0,abs(a-1)+abs(b-2)+abs(c-3)+abs(d-4) | ...
    out.i = tmp.i;

    // out[1,5]
    A16.i = _mm_srli_si128   ( A.i, 1 );
    A16.i = _mm_unpacklo_epi8( A16.i, _mm_setzero_si128() );        // b c | d e | f g | h i
    tmp.i = _mm_subs_epi16                 ( A16.i, B.i );
    tmp.i = ssp_abs_epi16_SSE2             ( tmp.i    );
    tmp.i = ssp_arithmetic_hadd4_epi16_SSE2( tmp.i, 1 );
    tmp.i = _mm_and_si128                  ( tmp.i, MASK_BITS15 );
    out.i = _mm_or_si128                   ( out.i, tmp.i );

    // out[2,6]
    A16.i = _mm_srli_si128   ( A.i, 2 );
    A16.i = _mm_unpacklo_epi8( A16.i, _mm_setzero_si128() );        // c d | e f | g h | i j
    tmp.i = _mm_subs_epi16                 ( A16.i, B.i );
    tmp.i = ssp_abs_epi16_SSE2             ( tmp.i    );
    tmp.i = ssp_arithmetic_hadd4_epi16_SSE2( tmp.i, 2 );
    tmp.i = _mm_and_si128                  ( tmp.i, MASK_BITS26 );
    out.i = _mm_or_si128                   ( out.i, tmp.i );

    // out[3,7]
    A16.i = _mm_srli_si128   ( A.i, 3 );
    A16.i = _mm_unpacklo_epi8( A16.i, _mm_setzero_si128() );        // d e | f g | h i | j k
    tmp.i = _mm_subs_epi16                 ( A16.i, B.i );
    tmp.i = ssp_abs_epi16_SSE2             ( tmp.i    );
    tmp.i = ssp_arithmetic_hadd4_epi16_SSE2( tmp.i, 3 );
    tmp.i = _mm_and_si128                  ( tmp.i, MASK_BITS37 );
    out.i = _mm_or_si128                   ( out.i, tmp.i );

    return out.i;
}


//---------------------------------------
// Dot Product
//---------------------------------------

/** \IMP{SSE2,_mm_dp_pd, SSE4.1} */
SSP_FORCEINLINE
__m128d ssp_dp_pd_SSE2( __m128d a, __m128d b, const int mask )               // _mm_dp_pd [SSE4,  cycles]
{
    int smallMask = (mask & 0x33)<<16;
    const static __m128i mulShiftImm_01 = SSP_CONST_SET_32I( 0x40000000, 0x40000000, 0x80000000, 0x80000000 );   // Shift mask multiply moves 0,1, bits to left, becomes MSB
    const static __m128i mulShiftImm_45 = SSP_CONST_SET_32I( 0x04000000, 0x04000000, 0x08000000, 0x08000000 );   // Shift mask multiply moves 4,5, bits to left, becomes MSB
    ssp_m128 mHi, mLo;

    mLo.i = _mm_set1_epi32( smallMask );// Load the mask into register
    mHi.i = _mm_mullo_epi16( mLo.i, mulShiftImm_01 );       // Shift the bits
    mLo.i = _mm_mullo_epi16( mLo.i, mulShiftImm_45 );       // Shift the bits

    mHi.i = _mm_cmplt_epi32( mHi.i, _mm_setzero_si128() );  // FFFFFFFF if bit set, 00000000 if not set
    mLo.i = _mm_cmplt_epi32( mLo.i, _mm_setzero_si128() );  // FFFFFFFF if bit set, 00000000 if not set

    a = _mm_and_pd( a, mHi.d );                                     // Clear input using the high bits of the mask
    a = _mm_mul_pd( a, b );

    b = _mm_shuffle_pd( a, a, _MM_SHUFFLE2(0, 1) );                 // Shuffle the values so that we b = { a[0], a[1] } and a = { a[1], a[0] }
    a = _mm_add_pd( a, b );                                         // Horizontally add the 4 values
    a = _mm_and_pd( a, mLo.d );                                     // Clear output using low bits of the mask
    return a;
}

/** \IMP{SSE2,_mm_dp_pd, SSE4.1} */
SSP_FORCEINLINE
__m128 ssp_dp_ps_SSE2( __m128 a, __m128 b, const int mask )                  // _mm_dp_ps() [SSE4, 28 cycles]
{
    const static __m128i mulShiftImm_0123 = SSP_CONST_SET_32I( 0x010000, 0x020000, 0x040000, 0x080000 );   // Shift mask multiply moves 0,1,2,3 bits to left, becomes MSB
    const static __m128i mulShiftImm_4567 = SSP_CONST_SET_32I( 0x100000, 0x200000, 0x400000, 0x800000 );   // Shift mask multiply moves 4,5,6,7 bits to left, becomes MSB

    // Begin mask preparation
    ssp_m128 mHi, mLo;
    mLo.i = _mm_set1_epi32( mask );                                 // Load the mask into register
    mLo.i = _mm_slli_si128( mLo.i, 3 );                             // Shift into reach of the 16 bit multiply

    mHi.i = _mm_mullo_epi16( mLo.i, mulShiftImm_0123 );             // Shift the bits
    mLo.i = _mm_mullo_epi16( mLo.i, mulShiftImm_4567 );             // Shift the bits

    mHi.i = _mm_cmplt_epi32( mHi.i, _mm_setzero_si128() );          // FFFFFFFF if bit set, 00000000 if not set
    mLo.i = _mm_cmplt_epi32( mLo.i, _mm_setzero_si128() );          // FFFFFFFF if bit set, 00000000 if not set
    // End mask preparation - Mask bits 0-3 in mLo, 4-7 in mHi

    a = _mm_and_ps( a, mHi.f );                                     // Clear input using the high bits of the mask
    a = _mm_mul_ps( a, b );

    a = ssp_arithmetic_hadd4_dup_ps_SSE2( a );                      // Horizontally add the 4 values
    a = _mm_and_ps( a, mLo.f );                                     // Clear output using low bits of the mask
    return a;
}

/** \IMP{SSE2,_mm_round_ps, SSE4.1}\n
\b NOTE_1: When rounding from negative numbers to zero, this function returns 0 and NOT -0. \n
If this behavor is desired, use the slower function ssp_round_ps_neg_zero_SSE2(). \n
\b NOTE_2: This functon should used only with input in the range (-2,147,483,648 -> 2,147,483,647) \n
If a greater range is desired, use the slower function ssp_round_ps_REF().
*/
SSP_FORCEINLINE
__m128 ssp_round_ps_SSE2( __m128  a, int iRoundMode )
{
    #pragma message( "" WARN() "SSEPlus SSE2 rounding functions overflow if input outside 32 bit integer range" )

    enum ENUM_MXCSR
    {
        CSR_ROUND_TO_EVEN = 0x00001F80, //
        CSR_ROUND_DOWN    = 0x00003F80, //
        CSR_ROUND_UP      = 0x00005F80, //
        CSR_ROUND_TRUNC   = 0x00007F80, //(_mm_getcsr() & ~_mm_ROUND_MASK) | _mm_ROUND_TOWARD_ZERO;
    }; 

    ssp_u32 bak = _mm_getcsr();
    ssp_m128 A, i;
    A.f = a;

    switch( iRoundMode & 0x3 )
    {
    case SSP_FROUND_CUR_DIRECTION:                                      break;
    case SSP_FROUND_TO_ZERO:            _mm_setcsr( CSR_ROUND_TRUNC  ); break;
    case SSP_FROUND_TO_POS_INF:         _mm_setcsr( CSR_ROUND_UP     ); break;
    case SSP_FROUND_TO_NEG_INF:         _mm_setcsr( CSR_ROUND_DOWN   ); break;
    default:                            _mm_setcsr( CSR_ROUND_TO_EVEN); break;
    }
    
    i.i    = _mm_cvtps_epi32( A.f );    // Convert to integer
    A.f    = _mm_cvtepi32_ps( i.i );    // Convert back to float

    i.u32[0] = bak;                     // Workaround for a bug in the MSVC compiler. MSVC was hoisting the mxcsr restore above the converts. 
    _mm_setcsr( i.u32[0] );
    return A.f;
}


SSP_FORCEINLINE
__m128d ssp_round_pd_SSE2( __m128d  a, int iRoundMode )
{
    #pragma message( "" WARN() "SSEPlus SSE2 rounding functions overflow if input outside 32 bit integer range" )

    enum ENUM_MXCSR
    {
        CSR_ROUND_TO_EVEN = 0x00001F80, //
        CSR_ROUND_DOWN    = 0x00003F80, //
        CSR_ROUND_UP      = 0x00005F80, //
        CSR_ROUND_TRUNC   = 0x00007F80, //(_mm_getcsr() & ~_mm_ROUND_MASK) | _mm_ROUND_TOWARD_ZERO;
    }; 

    ssp_u32 bak = _mm_getcsr();
    ssp_m128 A, i;
    A.d = a;
    

    switch( iRoundMode & 0x3 )
    {
    case SSP_FROUND_CUR_DIRECTION:                                      break;
    case SSP_FROUND_TO_ZERO:            _mm_setcsr( CSR_ROUND_TRUNC  ); break;
    case SSP_FROUND_TO_POS_INF:         _mm_setcsr( CSR_ROUND_UP     ); break;
    case SSP_FROUND_TO_NEG_INF:         _mm_setcsr( CSR_ROUND_DOWN   ); break;
    default:                            _mm_setcsr( CSR_ROUND_TO_EVEN); break;
    }
    
    i.i    = _mm_cvtpd_epi32( A.d );    // Convert to integer
    A.d    = _mm_cvtepi32_pd( i.i );    // Convert back to float

    i.u32[0] = bak;                     // Workaround for a bug in the MSVC compiler. MSVC was hoisting the mxcsr restore above the converts. 
    _mm_setcsr( i.u32[0] );             
    return A.d;
}

/** \IMP{SSE2,_mm_round_ss, SSE4.1} */
SSP_FORCEINLINE
__m128 ssp_round_ss_SSE2( __m128  a, __m128  b, int iRoundMode )
{
	//Commented code will generate linker error in x64 platform
    //ssp_m128 A,B;
    //A.f = a;
    //B.f = ssp_round_ps_SSE2( b, iRoundMode );

    //A.f = _mm_move_ss( A.f, B.f );

    ////A.f32[0] = B.f32[0];
	//return A.f;
	b = ssp_round_ps_SSE2(b, iRoundMode);               // B contains modified values through whole vector
	b =    _mm_shuffle_ps(b, a, _MM_SHUFFLE(1,1,0,0));  
    return _mm_shuffle_ps(b, a, _MM_SHUFFLE(3,2,2,0)); 
}

/** \IMP{SSE2,_mm_ceil_ps, SSE4.1} */
SSP_FORCEINLINE
__m128 ssp_ceil_ps_SSE2( __m128 a )
{
    return ssp_round_ps_SSE2( a, SSP_FROUND_TO_POS_INF );
}

/** \IMP{SSE2,_mm_floor_ps, SSE4.1} */
SSP_FORCEINLINE
__m128 ssp_floor_ps_SSE2( __m128 a )
{
    return ssp_round_ps_SSE2( a, SSP_FROUND_TO_NEG_INF );
}

/** \IMP{SSE2,_mm_floor_pd, SSE4.1} */
SSP_FORCEINLINE
__m128d ssp_floor_pd_SSE2( __m128d a )
{
    return ssp_round_pd_SSE2( a, SSP_FROUND_TO_NEG_INF );
}

/** \IMP{SSE2,_mm_ceil_pd, SSE4.1} */
SSP_FORCEINLINE
__m128d ssp_ceil_pd_SSE2( __m128d a )
{
    return ssp_round_pd_SSE2( a, SSP_FROUND_TO_POS_INF );
}

/** \IMP{SSE2,_mm_ceil_sd, SSE4.1} */
SSP_FORCEINLINE __m128d ssp_floor_sd_SSE2( __m128d a, __m128d b)                              
{
	b = ssp_round_pd_SSE2(b, SSP_FROUND_TO_NEG_INF );

    return _mm_shuffle_pd(b, a, _MM_SHUFFLE2(1,0));
}

/** \IMP{SSE2,_mm_ceil_sd, SSE4.1} */
SSP_FORCEINLINE __m128d ssp_ceil_sd_SSE2( __m128d a, __m128d b)                              
{
	b = ssp_round_pd_SSE2(b, SSP_FROUND_TO_POS_INF );

    return _mm_shuffle_pd(b, a, _MM_SHUFFLE2(1,0));
}

/** \IMP{SSE2,_mm_floor_ss, SSE4.1} */
SSP_FORCEINLINE __m128 ssp_floor_ss_SSE2( __m128 a, __m128 b)                              
{
	b = ssp_round_ps_SSE2(b, SSP_FROUND_TO_NEG_INF );
	b = _mm_shuffle_ps(b, a, _MM_SHUFFLE(1,1,0,0));
    return _mm_shuffle_ps(b, a, _MM_SHUFFLE(3,2,2,0));
}

/** \IMP{SSE2,_mm_ceil_ss, SSE4.1} */
SSP_FORCEINLINE __m128 ssp_ceil_ss_SSE2( __m128 a, __m128 b)                              
{
	b = ssp_round_ps_SSE2(b, SSP_FROUND_TO_POS_INF );
	b = _mm_shuffle_ps(b, a, _MM_SHUFFLE(1,1,0,0));
    return _mm_shuffle_ps(b, a, _MM_SHUFFLE(3,2,2,0));
}


//SSP_FORCEINLINE
//__m128i _mm_mul_epi32( __m128i a, __m128i b ) //_mm_mul_epi32
//{
//    //ssp_m128 sign;
//
//    //sign.i = ::_mm_xor_si128( a, b );
//
//    //__m128i t1;
//
//    a = _mm_min_epi32( a, b );
//
//    //a = _mm_slli_si128( a, 4 );
//    //b = _mm_slli_si128( b, 4 );
//
//    //a = _mm_mul_epu32( a, b );
//
//    //a = _mm_slli_si128( a, 4 );
//
//    return a;
//}


//type conversion

/** \IMP{SSE2,_mm_cvtepi8_epi16,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_cvtepi8_epi16_SSE2 ( __m128i a)
{
	__m128i b = _mm_setzero_si128 ();
	__m128i c = _mm_unpacklo_epi8(a, b);
	__m128i d = _mm_set1_epi16 (128);

	b = _mm_and_si128(d, c);
	d = _mm_set1_epi16(0x1FE);
	b = _mm_mullo_epi16(b, d);

	return _mm_add_epi16(c, b);

	//Another way, slower
	//__m128i b = _mm_set1_epi32 (-1);				//0xFFFFFFFF
	//__m128i c = _mm_unpacklo_epi8(a, b);			//FFa0FFa1....
	//__m128i d = _mm_set1_epi16 (128);				//0x80
	//b = _mm_andnot_si128(c, d);					// 0x80 for positive, 0x00 for negative
	//d = _mm_slli_epi16(b, 1);						// 0x100 for positive, 0x000 for negative
	//return _mm_add_epi16(c, d);
}

/** \IMP{SSE2,_mm_cvtepi8_epi32,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_cvtepi8_epi32_SSE2 ( __m128i a)
{
	__m128i b = _mm_set1_epi32 (-1);				//0xFFFFFFFF
	__m128i c = _mm_unpacklo_epi8(a, b);			//FFa0FFa1....
	__m128i d = _mm_set1_epi32 (128);				//0x80

	c = _mm_unpacklo_epi16(c, b);					//FFFFFFa0FFFFFFa1...
	b = _mm_andnot_si128(c, d);						// 0x80 for positive, 0x00 for negative
	d = _mm_slli_epi32(b, 1);						// 0x100 for positive, 0x000 for negative

	return _mm_add_epi32(c, d);
}

/** \IMP{SSE2,_mm_cvtepi8_epi64,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_cvtepi8_epi64_SSE2 ( __m128i a)
{
	__m128i b = _mm_set1_epi32 (-1);				//0xFFFFFFFF
	__m128i c = _mm_unpacklo_epi8(a, b);			//FFa0FFa1....
	__m128i d = _mm_set_epi32 (0, 128, 0, 128);		//0x80

	c = _mm_unpacklo_epi16(c, b);					//FFFFFFa0FFFFFFa1...
	c = _mm_unpacklo_epi32(c, b);					//FFFFFFFFFFFFFFa0...
	b = _mm_andnot_si128(c, d);						// 0x80 for positive, 0x00 for negative
	d = _mm_slli_epi64(b, 1);						// 0x100 for positive, 0x000 for negative

	return _mm_add_epi64(c, d);
}

/** \IMP{SSE2,_mm_cvtepi16_epi32,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_cvtepi16_epi32_SSE2 ( __m128i a)
{
	__m128i b = _mm_set1_epi32 (-1);				//0xFFFFFFFF
	__m128i c = _mm_unpacklo_epi16(a, b);			//FFFFa0**FFFFa1**....
	__m128i d = _mm_set1_epi32 (0x8000);			//0x8000

	b = _mm_andnot_si128(c, d);						// 0x80 for positive, 0x00 for negative
	d = _mm_slli_epi32(b, 1);						// 0x100 for positive, 0x000 for negative

	return _mm_add_epi32(c, d);
}

/** \IMP{SSE2,_mm_cvtepi16_epi64,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_cvtepi16_epi64_SSE2 ( __m128i a)
{
	__m128i b = _mm_set1_epi32 (-1);				//0xFFFFFFFF
	__m128i c = _mm_unpacklo_epi16(a, b);			//FFFFa0**FFFFa1**....
	__m128i d = _mm_set_epi32(0,0x8000, 0,0x8000);	//0x8000

	c = _mm_unpacklo_epi32(c, b);					//FFFFFFFFFFFFFFa0...
	b = _mm_andnot_si128(c, d);						// 0x80 for positive, 0x00 for negative
	d = _mm_slli_epi64(b, 1);						// 0x100 for positive, 0x000 for negative

	return _mm_add_epi64(c, d);
}

/** \IMP{SSE2,_mm_cvtepi32_epi64,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_cvtepi32_epi64_SSE2 ( __m128i a)
{
	__m128i b = _mm_set1_epi32 (-1);				//0xFFFFFFFF
	__m128i c = _mm_unpacklo_epi32(a, b);			//FFFFFFFFa0******FFFFFFFFa1******....
	__m128i d = _mm_set_epi32(0, 0x80000000,0,0x80000000);	//0x80000000

	b = _mm_andnot_si128(c, d);						// 0x80 for positive, 0x00 for negative
	d = _mm_slli_epi64(b, 1);						// 0x100 for positive, 0x000 for negative

	return _mm_add_epi64(c, d);
}

/** \IMP{SSE2,_mm_cvtepu8_epi16,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_cvtepu8_epi16_SSE2 ( __m128i a)
{
	__m128i b =_mm_setzero_si128 ();

	return _mm_unpacklo_epi8(a, b);
}

/** \IMP{SSE2,_mm_cvtepu8_epi32,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_cvtepu8_epi32_SSE2 ( __m128i a)
{
	__m128i b = _mm_setzero_si128 ();

	a = _mm_unpacklo_epi8(a, b);

	return _mm_unpacklo_epi16(a, b);
}

/** \IMP{SSE2,_mm_cvtepu8_epi64,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_cvtepu8_epi64_SSE2 ( __m128i a)
{
	__m128i b = _mm_setzero_si128 ();

	a = _mm_unpacklo_epi8(a, b);

	a = _mm_unpacklo_epi16(a, b);

	return _mm_unpacklo_epi32(a, b);
}

/** \IMP{SSE2,_mm_cvtepu16_epi32,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_cvtepu16_epi32_SSE2 ( __m128i a)
{
	__m128i b = _mm_setzero_si128 ();

	return _mm_unpacklo_epi16(a, b);
}

/** \IMP{SSE2,_mm_cvtepu16_epi64,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_cvtepu16_epi64_SSE2 ( __m128i a)
{
	__m128i b = _mm_setzero_si128 ();

	a = _mm_unpacklo_epi16(a, b);

	return _mm_unpacklo_epi32(a, b);
}

/** \IMP{SSE2,_mm_cvtepu32_epi64,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_cvtepu32_epi64_SSE2 ( __m128i a)
{
	__m128i b = _mm_setzero_si128 ();

	return _mm_unpacklo_epi32(a, b);
}

/** \IMP{SSE2,_mm_packus_epi32,SSE4.1} */
SSP_FORCEINLINE
__m128i ssp_packus_epi32_SSE2( __m128i a, __m128i b )
{
    const static __m128i val_32 = SSP_CONST_SET_32I(  0x8000, 0x8000, 0x8000, 0x8000 );
    const static __m128i val_16 = SSP_CONST_SET_16I(  0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000 );

    a = _mm_sub_epi32( a, val_32 );
    b = _mm_sub_epi32( b, val_32 );
    a = _mm_packs_epi32( a, b );
    a = _mm_add_epi16( a, val_16 );
    return a;
}

//SSSE3
// bit manipulation
//__m128i _mm_alignr_epi8(__m128i a, __m128i b, const int ralign);
/**  \IMP{Reference,_mm_alignr_epi8,SSSE3} */
SSP_FORCEINLINE
__m128i ssp_alignr_epi8_SSE2 (__m128i a, __m128i b, const int ralign)
{
	if (ralign < 0)  return b; //only shift to right, no negative
	//if (ralign > 32) return _mm_setzero_si128();
	//
	//if (ralign > 16) return _mm_srli_si128(a, ralign-16);

	//b = _mm_srli_si128(b, ralign);
	//a = _mm_slli_si128(a, 16-ralign);
	switch (ralign) {
        case 0: 
                return b;                       
        case 1:	
                b = _mm_srli_si128(b, 1);       
                a = _mm_slli_si128(a, 15);	    
                return _mm_or_si128( a, b );	
        case 2: 
                b = _mm_srli_si128(b, 2);       
                a = _mm_slli_si128(a, 14);	    
                return _mm_or_si128( a, b );	
        case 3:	
                b = _mm_srli_si128(b, 3);       
                a = _mm_slli_si128(a, 13);	    
                return _mm_or_si128( a, b );	
        case 4:				                
                b = _mm_srli_si128(b, 4);	    
                a = _mm_slli_si128(a, 12);	    
                return _mm_or_si128( a, b );	
        case 5:				                
                b = _mm_srli_si128(b, 5);	    
                a = _mm_slli_si128(a, 11);	    
                return _mm_or_si128( a, b );	
        case 6:				                
                b = _mm_srli_si128(b, 6);	    
                 a = _mm_slli_si128(a, 10);	    
                return _mm_or_si128( a, b );	
        case 7:				                
                b = _mm_srli_si128(b, 7);	    
                a = _mm_slli_si128(a, 9);	    
                return _mm_or_si128( a, b );	
        case 8:				                
                b = _mm_srli_si128(b, 8);	    
                a = _mm_slli_si128(a, 8);	    
                return _mm_or_si128( a, b );	
        case 9:				                
                b = _mm_srli_si128(b, 9);	    
                a = _mm_slli_si128(a, 7);	    
                return _mm_or_si128( a, b );	
        case 10:				            
                b = _mm_srli_si128(b, 10);	    
                a = _mm_slli_si128(a,  6);	    
                return _mm_or_si128( a, b );	
        case 11:				            
                b = _mm_srli_si128(b, 11);      
                a = _mm_slli_si128(a,  5);      
                return _mm_or_si128( a, b );	
        case 12:				            
                b = _mm_srli_si128(b, 12);      
                a = _mm_slli_si128(a,  4);      
                return _mm_or_si128( a, b );	
        case 13:				            
                b = _mm_srli_si128(b, 13);      
                a = _mm_slli_si128(a,  3);      
                return _mm_or_si128( a, b );	
        case 14:				            
                b = _mm_srli_si128(b, 14);	    
                a = _mm_slli_si128(a,  2);      
                return _mm_or_si128( a, b );	
        case 15:				            
                b = _mm_srli_si128(b, 15);	    
                a = _mm_slli_si128(a,  1);	    
                return _mm_or_si128( a, b );    
        case 16:                            
                return a;                       
        case 17:                            
	            a    = _mm_slli_si128(a,  1);   
	            return _mm_srli_si128(a,  1);   
        case 18:                            
	            a    = _mm_slli_si128(a,  2);   
	            return _mm_srli_si128(a,  2);   
        case 19:                            
	            a    = _mm_slli_si128(a,  3);   
	            return _mm_srli_si128(a,  3);   
        case 20:                            
	            a    = _mm_slli_si128(a,  4);   
	            return _mm_srli_si128(a,  4);   
        case 21:                            
	            a    = _mm_slli_si128(a,  5);   
	            return _mm_srli_si128(a,  5);   
        case 22:                            
	            a    = _mm_slli_si128(a,  6);   
	            return _mm_srli_si128(a,  6);   
        case 23:                            
	            a    = _mm_slli_si128(a,  7);   
	            return _mm_srli_si128(a,  7);   
        case 24:                            
	            a    = _mm_slli_si128(a,  8);   
	            return _mm_srli_si128(a,  8);   
        case 25:                            
	            a    = _mm_slli_si128(a,  9);   
	            return _mm_srli_si128(a,  9);   
        case 26:                            
	            a    = _mm_slli_si128(a, 10);   
	            return _mm_srli_si128(a, 10);   
        case 27:                            
	            a    = _mm_slli_si128(a, 11);   
	            return _mm_srli_si128(a, 11);   
        case 28:                            
	            a    = _mm_slli_si128(a, 12);   
	            return _mm_srli_si128(a, 12);   
        case 29:                            
	            a    = _mm_slli_si128(a, 13);   
	            return _mm_srli_si128(a, 13);   
        case 30:                            
	            a    = _mm_slli_si128(a, 14);   
	            return _mm_srli_si128(a, 14);   
        case 31:                            
	            a    = _mm_slli_si128(a, 15);   
	            return _mm_srli_si128(a, 15);   
        default:                            
	            return _mm_setzero_si128(); 
	}
}

//---------------------------------------
//Insert
//---------------------------------------
/** \IMP{SSE2,_mm_insert_epi8, SSE4.1} */
SSP_FORCEINLINE __m128i ssp_insert_epi8_SSE2( __m128i a, int b, const int ndx )
{
    ssp_m128 Ahi, Alo;
    b = b & 0xFF;                                           /* Convert to 8-bit integer */
    Ahi.i = _mm_unpackhi_epi8( a, _mm_setzero_si128() );    /* Ahi = a_8[8:15]  Simulate 8bit integers as 16-bit integers */
    Alo.i = _mm_unpacklo_epi8( a, _mm_setzero_si128() );    /* Alo = a_8[0:7]   Simulate 8bit integers as 16-bit integers */

    /* Insert b as a 16-bit integer to upper or lower half of a */
    switch( ndx & 0xF )
    {
    case 0:  Alo.i = _mm_insert_epi16( Alo.i, b, 0 ); break;
    case 1:  Alo.i = _mm_insert_epi16( Alo.i, b, 1 ); break;
    case 2:  Alo.i = _mm_insert_epi16( Alo.i, b, 2 ); break;
    case 3:  Alo.i = _mm_insert_epi16( Alo.i, b, 3 ); break;
    case 4:  Alo.i = _mm_insert_epi16( Alo.i, b, 4 ); break;
    case 5:  Alo.i = _mm_insert_epi16( Alo.i, b, 5 ); break;
    case 6:  Alo.i = _mm_insert_epi16( Alo.i, b, 6 ); break;
    case 7:  Alo.i = _mm_insert_epi16( Alo.i, b, 7 ); break;
    case 8:  Ahi.i = _mm_insert_epi16( Ahi.i, b, 0 ); break;
    case 9:  Ahi.i = _mm_insert_epi16( Ahi.i, b, 1 ); break;
    case 10: Ahi.i = _mm_insert_epi16( Ahi.i, b, 2 ); break;
    case 11: Ahi.i = _mm_insert_epi16( Ahi.i, b, 3 ); break;
    case 12: Ahi.i = _mm_insert_epi16( Ahi.i, b, 4 ); break;
    case 13: Ahi.i = _mm_insert_epi16( Ahi.i, b, 5 ); break;
    case 14: Ahi.i = _mm_insert_epi16( Ahi.i, b, 6 ); break;
    default: Ahi.i = _mm_insert_epi16( Ahi.i, b, 7 );
    }
    return _mm_packus_epi16( Alo.i, Ahi.i ); // Pack the 16-bit integers to 8bit again.

    ///* Another implementation, but slower: */
    //ssp_m128 A, B, mask;
    //mask.i = _mm_setzero_si128();
    //mask.s8[ ndx & 0x0F ] = (ssp_s8)0xFF;
    //B.i    = _mm_set1_epi8( (ssp_s8)b );
    //A.i    = _mm_andnot_si128( mask.i, a );
    //mask.i = _mm_and_si128( mask.i, B.i );
    //A.i = _mm_or_si128( A.i, mask.i );
    //return A.i;
}
/** \IMP{SSE2,_mm_inserti_si64, SSE4a} */
SSP_FORCEINLINE __m128i ssp_inserti_si64_SSE2( __m128i a, __m128i b, int len, int ndx )
{
    const static __m128i MASK = SSP_CONST_SET_32I( 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF );

    int left = ndx + len;
    __m128i m;
    m = _mm_slli_epi64( MASK, 64-left );    // clear the mask to the left
    m = _mm_srli_epi64( m,    64-len  );    // clear the mask to the right
    m = _mm_slli_epi64( m,    ndx     );    // put the mask into the proper position
    b = _mm_slli_epi64( b,    ndx     );    // put the insert bits into the proper position

    a = ssp_logical_bitwise_select_SSE2( b, a, m );
    return a;
}


/** \IMP{SSE2,_mm_insert_si64, SSE4a} */
SSP_FORCEINLINE __m128i ssp_insert_si64_SSE2( __m128i a, __m128i b )
{
    ssp_u32 ndx, len;
    ssp_m128 B;
    B.i = b;

    ndx = (ssp_u32)((B.u64[1] & 0x3F00) >> 8);    // Mask length field.
    len = (ssp_u32)((B.u64[1] & 0x003F));         // Mask ndx field.

    a = ssp_inserti_si64_SSE2( a, b, len, ndx );
    return a;
}

//---------------------------------------
//Extract
//---------------------------------------

/** \IMP{SSE2,_mm_extract_epi8, SSE4.1} */
SSP_FORCEINLINE int ssp_extract_epi8_SSE2( __m128i a, const int ndx )                       
{
    ssp_m128 mask;
    switch( ndx & 0xF )
    {
    case 15:  a = _mm_srli_si128( a, 15 ); break;
    case 14:  a = _mm_srli_si128( a, 14 ); break;
    case 13:  a = _mm_srli_si128( a, 13 ); break;
    case 12:  a = _mm_srli_si128( a, 12 ); break;
    case 11:  a = _mm_srli_si128( a, 11 ); break;
    case 10:  a = _mm_srli_si128( a, 10 ); break;
    case 9:   a = _mm_srli_si128( a,  9 ); break;
    case 8:   a = _mm_srli_si128( a,  8 ); break;
    case 7:   a = _mm_srli_si128( a,  7 ); break;
    case 6:   a = _mm_srli_si128( a,  6 ); break;
    case 5:   a = _mm_srli_si128( a,  5 ); break;
    case 4:   a = _mm_srli_si128( a,  4 ); break;
    case 3:   a = _mm_srli_si128( a,  3 ); break;
    case 2:   a = _mm_srli_si128( a,  2 ); break;
    case 1:   a = _mm_srli_si128( a,  1 ); break;
    }

    mask.i = _mm_setr_epi8 ( -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ); 
    // mask = { 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,FF }
    mask.i = _mm_and_si128 ( mask.i, a   );
    return mask.s8[0];
}

/** \IMP{SSE2,_mm_extract_epi32, SSE4.1} */
SSP_FORCEINLINE int ssp_extract_epi32_SSE2( __m128i a, const int imm )                            
{
    ssp_m128 mask;
    switch( imm & 0x3 )
    {
    case 3:  a = _mm_srli_si128( a, 12 ); break;
    case 2:  a = _mm_srli_si128( a, 8  ); break;
    case 1:  a = _mm_srli_si128( a, 4  ); break;
    }

    mask.i = _mm_set_epi32 ( 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF );
    mask.i = _mm_and_si128 ( mask.i, a   );

    return mask.s32[0];
}

/** \IMP{SSE2,_mm_extract_ps, SSE4.1} */
SSP_FORCEINLINE int ssp_extract_ps_SSE2( __m128 a, const int ndx )                          
{
    ssp_m128 A;
    A.f = a;
    return ssp_extract_epi32_SSE2( A.i, ndx );
}

/** \IMP{SSE2,_mm_extract_epi64, SSE4.1} */
SSP_FORCEINLINE ssp_s64 ssp_extract_epi64_SSE2( __m128i a, const int ndx )                  
{
    ssp_m128 mask;
    switch( ndx & 0x1 )
    {
    case 1:  a = _mm_srli_si128( a, 8  ); break;
    }

    mask.i = _mm_set_epi32 ( 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF );
    mask.i = _mm_and_si128 ( mask.i, a   );

    return mask.s64[0];
}

/**  \IMP{SSE2,_mm_extracti_si64,SSE4a}
\n  NOTE: The upper 64-bits of the destination register are undefined.
*/
SSP_FORCEINLINE __m128i ssp_extracti_si64_SSE2( __m128i a, int len, int ndx )   
{
    int left = ndx + len;   
    a = _mm_slli_epi64( a, 64-left );    // clear the mask to the left
    a = _mm_srli_epi64( a, 64-len  );    // clear the mask to the right      
    return a;
}


/**  \IMP{SSE2,_mm_extract_si64,SSE4a} 
\n  NOTE: The upper 64-bit of the destination register are undefined.
*/
SSP_FORCEINLINE __m128i ssp_extract_si64_SSE2( __m128i a ,__m128i b )        
{
    ssp_u32 len, ndx;   
    ssp_m128 B;
    B.i = b;

    ndx = (ssp_u32)((B.u64[0] & 0x3F00) >> 8);    // Mask ndx field.
    len = (ssp_u32)((B.u64[0] & 0x003F));         // Mask len field.

    a = ssp_extracti_si64_SSE2( a, len, ndx );   
    return a;
}


/**  \IMP{SSE2,_mm_shuffle_epi8,SSSE3} */
SSP_FORCEINLINE __m128i ssp_shuffle_epi8_SSE2 (__m128i a, __m128i mask)
{  
    ssp_m128 A,B, MASK, maskZero;	
    A.i        = a;
    maskZero.i = ssp_logical_cmpgte_epi8( mask, _mm_setzero_si128()        );    
    MASK.i     = _mm_and_si128          ( mask, _mm_set1_epi8( (char)0x0F) );

    B.s8[ 0] = A.s8[ (MASK.s8[ 0]) ];
	B.s8[ 1] = A.s8[ (MASK.s8[ 1]) ];
	B.s8[ 2] = A.s8[ (MASK.s8[ 2]) ];
	B.s8[ 3] = A.s8[ (MASK.s8[ 3]) ];
	B.s8[ 4] = A.s8[ (MASK.s8[ 4]) ];
	B.s8[ 5] = A.s8[ (MASK.s8[ 5]) ];
	B.s8[ 6] = A.s8[ (MASK.s8[ 6]) ];
	B.s8[ 7] = A.s8[ (MASK.s8[ 7]) ];
	B.s8[ 8] = A.s8[ (MASK.s8[ 8]) ];
	B.s8[ 9] = A.s8[ (MASK.s8[ 9]) ];
	B.s8[10] = A.s8[ (MASK.s8[10]) ];
	B.s8[11] = A.s8[ (MASK.s8[11]) ];
	B.s8[12] = A.s8[ (MASK.s8[12]) ];
	B.s8[13] = A.s8[ (MASK.s8[13]) ];
	B.s8[14] = A.s8[ (MASK.s8[14]) ];
	B.s8[15] = A.s8[ (MASK.s8[15]) ];  

    B.i = _mm_and_si128( B.i, maskZero.i );
	return B.i;
}


/** \IMP{SSE2,_mm_sign_epi8,SSSE3} */
SSP_FORCEINLINE 
__m128i ssp_sign_epi8_SSE2 (__m128i a, __m128i b)
{
    __m128i ap, an, c, d, zero, one;

	zero=_mm_setzero_si128();
	//Great than zero part
	d  = _mm_cmpgt_epi8(b, zero);
	ap = _mm_and_si128(a, d);

	//Less than zero
	c   = _mm_cmplt_epi8(b, zero);
	one = _mm_set1_epi8(1);
	an  = _mm_and_si128(a, c);  //get the all number which needs to be negated 
	an  = _mm_xor_si128(an, c);
	one = _mm_and_si128(one, c);
	an  = _mm_add_epi8(an, one);

	return _mm_or_si128(an, ap);//_mm_add_epi8(an, ap);
}

/** \IMP{SSE2,_mm_sign_epi16,SSSE3} */
SSP_FORCEINLINE 
__m128i ssp_sign_epi16_SSE2 (__m128i a, __m128i b)
{
    __m128i c, d, zero;

	zero=_mm_setzero_si128();
	d   = _mm_cmpgt_epi16(b, zero);
	c   = _mm_cmplt_epi16(b, zero);
	d   = _mm_srli_epi16(d, 15);
	c   = _mm_or_si128(c, d);
	a   = _mm_mullo_epi16(a, c);

	//The following method has same performance
	//zero=_mm_setzero_si128();
	//d   = _mm_cmpgt_epi16(b, zero);
	//c   = _mm_cmplt_epi16(b, zero);
	//one = _mm_set1_epi16(1);
	//d   = _mm_and_si128(d, one);
	//c   = _mm_add_epi16(c, d);
	//a   = _mm_mullo_epi16(a, c);

	return a;
}

/** \IMP{SSE2,_mm_sign_epi32,SSSE3} */
SSP_FORCEINLINE 
__m128i ssp_sign_epi32_SSE2 (__m128i a, __m128i b)
{
    __m128i ap, an, c, d, zero, one;

	zero=_mm_setzero_si128();
	//Great than zero part
	d  = _mm_cmpgt_epi32(b, zero);
	ap = _mm_and_si128(a, d);

	//Less than zero
	c   = _mm_cmplt_epi32(b, zero);
	one = _mm_set1_epi32(1);
	an  = _mm_and_si128(a, c);  //get the all number which needs to be negated 
	an  = _mm_xor_si128(an, c);
	one = _mm_and_si128(one, c);
	an  = _mm_add_epi8(an, one);

	return _mm_or_si128(an, ap);
}

//---------------------------------------
// Test
//---------------------------------------
/** \IMP{SSE2,_mm_testc_si128, SSE4.1} */
SSP_FORCEINLINE int ssp_testc_si128_SSE2( __m128i a, __m128i b)                              
{
    a = _mm_xor_si128( a, b );
    return ssp_testz_si128_SSE2( a, a );
}

/** \IMP{SSE2,_mm_testz_si128, SSE4.1} */
SSP_FORCEINLINE 
int ssp_testz_si128_SSE2( __m128i a, __m128i b)   // This is much faster in 64 bit                           
{
    ssp_m128 t;
    t.i = _mm_and_si128  ( a, b );   
    t.i = _mm_packs_epi32( t.i, _mm_setzero_si128() );   
    return t.u64[0] == 0;
}

/** \IMP{SSE2,_mm_testnzc_si128, SSE4.1} */
SSP_FORCEINLINE 
int ssp_testnzc_si128_SSE2( __m128i a, __m128i b)                            
{
    ssp_m128 zf, cf;    

    zf.i = _mm_and_si128  ( a, b );   
    zf.i = _mm_packs_epi32( zf.i, _mm_setzero_si128() ); 
 
    cf.i = _mm_andnot_si128( a, b );
    cf.i = _mm_packs_epi32( cf.i, _mm_setzero_si128() );  

    return ( !(zf.u64[0] == 0) && !(cf.u64[0] == 0));
}


//---------------------------------------
// Move
//---------------------------------------
/** \IMP{SSE2,_mm_movehdup_ps, SSE3} */
SSP_FORCEINLINE __m128 ssp_movehdup_ps_SSE2(__m128 a)                                   
{
    ssp_m128 A;
    A.f = a;
    A.i = _mm_shuffle_epi32( A.i, _MM_SHUFFLE( 3, 3, 1, 1) );
    return A.f;
}

/** \IMP{SSE2,_mm_moveldup_ps, SSE3} */
SSP_FORCEINLINE __m128 ssp_moveldup_ps_SSE2(__m128 a)                                   
{
    ssp_m128 A;
    A.f = a;
    A.i = _mm_shuffle_epi32( A.i, _MM_SHUFFLE( 2, 2, 0, 0) );
    return A.f;
}

/** \IMP{SSE2,_mm_movedup_pd, SSE3} */
SSP_FORCEINLINE __m128d ssp_movedup_pd_SSE2(__m128d a)                                  
{
    ssp_m128 A;
    A.d = a;
    return _mm_set_pd( A.f64[0], A.f64[0] );
}

//--------------------------------------
// Packed Shift Logical (bytes, words, dwords, qwords)
//--------------------------------------

/** \SSE5{SSE2,ssp_shl_epi16,pshlw } */ 
SSP_FORCEINLINE __m128i ssp_shl_epi16_SSE2(__m128i a, __m128i b)
{
    __m128i v1, v2, mask, mask2, b1, b2;
    b1 = ssp_abs_epi8_SSE2( b );
    mask = _mm_set_epi16( 0, 0, 0, 0, 0, 0, 0, -1 );
    mask2 = _mm_srli_epi16( mask, 12 );

    b2 = _mm_and_si128( b1, mask2 );
    v1 = _mm_and_si128( _mm_srl_epi16( a, b2), mask ); // negative shift
    v2 = _mm_and_si128( _mm_sll_epi16( a, _mm_and_si128( b2, mask2 ) ), mask ); // positive shift
    mask = _mm_slli_si128( mask, 2 );
    b1 = _mm_srli_si128( b1, 2 );

    b2 = _mm_and_si128( b1, mask2 );
    v1 = _mm_or_si128( v1, _mm_and_si128( _mm_srl_epi16( a, b2 ), mask ) ); // negative shift
    v2 = _mm_or_si128( v2, _mm_and_si128( _mm_sll_epi16( a, b2 ), mask ) ); // positive shift
    mask = _mm_slli_si128( mask, 2 );
    b1 = _mm_srli_si128( b1, 2 );

    b2 = _mm_and_si128( b1, mask2 );
    v1 = _mm_or_si128( v1, _mm_and_si128( _mm_srl_epi16( a, b2 ), mask ) ); // negative shift
    v2 = _mm_or_si128( v2, _mm_and_si128( _mm_sll_epi16( a, b2 ), mask ) ); // positive shift
    mask = _mm_slli_si128( mask, 2 );
    b1 = _mm_srli_si128( b1, 2 );

    b2 = _mm_and_si128( b1, mask2 );
    v1 = _mm_or_si128( v1, _mm_and_si128( _mm_srl_epi16( a, b2 ), mask ) ); // negative shift
    v2 = _mm_or_si128( v2, _mm_and_si128( _mm_sll_epi16( a, b2 ), mask ) ); // positive shift
    mask = _mm_slli_si128( mask, 2 );
    b1 = _mm_srli_si128( b1, 2 );

    b2 = _mm_and_si128( b1, mask2 );
    v1 = _mm_or_si128( v1, _mm_and_si128( _mm_srl_epi16( a, b2 ), mask ) ); // negative shift
    v2 = _mm_or_si128( v2, _mm_and_si128( _mm_sll_epi16( a, b2 ), mask ) ); // positive shift
    mask = _mm_slli_si128( mask, 2 );
    b1 = _mm_srli_si128( b1, 2 );

    b2 = _mm_and_si128( b1, mask2 );
    v1 = _mm_or_si128( v1, _mm_and_si128( _mm_srl_epi16( a, b2 ), mask ) ); // negative shift
    v2 = _mm_or_si128( v2, _mm_and_si128( _mm_sll_epi16( a, b2 ), mask ) ); // positive shift
    mask = _mm_slli_si128( mask, 2 );
    b1 = _mm_srli_si128( b1, 2 );

    b2 = _mm_and_si128( b1, mask2 );
    v1 = _mm_or_si128( v1, _mm_and_si128( _mm_srl_epi16( a, b2 ), mask ) ); // negative shift
    v2 = _mm_or_si128( v2, _mm_and_si128( _mm_sll_epi16( a, b2 ), mask ) ); // positive shift
    mask = _mm_slli_si128( mask, 2 );
    b1 = _mm_srli_si128( b1, 2 );

    b2 = _mm_and_si128( b1, mask2 );
    v1 = _mm_or_si128( v1, _mm_and_si128( _mm_srl_epi16( a, b2 ), mask ) ); // negative shift
    v2 = _mm_or_si128( v2, _mm_and_si128( _mm_sll_epi16( a, b2 ), mask ) ); // positive shift

    mask = _mm_setzero_si128();
    mask = _mm_cmpgt_epi8( mask, b ); // set mask to 0xFF for all negative shift counts in b
    mask2 = _mm_slli_epi16( mask, 8 );
    mask = _mm_or_si128( mask, mask2 );
    v1 = _mm_and_si128( v1, mask );
    mask = _mm_andnot_si128( mask, v2 );
    v1 = _mm_or_si128( v1, mask );
    return v1;
}

/** \SSE5{SSE2,ssp_sha_epi16,pshaw } */ 
SSP_FORCEINLINE __m128i ssp_sha_epi16_SSE2(__m128i a, __m128i b)
{
    __m128i v1, v2, mask, mask2, b1, b2;
    b1 = ssp_abs_epi8_SSE2( b );
    mask = _mm_set_epi16( 0, 0, 0, 0, 0, 0, 0, -1 );
    mask2 = _mm_srli_epi16( mask, 12 );

    b2 = _mm_and_si128( b1, mask2 );
    v1 = _mm_and_si128( _mm_sra_epi16( a, b2), mask ); // negative shift
    v2 = _mm_and_si128( _mm_sll_epi16( a, _mm_and_si128( b2, mask2 ) ), mask ); // positive shift
    mask = _mm_slli_si128( mask, 2 );
    b1 = _mm_srli_si128( b1, 2 );

    b2 = _mm_and_si128( b1, mask2 );
    v1 = _mm_or_si128( v1, _mm_and_si128( _mm_sra_epi16( a, b2 ), mask ) ); // negative shift
    v2 = _mm_or_si128( v2, _mm_and_si128( _mm_sll_epi16( a, b2 ), mask ) ); // positive shift
    mask = _mm_slli_si128( mask, 2 );
    b1 = _mm_srli_si128( b1, 2 );

    b2 = _mm_and_si128( b1, mask2 );
    v1 = _mm_or_si128( v1, _mm_and_si128( _mm_sra_epi16( a, b2 ), mask ) ); // negative shift
    v2 = _mm_or_si128( v2, _mm_and_si128( _mm_sll_epi16( a, b2 ), mask ) ); // positive shift
    mask = _mm_slli_si128( mask, 2 );
    b1 = _mm_srli_si128( b1, 2 );

    b2 = _mm_and_si128( b1, mask2 );
    v1 = _mm_or_si128( v1, _mm_and_si128( _mm_sra_epi16( a, b2 ), mask ) ); // negative shift
    v2 = _mm_or_si128( v2, _mm_and_si128( _mm_sll_epi16( a, b2 ), mask ) ); // positive shift
    mask = _mm_slli_si128( mask, 2 );
    b1 = _mm_srli_si128( b1, 2 );

    b2 = _mm_and_si128( b1, mask2 );
    v1 = _mm_or_si128( v1, _mm_and_si128( _mm_sra_epi16( a, b2 ), mask ) ); // negative shift
    v2 = _mm_or_si128( v2, _mm_and_si128( _mm_sll_epi16( a, b2 ), mask ) ); // positive shift
    mask = _mm_slli_si128( mask, 2 );
    b1 = _mm_srli_si128( b1, 2 );

    b2 = _mm_and_si128( b1, mask2 );
    v1 = _mm_or_si128( v1, _mm_and_si128( _mm_sra_epi16( a, b2 ), mask ) ); // negative shift
    v2 = _mm_or_si128( v2, _mm_and_si128( _mm_sll_epi16( a, b2 ), mask ) ); // positive shift
    mask = _mm_slli_si128( mask, 2 );
    b1 = _mm_srli_si128( b1, 2 );

    b2 = _mm_and_si128( b1, mask2 );
    v1 = _mm_or_si128( v1, _mm_and_si128( _mm_sra_epi16( a, b2 ), mask ) ); // negative shift
    v2 = _mm_or_si128( v2, _mm_and_si128( _mm_sll_epi16( a, b2 ), mask ) ); // positive shift
    mask = _mm_slli_si128( mask, 2 );
    b1 = _mm_srli_si128( b1, 2 );

    b2 = _mm_and_si128( b1, mask2 );
    v1 = _mm_or_si128( v1, _mm_and_si128( _mm_sra_epi16( a, b2 ), mask ) ); // negative shift
    v2 = _mm_or_si128( v2, _mm_and_si128( _mm_sll_epi16( a, b2 ), mask ) ); // positive shift

    mask = _mm_setzero_si128();
    mask = _mm_cmpgt_epi8( mask, b ); // set mask to 0xFF for all negative shift counts in b
    mask2 = _mm_slli_epi16( mask, 8 );
    mask = _mm_or_si128( mask, mask2 );
    v1 = _mm_and_si128( v1, mask );
    mask = _mm_andnot_si128( mask, v2 );
    v1 = _mm_or_si128( v1, mask );
    return v1;
}

/** @} 
 *  @}
 */


#endif // __SSEPLUS_EMULATION_SSE2_H__
