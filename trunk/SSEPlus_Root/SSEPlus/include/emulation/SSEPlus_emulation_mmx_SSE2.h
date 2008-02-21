//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __SSEPLUS_EMULATION_MMX_SSE2_H__
#define __SSEPLUS_EMULATION_MMX_SSE2_H__

#include "../SSEPlus_SSE2.h"
#include "../native/SSEPlus_native_SSE2.h"
#include "../logical/SSEPlus_logical_SSE2.h"
#include "../convert/SSEPlus_convert_SSE2.h"
#include "../convert/SSEPlus_convert_mmx_SSE2.h"
#include "../arithmetic/SSEPlus_arithmetic_SSE2.h"

/** @defgroup SSE2 SSE2 Optimized
 *  @{
 *  @name Emulated Instructions on MMX registers
 *  @{ */


/** \IMP{SSE2,_mm_abs_pi8,SSSE3} */
SSEPLUS_FORCEINLINE
__m64 ssp_abs_pi8_SSE2 ( __m64 a )
{
    ssp_m128 A;
    A.i      = _mm_movpi64_epi64( a );   
    A.i      = ssp_abs_epi8_SSE2( A.i );
    A.m64[0] = _mm_movepi64_pi64( A.i );
    return A.m64[0]; 
}

/** \IMP{SSE2,_mm_abs_pi16,SSSE3} */
SSEPLUS_FORCEINLINE
__m64 ssp_abs_pi16_SSE2 (__m64 a)
{
    ssp_m128 A;
    A.i      = _mm_movpi64_epi64( a );   
    A.i      = ssp_abs_epi16_SSE2( A.i );
    A.m64[0] = _mm_movepi64_pi64( A.i );
    return A.m64[0];    
}

/** \IMP{SSE2,_mm_abs_pi32,SSSE3} */
//This SSE2 implementation is slower than reference
//Because we extend the data to 128 bit and cannot use MMX instruction
SSEPLUS_FORCEINLINE
__m64 ssp_abs_pi32_SSE2 (__m64 a)
{
    ssp_m128 A;
    A.i      = _mm_movpi64_epi64( a );   
    A.i      = ssp_abs_epi32_SSE2( A.i );
    A.m64[0] = _mm_movepi64_pi64( A.i );
    return A.m64[0];   
}

