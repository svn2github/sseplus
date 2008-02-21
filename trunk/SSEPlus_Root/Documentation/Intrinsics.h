//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
// SSEn	    VS 2005	        VS 2008	        GCC
// MMX	    mmintrin.h	    mmintrin.h	    mmintrin.h
// SSE	    xmmintrin.h	    xmmintrin.h	    xmmintrin.h
// SSE2	    emmintrin.h	    emmintrin.h	    emmintrin.h
// SSE3	    intrin.h	    intrin.h	    pmmintrin.h
// SSSE3		            tmmintrin.h	    tmmintrin.h
// SSE4A		            intrin.h	    ammintrin.h
// SSE4.1		            smmintrin.h	    smmintrin.h
// SSE4.2		            nmmintrin.h	    nmmintrin.h
// SSE5			            bmmintrin.h

  
__m128              _mm_addsub_ps           (__m128 a, __m128 b);                                       // SSE3
__m128              _mm_hadd_ps             (__m128 a, __m128 b);                                       // SSE3
__m128              _mm_hsub_ps             (__m128 a, __m128 b);                                       // SSE3
__m128              _mm_movehdup_ps         (__m128 a);                                                 // SSE3
__m128              _mm_moveldup_ps         (__m128 a);                                                 // SSE3
__m128d             _mm_addsub_pd           (__m128d a, __m128d b);                                     // SSE3
__m128d             _mm_hadd_pd             (__m128d a, __m128d b);                                     // SSE3
__m128d             _mm_hsub_pd             (__m128d a, __m128d b);                                     // SSE3
__m128d             _mm_loaddup_pd          (double const * dp);                                        // SSE3
__m128d             _mm_movedup_pd          (__m128d a);                                                // SSE3
__m128i             _mm_lddqu_si128         (__m128i const *p);                                         // SSE3   
__m128i             _mm_hadd_epi16          (__m128i a, __m128i b);                                     // SSSE3
__m128i             _mm_hadd_epi32          (__m128i a, __m128i b);                                     // SSSE3
__m128i             _mm_hadds_epi16         (__m128i a, __m128i b);                                     // SSSE3
__m64               _mm_hadd_pi16           (__m64 a, __m64 b);                                         // SSSE3
__m64               _mm_hadd_pi32           (__m64 a, __m64 b);                                         // SSSE3
__m64               _mm_hadds_pi16          (__m64 a, __m64 b);                                         // SSSE3 
__m128i             _mm_hsub_epi16          (__m128i a, __m128i b);                                     // SSSE3
__m128i             _mm_hsub_epi32          (__m128i a, __m128i b);                                     // SSSE3
__m128i             _mm_hsubs_epi16         (__m128i a, __m128i b);                                     // SSSE3
__m64               _mm_hsub_pi16           (__m64 a, __m64 b);                                         // SSSE3
__m64               _mm_hsub_pi32           (__m64 a, __m64 b);                                         // SSSE3
__m64               _mm_hsubs_pi16          (__m64 a, __m64 b);                                         // SSSE3
__m128i             _mm_maddubs_epi16       (__m128i a, __m128i b);                                     // SSSE3
__m64               _mm_maddubs_pi16        (__m64 a, __m64 b);                                         // SSSE3
__m128i             _mm_mulhrs_epi16        (__m128i a, __m128i b);                                     // SSSE3
__m64               _mm_mulhrs_pi16         (__m64 a, __m64 b);                                         // SSSE3
__m128i             _mm_shuffle_epi8        (__m128i a, __m128i b);                                     // SSSE3    
__m64               _mm_shuffle_pi8         (__m64 a, __m64 b);                                         // SSSE3    
__m128i             _mm_sign_epi8           (__m128i a, __m128i b);                                     // SSSE3
__m128i             _mm_sign_epi16          (__m128i a, __m128i b);                                     // SSSE3
__m128i             _mm_sign_epi32          (__m128i a, __m128i b);                                     // SSSE3
__m64               _mm_sign_pi8            (__m64 a, __m64 b);                                         // SSSE3
__m64               _mm_sign_pi16           (__m64 a, __m64 b);                                         // SSSE3
__m64               _mm_sign_pi32           (__m64 a, __m64 b);                                         // SSSE3
__m128i             _mm_alignr_epi8         (__m128i a, __m128i b, int n);                              // SSSE3
__m64               _mm_alignr_pi8          (__m64 a, __m64 b, int n);                                  // SSSE3
__m128i             _mm_abs_epi8            (__m128i a);                                                // SSSE3
__m128i             _mm_abs_epi16           (__m128i a);                                                // SSSE3
__m128i             _mm_abs_epi32           (__m128i a);                                                // SSSE3
__m64               _mm_abs_pi8             (__m64 a);                                                  // SSSE3
__m64               _mm_abs_pi16            (__m64 a);                                                  // SSSE3
__m64               _mm_abs_pi32            (__m64 a);                                                  // SSSE3
__m128i             _mm_extract_si64        (__m128i,__m128i);                                          // SSE4a
__m128i             _mm_extracti_si64       (__m128i, int, int);                                        // SSE4a
__m128i             _mm_insert_si64         (__m128i,__m128i);                                          // SSE4a
__m128i             _mm_inserti_si64        (__m128i, __m128i, int, int);                               // SSE4a
void                _mm_stream_sd           (double*,__m128d);                                          // SSE4a
void                _mm_stream_ss           (float*,__m128);                                            // SSE4a
__m128i             _mm_blend_epi16         ( __m128i v1, __m128i v2, const int mask );                 // SSE4.1
__m128d             _mm_blend_pd            ( __m128d v1, __m128d v2, const int mask );                 // SSE4.1
__m128              _mm_blend_ps            ( __m128  v1, __m128  v2, const int mask );                 // SSE4.1
__m128i             _mm_blendv_epi8         ( __m128i v1, __m128i v2, __m128i   mask );                 // SSE4.1
__m128d             _mm_blendv_pd           ( __m128d v1, __m128d v2, __m128d   mask );                 // SSE4.1
__m128              _mm_blendv_ps           ( __m128  v1, __m128  v2, __m128    mask );                 // SSE4.1 
__m128d             _mm_ceil_pd             ( __m128d a );                                              // SSE4.1
__m128              _mm_ceil_ps             ( __m128  a );                                              // SSE4.1
__m128d             _mm_ceil_sd             ( __m128d a, __m128d b);                                    // SSE4.1
__m128              _mm_ceil_ss             ( __m128  a, __m128  b);                                    // SSE4.1
__m128d             _mm_floor_pd            ( __m128d a );                                              // SSE4.1
__m128              _mm_floor_ps            ( __m128  a );                                              // SSE4.1
__m128d             _mm_floor_sd            ( __m128d a, __m128d b);                                    // SSE4.1
__m128              _mm_floor_ss            ( __m128  a, __m128  b);                                    // SSE4.1
__m128d             _mm_round_pd            ( __m128d val, int iRoundMode );                            // SSE4.1
__m128              _mm_round_ps            ( __m128  val, int iRoundMode );                            // SSE4.1
__m128d             _mm_round_sd            ( __m128d dst, __m128d val, int iRoundMode );               // SSE4.1
__m128              _mm_round_ss            ( __m128  dst, __m128  val, int iRoundMode );               // SSE4.1
__m128i             _mm_cmpeq_epi64         (__m128i val1, __m128i val2);                               // SSE4.1   
__m128i             _mm_cvtepi8_epi16       ( __m128i byteValues  );                                    // SSE4.1
__m128i             _mm_cvtepi8_epi32       ( __m128i byteValues  );                                    // SSE4.1
__m128i             _mm_cvtepi8_epi64       ( __m128i byteValues  );                                    // SSE4.1 
__m128i             _mm_cvtepi16_epi32      ( __m128i shortValues );                                    // SSE4.1
__m128i             _mm_cvtepi16_epi64      ( __m128i shortValues );                                    // SSE4.1
__m128i             _mm_cvtepi32_epi64      ( __m128i intValues   );                                    // SSE4.1
__m128i             _mm_cvtepu8_epi16       ( __m128i byteValues  );                                    // SSE4.1
__m128i             _mm_cvtepu8_epi32       ( __m128i byteValues  );                                    // SSE4.1
__m128i             _mm_cvtepu8_epi64       ( __m128i shortValues );                                    // SSE4.1
__m128i             _mm_cvtepu16_epi32      ( __m128i shortValues );                                    // SSE4.1
__m128i             _mm_cvtepu16_epi64      ( __m128i shortValues );                                    // SSE4.1
__m128i             _mm_cvtepu32_epi64      ( __m128i intValues   );                                    // SSE4.1
__m128i             _mm_packus_epi32        ( __m128i val1, __m128i val2);                              // SSE4.1   
__m128d             _mm_dp_pd               ( __m128d val1, __m128d val2, const int mask );             // SSE4.1
__m128              _mm_dp_ps               ( __m128  val1, __m128  val2, const int mask );             // SSE4.1
__m128i             _mm_mpsadbw_epu8        ( __m128i s1,   __m128i s2,   const int msk  );             // SSE4.1
__m128i             _mm_mul_epi32           ( __m128i a,    __m128i b );                                // SSE4.1
__m128i             _mm_mullo_epi32         ( __m128i a,    __m128i b );                                // SSE4.1  
int                 _mm_extract_epi8        ( __m128i src, const int ndx );                             // SSE4.1
int                 _mm_extract_epi32       ( __m128i src, const int ndx );                             // SSE4.1
__int64             _mm_extract_epi64       ( __m128i src, const int ndx );                             // SSE4.1
int                 _mm_extract_ps          ( __m128  src, const int ndx );                             // SSE4.1   
__m128i             _mm_insert_epi8         ( __m128i dst,      int s, const int ndx );                 // SSE4.1
__m128i             _mm_insert_epi32        ( __m128i dst,      int s, const int ndx );                 // SSE4.1
__m128i             _mm_insert_epi64        ( __m128i dst, __int64  s, const int ndx );                 // SSE4.1
__m128              _mm_insert_ps           ( __m128  dst, __m128 src, const int ndx );                 // SSE4.1
__m128i             _mm_max_epi8            ( __m128i val1, __m128i val2 );                             // SSE4.1
__m128i             _mm_max_epi32           ( __m128i val1, __m128i val2 );                             // SSE4.1
__m128i             _mm_max_epu16           ( __m128i val1, __m128i val2 );                             // SSE4.1
__m128i             _mm_max_epu32           ( __m128i val1, __m128i val2 );                             // SSE4.1
__m128i             _mm_min_epi8            ( __m128i val1, __m128i val2 );                             // SSE4.1
__m128i             _mm_min_epi32           ( __m128i val1, __m128i val2 );                             // SSE4.1
__m128i             _mm_min_epu16           ( __m128i val1, __m128i val2 );                             // SSE4.1
__m128i             _mm_min_epu32           ( __m128i val1, __m128i val2 );                             // SSE4.1
__m128i             _mm_minpos_epu16        ( __m128i shortValues );                                    // SSE4.1
 __m128i            _mm_stream_load_si128   ( __m128i* v1);                                             // SSE4.1 
