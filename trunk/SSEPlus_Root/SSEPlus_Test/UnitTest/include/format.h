//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __FORMAT_H__
#define __FORMAT_H__
#include "../../../SSEPlus/include/SSEPlus_base.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>


bool g_update = false;


struct obj_m128i
{
	__m128i dat;

	obj_m128i( ssp_u32 v3, ssp_u32 v2, ssp_u32 v1, ssp_u32 v0 )
	{
		dat = _mm_set_epi32( v3,v2,v1,v0 );
	}

	obj_m128i( ssp_u8 v15, ssp_u8 v14, ssp_u8 v13, ssp_u8 v12, 
               ssp_u8 v11, ssp_u8 v10, ssp_u8 v9,  ssp_u8 v8,
               ssp_u8 v7,  ssp_u8 v6,  ssp_u8 v5,  ssp_u8 v4,
               ssp_u8 v3,  ssp_u8 v2,  ssp_u8 v1,  ssp_u8 v0 )
	{
		dat = _mm_set_epi8( v15,v14,v13,v12,v11,v10,v9,v8,v7,v6,v5,v4,v3,v2,v1,v0 );
	}

	obj_m128i( ssp_u16 v7,  ssp_u16 v6,  ssp_u16 v5,  ssp_u16 v4,
               ssp_u16 v3,  ssp_u16 v2,  ssp_u16 v1,  ssp_u16 v0 )
	{
		dat = _mm_set_epi16( v7,v6,v5,v4,v3,v2,v1,v0 );
	}

	__m128i * Address(){ return &dat; }
	__m128i   Value  (){ return  dat; }
};



//
// Vector Initialization
//

__m128i vS8( ssp_s8 v15, ssp_s8 v14, ssp_s8 v13, ssp_s8 v12, 
             ssp_s8 v11, ssp_s8 v10, ssp_s8 v9,  ssp_s8 v8,
             ssp_s8 v7,  ssp_s8 v6,  ssp_s8 v5,  ssp_s8 v4,
             ssp_s8 v3,  ssp_s8 v2,  ssp_s8 v1,  ssp_s8 v0 )
{
    return _mm_set_epi8( v15,v14,v13,v12,v11,v10,v9,v8,v7,v6,v5,v4,v3,v2,v1,v0 );
}
__m128i vU8( ssp_u8 v15, ssp_u8 v14, ssp_u8 v13, ssp_u8 v12, 
             ssp_u8 v11, ssp_u8 v10, ssp_u8 v9,  ssp_u8 v8,
             ssp_u8 v7,  ssp_u8 v6,  ssp_u8 v5,  ssp_u8 v4,
             ssp_u8 v3,  ssp_u8 v2,  ssp_u8 v1,  ssp_u8 v0 )
{
    return _mm_set_epi8( v15,v14,v13,v12,v11,v10,v9,v8,v7,v6,v5,v4,v3,v2,v1,v0 );
}

__m128i vS16( ssp_s16 v7,  ssp_s16 v6,  ssp_s16 v5,  ssp_s16 v4,
              ssp_s16 v3,  ssp_s16 v2,  ssp_s16 v1,  ssp_s16 v0 )
{
    return _mm_set_epi16( v7,v6,v5,v4,v3,v2,v1,v0 );
}
__m128i vU16( ssp_u16 v7,  ssp_u16 v6,  ssp_u16 v5,  ssp_u16 v4,
              ssp_u16 v3,  ssp_u16 v2,  ssp_u16 v1,  ssp_u16 v0 )
{
    return _mm_set_epi16( v7,v6,v5,v4,v3,v2,v1,v0 );
}

__m128i vS32( ssp_s32 v3, ssp_s32 v2, ssp_s32 v1, ssp_s32 v0 )
{
    return _mm_set_epi32( v3,v2,v1,v0 );
}
__m128i vU32( ssp_u32 v3, ssp_u32 v2, ssp_u32 v1, ssp_u32 v0 )
{
    return _mm_set_epi32( v3,v2,v1,v0 );
}
__m128 vF32( ssp_f32 v3, ssp_f32 v2, ssp_f32 v1, ssp_f32 v0 )
{
    return _mm_set_ps( v3,v2,v1,v0 );
}

