//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//

#include "../include/test.h" 
#include "../include/csvTable.h" 
#include "../../../SSEPlus/include/SSEPlus.h"

// Decoder Table
// 0 - REF      1 - SSE
// 2 - SSE2     3 - SSE3     
// 4 - SSSE3    5 - SSE4a    
// 6 - SSE4.1   7 - SSE4.2
// 8 - SSE5
//                                         0:REF        1:SSE        2:SSE2       3:SSE3       4:SSSE3      5:SSE4a      6:SSE4.1     7:SSE4.2     8:SSE5     
#define TEST_0(   f,t,...)Test<__VA_ARGS__,1,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   enum_##t >( csv[#f], #f, 
#define TEST_1(   f,t,...)Test<__VA_ARGS__,0,f##_SSE,   1,f##_SSE,   0,f##_SSE ,  0,f##_SSE2,  0,f##_SSE2,  0,f##_SSE2,  0,f##_SSE2,  0,f##_SSE2,  0,f##_SSE2,  enum_##t >( csv[#f], #f, 
#define TEST_2(   f,t,...)Test<__VA_ARGS__,0,f##_SSE2,  0,f##_SSE2,  1,f##_SSE2,  0,f##_SSE2,  0,f##_SSE2,  0,f##_SSE2,  0,f##_SSE2,  0,f##_SSE2,  0,f##_SSE2,  enum_##t >( csv[#f], #f, 
#define TEST_3(   f,t,...)Test<__VA_ARGS__,0,f##_SSE3,  0,f##_SSE3,  0,f##_SSE3,  1,f##_SSE3,  0,f##_SSE3,  0,f##_SSE3,  0,f##_SSE3,  0,f##_SSE3,  0,f##_SSE3,  enum_##t >( csv[#f], #f, 
#define TEST_4(   f,t,...)Test<__VA_ARGS__,0,f##_SSSE3, 0,f##_SSSE3, 0,f##_SSSE3, 0,f##_SSSE3, 1,f##_SSSE3, 0,f##_SSSE3, 0,f##_SSSE3, 0,f##_SSSE3, 0,f##_SSSE3, enum_##t >( csv[#f], #f,
#define TEST_5(   f,t,...)Test<__VA_ARGS__,0,f##_SSE4A, 0,f##_SSE4A, 0,f##_SSE4A, 0,f##_SSE4A, 0,f##_SSE4A, 1,f##_SSE4A, 0,f##_SSE4A, 0,f##_SSE4A, 0,f##_SSE4A, enum_##t >( csv[#f], #f, 
#define TEST_6(   f,t,...)Test<__VA_ARGS__,0,f##_SSE4_1,0,f##_SSE4_1,0,f##_SSE4_1,0,f##_SSE4_1,0,f##_SSE4_1,0,f##_SSE4_1,1,f##_SSE4_1,0,f##_SSE4_1,0,f##_SSE4_1,enum_##t >( csv[#f], #f, 
#define TEST_7(   f,t,...)Test<__VA_ARGS__,0,f##_SSE4_2,0,f##_SSE4_2,0,f##_SSE4_2,0,f##_SSE4_2,0,f##_SSE4_2,0,f##_SSE4_2,0,f##_SSE4_2,1,f##_SSE4_2,0,f##_SSE4_2,enum_##t >( csv[#f], #f, 
#define TEST_8(   f,t,...)Test<__VA_ARGS__,0,f##_SSE5  ,0,f##_SSE5  ,0,f##_SSE5  ,0,f##_SSE5  ,0,f##_SSE5  ,0,f##_SSE5  ,0,f##_SSE5  ,0,f##_SSE5  ,1,f##_SSE5  ,enum_##t >( csv[#f], #f, 

#define TEST_02(  f,t,...)Test<__VA_ARGS__,1,f##_REF,   0,f##_REF,   1,f##_SSE2,  0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   enum_##t >( csv[#f], #f, 
#define TEST_03(  f,t,...)Test<__VA_ARGS__,1,f##_REF,   0,f##_REF,   0,f##_REF,   1,f##_SSE3,  0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   enum_##t >( csv[#f], #f, 
#define TEST_04(  f,t,...)Test<__VA_ARGS__,1,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   1,f##_SSSE3, 0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   enum_##t >( csv[#f], #f, 
#define TEST_05(  f,t,...)Test<__VA_ARGS__,1,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF  , 1,f##_SSE4A, 0,f##_REF,   0,f##_REF,   0,f##_REF,   enum_##t >( csv[#f], #f, 
#define TEST_06(  f,t,...)Test<__VA_ARGS__,1,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   1,f##_SSE4_1,0,f##_REF,   0,f##_REF,   enum_##t >( csv[#f], #f, 
#define TEST_023( f,t,...)Test<__VA_ARGS__,1,f##_REF,   0,f##_REF,   1,f##_SSE2,  1,f##_SSE3,  0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   enum_##t >( csv[#f], #f, 
#define TEST_024( f,t,...)Test<__VA_ARGS__,1,f##_REF,   0,f##_REF,   1,f##_SSE2,  0,f##_REF,   1,f##_SSSE3, 0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   enum_##t >( csv[#f], #f, 
#define TEST_025( f,t,...)Test<__VA_ARGS__,1,f##_REF,   0,f##_REF,   1,f##_SSE2,  0,f##_REF,   0,f##_REF,   1,f##_SSE4A, 0,f##_REF,   0,f##_REF,   0,f##_REF,   enum_##t >( csv[#f], #f, 
#define TEST_026( f,t,...)Test<__VA_ARGS__,1,f##_REF,   0,f##_REF,   1,f##_SSE2,  0,f##_REF,   0,f##_REF,   0,f##_REF,   1,f##_SSE4_1,0,f##_REF,   0,f##_REF,   enum_##t >( csv[#f], #f, 
#define TEST_028( f,t,...)Test<__VA_ARGS__,1,f##_REF,   0,f##_REF,   1,f##_SSE2,  0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   0,f##_REF,   1,f##_SSE5,  enum_##t >( csv[#f], #f, 
#define TEST_0236(f,t,...)Test<__VA_ARGS__,1,f##_REF,   0,f##_REF,   1,f##_SSE2,  1,f##_SSE3,  0,f##_REF,   0,f##_REF,   1,f##_SSE4_1,0,f##_REF,   0,f##_REF,   enum_##t >( csv[#f], #f, 

// This code allows the unit test project to compile when the compiler doesn't support higher level SSE instructions
#ifndef SSP_COMPILER_SUPPORTS_SSSE3
#undef  TEST_04
#define TEST_04  TEST_0
#undef  TEST_024
#define TEST_024 TEST_02
#endif 

#ifndef SSP_COMPILER_SUPPORTS_SSE4a
#undef  TEST_05
#define TEST_05  TEST_0
#undef  TEST_025
#define TEST_025 TEST_02
#endif 

#ifndef SSP_COMPILER_SUPPORTS_SSE41
#undef  TEST_06
#define TEST_06   TEST_0
#undef  TEST_026
#define TEST_026  TEST_02
#undef  TEST_0236
#define TEST_0236 TEST_023
#endif 

#ifndef SSP_COMPILER_SUPPORTS_SSE5
#undef  TEST_028
#define TEST_028   TEST_02
#endif 

#ifndef SSP_COMPILER_SUPPORTS_SSE5
#undef  TEST_08
#define TEST_08   TEST_0
#endif 


#define MIN_INT     (-2147483647 - 1) /* minimum (signed) int value */

void SSE3_Tests( CSVTable & csv ) 
{
    TEST_023( ssp_addsub_pd, ssp_f64, __m128d,__m128d,__m128d )     vF64( 2,-1 ),  // Expected
        vF64( 1, 1 ),  // Input A
        vF64( 1, 2 )); // Input B  


    TEST_023( ssp_addsub_ps, ssp_f32, __m128,__m128,__m128 )        vF32( 4, -1,  2,  1 ),
        vF32( 1,  1,  1,  1 ), 
        vF32( 3,  2,  1,  0 ));  

    TEST_023( ssp_hadd_pd, ssp_f64, __m128d, __m128d, __m128d )     vF64( 9,  5 ),
        vF64( 3,  2  ), 
        vF64( 5,  4  )); 

    TEST_023( ssp_hadd_ps, ssp_f32, __m128 , __m128 , __m128 )      vF32( 4,  12,  5, 1 ),
        vF32( 3,  2,  1,  0 ), 
        vF32( 1,  3,  5,  7 ));  

    TEST_023( ssp_hsub_pd, ssp_f64, __m128d, __m128d, __m128d )     vF64( 2, -1 ),
        vF64( 3,  2 ), 
        vF64( 1,  3 ));  

    TEST_023( ssp_hsub_ps, ssp_f32, __m128 , __m128 , __m128  )     vF32( 2,  2,  -1, -1 ),
        vF32( 3,  2,  1,  0 ), 
        vF32( 1,  3,  5,  7 )); 
    { __m128i x = vS32( 3, 2, 1, 0 ); 
    TEST_03( ssp_lddqu_si128, ssp_f32, __m128i, const __m128i * )   vS32( 3,2,1,0),&x ); }

    {double d = 1.34;
    TEST_03( ssp_loaddup_pd, ssp_f32, __m128d, const double * )     vF64( 1.34, 1.34 ), &d ); }

    TEST_023( ssp_movedup_pd, ssp_f64, __m128d, __m128d )            vF64( 0.8, 0.8 ),
        vF64( 1.8, 0.8 )); 

    TEST_023( ssp_movehdup_ps, ssp_f32, __m128, __m128  )            vF32( 3.2f,  3.2f,  1.9f, 1.9f ),
        vF32( 3.2f,  2.3f,  1.9f,  0.9f ));  

    TEST_023( ssp_moveldup_ps, ssp_f32, __m128, __m128 )             vF32( 2.5f,  2.5f,  0.5f, 0.5f ),
        vF32( 3.5f,  2.5f,  1.5f, 0.5f ));     
}

void SSSE3_Tests( CSVTable & csv )
{
    TEST_024( ssp_abs_epi16, ssp_s16, __m128i, __m128i)  
        vS16(1,  22,  127, 0,  1234, 23456,  32767, -32768), 
        vS16(1, -22, -127, 0, -1234, 23456, -32767, -32768));

    TEST_024( ssp_abs_epi32, ssp_s32, __m128i, __m128i)  
        vS32(0,  32768,  2147483647, MIN_INT), 
        vS32(0, -32768, -2147483647, MIN_INT)); //MIN_INT = -2147483648 

    TEST_024( ssp_abs_epi8, ssp_s8, __m128i, __m128i)  
        vS8(1,  2, 11,  22, 33,  44, 55,  66, 77,  88, 99,  127, 0, -128, 111,  100), 
        vS8(1, -2, 11, -22, 33, -44, 55, -66, 77, -88, 99, -127, 0, -128, 111, -100)); 

    //__m128i _mm_alignr_epi8(__m128i a, __m128i b, const int ralign);
    TEST_024(ssp_alignr_epi8, ssp_u32, __m128i, __m128i, __m128i, int ) 
        vU32(0x89abcdef, 0xffffeeee, 0xddddcccc, 0xbbbbaaaa),
        vU32(0x01234567, 0x89ABDCEF, 0x01234567, 0x89ABCDEF),
        vU32(0xFFFFEEEE, 0xDDDDCCCC, 0xBBBBAAAA, 0x99998888), 4);	

    //  TEST_024( ssp_hadd_epi16, ssp_s16, __m128i, __m128i, __m128i )   
    //vS16(32767, -1,  9, 23,  3, 7, 11, -32762),
    //      vS16( 7,  6,  5,  4,  3,  2, 1, 0), 
    //      vS16(15, 14, 13,  12,  11,  10, 9, 8));


    TEST_024( ssp_hadd_epi16, ssp_s16, __m128i, __m128i, __m128i )   
        vS16(32767, -1,  9, 23,  3, 7, 11, -32762),
        vS16( 1,  2,  3,  4,  5,  6, 7, 32767), 
        vS16(-1, -32768, -5,  4,  1,  8, 2, 21));
    TEST_024( ssp_hadd_epi32, ssp_s32, __m128i, __m128i, __m128i )   
        vS32(2147483647, -1,  3,  -2147483646),
        vS32( 1,  2,  3,  2147483647), 
        vS32(-1, MIN_INT, -5,  4)); 

    TEST_024( ssp_hadds_epi16, ssp_s16, __m128i, __m128i, __m128i )   
        vS16(-32768, -1,  9, 23, 3,  7, 11, 32767),
        vS16( 1,      2,  3,  4, 5,  6, 7,  32767), 
        vS16(-1, -32768, -5,  4, 1,  8, 2,     21));

    TEST_024( ssp_hsub_epi16, ssp_s16, __m128i, __m128i, __m128i )   
        vS16(32767, -9,  7, 19,  1, 1, 1, -32762),
        vS16( 1,  2,  3,  4,  5,  6, -7, 32767), 
        vS16( 1, -32768, 5,  -4,  1,  8, 2, 21));
    TEST_024( ssp_hsub_epi32, ssp_s32, __m128i, __m128i, __m128i )   
        vS32(2147483647, 9,  1,  -2147483646),
        vS32( 1,  2,  -3,  2147483647), 
        vS32( 1, MIN_INT, -5,  4));
    TEST_024( ssp_hsubs_epi16, ssp_s16, __m128i, __m128i, __m128i )   
        vS16(-32768, -9, 7, 19, 1, 1, 1, 32767),
        vS16( 1,  2,  3, 4,  5,  6, -7, 32767), 
        vS16( 1, -32768, 5, -4,  1,  8, 2, 21));

    //__m128i _mm_maddubs_epi16( __m128i a,  __m128i b);
    // a is 8 bit unsigned integer, b is signed integer

    TEST_024(ssp_maddubs_epi16, ssp_s16, __m128i, __m128i, __m128i ) 
        vS16(32767, -32768, -10000, -95, 0, 140, 100, -17),
        vU8(255, 254,  253,  252, 100,  200, 50, 1,  2, 3,  4,  5,    6,   7,  8,  9),
        vS8(127, 100, -127, -126, 100, -100, -2, 5, -9, 6, 10, 20, -100, 100, -1, -1));

    TEST_024(ssp_maddubs_epi16, ssp_s16, __m128i, __m128i, __m128i ) 
        vS16(-421, -313, -221, -145, -85, -41, -13, -1),
        vU8( 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0),
        vU8(-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,-0));    

    /*   TEST_024(ssp_mulhrs_epi16, ssp_s16, __m128i, __m128i, __m128i ) 
    vS16(1,     -8,  -0x20,    0x80,   0,  0x400,  -0x400, 0),
    vS16(7, 6, 5, 4, 3, 2, 1, 0),
    vS16(15, 14, 13, 12,  11, 10,  9, 8));*/

    TEST_024(ssp_mulhrs_epi16, ssp_s16, __m128i, __m128i, __m128i ) 
        vS16(1,     -8,  -0x20,    0x80,   0,  0x400,  -0x400, 0),
        vS16(255, -254, 0x1000, -0x2000, 100, 0x2000, -0x2000, 1),
        vS16(127, 1000, -0x100, -0x200,  100, 0x1000,  0x1000, 5));

    TEST_024(ssp_shuffle_epi8, ssp_s8, __m128i, __m128i, __m128i)
        vS8(1, 0, 4, 0, 16, 0, 64, 0, -2, 0, -8, 0, -32, 0, -128, 0),
        vS8(-1, -128, -64, -32, -16, -8, -4, -2, 127, 64, 32, 16, 8, 4, 2, 1),
        vU8(0x00, 0x81, 0x02, 0x83, 0x04, 0x85, 0x06, 0x87, 0x08, 0x89, 0x0A, 0x8B, 0x0C, 0x8D, 0x0E, 0x8F));
    TEST_024(ssp_sign_epi16, ssp_s16, __m128i, __m128i, __m128i)
        vS16(-25,    0, -5421,   81, 32000, -128,     0, 42),
        vS16( 25, -999, -5421,  -81, 32000,  128, -3141, 42),
        vS16(-12,    0, 32000, -32768, 512,   -1,     0,  1));
    TEST_024(ssp_sign_epi32, ssp_s32, __m128i, __m128i, __m128i)
        vS32( 42, -3141259,  0, 32000),
        vS32(-42,  3141259, -6, 32000),
        vS32(-75000,    -1,  0,     1));
    TEST_024(ssp_sign_epi8, ssp_s8, __m128i, __m128i, __m128i)
        vS8(0, -60, -76, 125, -100,  97, -15,  0, 32, 127,  127,   52,  10,  0, -31, 25),
        vS8(1, -60,  76, 125,  100, -97, -15, 42, 32, 127, -127,  -52,  10, -1,  31, 25),
        vS8(0,   1,  -1,   1,   -1,  -1,   1,  0,  1,  31,  -42, -128, 127,  0,  -1, 1));

}