int                 _mm_testc_si128         ( __m128i mask, __m128i val );                              // SSE4.1
int                 _mm_testnzc_si128       ( __m128i mask, __m128i s2  );                              // SSE4.1
int                 _mm_testz_si128         ( __m128i mask, __m128i val );                              // SSE4.1
int                 _mm_cmpestra            ( __m128i a, int la, __m128i b, int lb, const int mode );   // SSE4.2
int                 _mm_cmpestrc            ( __m128i a, int la, __m128i b, int lb, const int mode );   // SSE4.2 
int                 _mm_cmpestri            ( __m128i a, int la, __m128i b, int lb, const int mode );   // SSE4.2 
__m128i             _mm_cmpestrm            ( __m128i a, int la, __m128i b, int lb, const int mode );   // SSE4.2 
int                 _mm_cmpestro            ( __m128i a, int la, __m128i b, int lb, const int mode );   // SSE4.2 
int                 _mm_cmpestrs            ( __m128i a, int la, __m128i b, int lb, const int mode );   // SSE4.2 
int                 _mm_cmpestrz            ( __m128i a, int la, __m128i b, int lb, const int mode );   // SSE4.2 
__m128i             _mm_cmpgt_epi64         ( __m128i a, __m128i b );                                   // SSE4.2
int                 _mm_cmpistra            ( __m128i a, __m128i b, const int mode );                   // SSE4.2
int                 _mm_cmpistrc            ( __m128i a, __m128i b, const int mode );                   // SSE4.2 
int                 _mm_cmpistri            ( __m128i a, __m128i b, const int mode );                   // SSE4.2
__m128i             _mm_cmpistrm            ( __m128i a, __m128i b, const int mode );                   // SSE4.2 
int                 _mm_cmpistro            ( __m128i a, __m128i b, const int mode );                   // SSE4.2
int                 _mm_cmpistrs            ( __m128i a, __m128i b, const int mode );                   // SSE4.2 
int                 _mm_cmpistrz            ( __m128i a, __m128i b, const int mode );                   // SSE4.2    
unsigned int        _mm_crc32_u8            ( unsigned int crc, unsigned char    v );                   // SSE4.2 
unsigned int        _mm_crc32_u16           ( unsigned int crc, unsigned short   v );                   // SSE4.2
unsigned int        _mm_crc32_u32           ( unsigned int crc, unsigned int     v );                   // SSE4.2 
unsigned __int64    _mm_crc32_u64           ( unsigned int crc, unsigned __int64 v );                   // SSE4.2   
int                 _mm_popcnt_u32          ( unsigned int a     );                                     // SSE4.2
int                 _mm_popcnt_u64          ( unsigned __int64 a );                                     // SSE4.2