__m128i vS64( ssp_s64 v1, ssp_s64 v0 )
{
   ssp_m128 t;
   t.s64[0] = v0;
   t.s64[1] = v1;
   return t.i;
}
__m128i vU64( ssp_u64 v1, ssp_u64 v0 )
{   
   ssp_m128 t;
   t.u64[0] = v0;
   t.u64[1] = v1;
   return t.i;
}
__m128d vF64( ssp_f64 v1, ssp_f64 v0 )
{
    return _mm_set_pd( v1,v0 );
}

__m64 vmS8( ssp_s8 v7,  ssp_s8 v6,  ssp_s8 v5,  ssp_s8 v4,
              ssp_s8 v3,  ssp_s8 v2,  ssp_s8 v1,  ssp_s8 v0 )
{
    ssp_m128 t;

    t.i = _mm_set_epi8( 0,0,0,0,0,0,0,0, v7,v6,v5,v4,v3,v2,v1,v0 );

    return t.m64[0];



    //return // Dont use MMX_mm_set_pi8( v7,v6,v5,v4,v3,v2,v1,v0 );
	//ssp_m64 t;
	//t.s8[0] = v0;
	//t.s8[1] = v1;
	//t.s8[2] = v2;
	//t.s8[3] = v3;
	//t.s8[4] = v4;
	//t.s8[5] = v5;
	//t.s8[6] = v6;
	//t.s8[7] = v7;
 //   return t.m64;
}

__m64 vmU8( ssp_u8 v7,  ssp_u8 v6,  ssp_u8 v5,  ssp_u8 v4,
              ssp_u8 v3,  ssp_u8 v2,  ssp_u8 v1,  ssp_u8 v0 )
{
	ssp_m64 t;
	t.u8[0] = v0;
	t.u8[1] = v1;
	t.u8[2] = v2;
	t.u8[3] = v3;
	t.u8[4] = v4;
	t.u8[5] = v5;
	t.u8[6] = v6;
	t.u8[7] = v7;
    return t.m64;//_mm_set_pi8( v7,v6,v5,v4,v3,v2,v1,v0 );
}

__m64 vmS16( ssp_s16 v3,  ssp_s16 v2,  ssp_s16 v1,  ssp_s16 v0 )
{
	ssp_m64 t;
	t.s16[0] = v0;
	t.s16[1] = v1;
	t.s16[2] = v2;
	t.s16[3] = v3;
    return t.m64;//_mm_set_pi16( v3,v2,v1,v0 );
}

__m64 vmU16( ssp_u16 v3,  ssp_u16 v2,  ssp_u16 v1,  ssp_u16 v0 )
{
	ssp_m64 t;
	t.u16[0] = v0;
	t.u16[1] = v1;
	t.u16[2] = v2;
	t.u16[3] = v3;
    return t.m64;//_mm_set_pi16( v3,v2,v1,v0 );
}

__m64 vmS32( ssp_s32 v1, ssp_s32 v0 )
{
	ssp_m64 t;
	t.s32[0] = v0;
	t.s32[1] = v1;
    return t.m64;//_mm_set_pi32( v1,v0 );
}

__m64 vmU32( ssp_u32 v1, ssp_u32 v0 )
{
	ssp_m64 t;
	t.u32[0] = v0;
	t.u32[1] = v1;
    return t.m64;//_mm_set_pi32( v1,v0 );
}

__m64 vmS64( ssp_s64 v0 )
{
   ssp_m64 t;
   t.s64 = v0;
   return t.m64;
}

__m64 vmU64( ssp_u64 v0 )
{   
   ssp_m64 t;
   t.u64 = v0;
   return t.m64;
}

//
// String Manipulation
//

enum enumPrintFormat
{
    enum_ssp_s8,
    enum_ssp_u8,
    enum_ssp_s16,
    enum_ssp_u16,
    enum_ssp_s32,
    enum_ssp_u32,
    enum_ssp_f32,
    enum_ssp_f64,
    enum_ssp_s64,
    enum_ssp_u64
};


