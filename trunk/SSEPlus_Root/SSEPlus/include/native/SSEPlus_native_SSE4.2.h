//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __SSEPLUS_NATIVE_SSE4_2_H__
#define __SSEPLUS_NATIVE_SSE4_2_H__

#include "../SSEPlus_base.h"
#include <nmmintrin.h>  // SSE4.2

/** @defgroup SSE42 SSE4.2 Optimized
 *  @{
 *  @name Native Instructions
 *  @{ */

/** \IMP{SSE4.2 Native,_mm_cmpestra,SSE4.2} */ 
SSP_FORCEINLINE int ssp_cmpestra_SSE4_2 ( __m128i a, int la, __m128i b, int lb, const int mode )
{
    switch( mode & 0xFF )
    {
        CASE_256( _mm_cmpestra, a, la, b, lb );
    }
}
/** \IMP{SSE4.2 Native,_mm_cmpestrc,SSE4.2} */ 
SSP_FORCEINLINE int ssp_cmpestrc_SSE4_2 ( __m128i a, int la, __m128i b, int lb, const int mode )
{
    switch( mode & 0xFF )
    {
        CASE_256( _mm_cmpestrc, a, la, b, lb );
    }
}
/** \IMP{SSE4.2 Native,_mm_cmpestri,SSE4.2} */ 
SSP_FORCEINLINE int ssp_cmpestri_SSE4_2 ( __m128i a, int la, __m128i b, int lb, const int mode )
{
    switch( mode & 0xFF )
    {
        CASE_256( _mm_cmpestri, a, la, b, lb );
    }
}
SSP_FORCEINLINE __m128i	ssp_cmpestrm_SSE4_2 ( __m128i a, int la, __m128i b, int lb, const int mode )
{
    switch( mode & 0xFF )
    {
        CASE_256( _mm_cmpestrm, a, la, b, lb );
    }
}
/** \IMP{SSE4.2 Native,_mm_cmpestro,SSE4.2} */ 
SSP_FORCEINLINE int ssp_cmpestro_SSE4_2 ( __m128i a, int la, __m128i b, int lb, const int mode )
{
    switch( mode & 0xFF )
    {
        CASE_256( _mm_cmpestro, a, la, b, lb );
    }
}
/** \IMP{SSE4.2 Native,_mm_cmpestrs,SSE4.2} */ 
SSP_FORCEINLINE int ssp_cmpestrs_SSE4_2 ( __m128i a, int la, __m128i b, int lb, const int mode )
{
    switch( mode & 0xFF)
    {
        CASE_256( _mm_cmpestrs, a, la, b, lb );
    }
}
/** \IMP{SSE4.2 Native,_mm_cmpestrz,SSE4.2} */ 
SSP_FORCEINLINE int ssp_cmpestrz_SSE4_2 ( __m128i a, int la, __m128i b, int lb, const int mode )
{
    switch( mode & 0xFF)
    {
        CASE_256( _mm_cmpestrz, a, la, b, lb );
    }
}
SSP_FORCEINLINE __m128i	ssp_cmpgt_epi64_SSE4_2 ( __m128i a, __m128i b )
{
    return _mm_cmpgt_epi64 ( a, b );
}
/** \IMP{SSE4.2 Native,_mm_cmpistra,SSE4.2} */ 
SSP_FORCEINLINE int ssp_cmpistra_SSE4_2 ( __m128i a, __m128i b, const int mode )
{
    switch( mode & 0xFF)
    {
        CASE_256( _mm_cmpistra, a, b );
    }
}
/** \IMP{SSE4.2 Native,_mm_cmpistrc,SSE4.2} */ 
SSP_FORCEINLINE int ssp_cmpistrc_SSE4_2 ( __m128i a, __m128i b, const int mode )
{
    switch( mode & 0xFF)
    {
        CASE_256( _mm_cmpistrc, a, b );
    }
}
/** \IMP{SSE4.2 Native,_mm_cmpistri,SSE4.2} */ 
SSP_FORCEINLINE int ssp_cmpistri_SSE4_2 ( __m128i a, __m128i b, const int mode )
{
    switch( mode & 0xFF)
    {
        CASE_256( _mm_cmpistri, a, b );
    }
}
SSP_FORCEINLINE __m128i	ssp_cmpistrm_SSE4_2 ( __m128i a, __m128i b, const int mode )
{
    switch( mode & 0xFF)
    {
        CASE_256( _mm_cmpistrm	, a, b );
    }
}
/** \IMP{SSE4.2 Native,_mm_cmpistro,SSE4.2} */ 
SSP_FORCEINLINE int ssp_cmpistro_SSE4_2 ( __m128i a, __m128i b, const int mode )
{
    switch( mode & 0xFF)
    {
        CASE_256( _mm_cmpistro, a, b );
    }
}
/** \IMP{SSE4.2 Native,_mm_cmpistrs,SSE4.2} */ 
SSP_FORCEINLINE int ssp_cmpistrs_SSE4_2 ( __m128i a, __m128i b, const int mode )
{
    switch( mode & 0xFF)
    {
        CASE_256( _mm_cmpistrs, a, b );
    }
}
/** \IMP{SSE4.2 Native,_mm_cmpistrz,SSE4.2} */ 
SSP_FORCEINLINE int ssp_cmpistrz_SSE4_2 ( __m128i a, __m128i b, const int mode )
{
    switch( mode & 0xFF)
    {
        CASE_256( _mm_cmpistrz, a, b );
    }
}
SSP_FORCEINLINE unsigned int ssp_crc32_u16_SSE4_2 ( unsigned int crc, unsigned short   v )
{
    return _mm_crc32_u16( crc, v );
}
SSP_FORCEINLINE unsigned int ssp_crc32_u32_SSE4_2 ( unsigned int crc, unsigned int     v )
{
    return _mm_crc32_u32( crc, v );
}

#ifdef SYS64
SSP_FORCEINLINE ssp_u64 ssp_crc32_u64_SSE4_2 ( unsigned int crc, ssp_u64 v )
{
    return _mm_crc32_u64( crc, v );
}
#endif

SSP_FORCEINLINE unsigned int ssp_crc32_u8_SSE4_2 ( unsigned int crc, unsigned char    v )
{
    return _mm_crc32_u8( crc, v );
}
/** \IMP{SSE4.2 Native,_mm_popcnt_u32,SSE4.2} */ 
SSP_FORCEINLINE int ssp_popcnt_u32_SSE4_2 ( unsigned int a     )
{
    return _mm_popcnt_u32( a );
}
#ifdef SYS64
/** \IMP{SSE4.2 Native,_mm_popcnt_u64,SSE4.2} */ 
SSP_FORCEINLINE int ssp_popcnt_u64_SSE4_2 ( ssp_u64 a )
{
    return _mm_popcnt_u64( a );
}
#endif 

//@}
//@}

#endif // __SSEPLUS_NATIVE_SSE4_2_H__