void SSE4A_Tests( CSVTable & csv ) 
{
    TEST_025( ssp_extract_si64, ssp_u64, __m128i, __m128i, __m128i ) 
        vU64(0x0000000000000000ll, 0x00000000030eca86ll),
        vU64(0x0000000000000000ll, 0xFEDCBA9876543210ll),
        vU64(0x0000000000000000ll, 0x0000000000000b1bll) );

    TEST_025( ssp_extracti_si64, ssp_u64, __m128i, __m128i , int, int ) 
        vU64(0x0000000000000000ll, 0x00000000030eca86ll),
        vU64(0x0000000000000000ll, 0xFEDCBA9876543210ll),
        0x1B,       //27,
        0x0B );     //11

    TEST_025( ssp_insert_si64, ssp_u64, __m128i, __m128i, __m128i ) 
        vU64(0x0000000000000000ll, 0xFFFFFFFFF3210FFFll),
        vU64(0x0000000000000000ll, 0xFFFFFFFFFFFFFFFFll),
        vU64(0x0000000000000c10ll, 0xfedcba9876543210ll),
        vU64(0x0000000000000000ll, 0xFFFFFFFFFFFFFFFFll)); // expMask

    TEST_025( ssp_inserti_si64, ssp_u64, __m128i, __m128i, __m128i, int, int ) 
        vU64(0x0000000000000000ll, 0xFFFFFFFFF3210FFFll),
        vU64(0x0000000000000000ll, 0xFFFFFFFFFFFFFFFFll),
        vU64(0x0000000000000000ll, 0xfedcba9876543210ll),
        0x10,       // 16
        0x0C );     // 12
    { 
        __m128d src = vF64( -1., 1. );
        double exp = 1.;
        double d = 0.;
        TEST_05( ssp_stream_sd, ssp_f64, double*, double*, __m128d, void )
            &exp,
            &d,
            src );
    }
    { 
        __m128 src = vF32( -4., -3., -2., -1. );
        float exp = -1.;
        float d = 0;
        TEST_05( ssp_stream_ss, ssp_f32, float*, float*, __m128, void )
            &exp,
            &d,
            src );
    }
    TEST_05( ssp_lzcnt16, ssp_u16, ssp_u16, ssp_u16 )
        1,
        0x7FFF );

    TEST_05( ssp_lzcnt16, ssp_u16, ssp_u16, ssp_u16 )
        1,
        0x7000 );

    TEST_05( ssp_lzcnt, ssp_u32, ssp_u32, ssp_u32 )
        16,
        0xFFFF );
    TEST_05( ssp_lzcnt, ssp_u32, ssp_u32, ssp_u32 )
        15,
        0x1FFFF );
#ifdef SYS64
    TEST_05( ssp_lzcnt64, ssp_u64, ssp_u64, ssp_u64 )
        48,
        0xFFFF );
    TEST_05( ssp_lzcnt64, ssp_u64, ssp_u64, ssp_u64 )
        47,
        0x1FFFF );
#else
    TEST_0( ssp_lzcnt64, ssp_u64, ssp_u64, ssp_u64 )
        48,
        0xFFFF );
    TEST_0( ssp_lzcnt64, ssp_u64, ssp_u64, ssp_u64 )
        47,
        0x1FFFF );
#endif

    TEST_05( ssp_popcnt16, ssp_u16, ssp_u16, ssp_u16 )
        8,
        0xFF );
    TEST_05( ssp_popcnt16, ssp_u16, ssp_u16, ssp_u16 )
        16,
        0xFFFF );

    TEST_05( ssp_popcnt, ssp_u32, ssp_u32, ssp_u32 )
        8,
        0xFF );
    TEST_05( ssp_popcnt, ssp_u32, ssp_u32, ssp_u32 )
        32,
        0xFFFFFFFF );

#ifdef SYS64
    TEST_05( ssp_popcnt64, ssp_u64, ssp_u64, ssp_u64 )
        8,
        0xFF );
#else
    TEST_0( ssp_popcnt64, ssp_u64, ssp_u64, ssp_u64 )
        8,
        0xFF );
    TEST_0( ssp_popcnt64, ssp_u64, ssp_u64, ssp_u64 )
        64,
        0xFFFFFFFFFFFFFFFFll );
#endif

}


void SSE4_1_Tests( CSVTable & csv ) 
{

    TEST_026( ssp_blend_epi16, ssp_s16, __m128i,__m128i,__m128i,int )
        vS16(0xF0, 0x01, 0xF2, 0x03, 0x04, 0xF5, 0x06, 0xF7),
        vS16(0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07), 
        vS16(0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7), 
        0xA5 ); // 1010 0101

    TEST_026( ssp_blend_pd, ssp_f64, __m128d,__m128d,__m128d,int )
        vF64(0xFFFF, 0x0123),
        vF64(0xFFFF, 0x0000), 
        vF64(0xABCD, 0x0123), 
        0x01 );

    TEST_026( ssp_blend_ps, ssp_f32, __m128, __m128, __m128, int )
        vF32(0x000F, 0x00F0, 0x0F00, 0xF000), 
        vF32(0x000F, 0xFFFF, 0x0F00, 0xFFFF), 
        vF32(0xFFFF, 0x00F0, 0xFFFF, 0xF000), 
        0x5 );

    TEST_026( ssp_blendv_epi8, ssp_s8, __m128i,__m128i,__m128i,__m128i )
        vU8(0x0F, 0x0F, 0x0E, 0x06, 0x0D, 0x0D, 0x03, 0x04, 0x0B, 0x0B, 0x05, 0x0A, 0x06, 0x01, 0x80, 0x80), 
        vU8(0x00, 0x0F, 0x01, 0x0E, 0x02, 0x0D, 0x03, 0x0C, 0x04, 0x0B, 0x05, 0x0A, 0x06, 0x09, 0x07, 0x80),
        vU8(0x0F, 0x07, 0x0E, 0x06, 0x0D, 0x05, 0x0C, 0x04, 0x0B, 0x03, 0x0A, 0x02, 0x09, 0x01, 0x80, 0x00),
        vU8(0x80, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00) );

    {
        ssp_u64 maskValue1 = 0x8000000000000000ll;
        ssp_u64 maskValue0 = 0x0000000000000000ll;
        TEST_026( ssp_blendv_pd, ssp_f64, __m128d,__m128d,__m128d,__m128d )  
            vF64( 3.141592, -21734.56),
            vF64( -500.17, -21734.56),
            vF64(3.141592, 10.5 ),
            vF64(*reinterpret_cast<ssp_f64 *>(&maskValue1), 
            *reinterpret_cast<ssp_f64 *>(&maskValue0)) );
    }
    {
        ssp_u64 maskValue1 = 0x0000000000000000ll;
        ssp_u64 maskValue0 = 0x8000000000000000ll;
        TEST_026( ssp_blendv_pd, ssp_f64, __m128d,__m128d,__m128d,__m128d ) 
            vF64(0x01010F0F, 0xF3F34040),
            vF64(0x01010F0F, 0xF1F12020),
            vF64(0x30302F2F, 0xF3F34040),
            vF64(*reinterpret_cast<ssp_f64 *>(&maskValue1), 
            *reinterpret_cast<ssp_f64 *>(&maskValue0)) );
    }
    {
        ssp_u32 maskValue3 = 0x80000000;
        ssp_u32 maskValue2 = 0x00000000;
        ssp_u32 maskValue1 = 0x80000000;
        ssp_u32 maskValue0 = 0x80000000;
        TEST_026( ssp_blendv_ps, ssp_f32, __m128, __m128, __m128, __m128 )  
            vF32(0x0000000A, 0x00000002, 0x0000000C, 0x0000000D),
            vF32(0x00000001, 0x00000002, 0x00000003, 0x00000004),
            vF32(0x0000000A, 0x0000000B, 0x0000000C, 0x0000000D),
            vF32(*reinterpret_cast<ssp_f32 *>(&maskValue3), 
            *reinterpret_cast<ssp_f32 *>(&maskValue2), 
            *reinterpret_cast<ssp_f32 *>(&maskValue1), 
            *reinterpret_cast<ssp_f32 *>(&maskValue0) ) );  
    }
  

    TEST_026( ssp_ceil_pd, ssp_f64, __m128d,__m128d  )
        vF64(1.0f,3.0f), 
        vF64(.1f,2.1f)           );    

    TEST_026( ssp_ceil_ps, ssp_f32, __m128, __m128 )  
        vF32(1.0f,3.0f,4.0f,4.0f), 
        vF32(.1f,2.1f,3.9f,4.0f) );

    TEST_026( ssp_ceil_sd, ssp_f64, __m128d,__m128d,__m128d   )
        vF64( 0.1f, -34.0f),
        vF64( 0.1f,   2.1f),
        vF64(90.5f, -34.2f) ); 

    TEST_026( ssp_ceil_ss, ssp_f32, __m128, __m128, __m128   )  
        vF32( 0.1f,   2.1f, 3.9f, -2.0f), 
        vF32( 0.1f,   2.1f, 3.9f,  4.0f),
        vF32(90.5f, -34.2f, 0.1f, -2.9f) );

 TEST_026( ssp_cmpeq_epi64, ssp_s64, __m128i, __m128i, __m128i  )
        vS64( 0x0000000000000000ll, 0xFFFFFFFFFFFFFFFFll ),
        vS64( 0x0000000000000002ll, 0x0100000000000000ll ),
        vS64( 0x0000000000000001ll, 0x0100000000000000ll ) ); 

    TEST_026( ssp_cmpeq_epi64, ssp_s64, __m128i, __m128i, __m128i  )
        vS64( 0xFFFFFFFFFFFFFFFFll, 0x0000000000000000ll ),
        vS64( 0x0000000000000001ll, 0x0200000000000000ll ),
        vS64( 0x0000000000000001ll, 0x0100000000000000ll ) ); 

    TEST_026(ssp_cvtepi16_epi32, ssp_s32, __m128i, __m128i ) 
        vS32(5,-5,8,-7),
        vS16(0,-1,3,-3,5,-5,8,-7));

    TEST_026(ssp_cvtepi16_epi64, ssp_s64, __m128i, __m128i )
        vS64(8,-7),
        vS16(0,-1,3,-3,5,-5,8,-7));

    TEST_026(ssp_cvtepi32_epi64, ssp_s64, __m128i, __m128i )
        vS64(8,-7),
        vS32(5,-5,8,-7));

    TEST_026(ssp_cvtepi8_epi16, ssp_s16, __m128i, __m128i )
        vS16(0,-1,3,-3,5,-5,8,-7),
        vS8(9,9,10,11,12,13,14,15, 0,-1,3,-3,5,-5,8,-7));

    TEST_026 (ssp_cvtepi8_epi32, ssp_s32, __m128i, __m128i )
        vS32(5,-5,8,-7),
        vS8(9,9,10,11,12,13,14,15, 0,-1,3,-3,5,-5,8,-7));

    TEST_026(ssp_cvtepi8_epi64, ssp_s64, __m128i, __m128i )
        vS64(8,-7),
        vS8(9,9,10,11,12,13,14,15, 0,-1,3,-3,5,-5,8,-7));

    TEST_026(ssp_cvtepu16_epi32, ssp_s32, __m128i, __m128i)
        vS32(5, 65531, 8, 65529),
        vU16(0,-1,3,-3,5,-5,8,-7));

    TEST_026(ssp_cvtepu16_epi64, ssp_s64, __m128i, __m128i)
        vS64(8, 65529),
        vU16(0,-1,3,-3,5,-5,8,-7));

    TEST_026(ssp_cvtepu32_epi64, ssp_s64, __m128i, __m128i) 
        vS64(8, 4294967289ll),
        vU32(5,-5,8,-7));	

    TEST_026(ssp_cvtepu8_epi16, ssp_s16, __m128i, __m128i ) 
        vS16(0, 255, 3, 253, 5, 251, 8, 249),
        vU8(9,9,10,11,12,13,14,15, 0,-1,3,-3,5,-5,8,-7));

    TEST_026(ssp_cvtepu8_epi32, ssp_s32, __m128i, __m128i)  
        vS32(5, 251, 8, 249),
        vU8(9,9,10,11,12,13,14,15, 0,-1,3,-3,5,-5,8,-7));

    TEST_026(ssp_cvtepu8_epi32, ssp_s32, __m128i, __m128i)  
        vS32(5, 251, 8, 249),
        vU8(9,9,10,11,12,13,14,15, 0,-1,3,-3,5,-5,8,-7));

    TEST_026(ssp_cvtepu8_epi64, ssp_s64, __m128i, __m128i)  
        vS64(8, 249),
        vU8(9,9,10,11,12,13,14,15, 0,-1,3,-3,5,-5,8,-7));	

    TEST_026(ssp_dp_pd, ssp_f64, __m128d, __m128d, __m128d, const int)
        vF64(50000, 50000), 
        vF64(100, 200), vF64(100, 200), 0x33);

    TEST_026(ssp_dp_pd, ssp_f64, __m128d, __m128d, __m128d, const int)
        vF64(-10012, 0), 
        vF64(100, 200), vF64(-100.12, 200), 0x22);

    TEST_0236(ssp_dp_ps, ssp_f32, __m128, __m128, __m128, const int)
        vF32(0, 0, 0, 30000), 
        vF32(100, 200, 300, 400), vF32(10, 20, 30, 40), 0xf1);
    TEST_0236(ssp_dp_ps, ssp_f32, __m128, __m128, __m128, const int) 
        vF32(0, 0, 29000, 29000), 
        vF32(100, 200, 300, 400), vF32(10, 20, 30, 40), 0x73);
    TEST_0236( ssp_dp_ps, ssp_f32, __m128, __m128, __m128, int )
        vF32(0,556.40625,0,556.40625),
        vF32(81,-11.0625,10.25,1.5), 
        vF32(100,-50.5,3.125,-1.5), 0x55 );   

    TEST_026( ssp_extract_epi32, ssp_s32, int, __m128i, int )     
        0x76543210,
        vS32( 0xFEDCBA98, 0x76543210, 0xFEDCBA98, 0x76543210 ),
        2);
#ifdef SYS64
    TEST_026( ssp_extract_epi64, ssp_s64,  ssp_s64, __m128i, int ) // TODO: Handle this more gracefully
        0xFFEEDDCCBBAA9988ll,
        vU64(0xFFEEDDCCBBAA9988ll, 0x7766554433221100ll),
        1 );     
