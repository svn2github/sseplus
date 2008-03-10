//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __SSEPLUS_NATIVE_SSE5_H__
#define __SSEPLUS_NATIVE_SSE5_H__

#include "../SSEPlus_base.h"

#include SSP_INCLUDE_FILE_SSE5
#include SSP_INCLUDE_FILE_SSE4_1_SSE5

/** @defgroup SSE5 SSE5 Optimized
 * @{
 * @name Native Instructions
 * @{ */

/** \IMP{SSE5 Native,_mm_macc_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_macc_ps_SSE5(__m128 a, __m128 b, __m128 c)
{
    return _mm_macc_ps( a, b, c);
}

/** \IMP{SSE5 Native,_mm_macc_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_macc_pd_SSE5(__m128d a, __m128d b, __m128d c)
{
    return _mm_macc_pd(a, b, c);
}

/** \IMP{SSE5 Native,_mm_macc_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_macc_ss_SSE5(__m128 a, __m128 b, __m128 c)
{
    return _mm_macc_ss(a, b, c);
}

/** \IMP{SSE5 Native,_mm_macc_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_macc_sd_SSE5(__m128d a, __m128d b, __m128d c)
{
    return _mm_macc_sd (a, b, c);
}

/** \IMP{SSE5 Native,_mm_msub_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_msub_ps_SSE5(__m128 a, __m128 b, __m128 c)
{
    return _mm_msub_ps (a, b, c);
}

/** \IMP{SSE5 Native,_mm_msub_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_msub_pd_SSE5(__m128d a, __m128d b, __m128d c)
{
    return _mm_msub_pd (a, b, c);
}

/** \IMP{SSE5 Native,_mm_msub_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_msub_ss_SSE5(__m128 a, __m128 b, __m128 c)
{
    return _mm_msub_ss (a, b, c);
}

/** \IMP{SSE5 Native,_mm_msub_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_msub_sd_SSE5(__m128d a, __m128d b, __m128d c)
{
    return _mm_msub_sd (a, b, c);
}

/** \IMP{SSE5 Native,_mm_nmacc_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_nmacc_ps_SSE5(__m128 a, __m128 b, __m128 c)
{
    return _mm_nmacc_ps (a, b, c);
}

/** \IMP{SSE5 Native,_mm_nmacc_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_nmacc_pd_SSE5(__m128d a, __m128d b, __m128d c)
{
    return _mm_nmacc_pd (a, b, c);
}

/** \IMP{SSE5 Native,_mm_nmacc_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_nmacc_ss_SSE5(__m128 a, __m128 b, __m128 c)
{
    return _mm_nmacc_ss (a, b, c);
}

/** \IMP{SSE5 Native,_mm_nmacc_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_nmacc_sd_SSE5(__m128d a, __m128d b, __m128d c)
{
    return _mm_nmacc_sd (a, b, c);
}

/** \IMP{SSE5 Native,_mm_nmsub_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_nmsub_ps_SSE5(__m128 a, __m128 b, __m128 c)
{
    return _mm_nmsub_ps (a, b, c);
}

/** \IMP{SSE5 Native,_mm_nmsub_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_nmsub_pd_SSE5(__m128d a, __m128d b, __m128d c)
{
    return _mm_nmsub_pd (a, b, c);
}

/** \IMP{SSE5 Native,_mm_nmsub_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_nmsub_ss_SSE5(__m128 a, __m128 b, __m128 c)
{
    return _mm_nmsub_ss (a, b, c);
}

/** \IMP{SSE5 Native,_mm_nmsub_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_nmsub_sd_SSE5(__m128d a, __m128d b, __m128d c)
{
    return _mm_nmsub_sd (a, b, c);
}

/** \IMP{SSE5 Native,_mm_maccs_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_maccs_epi16_SSE5(__m128i a, __m128i b, __m128i c)
{
    return _mm_maccs_epi16 (a,b, c);
}

/** \IMP{SSE5 Native,_mm_macc_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_macc_epi16_SSE5(__m128i a, __m128i b, __m128i c)
{
    return _mm_macc_epi16 (a, b, c);
}

/** \IMP{SSE5 Native,_mm_maccsd_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_maccsd_epi16_SSE5(__m128i a, __m128i b, __m128i c)
{
    return _mm_maccsd_epi16 (a, b, c);
}

/** \IMP{SSE5 Native,_mm_maccd_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_maccd_epi16_SSE5(__m128i a, __m128i b, __m128i c)
{
    return _mm_maccd_epi16 (a, b, c);
}

/** \IMP{SSE5 Native,_mm_maccs_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_maccs_epi32_SSE5(__m128i a, __m128i b, __m128i c)
{
    return _mm_maccs_epi32 (a, b, c);
}

/** \IMP{SSE5 Native,_mm_macc_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_macc_epi32_SSE5(__m128i a, __m128i b, __m128i c)
{
    return _mm_macc_epi32 (a, b, c);
}

/** \IMP{SSE5 Native,_mm_maccslo_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_maccslo_epi32_SSE5(__m128i a, __m128i b, __m128i c)
{
    return _mm_maccslo_epi32 (a, b, c);
}

/** \IMP{SSE5 Native,_mm_macclo_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_macclo_epi32_SSE5(__m128i a, __m128i b, __m128i c)
{
    return _mm_macclo_epi32 (a, b, c);
}

/** \IMP{SSE5 Native,_mm_maccshi_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_maccshi_epi32_SSE5(__m128i a, __m128i b, __m128i c)
{
    return _mm_maccshi_epi32 (a, b, c);
}

/** \IMP{SSE5 Native,_mm_macchi_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_macchi_epi32_SSE5(__m128i a, __m128i b, __m128i c)
{
    return _mm_macchi_epi32 (a, b, c);
}

/** \IMP{SSE5 Native,_mm_maddsd_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_maddsd_epi16_SSE5(__m128i a, __m128i b, __m128i c)
{
    return _mm_maddsd_epi16 (a,b,c);
}

/** \IMP{SSE5 Native,_mm_maddd_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_maddd_epi16_SSE5(__m128i a, __m128i b, __m128i c)
{
    return _mm_maddd_epi16 (a,b,c);
}

/** \IMP{SSE5 Native,_mm_haddw_epi8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_haddw_epi8_SSE5(__m128i a)
{
    return _mm_haddw_epi8 (a);
}

/** \IMP{SSE5 Native,_mm_haddd_epi8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_haddd_epi8_SSE5(__m128i a)
{
    return _mm_haddd_epi8 (a);
}

/** \IMP{SSE5 Native,_mm_haddq_epi8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_haddq_epi8_SSE5(__m128i a)
{
    return _mm_haddq_epi8 (a);
}

/** \IMP{SSE5 Native,_mm_haddd_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_haddd_epi16_SSE5(__m128i a)
{
    return _mm_haddd_epi16 (a);
}

/** \IMP{SSE5 Native,_mm_haddq_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_haddq_epi16_SSE5(__m128i a)
{
    return _mm_haddq_epi16 (a);
}

/** \IMP{SSE5 Native,_mm_haddq_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_haddq_epi32_SSE5(__m128i a)
{
    return _mm_haddq_epi32 (a);
}

/** \IMP{SSE5 Native,_mm_haddw_epu8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_haddw_epu8_SSE5(__m128i a)
{
    return _mm_haddw_epu8 (a);
}

/** \IMP{SSE5 Native,_mm_haddd_epu8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_haddd_epu8_SSE5(__m128i a)
{
    return _mm_haddd_epu8 (a);
}

/** \IMP{SSE5 Native,_mm_haddq_epu8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_haddq_epu8_SSE5(__m128i a)
{
    return _mm_haddq_epu8 (a);
}

/** \IMP{SSE5 Native,_mm_haddd_epu16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_haddd_epu16_SSE5(__m128i a)
{
    return _mm_haddd_epu16 (a);
}

/** \IMP{SSE5 Native,_mm_haddq_epu16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_haddq_epu16_SSE5(__m128i a)
{
    return _mm_haddq_epu16 (a);
}

/** \IMP{SSE5 Native,_mm_haddq_epu32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_haddq_epu32_SSE5(__m128i a)
{
    return _mm_haddq_epu32 (a);
}

/** \IMP{SSE5 Native,_mm_hsubw_epi8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_hsubw_epi8_SSE5(__m128i a)
{
    return _mm_hsubw_epi8 (a);
}

/** \IMP{SSE5 Native,_mm_hsubd_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_hsubd_epi16_SSE5(__m128i a)
{
    return _mm_hsubd_epi16 (a);
}

/** \IMP{SSE5 Native,_mm_hsubq_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_hsubq_epi32_SSE5(__m128i a)
{
    return _mm_hsubq_epi32 (a);
}

/** \IMP{SSE5 Native,_mm_cmov_si128,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_cmov_si128_SSE5(__m128i a, __m128i b, __m128i c)
{
    return _mm_cmov_si128 (a, b, c);
}

/** \IMP{SSE5 Native,_mm_perm_epi8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_perm_epi8_SSE5(__m128i a, __m128i b, __m128i c)
{
    return _mm_perm_epi8 (a, b, c);
}

/** \IMP{SSE5 Native,_mm_perm_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_perm_ps_SSE5(__m128 a, __m128 b, __m128i c)
{
    return _mm_perm_ps (a, b, c);
}

/** \IMP{SSE5 Native,_mm_perm_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_perm_pd_SSE5(__m128d a, __m128d b, __m128i c)
{
    return _mm_perm_pd (a, b, c);
}

/** \IMP{SSE5 Native,_mm_rot_epi8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_rot_epi8_SSE5(__m128i a, __m128i b)
{
    return _mm_rot_epi8 (a, b);
}

/** \IMP{SSE5 Native,_mm_rot_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_rot_epi16_SSE5(__m128i a, __m128i b)
{
    return _mm_rot_epi16 (a, b);
}

/** \IMP{SSE5 Native,_mm_rot_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_rot_epi32_SSE5(__m128i a, __m128i b)
{
    return _mm_rot_epi32 (a, b);
}

/** \IMP{SSE5 Native,_mm_rot_epi64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_rot_epi64_SSE5(__m128i a, __m128i b)
{
    return _mm_rot_epi64 (a, b);
}

/** \IMP{SSE5 Native,_mm_roti_epi8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_roti_epi8_SSE5(__m128i a, const int b)
{
    return _mm_roti_epi8 (a, b);
}

/** \IMP{SSE5 Native,_mm_roti_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_roti_epi16_SSE5(__m128i a, const int b)
{
    return _mm_roti_epi16 (a, b);
}

/** \IMP{SSE5 Native,_mm_roti_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_roti_epi32_SSE5(__m128i a, const int b)
{
    return _mm_roti_epi32 (a, b);
}

/** \IMP{SSE5 Native,_mm_roti_epi64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_roti_epi64_SSE5(__m128i a, const int b)
{
    return _mm_roti_epi64 (a, b);
}

/** \IMP{SSE5 Native,_mm_shl_epi8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_shl_epi8_SSE5(__m128i a, __m128i b)
{
    return _mm_shl_epi8 (a, b);
}

/** \IMP{SSE5 Native,_mm_shl_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_shl_epi16_SSE5(__m128i a, __m128i b)
{
    return _mm_shl_epi16 (a, b);
}

/** \IMP{SSE5 Native,_mm_shl_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_shl_epi32_SSE5(__m128i a, __m128i b)
{
    return _mm_shl_epi32 (a, b);
}

/** \IMP{SSE5 Native,_mm_shl_epi64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_shl_epi64_SSE5(__m128i a, __m128i b)
{
    return _mm_shl_epi64 (a, b);
}

/** \IMP{SSE5 Native,_mm_sha_epi8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_sha_epi8_SSE5(__m128i a, __m128i b)
{
    return _mm_sha_epi8 (a, b);
}

/** \IMP{SSE5 Native,_mm_sha_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_sha_epi16_SSE5(__m128i a, __m128i b)
{
    return _mm_sha_epi16 (a, b);
}

/** \IMP{SSE5 Native,_mm_sha_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_sha_epi32_SSE5(__m128i a, __m128i b)
{
    return _mm_sha_epi32 (a, b);
}

/** \IMP{SSE5 Native,_mm_sha_epi64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_sha_epi64_SSE5(__m128i a, __m128i b)
{
    return _mm_sha_epi64 (a, b);
}

/** \IMP{SSE5 Native,_mm_comeq_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comeq_ps_SSE5(__m128 a, __m128 b)
{
    return _mm_comeq_ps (a, b);
}

/** \IMP{SSE5 Native,_mm_comlt_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comlt_ps_SSE5(__m128 a, __m128 b)
{
    return _mm_comlt_ps (a, b);
}

/** \IMP{SSE5 Native,_mm_comle_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comle_ps_SSE5(__m128 a, __m128 b)
{
    return _mm_comle_ps (a, b);
}

/** \IMP{SSE5 Native,_mm_comunord_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comunord_ps_SSE5(__m128 a, __m128 b)
{
    return _mm_comunord_ps (a, b);
}

/** \IMP{SSE5 Native,_mm_comneq_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comneq_ps_SSE5(__m128 a, __m128 b)
{
    return _mm_comneq_ps (a, b);
}

/** \IMP{SSE5 Native,_mm_comnlt_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comnlt_ps_SSE5(__m128 a, __m128 b)
{
    return _mm_comnlt_ps (a, b);
}

/** \IMP{SSE5 Native,_mm_comnle_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comnle_ps_SSE5(__m128 a, __m128 b)
{
    return _mm_comnle_ps (a, b);
}

/** \IMP{SSE5 Native,_mm_comord_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comord_ps_SSE5(__m128 a, __m128 b)
{
    return _mm_comord_ps (a, b);
}

/** \IMP{SSE5 Native,_mm_comueq_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comueq_ps_SSE5(__m128 a, __m128 b)
{
    return _mm_comueq_ps (a, b);
}

/** \IMP{SSE5 Native,_mm_comnge_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comnge_ps_SSE5(__m128 a, __m128 b)
{
    return _mm_comnge_ps (a, b);
}

/** \IMP{SSE5 Native,_mm_comngt_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comngt_ps_SSE5(__m128 a, __m128 b)
{
    return _mm_comngt_ps (a, b);
}

/** \IMP{SSE5 Native,_mm_comfalse_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comfalse_ps_SSE5(__m128 a, __m128 b)
{
    return _mm_comfalse_ps (a, b);
}

/** \IMP{SSE5 Native,_mm_comoneq_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comoneq_ps_SSE5(__m128 a, __m128 b)
{
    return _mm_comoneq_ps (a, b);
}

/** \IMP{SSE5 Native,_mm_comge_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comge_ps_SSE5(__m128 a, __m128 b)
{
    return _mm_comge_ps (a, b);
}

/** \IMP{SSE5 Native,_mm_comgt_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comgt_ps_SSE5(__m128 a, __m128 b)
{
    return _mm_comgt_ps (a, b);
}

/** \IMP{SSE5 Native,_mm_comtrue_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comtrue_ps_SSE5(__m128 a, __m128 b)
{
    return _mm_comtrue_ps (a, b);
}

/** \IMP{SSE5 Native,_mm_comeq_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comeq_pd_SSE5(__m128d a, __m128d b)
{
    return _mm_comeq_pd (a, b);
}

/** \IMP{SSE5 Native,_mm_comlt_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comlt_pd_SSE5(__m128d a, __m128d b)
{
    return _mm_comlt_pd (a, b);
}

/** \IMP{SSE5 Native,_mm_comle_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comle_pd_SSE5(__m128d a, __m128d b)
{
    return _mm_comle_pd (a, b);
}

/** \IMP{SSE5 Native,_mm_comunord_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comunord_pd_SSE5(__m128d a, __m128d b)
{
    return _mm_comunord_pd (a, b);
}

/** \IMP{SSE5 Native,_mm_comneq_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comneq_pd_SSE5(__m128d a, __m128d b)
{
    return _mm_comneq_pd (a, b);
}

/** \IMP{SSE5 Native,_mm_comnlt_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comnlt_pd_SSE5(__m128d a, __m128d b)
{
    return _mm_comnlt_pd (a, b);
}

/** \IMP{SSE5 Native,_mm_comnle_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comnle_pd_SSE5(__m128d a, __m128d b)
{
    return _mm_comnle_pd (a, b);
}

/** \IMP{SSE5 Native,_mm_comord_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comord_pd_SSE5(__m128d a, __m128d b)
{
    return _mm_comord_pd (a, b);
}

/** \IMP{SSE5 Native,_mm_comueq_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comueq_pd_SSE5(__m128d a, __m128d b)
{
    return _mm_comueq_pd (a, b);
}

/** \IMP{SSE5 Native,_mm_comnge_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comnge_pd_SSE5(__m128d a, __m128d b)
{
    return _mm_comnge_pd (a, b);
}

/** \IMP{SSE5 Native,_mm_comngt_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comngt_pd_SSE5(__m128d a, __m128d b)
{
    return _mm_comngt_pd (a, b);
}

/** \IMP{SSE5 Native,_mm_comfalse_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comfalse_pd_SSE5(__m128d a, __m128d b)
{
    return _mm_comfalse_pd (a, b);
}

/** \IMP{SSE5 Native,_mm_comoneq_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comoneq_pd_SSE5(__m128d a, __m128d b)
{
    return _mm_comoneq_pd (a, b);
}

/** \IMP{SSE5 Native,_mm_comge_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comge_pd_SSE5(__m128d a, __m128d b)
{
    return _mm_comge_pd (a, b);
}

/** \IMP{SSE5 Native,_mm_comgt_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comgt_pd_SSE5(__m128d a, __m128d b)
{
    return _mm_comgt_pd (a, b);
}

/** \IMP{SSE5 Native,_mm_comtrue_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comtrue_pd_SSE5(__m128d a, __m128d b)
{
    return _mm_comtrue_pd (a, b);
}

/** \IMP{SSE5 Native,_mm_comeq_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comeq_ss_SSE5(__m128 a, __m128 b)
{
    return _mm_comeq_ss (a, b);
}

/** \IMP{SSE5 Native,_mm_comlt_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comlt_ss_SSE5(__m128 a, __m128 b)
{
    return _mm_comlt_ss (a, b);
}

/** \IMP{SSE5 Native,_mm_comle_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comle_ss_SSE5(__m128 a, __m128 b)
{
    return _mm_comle_ss (a, b);
}

/** \IMP{SSE5 Native,_mm_comunord_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comunord_ss_SSE5(__m128 a, __m128 b)
{
    return _mm_comunord_ss (a, b);
}

/** \IMP{SSE5 Native,_mm_comneq_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comneq_ss_SSE5(__m128 a, __m128 b)
{
    return _mm_comneq_ss (a, b);
}

/** \IMP{SSE5 Native,_mm_comnlt_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comnlt_ss_SSE5(__m128 a, __m128 b)
{
    return _mm_comnlt_ss (a, b);
}

/** \IMP{SSE5 Native,_mm_comnle_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comnle_ss_SSE5(__m128 a, __m128 b)
{
    return _mm_comnle_ss (a, b);
}

/** \IMP{SSE5 Native,_mm_comord_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comord_ss_SSE5(__m128 a, __m128 b)
{
    return _mm_comord_ss (a, b);
}

/** \IMP{SSE5 Native,_mm_comueq_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comueq_ss_SSE5(__m128 a, __m128 b)
{
    return _mm_comueq_ss (a, b);
}

/** \IMP{SSE5 Native,_mm_comnge_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comnge_ss_SSE5(__m128 a, __m128 b)
{
    return _mm_comnge_ss (a, b);
}

/** \IMP{SSE5 Native,_mm_comngt_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comngt_ss_SSE5(__m128 a, __m128 b)
{
    return _mm_comngt_ss (a, b);
}

/** \IMP{SSE5 Native,_mm_comfalse_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comfalse_ss_SSE5(__m128 a, __m128 b)
{
    return _mm_comfalse_ss (a, b);
}

/** \IMP{SSE5 Native,_mm_comoneq_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comoneq_ss_SSE5(__m128 a, __m128 b)
{
    return _mm_comoneq_ss (a, b);
}

/** \IMP{SSE5 Native,_mm_comge_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comge_ss_SSE5(__m128 a, __m128 b)
{
    return _mm_comge_ss (a, b);
}

/** \IMP{SSE5 Native,_mm_comgt_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comgt_ss_SSE5(__m128 a, __m128 b)
{
    return _mm_comgt_ss (a, b);
}

/** \IMP{SSE5 Native,_mm_comtrue_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_comtrue_ss_SSE5(__m128 a, __m128 b)
{
    return _mm_comtrue_ss (a, b);
}

/** \IMP{SSE5 Native,_mm_comeq_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comeq_sd_SSE5(__m128d a, __m128d b)
{
    return _mm_comeq_sd (a, b);
}

/** \IMP{SSE5 Native,_mm_comlt_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comlt_sd_SSE5(__m128d a, __m128d b)
{
    return _mm_comlt_sd (a, b);
}

/** \IMP{SSE5 Native,_mm_comle_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comle_sd_SSE5(__m128d a, __m128d b)
{
    return _mm_comle_sd (a, b);
}

/** \IMP{SSE5 Native,_mm_comunord_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comunord_sd_SSE5(__m128d a, __m128d b)
{
    return _mm_comunord_sd (a, b);
}

/** \IMP{SSE5 Native,_mm_comneq_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comneq_sd_SSE5(__m128d a, __m128d b)
{
    return _mm_comneq_sd (a, b);
}

/** \IMP{SSE5 Native,_mm_comnlt_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comnlt_sd_SSE5(__m128d a, __m128d b)
{
    return _mm_comnlt_sd (a, b);
}

/** \IMP{SSE5 Native,_mm_comnle_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comnle_sd_SSE5(__m128d a, __m128d b)
{
    return _mm_comnle_sd (a, b);
}

/** \IMP{SSE5 Native,_mm_comord_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comord_sd_SSE5(__m128d a, __m128d b)
{
    return _mm_comord_sd (a, b);
}

/** \IMP{SSE5 Native,_mm_comueq_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comueq_sd_SSE5(__m128d a, __m128d b)
{
    return _mm_comueq_sd (a, b);
}

/** \IMP{SSE5 Native,_mm_comnge_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comnge_sd_SSE5(__m128d a, __m128d b)
{
    return _mm_comnge_sd (a, b);
}

/** \IMP{SSE5 Native,_mm_comngt_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comngt_sd_SSE5(__m128d a, __m128d b)
{
    return _mm_comngt_sd (a, b);
}

/** \IMP{SSE5 Native,_mm_comfalse_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comfalse_sd_SSE5(__m128d a, __m128d b)
{
    return _mm_comfalse_sd (a, b);
}

/** \IMP{SSE5 Native,_mm_comoneq_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comoneq_sd_SSE5(__m128d a, __m128d b)
{
    return _mm_comoneq_sd (a, b);
}

/** \IMP{SSE5 Native,_mm_comge_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comge_sd_SSE5(__m128d a, __m128d b)
{
    return _mm_comge_sd (a, b);
}

/** \IMP{SSE5 Native,_mm_comgt_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comgt_sd_SSE5(__m128d a, __m128d b)
{
    return _mm_comgt_sd (a, b);
}

/** \IMP{SSE5 Native,_mm_comtrue_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_comtrue_sd_SSE5(__m128d a, __m128d b)
{
    return _mm_comtrue_sd (a, b);
}

/** \IMP{SSE5 Native,_mm_comlt_epu8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comlt_epu8_SSE5(__m128i a, __m128i b)
{
    return _mm_comlt_epu8 (a, b);
}

/** \IMP{SSE5 Native,_mm_comle_epu8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comle_epu8_SSE5(__m128i a, __m128i b)
{
    return _mm_comle_epu8 (a, b);
}

/** \IMP{SSE5 Native,_mm_comgt_epu8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comgt_epu8_SSE5(__m128i a, __m128i b)
{
    return _mm_comgt_epu8 (a, b);
}

/** \IMP{SSE5 Native,_mm_comge_epu8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comge_epu8_SSE5(__m128i a, __m128i b)
{
    return _mm_comge_epu8 (a, b);
}

/** \IMP{SSE5 Native,_mm_comeq_epu8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comeq_epu8_SSE5(__m128i a, __m128i b)
{
    return _mm_comeq_epu8 (a, b);
}

/** \IMP{SSE5 Native,_mm_comneq_epu8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comneq_epu8_SSE5(__m128i a, __m128i b)
{
    return _mm_comneq_epu8 (a, b);
}

/** \IMP{SSE5 Native,_mm_comfalse_epu8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comfalse_epu8_SSE5(__m128i a, __m128i b)
{
    return _mm_comfalse_epu8 (a, b);
}

/** \IMP{SSE5 Native,_mm_comtrue_epu8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comtrue_epu8_SSE5(__m128i a, __m128i b)
{
    return _mm_comtrue_epu8 (a, b);
}

/** \IMP{SSE5 Native,_mm_comlt_epu16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comlt_epu16_SSE5(__m128i a, __m128i b)
{
    return _mm_comlt_epu16 (a, b);
}

/** \IMP{SSE5 Native,_mm_comle_epu16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comle_epu16_SSE5(__m128i a, __m128i b)
{
    return _mm_comle_epu16 (a, b);
}

/** \IMP{SSE5 Native,_mm_comgt_epu16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comgt_epu16_SSE5(__m128i a, __m128i b)
{
    return _mm_comgt_epu16 (a, b);
}

/** \IMP{SSE5 Native,_mm_comge_epu16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comge_epu16_SSE5(__m128i a, __m128i b)
{
    return _mm_comge_epu16 (a, b);
}

/** \IMP{SSE5 Native,_mm_comeq_epu16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comeq_epu16_SSE5(__m128i a, __m128i b)
{
    return _mm_comeq_epu16 (a, b);
}

/** \IMP{SSE5 Native,_mm_comneq_epu16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comneq_epu16_SSE5(__m128i a, __m128i b)
{
    return _mm_comneq_epu16 (a, b);
}

/** \IMP{SSE5 Native,_mm_comfalse_epu16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comfalse_epu16_SSE5(__m128i a, __m128i b)
{
    return _mm_comfalse_epu16 (a, b);
}

/** \IMP{SSE5 Native,_mm_comtrue_epu16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comtrue_epu16_SSE5(__m128i a, __m128i b)
{
    return _mm_comtrue_epu16 (a, b);
}

/** \IMP{SSE5 Native,_mm_comlt_epu32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comlt_epu32_SSE5(__m128i a, __m128i b)
{
    return _mm_comlt_epu32 (a, b);
}

/** \IMP{SSE5 Native,_mm_comle_epu32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comle_epu32_SSE5(__m128i a, __m128i b)
{
    return _mm_comle_epu32 (a, b);
}

/** \IMP{SSE5 Native,_mm_comgt_epu32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comgt_epu32_SSE5(__m128i a, __m128i b)
{
    return _mm_comgt_epu32 (a, b);
}

/** \IMP{SSE5 Native,_mm_comge_epu32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comge_epu32_SSE5(__m128i a, __m128i b)
{
    return _mm_comge_epu32 (a, b);
}

/** \IMP{SSE5 Native,_mm_comeq_epu32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comeq_epu32_SSE5(__m128i a, __m128i b)
{
    return _mm_comeq_epu32 (a, b);
}

/** \IMP{SSE5 Native,_mm_comneq_epu32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comneq_epu32_SSE5(__m128i a, __m128i b)
{
    return _mm_comneq_epu32 (a, b);
}

/** \IMP{SSE5 Native,_mm_comfalse_epu32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comfalse_epu32_SSE5(__m128i a, __m128i b)
{
    return _mm_comfalse_epu32 (a, b);
}

/** \IMP{SSE5 Native,_mm_comtrue_epu32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comtrue_epu32_SSE5(__m128i a, __m128i b)
{
    return _mm_comtrue_epu32 (a, b);
}

/** \IMP{SSE5 Native,_mm_comlt_epu64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comlt_epu64_SSE5(__m128i a, __m128i b)
{
    return _mm_comlt_epu64 (a, b);
}

/** \IMP{SSE5 Native,_mm_comle_epu64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comle_epu64_SSE5(__m128i a, __m128i b)
{
    return _mm_comle_epu64 (a, b);
}

/** \IMP{SSE5 Native,_mm_comgt_epu64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comgt_epu64_SSE5(__m128i a, __m128i b)
{
    return _mm_comgt_epu64 (a, b);
}

/** \IMP{SSE5 Native,_mm_comge_epu64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comge_epu64_SSE5(__m128i a, __m128i b)
{
    return _mm_comge_epu64 (a, b);
}

/** \IMP{SSE5 Native,_mm_comeq_epu64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comeq_epu64_SSE5(__m128i a, __m128i b)
{
    return _mm_comeq_epu64 (a, b);
}

/** \IMP{SSE5 Native,_mm_comneq_epu64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comneq_epu64_SSE5(__m128i a, __m128i b)
{
    return _mm_comneq_epu64 (a, b);
}

/** \IMP{SSE5 Native,_mm_comfalse_epu64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comfalse_epu64_SSE5(__m128i a, __m128i b)
{
    return _mm_comfalse_epu64 (a, b);
}

/** \IMP{SSE5 Native,_mm_comtrue_epu64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comtrue_epu64_SSE5(__m128i a, __m128i b)
{
    return _mm_comtrue_epu64 (a, b);
}

/** \IMP{SSE5 Native,_mm_comlt_epi8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comlt_epi8_SSE5(__m128i a, __m128i b)
{
    return _mm_comlt_epi8 (a, b);
}

/** \IMP{SSE5 Native,_mm_comle_epi8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comle_epi8_SSE5(__m128i a, __m128i b)
{
    return _mm_comle_epi8 (a, b);
}

/** \IMP{SSE5 Native,_mm_comgt_epi8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comgt_epi8_SSE5(__m128i a, __m128i b)
{
    return _mm_comgt_epi8 (a, b);
}

/** \IMP{SSE5 Native,_mm_comge_epi8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comge_epi8_SSE5(__m128i a, __m128i b)
{
    return _mm_comge_epi8 (a, b);
}

/** \IMP{SSE5 Native,_mm_comeq_epi8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comeq_epi8_SSE5(__m128i a, __m128i b)
{
    return _mm_comeq_epi8 (a, b);
}

/** \IMP{SSE5 Native,_mm_comneq_epi8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comneq_epi8_SSE5(__m128i a, __m128i b)
{
    return _mm_comneq_epi8 (a, b);
}

/** \IMP{SSE5 Native,_mm_comfalse_epi8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comfalse_epi8_SSE5(__m128i a, __m128i b)
{
    return _mm_comfalse_epi8 (a, b);
}

/** \IMP{SSE5 Native,_mm_comtrue_epi8,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comtrue_epi8_SSE5(__m128i a, __m128i b)
{
    return _mm_comtrue_epi8 (a, b);
}

/** \IMP{SSE5 Native,_mm_comlt_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comlt_epi16_SSE5(__m128i a, __m128i b)
{
    return _mm_comlt_epi16 (a, b);
}

/** \IMP{SSE5 Native,_mm_comle_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comle_epi16_SSE5(__m128i a, __m128i b)
{
    return _mm_comle_epi16 (a, b);
}

/** \IMP{SSE5 Native,_mm_comgt_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comgt_epi16_SSE5(__m128i a, __m128i b)
{
    return _mm_comgt_epi16 (a, b);
}

/** \IMP{SSE5 Native,_mm_comge_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comge_epi16_SSE5(__m128i a, __m128i b)
{
    return _mm_comge_epi16 (a, b);
}

/** \IMP{SSE5 Native,_mm_comeq_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comeq_epi16_SSE5(__m128i a, __m128i b)
{
    return _mm_comeq_epi16 (a, b);
}

/** \IMP{SSE5 Native,_mm_comneq_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comneq_epi16_SSE5(__m128i a, __m128i b)
{
    return _mm_comneq_epi16 (a, b);
}

/** \IMP{SSE5 Native,_mm_comfalse_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comfalse_epi16_SSE5(__m128i a, __m128i b)
{
    return _mm_comfalse_epi16 (a, b);
}

/** \IMP{SSE5 Native,_mm_comtrue_epi16,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comtrue_epi16_SSE5(__m128i a, __m128i b)
{
    return _mm_comtrue_epi16 (a, b);
}

/** \IMP{SSE5 Native,_mm_comlt_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comlt_epi32_SSE5(__m128i a, __m128i b)
{
    return _mm_comlt_epi32 (a, b);
}

/** \IMP{SSE5 Native,_mm_comle_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comle_epi32_SSE5(__m128i a, __m128i b)
{
    return _mm_comle_epi32 (a, b);
}

/** \IMP{SSE5 Native,_mm_comgt_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comgt_epi32_SSE5(__m128i a, __m128i b)
{
    return _mm_comgt_epi32 (a, b);
}

/** \IMP{SSE5 Native,_mm_comge_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comge_epi32_SSE5(__m128i a, __m128i b)
{
    return _mm_comge_epi32 (a, b);
}

/** \IMP{SSE5 Native,_mm_comeq_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comeq_epi32_SSE5(__m128i a, __m128i b)
{
    return _mm_comeq_epi32 (a, b);
}

/** \IMP{SSE5 Native,_mm_comneq_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comneq_epi32_SSE5(__m128i a, __m128i b)
{
    return _mm_comneq_epi32 (a, b);
}

/** \IMP{SSE5 Native,_mm_comfalse_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comfalse_epi32_SSE5(__m128i a, __m128i b)
{
    return _mm_comfalse_epi32 (a, b);
}

/** \IMP{SSE5 Native,_mm_comtrue_epi32,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comtrue_epi32_SSE5(__m128i a, __m128i b)
{
    return _mm_comtrue_epi32 (a, b);
}

/** \IMP{SSE5 Native,_mm_comlt_epi64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comlt_epi64_SSE5(__m128i a, __m128i b)
{
    return _mm_comlt_epi64 (a, b);
}

/** \IMP{SSE5 Native,_mm_comle_epi64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comle_epi64_SSE5(__m128i a, __m128i b)
{
    return _mm_comle_epi64 (a, b);
}

/** \IMP{SSE5 Native,_mm_comgt_epi64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comgt_epi64_SSE5(__m128i a, __m128i b)
{
    return _mm_comgt_epi64 (a, b);
}

/** \IMP{SSE5 Native,_mm_comge_epi64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comge_epi64_SSE5(__m128i a, __m128i b)
{
    return _mm_comge_epi64 (a, b);
}

/** \IMP{SSE5 Native,_mm_comeq_epi64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comeq_epi64_SSE5(__m128i a, __m128i b)
{
    return _mm_comeq_epi64 (a, b);
}

/** \IMP{SSE5 Native,_mm_comneq_epi64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comneq_epi64_SSE5(__m128i a, __m128i b)
{
    return _mm_comneq_epi64 (a, b);
}

/** \IMP{SSE5 Native,_mm_comfalse_epi64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comfalse_epi64_SSE5(__m128i a, __m128i b)
{
    return _mm_comfalse_epi64 (a, b);
}

/** \IMP{SSE5 Native,_mm_comtrue_epi64,SSE5} */ 
SSP_FORCEINLINE __m128i ssp_comtrue_epi64_SSE5(__m128i a, __m128i b)
{
    return _mm_comtrue_epi64 (a, b);
}