template< enumPrintFormat epf >
std::string ToStr( __m128i a )
{
    ssp_m128 A;
    A.i = a;

    std::ostringstream oss;
    switch( epf )
    {
        case enum_ssp_s8:
        {
            for( ssp_u32 i=15; i>0; --i )
                oss << (int)A.s8[i] << " ";
            oss << (int)A.s8[0];
            break;
        }
        case enum_ssp_u8:
        {
            for( ssp_u32 i=15; i>0; --i )
                oss << (int)A.u8[i] << " ";
            oss << (int)A.u8[0];
            break;
        }
        case enum_ssp_s16:
        {           
           for( ssp_u32 i=7; i>0; --i )
               oss << A.s16[i] << " ";
           oss << A.s16[0];
           break;
        }
        case enum_ssp_u16:
        {           
           for( ssp_u32 i=7; i>0; --i )
                oss << A.u16[i] << " ";
           oss << A.u16[0];
           break;
        }   
        case enum_ssp_s32:
        {           
           for( ssp_u32 i=3; i>0; --i )
               oss << A.s32[i] << " ";
           oss << A.s32[0];
           break;
        }
        case enum_ssp_u32:
        {           
           for( ssp_u32 i=3; i>0; --i )
               oss << A.u32[i] << " ";
           oss << A.u32[0];
           break;
        }
        case enum_ssp_s64:
        {      
            oss << A.s64[1] << " " 
                << A.s64[0];
            break;           
        }
        case enum_ssp_u64:
        {      
            oss << A.u64[1] << " " 
                << A.u64[0];
            break;           
        }
    default:
        return "Unknown print format";
    }
    return oss.str();
}

template< enumPrintFormat epf >
std::string ToStr( __m128 a )
{
    if( epf != enum_ssp_f32 ) 
         return "Expected enum_F32";  

     ssp_m128 A;
     A.f = a;

    std::ostringstream oss;
    oss << A.f32[3] << " " 
        << A.f32[2] << " " 
        << A.f32[1] << " " 
        << A.f32[0];
 
    return oss.str();
}

template< enumPrintFormat epf >
std::string ToStr( __m128d a )
{
     if( epf != enum_ssp_f64 ) 
         return "Expected enum_F64";   

     ssp_m128 A;
     A.d = a;

    std::ostringstream oss;
    oss << A.f64[1] << " " 
        << A.f64[0];
    return oss.str();
}

template< enumPrintFormat epf >
std::string ToStr( __m64 a )
{
    ssp_m64 A;
    A.m64 = a;

    std::ostringstream oss;
    switch( epf )
    {
        case enum_ssp_s8:
        {
            for( ssp_u32 i=7; i>0; --i )
                oss << (int)A.s8[i] << " ";
            oss << (int)A.s8[0];
            break;
        }
        case enum_ssp_u8:
        {
            for( ssp_u32 i=7; i>0; --i )
                oss << (int)A.u8[i] << " ";
            oss << (int)A.u8[0];
            break;
        }
        case enum_ssp_s16:
        {           
           for( ssp_u32 i=3; i>0; --i )
               oss << A.s16[i] << " ";
           oss << A.s16[0];
           break;
        }
        case enum_ssp_u16:
        {           
           for( ssp_u32 i=3; i>0; --i )
                oss << A.u16[i] << " ";
           oss << A.u16[0];
           break;
        }   
        case enum_ssp_s32:
        {           
           oss << A.s32[1] << " " 
               << A.s32[0];
           break;
        }
        case enum_ssp_u32:
        {           
            oss << A.u32[1] << " " 
                << A.u32[0];
           break;
        }
        case enum_ssp_s64:
        {      
            oss << A.s64;
            break;           
        }
        case enum_ssp_u64:
        {      
            oss << A.u64;
            break;           
        }
    default:		
        return "Unknown print format";
    }			
	
    return oss.str();
}

template< enumPrintFormat epf, typename T >
std::string ToStr( T t )
{  

    std::ostringstream oss;
    oss << t;
    return oss.str();
}

//
// Printing
//