#else
    TEST_02( ssp_extract_epi64, ssp_s64,  ssp_s64, __m128i, int )  
        0xFFEEDDCCBBAA9988ll,
        vU64(0xFFEEDDCCBBAA9988ll, 0x7766554433221100ll),
        1 );
#endif

    TEST_026( ssp_extract_epi8, ssp_u8, int, __m128i, int )    
        7,
        vS8( 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 ),
        7);						

    // TODO: Look into this function. Should the ssp_f32 be converted to ssp_s32 (Test on Intel hardware)?
    TEST_026( ssp_extract_ps, ssp_f32,  int, __m128,  int )
        0x40490FD0, /*0x40490FD0 = 3.14159f */
        vF32( 3.14159f, 6.022f, 128.0f, 3.0f ),
        3 );        											

    TEST_026( ssp_floor_pd, ssp_f64, __m128d,__m128d   )
        vF64(0.0f,2.0f),           
        vF64(.1,2.1)            );

    TEST_026( ssp_floor_ps, ssp_f32, __m128, __m128    )
        vF32(0.0f,2.0f,3.0f,4.0f),
        vF32(.1f,2.1f,3.9f,4.0f));

    TEST_026( ssp_floor_sd, ssp_f64, __m128d,__m128d,__m128d )
        vF64( 34.2f,   2.0f),
        vF64( 34.2f, -32.3f),
        vF64(  0.1f,   2.1f) );

    TEST_026( ssp_floor_ss, ssp_f32, __m128, __m128, __m128   )
        vF32( 0.1f,   2.1f, 3.9f, -3.0f), 
        vF32( 0.1f,   2.1f, 3.9f,  4.0f),
        vF32(90.5f, -34.2f, 0.1f, -2.9f) );  															

    TEST_026(ssp_insert_epi32, ssp_s32, __m128i, __m128i, int, int )
        vS32(5678, -1234,  2345, 1234),
        vS32(5678, -1234, -5678, 1234),
        2345,
        1);

#ifdef SYS64
    TEST_06( ssp_insert_epi64, ssp_s64, __m128i, __m128i, ssp_s64, int )
        vS64(123456789,  123456789),
        vS64(123456789, -987654321),
        123456789,
        0);
#endif

    TEST_026( ssp_insert_epi8, ssp_s8, __m128i, __m128i, int, int )
        vS8(15,  4, 13, 12,11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0),
        vS8(15, 14, 13, 12,11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0),
        4,
        14);   


    TEST_06( ssp_insert_ps, ssp_f32, __m128, __m128, __m128, int )
        vF32(   0.000f,    0.000f, -789.123f,    0.000f),
        vF32( 987.654f,  321.654f,  123.456f,  789.123f),
        vF32(-123.456f, -789.123f, -456.789f, -123.000f),
        0x9D);  // 10 01 1101

    TEST_026( ssp_max_epi32, ssp_s32, __m128i,__m128i,__m128i )
        vS32(1,3,3,5), vS32(1,2,3,4), vS32(1,3,2,5) ); 


    TEST_026( ssp_max_epi8, ssp_s8, __m128i,__m128i,__m128i )
        vS8(0,1,3,3,5,5,8,7,9,9,10,11,12,13,14,15), 
        vS8(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15), 
        vS8(0,0,3,2,5,5,8,2,9,3, 7, 2, 1, 8, 9, 7) ); 

    TEST_026( ssp_max_epu16, ssp_u16, __m128i,__m128i,__m128i )
        vU16(65535,65535,65534,65534,5,5,8,7), 
        vU16(65535,65534,32767,65534,4,5,6,7), 
        vU16(65534,65535,65534,32767,5,5,8,2) );  

    TEST_026( ssp_max_epu32, ssp_s32, __m128i,__m128i,__m128i )
        vS32(1,3,3,5), vS32(1,2,3,4), vS32(0,3,2,5) );

    TEST_026( ssp_min_epi32, ssp_s32, __m128i,__m128i,__m128i )
        vS32(0,2,2,4), vS32(1,2,3,4), vS32(0,3,2,5) ); 

    TEST_026( ssp_min_epi8, ssp_s8, __m128i,__m128i,__m128i )
        vS8(0,0,2,2,4,5,6,2,8,3, 7, 2, 1, 8, 9, 7), 
        vS8(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15), 
        vS8(0,0,3,2,5,5,8,2,9,3, 7, 2, 1, 8, 9, 7) ); 

    TEST_026( ssp_min_epu16, ssp_u16,  __m128i,__m128i,__m128i )
        vU16(65534,65534,32767,32767,4,5,6,2), 
        vU16(65535,65534,32767,65534,4,5,6,7), 
        vU16(65534,65535,65534,32767,5,5,8,2) ); 


    TEST_026( ssp_min_epu32, ssp_s32, __m128i,__m128i,__m128i )
        vS32(0,2,2,4), vS32(1,2,3,4), vS32(0,3,2,5) );   

    TEST_06( ssp_minpos_epu16, ssp_u16, __m128i,__m128i )
        vU16(0,0,0,0,0,0,4,2), 
        vU16(5,8,9,2,3,4,5,6) );    


    TEST_026(ssp_mpsadbw_epu8, ssp_u16, __m128i, __m128i, __m128i, const int)
        vU16(182, 246, 310, 374, 438, 502, 566, 630), 
        vU8(0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0, 0xf1), 
        vU8(0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x10), 5);

    TEST_026(ssp_mpsadbw_epu8, ssp_u16, __m128i, __m128i, __m128i, const int)
        vU16(214, 278, 342, 406, 470, 534, 598, 662), 
        vU8(0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0, 0xf1), 
        vU8(0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x10), 7);

    TEST_026( ssp_packus_epi32, ssp_u16, __m128i, __m128i, __m128i ) 
        vU16( 0x0000, 0xFFFF, 0x0FFF, 0x0000, 0x0000, 0xFFFF, 0x0FFF, 0x0000 ),
        vS32( 0xFFFFFFFF, 0x7FFFFFFF, 0x00000FFF, 0x0000000 ),
        vS32( 0xFFFFFFFF, 0x7FFFFFFF, 0x00000FFF, 0x0000000) );


    TEST_026( ssp_round_pd, ssp_f64, __m128d, __m128d, int  )        
        vF64( 128.0, -315.0   ),
        vF64( 127.5, -315.125 ),
        SSP_FROUND_TO_NEAREST_INT );

    TEST_06( ssp_round_sd, ssp_f64, __m128d, __m128d, __m128d, int  )        
        vF64( 127.5, -315.0   ),
        vF64( 127.5,      0   ),
        vF64(     0, -315.125 ),
        SSP_FROUND_TO_NEAREST_INT );

    TEST_026( ssp_round_pd, ssp_f64, __m128d, __m128d, int  )   
        vF64( 128.0, -315.0   ),
        vF64( 127.5, -315.125 ),
        SSP_FROUND_TO_POS_INF     );
    TEST_026( ssp_round_pd, ssp_f64, __m128d, __m128d, int  )
        vF64( 127.0, -316.0   ),
        vF64( 127.5, -315.525 ),
        SSP_FROUND_TO_NEG_INF     );
    TEST_026( ssp_round_pd, ssp_f64, __m128d, __m128d, int  )
        vF64( 40.0, -30.0     ),
        vF64( 40.5, -30.9     ),
        SSP_FROUND_TO_ZERO        );

    TEST_026( ssp_round_ps, ssp_f32, __m128, __m128, int )
        vF32( 128.0f, -315.0f,   0.0f,   -1.0f   ),
        vF32( 127.5f, -315.125f, 0.123f, -0.789f ),
        SSP_FROUND_TO_NEAREST_INT   );
    TEST_026( ssp_round_ps, ssp_f32, __m128, __m128, int )
        vF32( 128.0f, -315.0f,   1.0f,   0.0f   ),
        vF32( 127.5f, -315.125f, 0.123f, -0.789f ),
        SSP_FROUND_TO_POS_INF       );
    TEST_026( ssp_round_ps, ssp_f32, __m128, __m128, int )
        vF32( 127.0f, -316.0f,   0.0f,   -1.0f   ),
        vF32( 127.5f, -315.525f, 0.123f, -0.789f ),
        SSP_FROUND_TO_NEG_INF       );
    TEST_026( ssp_round_ps, ssp_f32, __m128, __m128, int )
        vF32( 40.0f, -30.0f,     0.0f,   0.0f   ),
        vF32( 40.5f, -30.9f    , 0.123f, -0.789f ),
        SSP_FROUND_TO_ZERO          );

    TEST_026( ssp_round_ss, ssp_f32, __m128, __m128, __m128, int  )
        vF32( -315.125f, 0.123f, 127.5f, 128.0f ), 
        vF32( -315.125f, 0.123f, 127.5f,   0.0f ),
        vF32(  127.5f,   0.3f,   1.4f,   127.5f ),
        SSP_FROUND_TO_NEAREST_INT   );
    TEST_026( ssp_round_ss, ssp_f32, __m128, __m128, __m128, int )
        vF32( 127.5f, -315.125f, 0.123f,   -0.0f   ),
        vF32( 127.5f, -315.125f, 0.123f,  127.5f   ),
        vF32(  127.5f,   0.3f,   1.4f,     -0.789f ),
        SSP_FROUND_TO_POS_INF       );
    TEST_026( ssp_round_ss, ssp_f32, __m128, __m128, __m128, int )
        vF32( 127.5f, -315.525f, 0.123f,  -1.0f   ),
        vF32( 127.5f, -315.525f, 0.123f, 127.5f   ),
        vF32(  127.5f,   0.3f,   1.4f,    -0.789f ),
        SSP_FROUND_TO_NEG_INF       );
    TEST_026( ssp_round_ss, ssp_f32, __m128, __m128, __m128, int )
        vF32( 40.5f, -30.9f    , 0.123f,  -0.0f   ),
        vF32( 40.5f, -30.9f    , 0.123f, 127.5f   ),
        vF32(  127.5f,   0.3f,   1.4f,    -0.789f ),
        SSP_FROUND_TO_ZERO          );   

    TEST_026( ssp_testc_si128, ssp_u32, int,   __m128i,__m128i )
        1,
        vU64( 0xFEDCBA9876543210ll, 0xAAAA55551111FFFFll ),
        vU64( 0xFEDCBA9876543210ll, 0xAAAA55551111FFFFll ) );
    TEST_026( ssp_testc_si128, ssp_u32, int,   __m128i,__m128i )
        0,
        vU64( 0xFEDCBA9876543210ll, 0xAAAA55551111FFFFll ),
        vU64( 0xFEDCBA9876543210ll, 0xAAAA55551011FFFFll ) );
    TEST_026( ssp_testnzc_si128, ssp_u32, int,   __m128i,__m128i )
        0,
        vU64( 0x0000000000000000ll, 0x0000000000000000ll ),
        vU64( 0x0000000000000000ll, 0xFFFFFFFFFFFFFFFFll ) );
    TEST_026( ssp_testnzc_si128, ssp_u32, int,   __m128i,__m128i )
        1,
        vU64( 0x0000000000000000ll, 0x0000000000000001ll ),
        vU64( 0x0000000000000000ll, 0xFFFFFFFFFFFFFFFFll ) );

    TEST_026( ssp_testz_si128, ssp_u32, int,   __m128i,__m128i )
        0,
        vU64( 0xF0FAF0F0F0F0F0F0ll, 0x1020354050607080ll ),
        vU64( 0x0F0F0F0F0F0F0F0Fll, 0x090A0B0C0D0E0FB0ll ) );  

    TEST_026( ssp_testz_si128, ssp_u32, int,   __m128i,__m128i )
        1,
        vU64( 0xF0F0F0F0F0F0F0F0ll, 0x1020304050607080ll ),
        vU64( 0x0F0F0F0F0F0F0F0Fll, 0x090A0B0C0D0E0F00ll ) );
    TEST_026( ssp_testz_si128, ssp_u32, int,   __m128i,__m128i )
        0,
        vU64( 0xF0F0F0F0F0F0F0F0ll, 0x1020304050607080ll ),
        vU64( 0x0F0F0F0F0F0F0F0Fll, 0x090A0B0C0D0E0FB0ll ) );   

    TEST_06( ssp_mullo_epi32, ssp_s32, __m128i, __m128i, __m128i )
        vS32(-1,4,-9,16),
        vS32( 1,2, 3,4),
        vS32(-1,2,-3,4) );

    TEST_06( ssp_mul_epi32, ssp_s32, __m128i, __m128i, __m128i  )
        vS32(0,4,0,16),
        vS32( 1,2, 3,4), 
        vS32(-1,2,-3,4) );

    //expected_output.u64[0] = 0xFFFFFFFFFFFFFFFFll; expected_output.u64[1] = 0xFFF8FFFFFFFFFFFFll; 
    //input.u64[0] = 0x7FF0000000000001ll; input.u64[1] = 0xFFF8FFFFFFFFFFFFll;
    //TEST_0(__m128d, __m128d, int,  ARG(ssp_f64, ssp_round_pd ), vF64( expected_output.f64[1], expected_output.f64[0] ),
    //                                                      vF64( input.f64[1], input.f64[0] ),
    //                                                      SSP_FROUND_TO_NEAREST_INT );
    //expected_output.u64[0] = 0x7FF8FFFFFFFFFFFFll; expected_output.u64[1] = 0xFFFFFFFFFFFFFFFFll; 
    //input.u64[0] = 0x7FF8FFFFFFFFFFFFll; input.u64[1] = 0xFFFFFFFFFFFFFFFFll;
    //TEST_0(__m128d, __m128d, int,  ARG(ssp_f64, ssp_round_pd ), vF64( expected_output.f64[1], expected_output.f64[0]  ),
    //                                                      vF64( input.f64[1], input.f64[0]  ),
    //                                                      SSP_FROUND_TO_NEAREST_INT );

    //expected_output.s32[0] = 0xFFD00000; expected_output.s32[1] = 0x7FD010101; expected_output.s32[3] = 0xFFFFFFFE;
    //input.s32[0] = 0xFFD00000; input.s32[1] = 0x7FD010101; input.s32[2] = 0xFFFFFFFE;
    //TEST_0(__m128, __m128, int,  ARG(ssp_f32, ssp_round_ps ), vF32( expected_output.f32[0], expected_output.f32[1], 129.0f, expected_output.f32[3] ),
    //                                                    vF32( input.f32[0], input.f32[1], 128.5f, input.f32[2] ),
    //                                                    SSP_FROUND_TO_NEAREST_INT   );
}