/** \IMP{SSE5 Native,_mm_frcz_ps,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_frcz_ps_SSE5 (__m128 a)
{
    return _mm_frcz_ps (a);
}

/** \IMP{SSE5 Native,_mm_frcz_pd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_frcz_pd_SSE5 (__m128d a)
{
    return _mm_frcz_pd (a);
}

/** \IMP{SSE5 Native,_mm_frcz_ss,SSE5} */ 
SSP_FORCEINLINE __m128 ssp_frcz_ss_SSE5 (__m128 a, __m128 b)
{
    return _mm_frcz_ss (a, b);
}

/** \IMP{SSE5 Native,_mm_frcz_sd,SSE5} */ 
SSP_FORCEINLINE __m128d ssp_frcz_sd_SSE5 (__m128d a, __m128d b)
{
    return _mm_frcz_sd (a, b);
}



//
// Functions common with SSE4.1
//

/** \IMP{SSE5 Native,_mm_testz_si128,SSE4.1 and SSE5} */ 
SSP_FORCEINLINE int ssp_testz_si128_SSE5(__m128i mask, __m128i a)
{
    return _mm_testz_si128( mask, a);
}

/** \IMP{SSE5 Native,_mm_testc_si128,SSE4.1 and SSE5} */ 
SSP_FORCEINLINE int ssp_testc_si128_SSE5(__m128i mask, __m128i a)
{
    return _mm_testc_si128( mask, a);
}