/** \IMP{SSE2,_mm_hadd_pi16, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSEPLUS_FORCEINLINE __m64 ssp_hadd_pi16_SSE2 ( __m64 a, __m64 b )                        
{
    ssp_m128 A,B;
    A.f = ssp_convert_load_m64_m64( a, b );             // Load a and b side by side in 128 bit register                 

    B.i = _mm_slli_epi32( A.i, 16  );                   // Offset to the left by one 16 bit value
    A.i = _mm_add_epi16 ( A.i, B.i );                   // 16 bit add   
    A.i = _mm_srai_epi32( A.i, 16 );                    // Shift back, fix the sign

    A.i = _mm_packs_epi32( A.i, _mm_setzero_si128() );  // Pack into lower 16 bytes
    A.m64[0] = _mm_movepi64_pi64( A.i );                // Return the result
    return A.m64[0];   
}


/** \IMP{SSE2,_mm_hadds_pi16, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSEPLUS_FORCEINLINE __m64 ssp_hadds_pi16_SSE2 ( __m64 a, __m64 b )                        
{
    ssp_m128 A,B;
    A.f = ssp_convert_load_m64_m64( a, b );             // Load a and b side by side in 128 bit register                 

    B.i = _mm_slli_epi32( A.i, 16  );                   // Offset to the left by one 16 bit value
    A.i = _mm_adds_epi16 ( A.i, B.i );                   // 16 bit add   
    A.i = _mm_srai_epi32( A.i, 16 );                    // Shift back, fix the sign

    A.i = _mm_packs_epi32( A.i, _mm_setzero_si128() );  // Pack into lower 16 bytes
    A.m64[0] = _mm_movepi64_pi64( A.i );                // Return the result
    return A.m64[0];   
}


/** \IMP{SSE2,_mm_hsub_pi16, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSEPLUS_FORCEINLINE __m64 ssp_hsub_pi16_SSE2 ( __m64 a, __m64 b )                        
{
    ssp_m128 A,B;
    A.f = ssp_convert_load_m64_m64( a, b );             // Load a and b side by side in 128 bit register                 

    B.i = _mm_slli_epi32( A.i, 16  );                   // Offset to the left by one 16 bit value
    A.i = _mm_sub_epi16 ( B.i, A.i );                   // 16 bit sub   
    A.i = _mm_srai_epi32( A.i, 16 );                    // Shift back, fix the sign

    A.i = _mm_packs_epi32( A.i, _mm_setzero_si128() );  // Pack into lower 16 bytes
    A.m64[0] = _mm_movepi64_pi64( A.i );                // Return the result
    return A.m64[0];   
}


/** \IMP{SSE2,_mm_hsubs_pi16, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSEPLUS_FORCEINLINE __m64 ssp_hsubs_pi16_SSE2 ( __m64 a, __m64 b )                        
{
    ssp_m128 A,B;
    A.f = ssp_convert_load_m64_m64( a, b );             // Load a and b side by side in 128 bit register                 

    B.i = _mm_slli_epi32( A.i, 16  );                   // Offset to the left by one 16 bit value
    A.i = _mm_subs_epi16 ( B.i, A.i );                   // 16 bit sub   
    A.i = _mm_srai_epi32( A.i, 16 );                    // Shift back, fix the sign

    A.i = _mm_packs_epi32( A.i, _mm_setzero_si128() );  // Pack into lower 16 bytes
    A.m64[0] = _mm_movepi64_pi64( A.i );                // Return the result
    return A.m64[0];   
}

/** \IMP{SSE2,_mm_add_pi32, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSEPLUS_FORCEINLINE __m64 ssp_hadd_pi32_SSE2 ( __m64 a, __m64 b )                        
{ 
    ssp_m128 A,B;
    A.f = ssp_convert_load_m64_m64( a, b );             // Load a and b side by side in 128 bit register  

    B.i = _mm_slli_epi64( A.i, 32  );                   // Offset to the left by one 32 bit value
    A.i = _mm_add_epi32 ( A.i, B.i );                   // 32 bit add  
    A.i = _mm_shuffle_epi32( A.i, _MM_SHUFFLE(0,0,3,1) );
    A.m64[0] = _mm_movepi64_pi64( A.i );                // Return the result
    return A.m64[0];    
}

/** \IMP{SSE2,_mm_sub_pi32, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSEPLUS_FORCEINLINE __m64 ssp_hsub_pi32_SSE2 ( __m64 a, __m64 b )                        
{ 
    ssp_m128 A,B;
    A.f = ssp_convert_load_m64_m64( a, b );             // Load a and b side by side in 128 bit register  

    B.i = _mm_slli_epi64( A.i, 32  );                   // Offset to the left by one 32 bit value
    A.i = _mm_sub_epi32 ( B.i, A.i );                   // 32 bit sub  
    A.i = _mm_shuffle_epi32( A.i, _MM_SHUFFLE(0,0,3,1) );
    A.m64[0] = _mm_movepi64_pi64( A.i );                // Return the result
    return A.m64[0];    
}



//__m64 _mm_mulhrs_epi16( __m64 a,  __m64 b);
/** \IMP{SSE2,_mm_mulhrs_pi16, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSEPLUS_FORCEINLINE __m64 ssp_mulhrs_pi16_SSE2( __m64 a, __m64 b )
{
    ssp_m128 A,B;
    A.i = _mm_movpi64_epi64( a );
    B.i = _mm_movpi64_epi64( b );

    A.i = ssp_mulhrs_epi16_SSE2( A.i, B.i );

    A.m64[0] = _mm_movepi64_pi64( A.i );                // Return the result
    return A.m64[0];    
}


/** \IMP{SSE2,_mm_maddubs_pi16, SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
 */
//__m64 _mm_maddubs_pi16( __m64 a,  __m64 b); [SSSE3]
SSEPLUS_FORCEINLINE __m64 ssp_maddubs_pi16_SSE2( __m64 a,  __m64 b)
{
    ssp_m128 A,B;
    A.i = _mm_movpi64_epi64( a );
    B.i = _mm_movpi64_epi64( b );

    A.i = ssp_maddubs_epi16_SSE2( A.i, B.i );

    A.m64[0] = _mm_movepi64_pi64( A.i );                // Return the result
    return A.m64[0];      
}