void SSE5_Tests( CSVTable & csv )
{
	//Extract fraction
	TEST_0(ssp_frcz_pd, ssp_f64, __m128d, __m128d)
		vF64(0.123456789, -0.123456789),
		vF64(10.123456789, -10.123456789));

	TEST_0(ssp_frcz_ps, ssp_f32, __m128, __m128)
		vF32(0.123456f, -0.123456f, 0.789f, -0.789f),
		vF32(10.123456f, -10.123456f, 11.789f, -12.789f));

	TEST_0(ssp_frcz_sd, ssp_f64, __m128d, __m128d, __m128d)
		vF64(9.123456789, -0.123456789),
		vF64(10.123456789, -10.123456789),
		vF64(9.123456789,   -8.983456789));

	TEST_0(ssp_frcz_ss, ssp_f32, __m128, __m128, __m128)
		vF32(19.123456f, -12.123456f, 13.789f, -0.789f),
		vF32(10.123456f, -10.123456f, 11.789f, -12.789f),
		vF32(19.123456f, -12.123456f, 13.789f, -11.999f));

	//Horizontal Add/Sub
	TEST_0(ssp_haddd_epi16, ssp_s32, __m128i, __m128i)
		vS32(300, -700, 32768, -32769),
		vS16(100, 200, -300, -400, 32700, 68, -32700, -69));

	TEST_0(ssp_haddd_epi8, ssp_s32, __m128i, __m128i)
		vS32(-4, -10, 211, -11),
		vS8(1, 2, -3, -4, 5, -6, -17, 8, 100, 112, -128, 127, 45, 68, -55, -69));

	TEST_0(ssp_haddd_epu16, ssp_u32, __m128i, __m128i)
		vU32(300, 90000, 131069, 60069),
		vU16(100, 200, 40000, 50000, 65535, 65534, 60000, 69));

	TEST_0(ssp_haddd_epu8, ssp_u32, __m128i, __m128i)
		vU32(10, 36, 467, 537),
		vU8(1, 2, 3, 4, 5, 6, 17, 8, 100, 112, 128, 127, 45, 68, 255, 169));

	TEST_0(ssp_haddq_epi16, ssp_s64, __m128i, __m128i)
		vS64(-400, -1),
		vS16(100, 200, -300, -400, 32700, 68, -32700, -69));

	TEST_0(ssp_haddq_epi32, ssp_s64, __m128i, __m128i)
		vS64(-400, 2147483715LL),
		vS32(-100, -300, 2147483647, 68));

	TEST_0(ssp_haddq_epi8, ssp_s64, __m128i, __m128i)
		vS64(400, 665),
		vS8(100, 100, 100, 100, -50, 60, -70, 60, 127, -128, 111, 111, 111, 111, 111, 111));

	TEST_0(ssp_haddq_epu16, ssp_u64, __m128i, __m128i)
		vU64(1000, 98372),
		vU16(100, 200, 300, 400, 32700, 68, 65535, 69));

	TEST_0(ssp_haddq_epu32, ssp_u64, __m128i, __m128i)
		vU64(400, 6442450941LL),
		vU32(100, 300, 2147483647, 4294967294));

	TEST_0(ssp_haddq_epu8, ssp_u64, __m128i, __m128i)
		vU64(640, 921),
		vU8(100, 100, 100, 100, 50, 60, 70, 60, 127, 128, 111, 111, 111, 111, 111, 111));

	TEST_0(ssp_haddw_epi8, ssp_s16, __m128i, __m128i)
		vS16(3, -7, -1, -9, 212, -1, 113, -124),
		vS8(1, 2, -3, -4, 5, -6, -17, 8, 100, 112, -128, 127, 45, 68, -55, -69));

	TEST_0(ssp_haddw_epu8, ssp_u16, __m128i, __m128i)
		vU16(3, 7, 11, 25, 412, 400, 313, 424),
		vU8(1, 2, 3, 4, 5, 6, 17, 8, 200, 212, 255, 145, 245, 68, 255, 169));

	TEST_0(ssp_hsubd_epi16, ssp_s32, __m128i, __m128i)
		vS32(-12, -65535, 65535, 14),
		vS16(100, 112, -32768, 32767, 32767, -32768, -55, -69));

	TEST_0(ssp_hsubq_epi32, ssp_s64, __m128i, __m128i)
		vS64(-4294967295LL, 4294967295LL),
		vS32(MIN_INT, 2147483647, 2147483647, MIN_INT));

	TEST_0(ssp_hsubw_epi8, ssp_s16, __m128i, __m128i)
		vS16(-1, 1, 11, -25, -12, -255, -23, 14),
		vS8(1, 2, -3, -4, 5, -6, -17, 8, 100, 112, -128, 127, 45, 68, -55, -69));

    // Mul Add
    TEST_028( ssp_macc_epi16, ssp_s16, __m128i, __m128i, __m128i, __m128i )
        vS16(200,  100,  200,  31636, -31236, 32663,    100, -3392),
        vS16(0,    -1,     2,     -3,     -4,     5,      6,   - 7), 
        vS16(100,  200,  300,    400,   -400, 32767, -32768, 30000),
        vS16(200,  300, -400, -32700,  32700,  -100,    100, 10000));

	TEST_028( ssp_macc_epi32, ssp_s32, __m128i, __m128i, __m128i, __m128i )
        vS32( -189934392,    94967596,   -94967696, -2005065404),
        vS32(         -4,          -2,           2,          -3), 
        vS32(-2100000000,  2100000000,  2100000000,  2100000000),
        vS32(        200,         300,        -400,      -32700));

    TEST_028( ssp_macc_ps, ssp_f32, __m128, __m128, __m128, __m128 )
        vF32( 24.75f,-0.09f,0.0f, 14.19f ),
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ), 
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ),
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ));

    TEST_028( ssp_macc_pd, ssp_f64, __m128d, __m128d, __m128d, __m128d )
        vF64( 24.75, 14.19 ),
        vF64(-5.5  , 3.3   ), 
        vF64(-5.5  , 3.3   ),
        vF64(-5.5  , 3.3   ));

    TEST_028( ssp_macc_ss, ssp_f32, __m128, __m128, __m128, __m128 )
        vF32( 3.0f  , 2.0f ,1.0f, 14.19f ),
        vF32( 3.0f  , 2.0f ,1.0f, 3.3f   ), 
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ),
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ));

    TEST_028( ssp_macc_sd, ssp_f64, __m128d, __m128d, __m128d, __m128d )
        vF64( 1.0, 14.19 ),
        vF64( 1.0, 3.3   ), 
        vF64(-5.5, 3.3   ),
        vF64(-5.5, 3.3   ));

	TEST_028( ssp_maccd_epi16, ssp_s32, __m128i, __m128i, __m128i, __m128i )
        vS32(0,  -900,  163435, -242700),
        vS16(0,    -1,     2,     -3,     -4,     5,      6,   - 7), 
        vS16(100,  200,  300,    400,   -400, 32767, -32768, 30000),
        vS32(200,  300, -400, -32700));

	TEST_028( ssp_macchi_epi32, ssp_s64, __m128i, __m128i, __m128i, __m128i )
        vS64(2200,  -300),
        vS32( -20,   -1,    2,     -3), 
        vS32(-100,  200, -300,   -400),
        vS64( 200,        300));

	TEST_028( ssp_macclo_epi32, ssp_s64, __m128i, __m128i, __m128i, __m128i )
        vS64(-500,  1500),
        vS32(0,    -1,     2,    -3), 
        vS32(100,  200,  300,  -400),
        vS64(-300,  300));

	TEST_028( ssp_maccs_epi16, ssp_s16, __m128i, __m128i, __m128i, __m128i )
        vS16(200,  100,  32764, -32768,  32767, 32767, -32768, -32768),
        vS16(0,    -1,       2,     -3,     -4,     5,      6,     -7), 
        vS16(100,  200,  32766,    400,   -400, 32767, -32768,  30000),
        vS16(200,  300, -32768, -32700,  32700,  -100,    100,  10000));

	TEST_028( ssp_maccs_epi32, ssp_s32, __m128i, __m128i, __m128i, __m128i )
        vS32(200,  100,  2147483647, MIN_INT),
        vS32(0,    -1,            6,         -7), 
        vS32(100,  200,  2147483647,  2147483647),
        vS32(200,  300,         100,  2147483647));

	TEST_0( ssp_maccsd_epi16, ssp_s32, __m128i, __m128i, __m128i, __m128i )
        vS32(0,  -900,  2147483647, MIN_INT),
        vS16(0,    -1,     2,     -3,     -4,     5,      6,   - 7), 
        vS16(100,  200,  300,    400,   -400, 32767, -32768, 30000),
        vS32(200,  300, 2147483647, -2147483647));

	TEST_0( ssp_maccshi_epi32, ssp_s64, __m128i, __m128i, __m128i, __m128i )
        vS64(0x8000000000000000LL,  0x7FFFFFFFFFFFFFFFLL),
        vS32(100,    -1,  200,     -3), 
        vS32(-100,  200,  300,    400),
        vS64(0x8000000000000011LL,  0x7FFFFFFFFFFFFFEELL));

	TEST_0( ssp_maccshi_epi32, ssp_s64, __m128i, __m128i, __m128i, __m128i )
        vS64(200,  900),
        vS32(0,    -1,     2,     -3), 
        vS32(100,  200,  300,    400),
        vS64(200,  300));

	TEST_0( ssp_maccslo_epi32, ssp_s64, __m128i, __m128i, __m128i, __m128i )
        vS64(0x7FFFFFFFFFFFFFFFLL,  0x8000000000000000LL),
        vS32(0,   0x7ffffffe,    2,    0x7ffffffd), 
        vS32(100, 0x7fffffff,  300,    0x80004000),
        vS64(0x7ffffffffffffffeLL,  0x8000000000000001LL));

	TEST_0( ssp_maccslo_epi32, ssp_s64, __m128i, __m128i, __m128i, __m128i )
        vS64(0,  -900),
        vS32(0,    -1,     2,     -3), 
        vS32(100,  200,  300,    400),
        vS64(200,  300));

	TEST_0( ssp_maddd_epi16, ssp_s32, __m128i, __m128i, __m128i, __m128i )
        vS32(0,  -300,  165035, -439308),
        vS16(0,    -1,     2,     -3,     -4,     5,      6,   - 7), 
        vS16(100,  200,  300,    400,   -400, 32767, -32768, 30000),
        vS32(200,  300, -400, -32700));

	TEST_0( ssp_maddsd_epi16, ssp_s32, __m128i, __m128i, __m128i, __m128i )
        vS32(0,  -300,  2147483647, MIN_INT),
        vS16(0,    -1,     2,     -3,  -4000,   500,    600,  -700), 
        vS16(100,  200,  300,    400,   -400, 32767, -32768, 30000),
        vS32(200,  300, 2147483600, -2147483600));

    // Neg Mul Add
    TEST_028( ssp_nmacc_ps, ssp_f32, __m128, __m128, __m128, __m128 )
        vF32(-35.75f,-0.11f,0.0f, -7.59f ),
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ), 
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ),
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ));

    TEST_028( ssp_nmacc_pd, ssp_f64, __m128d, __m128d, __m128d, __m128d )
        vF64(-35.75, -7.59 ),
        vF64(-5.5  , 3.3   ), 
        vF64(-5.5  , 3.3   ),
        vF64(-5.5  , 3.3   ));

    TEST_028( ssp_nmacc_ss, ssp_f32, __m128, __m128, __m128, __m128 )
        vF32( 3.0f  , 2.0f ,1.0f, -7.59f ),
        vF32( 3.0f  , 2.0f ,1.0f, 3.3f   ), 
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ),
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ));

    TEST_028( ssp_nmacc_sd, ssp_f64, __m128d, __m128d, __m128d, __m128d )
        vF64( 1.0, -7.59 ),
        vF64( 1.0, 3.3   ), 
        vF64(-5.5, 3.3   ),
        vF64(-5.5, 3.3   ));


    // Mul Sub
    TEST_028( ssp_msub_ps, ssp_f32, __m128, __m128, __m128, __m128 )
        vF32( 35.75f, 0.11f,0.0f, 7.59f  ),
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ), 
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ),
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ));

    TEST_028( ssp_msub_pd, ssp_f64, __m128d, __m128d, __m128d, __m128d )
        vF64( 35.75, 7.59  ),
        vF64(-5.5  , 3.3   ), 
        vF64(-5.5  , 3.3   ),
        vF64(-5.5  , 3.3   ));

    TEST_028( ssp_msub_ss, ssp_f32, __m128, __m128, __m128, __m128 )
        vF32( 3.0f  , 2.0f ,1.0f, 7.59f ),
        vF32( 3.0f  , 2.0f ,1.0f, 3.3f   ), 
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ),
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ));

    TEST_028( ssp_msub_sd, ssp_f64, __m128d, __m128d, __m128d, __m128d )
        vF64( 1.0, 7.59 ),
        vF64( 1.0, 3.3   ), 
        vF64(-5.5, 3.3   ),
        vF64(-5.5, 3.3   ));

    // Neg Mul Sub
    TEST_028( ssp_nmsub_ps, ssp_f32, __m128, __m128, __m128, __m128 )
        vF32(-24.75f, 0.09f,0.0f,-14.19f  ),
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ), 
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ),
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ));

    TEST_028( ssp_nmsub_pd, ssp_f64, __m128d, __m128d, __m128d, __m128d )
        vF64(-24.75,-14.19  ),
        vF64(-5.5  , 3.3   ), 
        vF64(-5.5  , 3.3   ),
        vF64(-5.5  , 3.3   ));

    TEST_028( ssp_nmsub_ss, ssp_f32, __m128, __m128, __m128, __m128 )
        vF32( 3.0f  , 2.0f ,1.0f,-14.19f ),
        vF32( 3.0f  , 2.0f ,1.0f, 3.3f   ), 
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ),
        vF32(-5.5f  ,-0.1f ,0.0f, 3.3f   ));

    TEST_028( ssp_nmsub_sd, ssp_f64, __m128d, __m128d, __m128d, __m128d )
        vF64( 1.0,-14.19 ),
        vF64( 1.0, 3.3   ), 
        vF64(-5.5, 3.3   ),
        vF64(-5.5, 3.3   ));

    // permute
    TEST_08( ssp_perm_epi8, ssp_u8, __m128i, __m128i, __m128i, __m128i )
// in val      00    11    55    66    AA    BB    EE    FF    F0    C3    B4    87    78    69    3C    2D
        vU8( 0x00, 0xEE, 0xAA, 0x99, 0x00, 0xFF, 0xFF, 0x00, 0xF0, 0x3C, 0x2D, 0x1E, 0x00, 0xFF, 0x00, 0xFF ),
        vU8( 0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00 ),
        vU8( 0x0F, 0x1E, 0x2D, 0x3C, 0x4B, 0x5A, 0x69, 0x78, 0x87, 0x96, 0xA5, 0xB4, 0xC3, 0xD2, 0xE1, 0xF0 ),
// src (hex)   00    01    05    06    0A    0B    0E    0F    10    13    14    17    18    19    1C    1D
// op (bin)   000   001   010   011   100   101   110   111   000   001   010   011   100   101   110   111
        vU8( 0x00, 0x21, 0x45, 0x66, 0x8A, 0xAB, 0xCE, 0xDF, 0x10, 0x33, 0x54, 0x77, 0x98, 0xB9, 0xDC, 0xFD )); 

    TEST_08( ssp_perm_ps, ssp_f32, __m128, __m128, __m128, __m128i )
// in val      -50  -100   100   -25
        vF32(  -50,  100, -100,  -25 ),
        vF32( -100,  -50,   50,  100 ),
        vF32(   25,  -10,   10,  -25 ),
// src (hex)    02    03    00    04
// op (bin)  000   001   010   011  
        vU32( 0x02, 0x23, 0x40, 0x64 ));

    TEST_08( ssp_perm_ps, ssp_f32, __m128, __m128, __m128, __m128i )
        vF32( 0.0f,-1.0f, 1.0f, 3.141593f ),
        vF32( -100,  -50,   50,  100 ),
        vF32(   25,  -10,   10,  -25 ),
// src (hex)    02    03    00    04
// op (bin)  100   101   110   111  
        vU32( 0x82, 0xA3, 0xC0, 0xE4 ));

    TEST_08( ssp_perm_pd, ssp_f64, __m128d, __m128d, __m128d, __m128i )
// in val      -50  -100
        vF64(  -50,  100 ),
        vF64( -100,  -50 ),
        vF64(   25,  -10 ),
// src (hex)    00    01
// op (bin)  000   001
        vU64( 0x00, 0x21 ));

    TEST_08( ssp_perm_pd, ssp_f64, __m128d, __m128d, __m128d, __m128i )
// in val       100   -25
        vF64(  -100,  -25 ),
        vF64(    50,  100 ),
        vF64(    10,  -25 ),
