//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __SSEPLUS_H__
#define __SSEPLUS_H__

#include "SSEPlus_base.h"
#include "SSEPlus_REF.h"
#include "SSEPlus_SSE.h"
#include "SSEPlus_SSE2.h"
#include "SSEPlus_SSE3.h"

#ifdef SSEPLUS_SSSE3_SSE4A_SSE41_SSE42
#include "SSEPlus_SSSE3.h"
#include "SSEPlus_SSE4a.h"
#include "SSEPlus_SSE4.1.h"
#include "SSEPlus_SSE4.2.h"
#endif // SSEPLUS_SSSE3_SSE4A_SSE41_SSE42

#endif // __SSEPLUS_H__