/**  \IMP{Reference,_mm_alignr_pi8,SSSE3} */
SSEPLUS_FORCEINLINE
__m64 ssp_alignr_pi8_SSE2 (__m64 a, __m64 b, const int ralign)
{
	ssp_m128 A;
	A.m64[0]=b;
	A.m64[1]=a;
	if (ralign < 0)  return b; //only shift to right, no negative

	switch (ralign) {
		case 0:  return b;                          
        case 1:  A.i = _mm_srli_si128(A.i, 1);  break;
        case 2:  A.i = _mm_srli_si128(A.i, 2);  break;
        case 3:  A.i = _mm_srli_si128(A.i, 3);  break;
        case 4:  A.i = _mm_srli_si128(A.i, 4);  break;
        case 5:  A.i = _mm_srli_si128(A.i, 5);  break;
        case 6:  A.i = _mm_srli_si128(A.i, 6);  break;
        case 7:  A.i = _mm_srli_si128(A.i, 7);  break;
        case 8:  A.i = _mm_srli_si128(A.i, 8);  break;
        case 9:  A.i = _mm_srli_si128(A.i, 9);  break;
        case 10: A.i = _mm_srli_si128(A.i, 10); break;
        case 11: A.i = _mm_srli_si128(A.i, 11); break;
        case 12: A.i = _mm_srli_si128(A.i, 12); break;
        case 13: A.i = _mm_srli_si128(A.i, 13); break;
        case 14: A.i = _mm_srli_si128(A.i, 14); break;
        case 15: A.i = _mm_srli_si128(A.i, 15); break; 	                       
        default: A.i = _mm_setzero_si128();     break;        
	}
    return A.m64[0];    
}           

/**  \IMP{SSE2,_mm_shuffle_pi8,SSSE3}
\n \b NOTE: The user must call _mm_empty() after a call to this function.
*/
SSEPLUS_FORCEINLINE __m64 ssp_shuffle_pi8_SSE2 (__m64 a, __m64 mask)
{
    ssp_m128 A,MASK;
    A.i    = _mm_movpi64_epi64( a    );
    MASK.i = _mm_movpi64_epi64( mask );

    A.i = ssp_shuffle_epi8_SSE2( A.i, MASK.i );    

    A.m64[0] = _mm_movepi64_pi64( A.i );                // Return the result
    return A.m64[0];      
}

/** \IMP{SSE2,_mm_sign_pi8,SSSE3} */
SSEPLUS_FORCEINLINE 
__m64 ssp_sign_pi8_SSE2 (__m64 a, __m64 b)
{
    __m128i ap, an, c, d, zero, one;
	ssp_m128 A, B;
	A.m64[0] = a;
	B.m64[0] = b;

	zero=_mm_setzero_si128();
	//Great than zero part
	d  = _mm_cmpgt_epi8(B.i, zero);
	ap = _mm_and_si128(A.i, d);

	//Less than zero
	c   = _mm_cmplt_epi8(B.i, zero);
	one = _mm_set1_epi8(1);
	an  = _mm_and_si128(A.i, c);  //get the all number which needs to be negated 
	an  = _mm_xor_si128(an, c);
	one = _mm_and_si128(one, c);
	an  = _mm_add_epi8(an, one);
	A.i = _mm_or_si128(an, ap);

	return A.m64[0];
}

/** \IMP{SSE2,_mm_sign_pi16,SSSE3} */
SSEPLUS_FORCEINLINE 
__m64 ssp_sign_pi16_SSE2 (__m64 a, __m64 b)
{
    __m128i c, d, zero, one;
	ssp_m128 A, B;
	A.m64[0] = a;
	B.m64[0] = b;

	zero=_mm_setzero_si128();
	d   = _mm_cmpgt_epi16(B.i, zero);
	c   = _mm_cmplt_epi16(B.i, zero);
	one = _mm_set1_epi16(1);
	d   = _mm_and_si128(d, one);
	c   = _mm_or_si128(c, d);
	A.i = _mm_mullo_epi16(A.i, c);

	return A.m64[0];
}

/** \IMP{SSE2,_mm_sign_pi32,SSSE3} */
SSEPLUS_FORCEINLINE 
__m64 ssp_sign_pi32_SSE2 (__m64 a, __m64 b)
{
    __m128i ap, an, c, d, zero, one;
	ssp_m128 A, B;
	A.m64[0] = a;
	B.m64[0] = b;

	zero=_mm_setzero_si128();
	//Great than zero part
	d  = _mm_cmpgt_epi32(B.i, zero);
	ap = _mm_and_si128(A.i, d);

	//Less than zero
	c   = _mm_cmplt_epi32(B.i, zero);
	one = _mm_set1_epi32(1);
	an  = _mm_and_si128(A.i, c);  //get the all number which needs to be negated 
	an  = _mm_xor_si128(an, c);
	one = _mm_and_si128(one, c);
	an  = _mm_add_epi8(an, one);
	A.i = _mm_or_si128(an, ap);

	return A.m64[0];
}

//@}
//@}


#endif // __SSEPLUS_EMULATION_MMX_SSE2_H__