// src (hex)    00    02
// op (bin)  010   011  
        vU64( 0x40, 0x62 ));

    TEST_08( ssp_perm_pd, ssp_f64, __m128d, __m128d, __m128d, __m128i )
        vF64( 0.0f,-1.0f ),
        vF64( -100,  -50 ),
        vF64(   25,  -10 ),
// src (hex)    00    01
// op (bin)  100   101
        vU64( 0x80, 0xA1 ));

    TEST_08( ssp_perm_pd, ssp_f64, __m128d, __m128d, __m128d, __m128i )
        vF64( 1.0f, 3.1415926535897931 ),
        vF64(   50,  100 ),
        vF64(   10,  -25 ),
// src (hex)    02    03
// op (bin)  110   111  
        vU64( 0xC2, 0xE3 ));

    // rotates
    TEST_028( ssp_rot_epi8, ssp_u8, __m128i, __m128i, __m128i )
        vU8( 0x60, 0xC0, 0x81, 0x03, 0x06, 0x60, 0xC0, 0x81, 0x03, 0x06, 0x60, 0xC0, 0x81, 0x03, 0x06, 0x60 ),
        vU8( 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81 ),
        vU8( 0xFE, 0xFF, 0x00, 0x01, 0x02, 0xFE, 0xFF, 0x00, 0x01, 0x02, 0xFE, 0xFF, 0x00, 0x01, 0x02, 0xFE )); 

    TEST_028( ssp_rot_epi16, ssp_u16, __m128i, __m128i, __m128i )
        vU16( 0x6000, 0xC000, 0x8001, 0x0003, 0x0006, 0x6000, 0xC000, 0x8001 ),
        vU16( 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001 ),
        vU16( 0xFFFE, 0xFFFF, 0x0000, 0x0001, 0x0002, 0xFFFE, 0xFFFF, 0x0000 )); 

    TEST_028( ssp_rot_epi32, ssp_u32, __m128i, __m128i, __m128i )
        vU32( 0x60000000, 0xC0000000, 0x80000001, 0x00000003 ),
        vU32( 0x80000001, 0x80000001, 0x80000001, 0x80000001 ),
        vS32(         -2,         -1,          0,          1 )); 

    TEST_028( ssp_rot_epi64, ssp_u64, __m128i, __m128i, __m128i )
        vU64( 0xC000000000000000, 0x0000000000000003 ),
        vU64( 0x8000000000000001, 0x8000000000000001 ),
        vS64(                 -1,                  1)); 

    TEST_028( ssp_roti_epi8, ssp_u8, __m128i, __m128i, int )
        vU8( 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 ),
        vU8( 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81 ),
        1); 

    TEST_028( ssp_roti_epi8, ssp_u8, __m128i, __m128i, int )
        vU8( 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0 ),
        vU8( 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81 ),
        -1); 

    TEST_028( ssp_roti_epi16, ssp_u16, __m128i, __m128i, int )
        vU16( 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003 ),
        vU16( 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001 ),
        1); 

    TEST_028( ssp_roti_epi16, ssp_u16, __m128i, __m128i, int )
        vU16( 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000 ),
        vU16( 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001 ),
        -1); 

    TEST_028( ssp_roti_epi32, ssp_u32, __m128i, __m128i, int )
        vU32( 0x00000003, 0x00000003, 0x00000003, 0x00000003 ),
        vU32( 0x80000001, 0x80000001, 0x80000001, 0x80000001 ),
        1); 

    TEST_028( ssp_roti_epi32, ssp_u32, __m128i, __m128i, int )
        vU32( 0xC0000000, 0xC0000000, 0xC0000000, 0xC0000000 ),
        vU32( 0x80000001, 0x80000001, 0x80000001, 0x80000001 ),
        -1); 

    TEST_028( ssp_roti_epi64, ssp_u64, __m128i, __m128i, int )
        vU64( 0x0000000000000003, 0x0000000000000003 ),
        vU64( 0x8000000000000001, 0x8000000000000001 ),
        1); 

    TEST_028( ssp_roti_epi64, ssp_u64, __m128i, __m128i, int )
        vU64( 0xC000000000000000, 0xC000000000000000 ),
        vU64( 0x8000000000000001, 0x8000000000000001 ),
        -1); 

    // Logical and arithmetic shifts
    TEST_028( ssp_shl_epi8, ssp_s8, __m128i, __m128i, __m128i )
        vS8( -20,   78, -50,  0, 0, 50,  50, 20, -20,   78, -50,  0, 0, 50,  50, 20 ),
        vS8( -10, -100, -25,  0, 0, 25, 100, 10, -10, -100, -25,  0, 0, 25, 100, 10 ), 
        vS8(   1,   -1,   1, -1, 1,  1,  -1,  1,   1,   -1,   1, -1, 1,  1,  -1,  1 ));

    TEST_028( ssp_sha_epi8, ssp_s8, __m128i, __m128i, __m128i )
        vS8( -20,  -50, -50,  0, 0, 50,  50, 20, -20,  -50, -50,  0, 0, 50,  50, 20 ),
        vS8( -10, -100, -25,  0, 0, 25, 100, 10, -10, -100, -25,  0, 0, 25, 100, 10 ), 
        vS8(   1,   -1,   1, -1, 1,  1,  -1,  1,   1,   -1,   1, -1, 1,  1,  -1,  1 ));

    TEST_028( ssp_shl_epi16, ssp_s16, __m128i, __m128i, __m128i )
        vS16( -200, 32718, -50, 0, 50, 12, 400,  25 ),
        vS16( -100,  -100, -25, 0, 25, 25, 100, 100 ), 
        vS16(    1,    -1,   1, 1,  1, -1,   2,  -2 ));

    TEST_028( ssp_sha_epi16, ssp_s16, __m128i, __m128i, __m128i )
        vS16( -200,  -50, -50, 0, 50, 12, 400,  25 ),
        vS16( -100, -100, -25, 0, 25, 25, 100, 100 ), 
        vS16(    1,   -1,   1, 1,  1, -1,   2,  -2 ));

    TEST_028( ssp_shl_epi32, ssp_s32, __m128i, __m128i, __m128i )
        vS32( -200000, 2147433648, 200000,  50000 ),
        vS32( -100000,    -100000, 100000, 100000 ),
        vS32(       1,         -1,      1,     -1 ));

    TEST_028( ssp_sha_epi32, ssp_s32, __m128i, __m128i, __m128i )
        vS32( -200000,  -50000,  200000,  50000 ),
        vS32( -100000, -100000,  100000, 100000 ),
        vS32(       1,      -1,       1,     -1 ));

    TEST_028( ssp_shl_epi64, ssp_s64, __m128i, __m128i, __m128i )
        vS64( -200, 0x7FFFFFFFFFFFFFCE ),
        vS64( -100,               -100 ),
        vS64(    1,                 -1 ));

    TEST_028( ssp_sha_epi64, ssp_s64, __m128i, __m128i, __m128i )
        vS64( -200,  -50 ),
        vS64( -100, -100 ),
        vS64(    1,   -1 ));

    // Comparison

     TEST_02( ssp_comlt_epu16, ssp_u16, __m128i, __m128i, __m128i) 
        vU16(0xFFFF,    0,0xFFFF,    0,0,0xFFFF,0,0 ), 
        vU16( 65534,65535, 32767,65535,1,     0,     1,     0 ),
        vU16( 65535,65534, 65535,32767,0,     1,     1,     0 )); 

    TEST_02( ssp_comgt_epu16, ssp_u16, __m128i, __m128i, __m128i) 
        vU16(     0,0xFFFF,    0,0xFFFF,0xFFFF,0,0,0 ), 
        vU16( 65534, 65535,32767, 65535,     1,0,     1,     0 ),
        vU16( 65535, 65534,65535, 32767,     0,1,     1,     0 )); 

    TEST_02( ssp_comlt_epu32, ssp_u16, __m128i, __m128i, __m128i) 
        vU32(0xFFFFFFFF,         0,0xFFFFFFFF,         0 ), 
        vU32(4294967294ll,4294967295ll,2147483647ll,4294967295ll ),
        vU32(4294967295ll,4294967294ll,4294967295ll,2147483647ll )); 

    TEST_02( ssp_comgt_epu32, ssp_u16, __m128i, __m128i, __m128i) 
        vU32(         0,0xFFFFFFFF,         0,0xFFFFFFFF ), 
        vU32(4294967294ll,4294967295ll,2147483647ll,4294967295ll ),
        vU32(4294967295ll,4294967294ll,4294967295ll,2147483647ll )); 



    TEST_02( ssp_comeq_epi16, ssp_u16, __m128i, __m128i, __m128i )
            vU16( 0xFFFF, 0, 0xFFFF, 0, 0, 0, 0, 0),
            vS16( -1234, 1111, 0, 124, 125, -124, -125, 100 ),
            vS16( -1234, 2222, 0, 0,   123, -123, -100, -100 ));

	TEST_02( ssp_comeq_epi32, ssp_u32, __m128i, __m128i, __m128i )
            vU32( 0xFFFFFFFF, 0, 0xFFFFFFFF, 0),
            vS32( -12345, 11, 0, 124678),
            vS32( -12345, 22, 0,     0));

	TEST_023( ssp_comeq_epi64, ssp_u64, __m128i, __m128i, __m128i )
            vU64( 0xFFFFFFFFFFFFFFFF, 0),
            vS64( -1234578901ll, 11),
            vS64( -1234578901ll, 22));

    TEST_02( ssp_comeq_epi8, ssp_u8, __m128i, __m128i, __m128i )
            vU8( 0xFF, 0, 0xFF, 0, 0, 0, 0, 0, 0xFF, 0, 0xFF, 0, 0, 0, 0, 0),
            vS8( -1, 11, 0, 124, 125, -124, -125,  100, 11, -11, 10, -124, -125, 124, 125, -100 ),
            vS8( -1, 22, 0,   0, 123, -123, -100, -100, 11, -22, 10,    0, -123, 123, 100,  100 ));

    TEST_02( ssp_comeq_epu16, ssp_u16, __m128i, __m128i, __m128i )
            vU16( 0xFFFF, 0, 0xFFFF, 0, 0, 0, 0, 0xFFFF),
            vU16( 1234, 1111, 0, 124, 125, 124, 125, 100 ),
            vU16( 1234, 2222, 0, 0,   123, 123, 100, 100 ));

	TEST_02( ssp_comeq_epu32, ssp_u32, __m128i, __m128i, __m128i )
            vU32( 0xFFFFFFFF, 0, 0xFFFFFFFF, 0),
            vU32( 12345, 11, 0, 124678),
            vU32( 12345, 22, 0,     0));

	TEST_02( ssp_comeq_epu64, ssp_u64, __m128i, __m128i, __m128i )
            vU64( 0xFFFFFFFFFFFFFFFF, 0),
            vU64( 1234578901ll, 11),
            vU64( 1234578901ll, 22));

    TEST_02( ssp_comeq_epu8, ssp_u8, __m128i, __m128i, __m128i )
            vU8( 0xFF, 0, 0xFF, 0, 0, 0, 0, 0xFF, 0xFF, 0, 0xFF, 0, 0, 0, 0, 0xFF),
            vU8( 1, 11, 0, 124, 125, 124, 125, 100, 11, 11, 10, 124, 125, 124, 125, 100 ),
            vU8( 1, 22, 0,   0, 123, 123, 100, 100, 11, 22, 10,   0, 123, 123, 100, 100 ));
 
	TEST_02( ssp_comneq_epi16, ssp_u16, __m128i, __m128i, __m128i )
            vU16(     0, 0xFFFF, 0, 0xFFFF,   0,    0, 0xFFFF,   0 ),
            vS16( -1234,   1111, 0,    124, 123, -123,   -125, 100 ),
            vS16( -1234,   2222, 0,      0, 123, -123,   -100, 100 ));

	TEST_02( ssp_comneq_epi32, ssp_u32, __m128i, __m128i, __m128i )
            vU32(      0, 0xFFFFFFFF, 0, 0xFFFFFFFF),
            vS32( -12345,         11, 0, 124678),
            vS32( -12345,         22, 0,     0));

	TEST_02( ssp_comneq_epi64, ssp_u64, __m128i, __m128i, __m128i )
            vU64( 0, 0xFFFFFFFFFFFFFFFF),
            vS64( -1234578901ll, 11),
            vS64( -1234578901ll, 22));

    TEST_02( ssp_comneq_epi8, ssp_u8, __m128i, __m128i, __m128i )
            vU8(  0, 0xFF, 0, 0xFF,  0,    0,    0, 0xFF,  0, 0xFF,  0, 0xFF,    0,   0,   0, 0xFF),
            vS8( -1,   11, 0, 124, 123, -123, -100,  100, 11,  -11, 10, -124, -123, 123, 100, -100 ),
            vS8( -1,   22, 0,   0, 123, -123, -100, -100, 11,  -22, 10,    0, -123, 123, 100,  100 ));

    TEST_02( ssp_comneq_epu16, ssp_u16, __m128i, __m128i, __m128i )
            vU16(    0, 0xFFFF, 0, 0xFFFF,   0,   0, 0xFFFF,   0 ),
            vU16( 1234,   1111, 0,    124, 125, 124,    125, 100 ),
            vU16( 1234,   2222, 0,      0, 125, 124,    100, 100 ));

	TEST_02( ssp_comneq_epu32, ssp_u32, __m128i, __m128i, __m128i )
            vU32( 0, 0xFFFFFFFF, 0, 0xFFFFFFFF),
            vU32( 12345, 11, 0, 124678),
            vU32( 12345, 22, 0,     0));

	TEST_02( ssp_comneq_epu64, ssp_u64, __m128i, __m128i, __m128i )
            vU64( 0, 0xFFFFFFFFFFFFFFFF),
            vU64( 1234578901ll, 11),
            vU64( 1234578901ll, 22));

    TEST_02( ssp_comneq_epu8, ssp_u8, __m128i, __m128i, __m128i )
            vU8( 0, 0xFF, 0, 0xFF,  0,   0,   0,   0, 0xFF, 0xFF,  0, 0xFF,  0,   0,   0, 0xFF),
            vU8( 1,   11, 0, 124, 125, 124, 125, 100,   12,   11, 10, 124, 125, 123, 100, 101 ),
            vU8( 1,   22, 0,   0, 125, 124, 125, 100,   11,   22, 10,   0, 125, 123, 100, 100 ));

	TEST_028( ssp_comfalse_epi16, ssp_u16, __m128i, __m128i, __m128i )
            vU16( 0, 0, 0, 0, 0, 0, 0, 0),
            vS16( -1234, 1111, 0, 124, 125, -124, -125, 100 ),
            vS16( -1234, 2222, 0, 0,   123, -123, -100, -100 ));

	TEST_028( ssp_comfalse_epi32, ssp_u32, __m128i, __m128i, __m128i )
            vU32( 0, 0, 0, 0),
            vS32( -12345, 11, 0, 124678),
            vS32( -12345, 22, 0,     0));

	TEST_028( ssp_comfalse_epi64, ssp_u64, __m128i, __m128i, __m128i )
            vU64( 0, 0),
            vS64( -1234578901ll, 11),
            vS64( -1234578901ll, 22));

    TEST_028( ssp_comfalse_epi8, ssp_u8, __m128i, __m128i, __m128i )
            vU8( 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
            vS8( -1, 11, 0, 124, 125, -124, -125,  100, 11, -11, 10, -124, -125, 124, 125, -100 ),
            vS8( -1, 22, 0,   0, 123, -123, -100, -100, 11, -22, 10,    0, -123, 123, 100,  100 ));

    TEST_028( ssp_comfalse_epu16, ssp_u16, __m128i, __m128i, __m128i )
            vU16( 0, 0, 0, 0, 0, 0, 0, 0),
            vU16( 1234, 1111, 0, 124, 125, 124, 125, 100 ),
            vU16( 1234, 2222, 0, 0,   123, 123, 100, 100 ));

	TEST_028( ssp_comfalse_epu32, ssp_u32, __m128i, __m128i, __m128i )
            vU32( 0, 0, 0, 0),
            vU32( 12345, 11, 0, 124678),
            vU32( 12345, 22, 0,     0));

	TEST_028( ssp_comfalse_epu64, ssp_u64, __m128i, __m128i, __m128i )
            vU64( 0, 0),
            vU64( 1234578901ll, 11),
            vU64( 1234578901ll, 22));

    TEST_028( ssp_comfalse_epu8, ssp_u8, __m128i, __m128i, __m128i )
            vU8( 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
            vU8( 1, 11, 0, 124, 125, 124, 125, 100, 11, 11, 10, 124, 125, 124, 125, 100 ),
            vU8( 1, 22, 0,   0, 123, 123, 100, 100, 11, 22, 10,   0, 123, 123, 100, 100 ));

	TEST_028( ssp_comtrue_epi16, ssp_u16, __m128i, __m128i, __m128i )
            vU16( 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff),
            vS16( -1234, 1111, 0, 124, 125, -124, -125, 100 ),
            vS16( -1234, 2222, 0, 0,   123, -123, -100, -100 ));

	TEST_028( ssp_comtrue_epi32, ssp_u32, __m128i, __m128i, __m128i )
            vU32( 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff),
            vS32( -12345, 11, 0, 124678),
            vS32( -12345, 22, 0,     0));

	TEST_028( ssp_comtrue_epi64, ssp_u64, __m128i, __m128i, __m128i )
            vU64( 0xffffffffffffffff, 0xffffffffffffffff),
            vS64( -1234578901ll, 11),
            vS64( -1234578901ll, 22));

    TEST_028( ssp_comtrue_epi8, ssp_u8, __m128i, __m128i, __m128i )
            vU8( 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff),
            vS8( -1, 11, 0, 124, 125, -124, -125,  100, 11, -11, 10, -124, -125, 124, 125, -100 ),
            vS8( -1, 22, 0,   0, 123, -123, -100, -100, 11, -22, 10,    0, -123, 123, 100,  100 ));

    TEST_028( ssp_comtrue_epu16, ssp_u16, __m128i, __m128i, __m128i )
            vU16( 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff),
            vU16( 1234, 1111, 0, 124, 125, 124, 125, 100 ),
            vU16( 1234, 2222, 0, 0,   123, 123, 100, 100 ));

	TEST_028( ssp_comtrue_epu32, ssp_u32, __m128i, __m128i, __m128i )
            vU32( 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff),
            vU32( 12345, 11, 0, 124678),
            vU32( 12345, 22, 0,     0));

	TEST_028( ssp_comtrue_epu64, ssp_u64, __m128i, __m128i, __m128i )
            vU64( 0xffffffffffffffff, 0xffffffffffffffff),
            vU64( 1234578901ll, 11),
            vU64( 1234578901ll, 22));

    TEST_028( ssp_comtrue_epu8, ssp_u8, __m128i, __m128i, __m128i )
            vU8( 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff),
            vU8( 1, 11, 0, 124, 125, 124, 125, 100, 11, 11, 10, 124, 125, 124, 125, 100 ),
            vU8( 1, 22, 0,   0, 123, 123, 100, 100, 11, 22, 10,   0, 123, 123, 100, 100 ));

	TEST_02( ssp_comge_epi16, ssp_u16, __m128i, __m128i, __m128i )
            vU16( 0xFFFF,   0, 0xFFFF, 0xFFFF,   0,    0,   0, 0xFFFF),
            vS16( -1234, 1111,      0,    124,  25, -124, -125,  100 ),
            vS16( -1234, 2222,      0,      0, 123, -123, -100, -100 ));

	TEST_02( ssp_comge_epi32, ssp_u32, __m128i, __m128i, __m128i )
            vU32( 0xFFFFFFFF,  0, 0xFFFFFFFF, 0xFFFFFFFF),
            vS32( -12345,     11,         0, 124678),
            vS32( -12345,     22,         0,     0));

	TEST_02( ssp_comge_epi64, ssp_u64, __m128i, __m128i, __m128i )
            vU64( 0xFFFFFFFFFFFFFFFF, 0),
            vS64( -1234578901ll, 11),
            vS64( -1234578901ll, 22));

    TEST_02( ssp_comge_epi8, ssp_u8, __m128i, __m128i, __m128i )
            vU8( 0xFF, 0, 0xFF, 0xFF, 0xFF,   0,     0, 0xFF, 0xFF,  0, 0xFF,   0,    0, 0xFF, 0xFF, 0),
            vS8( -1,  11,    0,  124,  125, -124, -125,  100,   11, -31, 10, -124, -125,  124,  125, -100 ),
            vS8( -1,  22,    0,    0,  123, -123, -100, -100,   11, -22, 10,    0, -123,  123,  100,  100 ));

    TEST_02( ssp_comge_epu16, ssp_u16, __m128i, __m128i, __m128i )
            vU16( 0xFFFF,  0, 0xFFFF, 0xFFFF, 0xFFFF, 0,     0, 0xFFFF),
            vU16( 1234, 1111,      0,    124,    125, 122,  25, 100 ),
            vU16( 1234, 2222,      0,      0,    123, 123, 100, 100 ));

	TEST_02( ssp_comge_epu32, ssp_u32, __m128i, __m128i, __m128i )
            vU32( 0xFFFFFFFF, 0, 0, 0xFFFFFFFF),
            vU32( 12345, 11, 0, 124678),
            vU32( 12345, 22, 1,     0));

	TEST_02( ssp_comge_epu64, ssp_u64, __m128i, __m128i, __m128i )
            vU64( 0xFFFFFFFFFFFFFFFF, 0),
            vU64( 1234578901ll, 11),
            vU64( 1234578901ll, 22));

    TEST_02( ssp_comge_epu8, ssp_u8, __m128i, __m128i, __m128i )
            vU8( 0xFF,  0, 0xFF,   0,   0,   0,   0, 0xFF, 0xFF,  0, 0xFF,  0,  0,   0,   0, 0xFF),
            vU8(    1, 11,    0, 124, 115, 114,  25,  100,   11, 11,   10, 24,  25,  24,  25, 100 ),
            vU8(    1, 22,    0, 127, 123, 123, 100,  100,   10, 22,   10, 30, 123, 123, 100, 100 ));

	TEST_02( ssp_comgt_epi16, ssp_u16, __m128i, __m128i, __m128i )
            vU16(     0,   0,    0, 0xFFFF,   0,    0,   0, 0xFFFF),
            vS16( -1234, 1111,   0,    124,  25, -124, -125,  100 ),
            vS16( -1234, 2222,   0,      0, 123, -123, -100, -100 ));

	TEST_02( ssp_comgt_epi32, ssp_u32, __m128i, __m128i, __m128i )
            vU32(     0,  0xFFFFFFFF, 0, 0xFFFFFFFF),
            vS32( -12345, 31,         0, 124678),
            vS32( -12345, 22,         0,     0));

	TEST_02( ssp_comgt_epi64, ssp_u64, __m128i, __m128i, __m128i )
            vU64( 0xFFFFFFFFFFFFFFFF, 0),
            vS64( -1234578901ll, 11),
            vS64( -1234578911ll, 22));

    TEST_02( ssp_comgt_epi8, ssp_u8, __m128i, __m128i, __m128i )
            vU8(  0,   0, 0, 0xFF, 0xFF,   0,     0, 0xFF, 0xFF,  0,   0,   0,    0, 0xFF, 0xFF, 0),
            vS8( -1,  11, 0,  124,  125, -124, -125,  100,   11, -31, 10, -124, -125,  124,  125, -100 ),
            vS8( -1,  22, 0,    0,  123, -123, -100, -100,   10, -22, 10,    0, -123,  123,  100,  100 ));

    TEST_02( ssp_comgt_epu16, ssp_u16, __m128i, __m128i, __m128i )
            vU16(    0,    0, 0xFFFF, 0xFFFF, 0xFFFF, 0,     0,   0 ),
            vU16( 1234, 1111,     10,    124,    125, 122,  25, 100 ),
            vU16( 1234, 2222,      0,      0,    123, 123, 100, 100 ));

	TEST_02( ssp_comgt_epu32, ssp_u32, __m128i, __m128i, __m128i )
            vU32( 0xFFFFFFFF, 0, 0, 0xFFFFFFFF),
            vU32( 12346, 11, 0, 124678),
            vU32( 12345, 22, 1,     0));

	TEST_02( ssp_comgt_epu64, ssp_u64, __m128i, __m128i, __m128i )
            vU64( 0, 0),
            vU64( 1234578901ll, 11),
            vU64( 1234578901ll, 22));

    TEST_02( ssp_comgt_epu8, ssp_u8, __m128i, __m128i, __m128i )
            vU8( 0,  0, 0xFF,   0,   0,   0,   0, 0xFF, 0xFF,  0,  0,  0,  0,   0,   0, 0xFF),
            vU8( 1, 11,   10, 124, 115, 114,  25,  111,   11, 11, 10, 24,  25,  24,  25, 101 ),
            vU8( 1, 22,    0, 127, 123, 123, 100,  100,   10, 22, 10, 30, 123, 123, 100, 100 ));
 
	TEST_02( ssp_comle_epi16, ssp_u16, __m128i, __m128i, __m128i )
            vU16( 0xFFFF, 0xFFFF, 0xFFFF,   0,   0, 0xFFFF,    0,    0 ),
            vS16( -1234,    1111,      0, 124, 125,   -124, -125,  100 ),
            vS16( -1234,    2222,      0,   0, 123,   -123, -127, -100 ));

	TEST_02( ssp_comle_epi32, ssp_u32, __m128i, __m128i, __m128i )
            vU32( 0xFFFFFFFF, 0xFFFFFFFF, 0, 0),
            vS32( -12345, 11, 1, 124678),
            vS32( -12345, 22, 0,     -1));

	TEST_02( ssp_comle_epi64, ssp_u64, __m128i, __m128i, __m128i )
            vU64( 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF),
            vS64( -1234578901ll, 11),
            vS64( -1234578901ll, 22));

    TEST_02( ssp_comle_epi8, ssp_u8, __m128i, __m128i, __m128i )
            vU8( 0xFF, 0xFF, 0xFF,   0,   0, 0xFF,    0,    0, 0xFF,   0, 0xFF, 0xFF,    0,   0,  0,  0xFF ),
            vS8(   -1,   11,    0, 124, 125, -124, -125,  100,   11, -11,   10, -124, -121, 124, 125, -100 ),
            vS8(   -1,   22,    0,   0, 123, -123, -127, -100,   11, -22,   10,    0, -123, 123, 100,  100 ));

    TEST_02( ssp_comle_epu16, ssp_u16, __m128i, __m128i, __m128i )
            vU16( 0xFFFF, 0xFFFF, 0xFFFF,   0,   0,   0,   0, 0xFFFF),
            vU16(   1234,   1111,      0, 124, 125, 124, 125, 100 ),
            vU16(   1234,   2222,      0,   0, 123, 123, 100, 100 ));

	TEST_02( ssp_comle_epu32, ssp_u32, __m128i, __m128i, __m128i )
            vU32( 0xFFFFFFFF, 0xFFFFFFFF, 0, 0),
            vU32( 12345, 11, 2, 124678),
            vU32( 12345, 22, 1,     0));

	TEST_02( ssp_comle_epu64, ssp_u64, __m128i, __m128i, __m128i )
            vU64( 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF),
            vU64( 1234578901ll, 11),
            vU64( 1234578901ll, 22));

    TEST_02( ssp_comle_epu8, ssp_u8, __m128i, __m128i, __m128i )
            vU8( 0xFF, 0xFF, 0xFF,   0,   0,   0,   0, 0xFF, 0xFF, 0xFF, 0xFF,   0,  0,    0,   0, 0xFF),
            vU8(    1,   11,    0, 124, 125, 124, 125,  100,   11,   11,   10, 124, 125, 124, 125, 100 ),
            vU8(    1,   22,    0,   0, 123, 123, 100,  100,   11,   22,   10,   0, 123, 123, 100, 100 ));
  
	TEST_02( ssp_comlt_epi16, ssp_u16, __m128i, __m128i, __m128i )
            vU16(     0, 0xFFFF, 0,   0,   0, 0xFFFF,    0,    0 ),
            vS16( -1234,   1111, 0, 124, 125,   -124, -125,  100 ),
            vS16( -1234,   2222, 0,   0, 123,   -123, -127, -100 ));

	TEST_02( ssp_comlt_epi32, ssp_u32, __m128i, __m128i, __m128i )
            vU32(      0, 0xFFFFFFFF, 0, 0),
            vS32( -12345, 11, 1, 124678),
            vS32( -12345, 22, 0,     -1));

	TEST_02( ssp_comlt_epi64, ssp_u64, __m128i, __m128i, __m128i )
            vU64( 0, 0xFFFFFFFFFFFFFFFF),
            vS64( -1234578901ll, 11),
            vS64( -1234578901ll, 22));

    TEST_02( ssp_comlt_epi8, ssp_u8, __m128i, __m128i, __m128i )
            vU8(  0, 0xFF, 0,   0,   0, 0xFF,    0,    0,  0,   0,  0, 0xFF,    0,   0,  0,  0xFF ),
            vS8( -1,   11, 0, 124, 125, -124, -125,  100, 11, -11, 10, -124, -121, 124, 125, -100 ),
            vS8( -1,   22, 0,   0, 123, -123, -127, -100, 11, -22, 10,    0, -123, 123, 100,  100 ));

    TEST_02( ssp_comlt_epu16, ssp_u16, __m128i, __m128i, __m128i )
            vU16(    0, 0xFFFF, 0,   0,   0,   0,   0,   0),
            vU16( 1234,   1111, 0, 124, 125, 124, 125, 100 ),
            vU16( 1234,   2222, 0,   0, 123, 123, 100, 100 ));

	TEST_02( ssp_comlt_epu32, ssp_u32, __m128i, __m128i, __m128i )
            vU32( 0, 0xFFFFFFFF, 0, 0),
            vU32( 12345, 11, 2, 124678),
            vU32( 12345, 22, 1,     0));

	TEST_02( ssp_comlt_epu64, ssp_u64, __m128i, __m128i, __m128i )
            vU64( 0, 0xFFFFFFFFFFFFFFFF),
            vU64( 1234578901ll, 11),
            vU64( 1234578901ll, 22));

    TEST_02( ssp_comlt_epu8, ssp_u8, __m128i, __m128i, __m128i )
            vU8( 0, 0xFF, 0,   0,   0,   0,   0,   0, 0xFF, 0xFF, 0xFF,   0,  0,    0,   0, 0  ),
            vU8( 1,   11, 0, 124, 125, 124, 125, 100,   11,   11,   10, 124, 125, 124, 125, 100 ),
            vU8( 1,   22, 0,   0, 123, 123, 100, 100,   12,   22,  100,   0, 123, 123, 100, 100 ));
 
	//for double precision comparison
	{
        long long   tmp    = 0xFFFFFFFFFFFFFFFF;
        double allF = *(double*)&tmp;

        tmp = 0x7FF8000100000000;
        double nan = *(double*)&tmp;

        TEST_02( ssp_comeq_pd, ssp_f64, __m128d, __m128d, __m128d )
            vF64(    allF,  0  ),
            vF64( -1.123456789,  nan ),
            vF64( -1.123456789,  nan ));
        
		TEST_02( ssp_comeq_sd, ssp_f64, __m128d, __m128d, __m128d )
            vF64( 0.12345,   allF  ),
            vF64( 0.12345, -1.123456789),
            vF64( nan,     -1.123456789));

        TEST_02( ssp_comlt_pd, ssp_f64, __m128d, __m128d, __m128d )
            vF64(       0,    0 ),
            vF64( -1.1234567, nan  ),
            vF64( -1.1234567, 1.0  ));

		TEST_02( ssp_comlt_sd, ssp_f64, __m128d, __m128d, __m128d )
            vF64( -1.1234567,   0 ),
            vF64( -1.1234567, nan  ),
            vF64( -1.1234567, 1.0  ));

        TEST_02( ssp_comle_pd, ssp_f64, __m128d, __m128d, __m128d )
            vF64(   allF,   0 ),
            vF64( -1.12345678, nan ),
            vF64( -1.12345678, nan ));
 
		TEST_02( ssp_comle_sd, ssp_f64, __m128d, __m128d, __m128d )
            vF64( -1.12345678,   0 ),
            vF64( -1.12345678, nan ),
            vF64( -1.12345678, nan ));

        TEST_02( ssp_comunord_pd, ssp_f64, __m128d, __m128d, __m128d )
            vF64(       0,   allF ),
            vF64( -1.123456,  nan ),
            vF64( -1.123789, 1.123 ));

        TEST_02( ssp_comunord_sd, ssp_f64, __m128d, __m128d, __m128d )
            vF64(  -1.123456, allF ),
            vF64( -1.123456,  nan ),
            vF64( -1.123789, 1.123 ));
         
        TEST_02( ssp_comneq_pd, ssp_f64, __m128d, __m128d, __m128d )
            vF64(       0,   allF ),
            vF64( -1.123456789, nan),
            vF64( -1.123456789, 1.123456789));
        
		TEST_02( ssp_comneq_sd, ssp_f64, __m128d, __m128d, __m128d )
            vF64( -1.123456789, allF ),
            vF64( -1.123456789, nan),
            vF64( -1.123456789, 1.123456789));

        TEST_02( ssp_comge_pd, ssp_f64, __m128d, __m128d, __m128d )
            vF64(allF,  0   ),
            vF64( 1.2,  1.1 ),
            vF64( 1.1,  nan ));
 
		TEST_02( ssp_comge_sd, ssp_f64, __m128d, __m128d, __m128d )
            vF64( 1.123456,      0 ),
            vF64( 1.123456, 1.0123 ),
            vF64( 1.223456,    nan ));

        TEST_02( ssp_comnle_pd, ssp_f64, __m128d, __m128d, __m128d )
            vF64(       0,     allF ),
            vF64( -1.123456,  1.123123 ),
            vF64( -1.123456,    nan ));

        TEST_02( ssp_comnle_sd, ssp_f64, __m128d, __m128d, __m128d )
            vF64( -1.123456,   allF ),
            vF64( -1.123456,  1.123123 ),
            vF64( -1.123456,    nan ));

        TEST_02( ssp_comord_pd, ssp_f64, __m128d, __m128d, __m128d )
            vF64(    allF,      0 ),
            vF64( -1.1234567, nan ),
            vF64( -1.1234567, nan ));

        TEST_02( ssp_comord_sd, ssp_f64, __m128d, __m128d, __m128d )
            vF64( -1.1234567,   0 ),
            vF64( -1.1234567, nan ),
            vF64( -1.1234567, nan ));

        TEST_02( ssp_comueq_pd, ssp_f64, __m128d, __m128d, __m128d )
            vF64(      allF,   allF ),
            vF64( -1.123456,    nan ),
            vF64( -1.123456, -1.122 ));

        TEST_02( ssp_comueq_sd, ssp_f64, __m128d, __m128d, __m128d )
            vF64( -1.123456,   allF ),
            vF64( -1.123456,    nan ),
            vF64( -1.123456, -1.122 ));
  
        TEST_02( ssp_comnge_pd, ssp_f64, __m128d, __m128d, __m128d )
            vF64(       0,   allF ),
            vF64( -1.123456, nan ),
            vF64( -1.123456,   0 ));       

        TEST_02( ssp_comnge_sd, ssp_f64, __m128d, __m128d, __m128d )
            vF64( -1.123456, allF ),
            vF64( -1.123456, nan ),
            vF64( -1.123456,   0 ));    

         TEST_02( ssp_comngt_pd, ssp_f64, __m128d, __m128d, __m128d )
            vF64(   allF,  allF ),
            vF64( -1.123456, 1.0 ),
            vF64( -1.123456, 1.0 ));

         TEST_02( ssp_comngt_sd, ssp_f64, __m128d, __m128d, __m128d )
            vF64( -1.123456, allF ),
            vF64( -1.123456, 1.0 ),
            vF64( -1.123456, 1.0 ));

         TEST_02( ssp_comfalse_pd, ssp_f64, __m128d, __m128d, __m128d )
            vF64(       0,   0   ),
            vF64( -11.1234,  nan ),
            vF64( -1.12356,  0   ));

		 TEST_02( ssp_comfalse_sd, ssp_f64, __m128d, __m128d, __m128d )
            vF64( -11.1234,   0   ),
            vF64( -11.1234,  nan ),
            vF64( -1.12356,  0   ));

         TEST_02( ssp_comoneq_pd, ssp_f64, __m128d, __m128d, __m128d )
            vF64(allF,    0),
            vF64(1.02345678, 1.0),
            vF64(1.12345678, nan));       

         TEST_02( ssp_comoneq_sd, ssp_f64, __m128d, __m128d, __m128d )
            vF64(1.02345678,   0),
            vF64(1.02345678, 1.0),
            vF64(1.12345678, nan));       

        TEST_02( ssp_comnlt_pd, ssp_f64, __m128d, __m128d, __m128d )
            vF64( allF,      allF ),
            vF64( 1.1234567, nan ),
            vF64( 1.0234567, 1.0 )); 

        TEST_02( ssp_comnlt_sd, ssp_f64, __m128d, __m128d, __m128d )
            vF64( 1.1234567, allF ),
            vF64( 1.1234567, nan  ),
            vF64( 1.0234567, 1.0  )); 

         TEST_02( ssp_comnlt_sd, ssp_f64, __m128d, __m128d, __m128d )
            vF64( 1.1234567, allF ),
            vF64( 1.1234567, 2.0  ),
            vF64( 1.0234567, 1.0  )); 

        TEST_02( ssp_comgt_pd, ssp_f64, __m128d, __m128d, __m128d )
            vF64(    allF,      0 ),
            vF64( -1.121456,  nan ),
            vF64( -1.123456,  1.0 )); 
 
		TEST_02( ssp_comgt_sd, ssp_f64, __m128d, __m128d, __m128d )
            vF64( -1.121456,    0 ),
            vF64( -1.121456,  nan ),
            vF64( -1.123456,  1.0 )); 

        TEST_02( ssp_comtrue_pd, ssp_f64, __m128d, __m128d, __m128d )
            vF64(       allF,  allF ),
            vF64( -1.12378901, nan  ),
            vF64( -1.12345678,   0  ));

        TEST_02( ssp_comtrue_sd, ssp_f64, __m128d, __m128d, __m128d )
            vF64( -1.12378901, allF ),
            vF64( -1.12378901, nan  ),
            vF64( -1.12345678,   0  ));
    }

	//for single precision comparison
    {
        int   tmp    = 0xFFFFFFFF;
        float allF = *(float*)&tmp;

        tmp = 0x7F800001;
        float nan = *(float*)&tmp;

        tmp = tmp = 0x7F800000;
        float inf = *(float*)&tmp;    

        TEST_02( ssp_comeq_ps, ssp_f32, __m128, __m128, __m128 )
            vF32(    allF,      0,   0, allF ),
            vF32( -1.123f, 1.123f, nan, inf  ),
            vF32( -1.123f, 1.124f, nan, inf  ));
 
		TEST_02( ssp_comeq_ss, ssp_f32, __m128, __m128, __m128 )
            vF32( -1.123f, 1.123f, 0.0f,  allF  ),
            vF32( -1.123f, 1.123f, 0.0f, -1.123f ),
            vF32( -1.123f, 1.124f, nan , -1.123f ));

        TEST_02( ssp_comlt_ps, ssp_f32, __m128, __m128, __m128 )
            vF32(       0, allF,    0,      0  ),
            vF32( -1.123f, 1.123f, 1.0f,  nan  ),
            vF32( -1.123f, 1.124f,  nan,  1.0f ));
 
		TEST_02( ssp_comlt_ss, ssp_f32, __m128, __m128, __m128 )
            vF32( -1.123f, 1.123f, 1.0f,    0  ),
            vF32( -1.123f, 1.123f, 1.0f,  nan  ),
            vF32( -1.123f, 1.124f,  nan,  1.0f ));

        TEST_02( ssp_comle_ps, ssp_f32, __m128, __m128, __m128 )
            vF32(    allF,   allF,    0,   0 ),
            vF32( -1.123f, 1.123f, 0.0f, nan ),
            vF32( -1.123f, 1.124f,  nan, nan ));

		TEST_02( ssp_comle_ss, ssp_f32, __m128, __m128, __m128 )
            vF32( -1.123f, 1.123f, 0.0f,   0 ),
            vF32( -1.123f, 1.123f, 0.0f, nan ),
            vF32( -1.123f, 1.124f,  nan, nan ));

        TEST_02( ssp_comunord_ps, ssp_f32, __m128, __m128, __m128 )
            vF32(       0,   allF, allF, allF ),
            vF32( -1.123f,    nan, 0.0f,  nan ),
            vF32( -1.123f, 1.123f,  nan,  nan ));

        TEST_02( ssp_comunord_ss, ssp_f32, __m128, __m128, __m128 )
            vF32( -1.123f,    nan, 0.0f, allF ),
            vF32( -1.123f,    nan, 0.0f,  nan ),
            vF32( -1.123f, 1.123f,  nan,  nan ));
        
        TEST_02( ssp_comneq_ps, ssp_f32, __m128, __m128, __m128 )
            vF32(       0,   allF,   allF, allF ),
            vF32( -1.123f, 1.121f,    nan, 1.0f ),
            vF32( -1.123f, 1.123f, 1.123f, nan  ));
 
		TEST_02( ssp_comneq_ss, ssp_f32, __m128, __m128, __m128 )
            vF32( -1.123f, 1.121f, nan, allF ),
            vF32( -1.123f, 1.121f, nan, 1.0f ),
            vF32( -1.123f, 1.123f, nan, 0.9f ));

        TEST_02( ssp_comge_ps, ssp_f32, __m128, __m128, __m128 )
            vF32(    0, allF,    0,    0 ),
            vF32( 1.1f, 1.2f,  nan, 1.0f ),
            vF32( 1.2f, 1.1f, 1.1f,  nan ));
 
		TEST_02( ssp_comge_ss, ssp_f32, __m128, __m128, __m128 )
            vF32( 1.1f, 1.2f,  nan, allF ),
            vF32( 1.1f, 1.2f,  nan, 1.0f ),
            vF32( 1.2f, 1.1f, 1.1f, 0.9f ));

        TEST_02( ssp_comnle_ps, ssp_f32, __m128, __m128, __m128 )
            vF32(       0,   allF,   allF,   allF ),
            vF32( -1.123f, 1.123f,    nan, 1.123f ),
            vF32( -1.123f, 1.121f, 1.123f,    nan ));

        TEST_02( ssp_comnle_ss, ssp_f32, __m128, __m128, __m128 )
            vF32( -1.123f, 1.123f,    nan,   allF ),
            vF32( -1.123f, 1.123f,    nan, 1.123f ),
            vF32( -1.123f, 1.121f, 1.123f,    nan ));

        TEST_02( ssp_comord_ps, ssp_f32, __m128, __m128, __m128 )
            vF32(    allF,      0,   0,   0 ),
            vF32( -1.123f,    nan,   0, nan ),
            vF32( -1.123f, 1.123f, nan, nan ));

        TEST_02( ssp_comord_ss, ssp_f32, __m128, __m128, __m128 )
            vF32( -1.123f,    nan,   0,   0 ),
            vF32( -1.123f,    nan,   0, nan ),
            vF32( -1.123f, 1.123f, nan, nan ));

        TEST_02( ssp_comueq_ps, ssp_f32, __m128, __m128, __m128 )
            vF32(    allF,      0, allF,    allF ),
            vF32( -1.123f, 1.121f, 0.0f,     nan ),
            vF32( -1.123f, 1.123f,  nan, -1.122f ));

        TEST_02( ssp_comueq_ss, ssp_f32, __m128, __m128, __m128 )
            vF32( -1.123f, 1.121f, 0.0f,    allF ),
            vF32( -1.123f, 1.121f, 0.0f,     nan ),
            vF32( -1.123f, 1.123f,  nan, -1.122f ));

        TEST_02( ssp_comnge_ps, ssp_f32, __m128, __m128, __m128 )
            vF32(       0,   allF, allF, allF ),
            vF32( -1.123f, 1.123f,    0,  nan ),
            vF32( -1.123f, 1.124f,  nan,    0 ));       

        TEST_02( ssp_comnge_ss, ssp_f32, __m128, __m128, __m128 )
            vF32( -1.123f, 1.123f,    0, allF ),
            vF32( -1.123f, 1.123f,    0,  nan ),
            vF32( -1.123f, 1.124f,  nan,    0 ));       

         TEST_02( ssp_comngt_ps, ssp_f32, __m128, __m128, __m128 )
            vF32(    allF,      0, allF, allF ),
            vF32( -1.123f, 1.124f, 0.0f,  nan ),
            vF32( -1.123f, 1.123f,  nan, 1.0f ));

         TEST_02( ssp_comngt_ss, ssp_f32, __m128, __m128, __m128 )
            vF32( -1.123f, 1.124f, 0.0f, allF ),
            vF32( -1.123f, 1.124f, 0.0f,  nan ),
            vF32( -1.123f, 1.123f,  nan, 1.0f ));

         TEST_02( ssp_comfalse_ps, ssp_f32, __m128, __m128, __m128 )
            vF32(       0,    0,   0, 0   ),
            vF32( -1.123f, 1.0f,   0, nan ),
            vF32( -1.123f, 1.1f, nan, 0   ));

		 TEST_02( ssp_comfalse_ss, ssp_f32, __m128, __m128, __m128 )
            vF32( -1.123f, 1.0f,  nan, 0   ),
            vF32( -1.123f, 1.0f,  nan, 100.1f ),
            vF32( -1.123f, 1.1f, nan, 0   ));

         TEST_02( ssp_comoneq_ps, ssp_f32, __m128, __m128, __m128 )
            vF32(       0, allF,    0,    0 ),
            vF32( -1.123f, 1.0f, 1.0f,  nan ),
            vF32( -1.123f, 1.1f,  nan, 1.0f ));       

         TEST_02( ssp_comoneq_ss, ssp_f32, __m128, __m128, __m128 )
            vF32( -1.123f, 1.0f, 1.0f,    0 ),
            vF32( -1.123f, 1.0f, 1.0f,  nan ),
            vF32( -1.123f, 1.1f,  nan, 1.0f ));       

        TEST_02( ssp_comnlt_ps, ssp_f32, __m128, __m128, __m128 )
            vF32(    0,   allF, allF, allF ),
            vF32( 1.0f, 1.121f, 1.0f,  nan ),
            vF32( 1.1f, 1.121f,  nan, 1.0f )); 

        TEST_02( ssp_comnlt_ss, ssp_f32, __m128, __m128, __m128 )
            vF32( 1.1f, 1.121f, 1.0f,  allF ),
            vF32( 1.1f, 1.121f, 1.0f,  nan ),
            vF32( 1.0f, 1.121f,  nan, 1.0f )); 

        TEST_02( ssp_comgt_ps, ssp_f32, __m128, __m128, __m128 )
            vF32(    allF,      0,    0,    0 ),
            vF32( -1.121f, 1.121f, 1.0f,  nan ),
            vF32( -1.123f, 1.123f,  nan, 1.0f )); 
  
		TEST_02( ssp_comgt_ss, ssp_f32, __m128, __m128, __m128 )
            vF32( -1.121f, 1.121f, 1.0f, allF ),
            vF32( -1.121f, 1.121f, 1.0f, 1.1f ),
            vF32( -1.123f, 1.123f,  nan, 1.0f )); 

        TEST_02( ssp_comtrue_ps, ssp_f32, __m128, __m128, __m128 )
            vF32(    allF, allF,allF, allF ),
            vF32( -1.123f, 1.0f,   0, nan  ),
            vF32( -1.123f, 1.1f, nan,   0  ));

        TEST_02( ssp_comtrue_ss, ssp_f32, __m128, __m128, __m128 )
            vF32( -1.123f, 1.0f,   0, allF ),
            vF32( -1.123f, 1.0f,   0, nan  ),
            vF32( -1.123f, 1.1f, nan,   0  ));
    }
}