/** \IMP{SSE5 Native,_mm_testnzc_si128,SSE4.1 and SSE5} */ 
SSP_FORCEINLINE int ssp_testnzc_si128_SSE5(__m128i mask, __m128i b)
{
    return _mm_testnzc_si128( mask, b);
}

/** \IMP{SSE5 Native,_mm_round_pd,SSE4.1 and SSE5} */ 
SSP_FORCEINLINE __m128d ssp_round_pd_SSE5(__m128d a, int iRoundMode)
{
    switch( iRoundMode & 0xF )
    {
        CASE_16( _mm_round_pd, a );
    }
}

/** \IMP{SSE5 Native,_mm_round_sd,SSE4.1 and SSE5} */ 
SSP_FORCEINLINE __m128d ssp_round_sd_SSE5(__m128d dst, __m128d a, int iRoundMode)
{
    switch( iRoundMode & 0xF )
    {
        CASE_16( _mm_round_sd, dst, a );
    }
}

/** \IMP{SSE5 Native,_mm_round_ps,SSE4.1 and SSE5} */ 
SSP_FORCEINLINE __m128 ssp_round_ps_SSE5(__m128  a, int iRoundMode)
{
    switch( iRoundMode & 0xF )
    {
        CASE_16( _mm_round_ps, a );
    }
}

/** \IMP{SSE5 Native,_mm_round_ss,SSE4.1 and SSE5} */ 
SSP_FORCEINLINE __m128 ssp_round_ss_SSE5(__m128 dst, __m128  a, int iRoundMode)
{
    switch( iRoundMode & 0xF )
    {
        CASE_16( _mm_round_ss, dst, a );
    }
}


//@}
//@}

#endif // __SSEPLUS_NATIVE_SSE5_H__