enum ENUM_COL_WIDTHS
{
	COL_WIDTH_NAME   = 30,
    COL_WIDTH_ASSEMBLY = 10,
    COL_WIDTH_SOURCE = 6,
    COL_WIDTH_CYCLES = 6,
    COL_WIDTH_BAR    = 1,
    COL_WIDTH_EXP    = 4,
    COL_WIDTH_TOTAL  = COL_WIDTH_CYCLES+COL_WIDTH_BAR+COL_WIDTH_EXP
};

void PrintHeader()
{
    std::cout <<        std::left << std::setw(COL_WIDTH_NAME )  << "Function";

    if( g_update )
        std::cout << "," << std::left << std::setw(COL_WIDTH_ASSEMBLY)  << "Assembly";

    std::cout << "," << std::left << std::setw( COL_WIDTH_SOURCE )<< "Source"; 
    std::cout << "," << std::setw(COL_WIDTH_TOTAL)  << "   REF"; 
    std::cout << "," << std::setw(COL_WIDTH_TOTAL)  << "   SSE"; 
    std::cout << "," << std::setw(COL_WIDTH_TOTAL)  << "  SSE2"; 
    std::cout << "," << std::setw(COL_WIDTH_TOTAL)  << "  SSE3"; 
    std::cout << "," << std::setw(COL_WIDTH_TOTAL)  << " SSSE3"; 
    std::cout << "," << std::setw(COL_WIDTH_TOTAL)  << " SSE4A"; 
    std::cout << "," << std::setw(COL_WIDTH_TOTAL)  << "SSE4_1"; 
    std::cout << "," << std::setw(COL_WIDTH_TOTAL)  << "SSE4_2"; 
    std::cout << "," << std::setw(COL_WIDTH_TOTAL)  << "  SSE5"; 
    std::cout << "," << std::endl;   
}

void PrintName( const char * name, const std::string & assembly, const std::string & source )
{
    std::cout <<  std::left << std::setw(COL_WIDTH_NAME) << name   << ",";  

    if( g_update )
        std::cout << std::setw(COL_WIDTH_ASSEMBLY) << assembly   << ",";
    
    std::cout << std::setw(COL_WIDTH_SOURCE)      << source;
}

void PrintCell( const std::string &result, double expected )
{
    std::string tmp = result;

    if( g_update && result.empty() && expected != 0 )
    {
        std::ostringstream oss; 
        oss << expected;
        tmp = oss.str();
    }

    std::cout.setf( std::ios::fixed, std::ios::floatfield);
    std::cout.setf( std::ios::showpoint);
    std::cout << std::setprecision(1); 
    std::cout << "," << std::setw(COL_WIDTH_CYCLES) << std::right << tmp;

	if( expected && !g_update && expected > 0 )
		std::cout << "|" << std::setw(COL_WIDTH_EXP)    << std::right  << expected;
	else
		std::cout << std::setw( COL_WIDTH_EXP + COL_WIDTH_BAR) << " " ;  
}

void PrintSpace( double expectedCycles )
{
     PrintCell( g_update ? "" : " " , expectedCycles );
}

void PrintException( double expectedCycles ) // Instruction threw exception
{
    PrintCell( g_update ? "" : "X" , expectedCycles );
}    

void PrintDisabled( double expectedCycles ) // No support on CPU
{
	PrintCell( g_update ? "" : "-" , expectedCycles );
}

void PrintFail( double expectedCycles ) // Failed its test
{
	PrintCell( g_update ? "" : "F" , expectedCycles );
}

void PrintResult( double expectedCycles, double elapsed )
{
    if( g_update && expectedCycles>0 )
         elapsed = std::min<double>( elapsed, expectedCycles );

	std::ostringstream oss;
    oss.setf( std::ios::fixed, std::ios::floatfield);
    oss.setf( std::ios::showpoint);
    oss << std::setprecision(1);  
	oss << std::right << std::setw(COL_WIDTH_CYCLES) << elapsed;   

    if( elapsed < expectedCycles+1)
        expectedCycles = 0;

	PrintCell( oss.str(), expectedCycles );   
}


void PrintErrors( std::string & errorList )
{
    std::cout << "," << errorList << std::endl;
    errorList.clear();
}

#endif // __FORMAT_H__