void SSP_Tests( CSVTable & csv )
{
    TEST_023( ssp_arithmetic_hadd4_dup_ps, ssp_f32, __m128, __m128)
        vF32(6,6,6,6), 
        vF32(3,2,1,0) );    

    TEST_2( ssp_logical_bitwise_select, ssp_u32, __m128i, __m128i, __m128i, __m128i)  
        vU32(3,3,1,5), 
        vU32(3,2,1,0),
        vU32(2,3,4,5),
        vU32(0xFFFFFFFF,0,0xFFFFFFFF,0)); 

    /*    TEST_2( ssp_generate_mask_imm8_to_epi16, ssp_u16, __m128i, int)  
    vU16( 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0x0000, 0xFFFF), 
    0xA5);*/ 

    TEST_2( ssp_movmask_imm8_to_epi32, ssp_u32, __m128i, int )
        vU32( 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF ),
        0x5 );

    TEST_02( ssp_memory_load1_epu8, ssp_u8, __m128i, unsigned char )
        vU8( 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 ),
        3 );

    TEST_02( ssp_convert_reverse_transpose, ssp_u32, __m128i*, __m128i*, __m128i* )        
        obj_m128i( 3, 2, 1, 0 ).Address(),        
        obj_m128i( 7, 6, 5, 4 ).Address(),        
        obj_m128i( 11,10,9, 8 ).Address(),

        obj_m128i( 9 , 6, 3, 0 ).Address(),
        obj_m128i( 10, 7, 4, 1 ).Address(),
        obj_m128i( 11, 8, 5, 2 ).Address() );

    TEST_02( ssp_convert_3c_3p_epi8, ssp_u8, __m128i*, __m128i*, __m128i* )
        obj_m128i( 151,141,131,121,111,101, 91, 81, 71, 61, 51, 41, 31, 21, 11,  1 ).Address(),
        obj_m128i( 152,142,132,122,112,102, 92, 82, 72, 62, 52, 42, 32, 22, 12,  2 ).Address(),
        obj_m128i( 153,143,133,123,113,103, 93, 83, 73, 63, 53, 43, 33, 23, 13,  3 ).Address(),

        obj_m128i(  51, 43, 42, 41, 33, 32, 31, 23, 22, 21, 13, 12, 11,  3,  2,  1 ).Address(),        
        obj_m128i( 102,101, 93, 92, 91, 83, 82, 81, 73, 72, 71, 63, 62, 61, 53, 52 ).Address(),        
        obj_m128i( 153,152,151,143,142,141,133,132,131,123,122,121,113,112,111,103 ).Address() );    

    TEST_02( ssp_convert_3p_3c_epi8, ssp_u8, __m128i*, __m128i*, __m128i* )        
        obj_m128i(  51, 43, 42, 41, 33, 32, 31, 23, 22, 21, 13, 12, 11,  3,  2,  1 ).Address(),        
        obj_m128i( 102,101, 93, 92, 91, 83, 82, 81, 73, 72, 71, 63, 62, 61, 53, 52 ).Address(),        
        obj_m128i( 153,152,151,143,142,141,133,132,131,123,122,121,113,112,111,103 ).Address(),

        obj_m128i( 151,141,131,121,111,101, 91, 81, 71, 61, 51, 41, 31, 21, 11,  1 ).Address(),
        obj_m128i( 152,142,132,122,112,102, 92, 82, 72, 62, 52, 42, 32, 22, 12,  2 ).Address(),
        obj_m128i( 153,143,133,123,113,103, 93, 83, 73, 63, 53, 43, 33, 23, 13,  3 ).Address() );      

    TEST_02( ssp_convert_3c_3p_epi16, ssp_u16, __m128i*, __m128i*, __m128i* )
        obj_m128i( 10022, 10019, 10016, 10013, 10010, 10007, 10004, 10001 ).Address(),
        obj_m128i( 10023, 10020, 10017, 10014, 10011, 10008, 10005, 10002 ).Address(),
        obj_m128i( 10024, 10021, 10018, 10015, 10012, 10009, 10006, 10003 ).Address(),
																		  
        obj_m128i( 10008, 10007, 10006, 10005, 10004, 10003, 10002, 10001 ).Address(),
        obj_m128i( 10016, 10015, 10014, 10013, 10012, 10011, 10010, 10009 ).Address(),
        obj_m128i( 10024, 10023, 10022, 10021, 10020, 10019, 10018, 10017 ).Address() );

    TEST_02( ssp_convert_3p_3c_epi16, ssp_u16, __m128i*, __m128i*, __m128i* )
        obj_m128i( 10008, 10007, 10006, 10005, 10004, 10003, 10002, 10001 ).Address(),
        obj_m128i( 10016, 10015, 10014, 10013, 10012, 10011, 10010, 10009 ).Address(),
        obj_m128i( 10024, 10023, 10022, 10021, 10020, 10019, 10018, 10017 ).Address(),

        obj_m128i( 10022, 10019, 10016, 10013, 10010, 10007, 10004, 10001 ).Address(),
        obj_m128i( 10023, 10020, 10017, 10014, 10011, 10008, 10005, 10002 ).Address(),
        obj_m128i( 10024, 10021, 10018, 10015, 10012, 10009, 10006, 10003 ).Address() );

    TEST_02( ssp_convert_3c_3p_epi32, ssp_u32, __m128i*, __m128i*, __m128i* )
        obj_m128i( 1000010, 1000007, 1000004, 1000001 ).Address(),
        obj_m128i( 1000011, 1000008, 1000005, 1000002 ).Address(),
        obj_m128i( 1000012, 1000009, 1000006, 1000003 ).Address(),

        obj_m128i( 1000004, 1000003, 1000002, 1000001 ).Address(),
        obj_m128i( 1000008, 1000007, 1000006, 1000005 ).Address(),
        obj_m128i( 1000012, 1000011, 1000010, 1000009 ).Address() );

    TEST_02( ssp_convert_3p_3c_epi32, ssp_u32, __m128i*, __m128i*, __m128i* )
        obj_m128i( 1000004, 1000003, 1000002, 1000001 ).Address(),
        obj_m128i( 1000008, 1000007, 1000006, 1000005 ).Address(),
        obj_m128i( 1000012, 1000011, 1000010, 1000009 ).Address(),

        obj_m128i( 1000010, 1000007, 1000004, 1000001 ).Address(),
        obj_m128i( 1000011, 1000008, 1000005, 1000002 ).Address(),
        obj_m128i( 1000012, 1000009, 1000006, 1000003 ).Address() );

    TEST_02( ssp_convert_4c_4p_epi8, ssp_u8, __m128i*, __m128i*, __m128i*, __m128i* )
        obj_m128i( 151,141,131,121,111,101, 91, 81, 71, 61, 51, 41, 31, 21, 11,  1 ).Address(),
        obj_m128i( 152,142,132,122,112,102, 92, 82, 72, 62, 52, 42, 32, 22, 12,  2 ).Address(),
        obj_m128i( 153,143,133,123,113,103, 93, 83, 73, 63, 53, 43, 33, 23, 13,  3 ).Address(),
        obj_m128i( 154,144,134,124,114,104, 94, 84, 74, 64, 54, 44, 34, 24, 14,  4 ).Address(),

        obj_m128i(  34, 33, 32, 31, 24, 23, 22, 21, 14, 13, 12, 11,  4,  3,  2,  1 ).Address(),
        obj_m128i(  74, 73, 72, 71, 64, 63, 62, 61, 54, 53, 52, 51, 44, 43, 42, 41 ).Address(),
        obj_m128i( 114,113,112,111,104,103,102,101, 94, 93, 92, 91, 84, 83, 82, 81 ).Address(),
        obj_m128i( 154,153,152,151,144,143,142,141,134,133,132,131,124,123,122,121 ).Address() );

    TEST_02( ssp_convert_4p_4c_epi8, ssp_u8, __m128i*, __m128i*, __m128i*, __m128i* )
        obj_m128i(  34, 33, 32, 31, 24, 23, 22, 21, 14, 13, 12, 11,  4,  3,  2,  1 ).Address(),
        obj_m128i(  74, 73, 72, 71, 64, 63, 62, 61, 54, 53, 52, 51, 44, 43, 42, 41 ).Address(),
        obj_m128i( 114,113,112,111,104,103,102,101, 94, 93, 92, 91, 84, 83, 82, 81 ).Address(),
        obj_m128i( 154,153,152,151,144,143,142,141,134,133,132,131,124,123,122,121 ).Address(),

        obj_m128i( 151,141,131,121,111,101, 91, 81, 71, 61, 51, 41, 31, 21, 11,  1 ).Address(),
        obj_m128i( 152,142,132,122,112,102, 92, 82, 72, 62, 52, 42, 32, 22, 12,  2 ).Address(),
        obj_m128i( 153,143,133,123,113,103, 93, 83, 73, 63, 53, 43, 33, 23, 13,  3 ).Address(),
        obj_m128i( 154,144,134,124,114,104, 94, 84, 74, 64, 54, 44, 34, 24, 14,  4 ).Address() );

    TEST_02( ssp_convert_4c_4p_epi8, ssp_u8, __m128i*, __m128i*, __m128i*, __m128i* )
        obj_m128i( 151,141,131,121,111,101, 91, 81, 71, 61, 51, 41, 31, 21, 11,  1 ).Address(),
        obj_m128i( 152,142,132,122,112,102, 92, 82, 72, 62, 52, 42, 32, 22, 12,  2 ).Address(),
        obj_m128i( 153,143,133,123,113,103, 93, 83, 73, 63, 53, 43, 33, 23, 13,  3 ).Address(),
        obj_m128i( 154,144,134,124,114,104, 94, 84, 74, 64, 54, 44, 34, 24, 14,  4 ).Address(),

        obj_m128i(  34, 33, 32, 31, 24, 23, 22, 21, 14, 13, 12, 11,  4,  3,  2,  1 ).Address(),
        obj_m128i(  74, 73, 72, 71, 64, 63, 62, 61, 54, 53, 52, 51, 44, 43, 42, 41 ).Address(),
        obj_m128i( 114,113,112,111,104,103,102,101, 94, 93, 92, 91, 84, 83, 82, 81 ).Address(),
        obj_m128i( 154,153,152,151,144,143,142,141,134,133,132,131,124,123,122,121 ).Address() );

    TEST_02( ssp_convert_4p_4c_epi16, ssp_u16, __m128i*, __m128i*, __m128i*, __m128i* )
        obj_m128i(  14, 13, 12, 11,  4,  3,  2,  1 ).Address(),
        obj_m128i(  34, 33, 32, 31, 24, 23, 22, 21 ).Address(),
        obj_m128i(  54, 53, 52, 51, 44, 43, 42, 41 ).Address(),
        obj_m128i(  74, 73, 72, 71, 64, 63, 62, 61 ).Address(),

        obj_m128i(  71, 61, 51, 41, 31, 21, 11,  1 ).Address(),
        obj_m128i(  72, 62, 52, 42, 32, 22, 12,  2 ).Address(),
        obj_m128i(  73, 63, 53, 43, 33, 23, 13,  3 ).Address(),
        obj_m128i(  74, 64, 54, 44, 34, 24, 14,  4 ).Address() );

    TEST_02( ssp_convert_4c_4p_epi16, ssp_u16, __m128i*, __m128i*, __m128i*, __m128i* )
        obj_m128i(  71, 61, 51, 41, 31, 21, 11,  1 ).Address(),
        obj_m128i(  72, 62, 52, 42, 32, 22, 12,  2 ).Address(),
        obj_m128i(  73, 63, 53, 43, 33, 23, 13,  3 ).Address(),
        obj_m128i(  74, 64, 54, 44, 34, 24, 14,  4 ).Address(),

        obj_m128i(  14, 13, 12, 11,  4,  3,  2,  1 ).Address(),
        obj_m128i(  34, 33, 32, 31, 24, 23, 22, 21 ).Address(),
        obj_m128i(  54, 53, 52, 51, 44, 43, 42, 41 ).Address(),
        obj_m128i(  74, 73, 72, 71, 64, 63, 62, 61 ).Address() );

    TEST_02( ssp_convert_4p_4c_epi32, ssp_u32, __m128i*, __m128i*, __m128i*, __m128i* )
        obj_m128i(  4,  3,  2,  1  ).Address(),
        obj_m128i(  14, 13, 12, 11 ).Address(),
        obj_m128i(  24, 23, 22, 21 ).Address(),
        obj_m128i(  34, 33, 32, 31 ).Address(),

        obj_m128i(  31, 21, 11,  1 ).Address(),
        obj_m128i(  32, 22, 12,  2 ).Address(),
        obj_m128i(  33, 23, 13,  3 ).Address(),
        obj_m128i(  34, 24, 14,  4 ).Address() );

    TEST_02( ssp_convert_4c_4p_epi32, ssp_u32, __m128i*, __m128i*, __m128i*, __m128i* )
        obj_m128i(  31, 21, 11,  1 ).Address(),
        obj_m128i(  32, 22, 12,  2 ).Address(),
        obj_m128i(  33, 23, 13,  3 ).Address(),
        obj_m128i(  34, 24, 14,  4 ).Address(),

        obj_m128i(  4,  3,  2,  1  ).Address(),
        obj_m128i(  14, 13, 12, 11 ).Address(),
        obj_m128i(  24, 23, 22, 21 ).Address(),
        obj_m128i(  34, 33, 32, 31 ).Address() );

}


int main(int argc, char *argv[])
{
    std::string file = "../../fnData.csv";

    if( argc >= 2 )
        file = argv[1];

    if( 3   == argc && 
        !strcmp( "update", argv[2] ))
        g_update = true;
      
    CSVTable csv( file.c_str() );   

    PrintHeader();
    SSE3_Tests( csv );
    std::cout << std::endl;

    PrintHeader();
    SSSE3_Tests( csv );
    std::cout << std::endl;   

    PrintHeader();
    SSE4A_Tests( csv );
    std::cout << std::endl;

    PrintHeader();
    SSE4_1_Tests( csv );
    std::cout << std::endl;    

    PrintHeader();
    SSE5_Tests( csv );
    std::cout << std::endl;  

    PrintHeader();
    SSP_Tests( csv );

    std::cout << "\nUntested (SSE3 and above):\n";
    std::cout << csv.UnusedEntriesString( g_update ) << std::endl;    
    return 0;
}
