//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __TEST_H__
#define __TEST_H__

#include "csvTable.h"
#include "../../../SSEPlus/include/SSEPlus_platform.h"
#include <list>

#if defined(SSEPLUS_MSVC)

#include <windows.h>
#include <intrin.h>
#define get_rdtsc __rdtsc

#elif defined(SSEPLUS_GNUC)

#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

// RDTSC
#define rdtsc(low,high) __asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high))

static inline unsigned long long get_rdtsc()
{
	unsigned long low, high;
	rdtsc(low, high);
	return ((unsigned long long)high << 32) | (unsigned long long)low;
}
	
#endif

//#pragma warning( disable: 4799 )
#ifdef SYS32
#define	MMX_EMPTY _mm_empty()
#else
#define	MMX_EMPTY 
#endif

#include "format.h"
#include "../../../SSEPlus/include/logical/SSEPlus_logical_REF.h"

// Disable use of microsoft specific m128 type accessors

#define m128i_i8     DO_NOT_USE
#define m128i_i16    DO_NOT_USE
#define m128i_i32    DO_NOT_USE
#define m128i_i64    DO_NOT_USE
#define m128i_u8     DO_NOT_USE
#define m128i_u16    DO_NOT_USE
#define m128i_u32    DO_NOT_USE
#define m128i_u64    DO_NOT_USE
#define m128d_f64    DO_NOT_USE
#define m128_f32     DO_NOT_USE
#define m128_i8      DO_NOT_USE
#define m128_i16     DO_NOT_USE
#define m128_i32     DO_NOT_USE
#define m128_i64     DO_NOT_USE
#define m128_u8      DO_NOT_USE
#define m128_u16     DO_NOT_USE
#define m128_u32     DO_NOT_USE
#define m128_u64     DO_NOT_USE

const static ssp_u32 LOOP_COUNT = 100 * 1000;

namespace p
{  
    //
    // Timer
    //

    struct Timer
    {
        ssp_u64 start;
        ssp_u32 expCycles;
        bool pass;

        Timer( bool pass_, unsigned int expCycles_ )
        :start    ( get_rdtsc() )
        ,expCycles( expCycles_  )
        ,pass     ( pass_       ){}

        ~Timer()
        {
            ssp_u64 stop = get_rdtsc(); 

            double elapsed = (double)(stop-start) / LOOP_COUNT;     

            if( elapsed > 9999.9 )
                elapsed = 9999.9;

            std::cout.setf( std::ios::fixed, std::ios::floatfield);
            std::cout.setf( std::ios::showpoint);
            std::cout << std::setprecision(1) << ",";
            

            unsigned int width = COL_WIDTH_CYCLES;

            if( !pass )
            {
                --width;
                std::cout << "#";
            }          

            std::cout <<  std::right << std::setw(width) << elapsed;

            if( expCycles && elapsed > expCycles+1 )
            { 
                std::cout <<  "|" << std::left << std::setw(COL_WIDTH_EXP) << expCycles;  
            }
            else
            {
                std::cout << std::setw( COL_WIDTH_EXP + COL_WIDTH_BAR) << " " ;  
            } 
        }
    };

    std::string errorList;    

    //
    // Equal
    // 
  
    template< enumPrintFormat epf, typename T >
    bool Equal( T value, T expected, __m128i expMask )
    {
        if( 16 == sizeof(T) )
        {
            __m128i tmp = *((__m128i*)&value);
            tmp = _mm_and_si128( tmp, expMask );
            value = *((T*)&tmp);           

            tmp = *((__m128i*)&expected);
			tmp = _mm_and_si128( tmp, expMask );
			expected = *((T*)&tmp);      
        }


       if( memcmp(&value,&expected,sizeof(T)) )
       {
           std::ostringstream oss;
           oss << "ERROR[ "    << ToStr<epf>(value   ) << " ] ";
           oss << "Expected[ " << ToStr<epf>(expected) << " ]";

           errorList += " " + oss.str();
			MMX_EMPTY;
           return false;
       }
	   
	   MMX_EMPTY;
       return true;
    }    

    //
    // Test
    //

    ssp_u32 g_no_opt=0;
    #define NO_OPT( a ) g_no_opt = *(ssp_u32*)&a;    

    template< typename TR, typename T1, enumPrintFormat epf, TR(*fn)(T1) >
    void Test( ssp_u32 expCycles, TR exp, T1 a, __m128i expMask )
    {
        TR out = fn( a );
        bool pass = Equal<epf>( out, exp, expMask );

        Timer t( pass, expCycles );    
        for( int i=0; i<LOOP_COUNT; ++i )
            out = fn( out ); 

        NO_OPT( out );
			
		MMX_EMPTY;
    }    

    template< typename TR, typename T1, typename T2, enumPrintFormat epf, TR(*fn)(T1,T2) >
    void Test( ssp_u32 expCycles, TR exp, T1 a, T2 b, __m128i expMask )
    {   
        TR out = fn( a,b );
        bool pass= Equal<epf>( out, exp, expMask );

        Timer t( pass, expCycles );    
        for( int i=0; i<LOOP_COUNT; ++i )
            out = fn( out,b );    

        NO_OPT( out );  
		
		MMX_EMPTY;
    }   

    template< typename TR, typename T1, typename T2, typename T3, enumPrintFormat epf, TR(*fn)(T1,T2,T3) >
    void Test( ssp_u32 expCycles, TR exp, T1 a, T2 b, T3 c, __m128i expMask )
    {
        TR out = fn( a,b,c );
        bool pass = Equal<epf>( out, exp, expMask );

        Timer t( pass, expCycles );    
        for( int i=0; i<LOOP_COUNT; ++i )
            out = fn( out,b,c );    

        NO_OPT( out );
		MMX_EMPTY;
    }

    template< typename TR, typename T1, typename T2, typename T3, typename T4, enumPrintFormat epf, TR(*fn)(T1,T2,T3,T4) >
    void Test( ssp_u32 expCycles, TR exp, T1 a, T2 b, T3 c, T4 d, __m128i expMask )
    {
        TR out = fn( a,b,c,d );
        bool pass = Equal<epf>( out, exp, expMask );

        Timer t( pass, expCycles );    
        for( int i=0; i<LOOP_COUNT; ++i )
            out = fn( out,b,c,d );    

        NO_OPT( out );
		MMX_EMPTY;
    }

    // Type specific overloads

    template< typename TR, typename T1, enumPrintFormat epf, TR(*fn)(T1) >
    void Test( ssp_u32 expCycles, __m128i exp, int a, __m128i expMask )
    {
        TR out = fn( a );
        bool pass = Equal<epf>( out, exp, expMask );

        Timer t( pass, expCycles );    
        for( int i=0; i<LOOP_COUNT; ++i )
        {
            out = fn( a ); 
            out = _mm_xor_si128(out, out);
        }

        NO_OPT( out );
    }

    template< typename TR, typename T1, enumPrintFormat epf, TR(*fn)(T1) >
    void Test( ssp_u32 expCycles, TR exp, const __m128i * a, __m128i expMask )//This is a load. TODO: ?
    {
        TR out = fn( a );
        bool pass = Equal<epf>( out, exp, expMask );

        Timer t( pass, expCycles );    
        for( int i=0; i<LOOP_COUNT; ++i )
            out = fn( a ); 

        NO_OPT( out );
    }

    template< typename TR, typename T1, enumPrintFormat epf, TR(*fn)(T1) >
    void Test( ssp_u32 expCycles, TR exp, const double * a, __m128i expMask )//This is a load. TODO: ?
    {
        TR out = fn( a );
        bool pass = Equal<epf>( out, exp, expMask );

        Timer t( pass, expCycles );    
        for( int i=0; i<LOOP_COUNT; ++i )
            out = fn( a ); 

        NO_OPT( out );
    }

    template< typename TR, typename T1, typename T2, enumPrintFormat epf, TR(*fn)(T1,T2) >
    void Test( ssp_u32 expCycles, int exp, T1 a, T2 b, __m128i expMask )
    {
        TR out = fn( a,b );
        bool pass = Equal<epf>( out, exp, expMask );

        Timer t( pass, expCycles );    
        for( int i=0; i<LOOP_COUNT; ++i )
            out |= fn( a, b );    

        NO_OPT( out );
    }

    template< typename TEXP, typename T1, typename T2, typename TR, enumPrintFormat epf, TR(*fn)(T1,T2) >
    void Test( ssp_u32 expCycles, TEXP exp, T1 a, T2 b )
    {   
        fn( a,b );
        bool pass = false;
        if( *exp == *a )
            pass = true;

        Timer t( pass, expCycles );    
        for( int i=0; i<LOOP_COUNT; ++i )
        {
            *a = *a+1;
            fn( a, b );    
        }
		
		MMX_EMPTY;
    } 

    template< typename TR, typename T1, typename T2, enumPrintFormat epf, TR(*fn)(T1,T2) >
    void Test( ssp_u32 expCycles, ssp_s64 exp, T1 a, T2 b, __m128i expMask )
    {
        TR out = fn( a,b );
        bool pass = Equal<epf>( out, exp, expMask );

        Timer t( pass, expCycles );  
        for( int i=0; i<LOOP_COUNT; ++i )
            out = fn( a, (T2)out );    

        NO_OPT( out );
    }
};

#ifdef SSEPLUS_MSVC

// STATUS_ILLEGAL_INSTRUCTION #include <windows.h> 
#define TRY(  ... )             \
        try                     \
        {                       \
            __VA_ARGS__;        \
        }                       \
        catch( ... )            \
        {                       \
            PrintException( cycles );   \
        }

#endif

#ifdef SSEPLUS_GNUC

#define SSEPLUS_SIGILL_RET 1
sigjmp_buf env;

void handle_illegal_instruction(int num)
{
	if(num == SIGILL)
	{
		signal(SIGILL, handle_illegal_instruction);
		siglongjmp(env, SSEPLUS_SIGILL_RET);
	}
	else
	{
		printf("Unhandled signal, exiting ...\n");
		exit(-1);
	}
}
		
#define TRY(  ... )                                                \
	signal(SIGILL, handle_illegal_instruction);                \
        {                                                          \
	    int sj = sigsetjmp(env, 1);                            \
	    if(sj == 0)                                            \
	    {                                                      \
	        __VA_ARGS__;                                       \
	    }                                                      \
	    else if(sj == SSEPLUS_SIGILL_RET)                      \
	    {                                                      \
	        PrintException( cycles );                          \
	    }                                                      \
	    else                                                   \
	    {                                                      \
	        printf("Unhandled setjmp return, exiting ...\n");  \
	        exit(-1);                                          \
	    }                                                      \
        }

#endif

//
// External Test Entry Points (void return type)
// 
//====================================
template< 
    typename TEXP, typename T1, typename T2, typename TR,
    TR(*fn_ref    )(T1,T2), bool REF_RUN,
    TR(*fn_sse2   )(T1,T2), bool SSE2_RUN,
	TR(*fn_sse3   )(T1,T2), bool SSE3_RUN,
	TR(*fn_ssse3  )(T1,T2), bool SSSE3_RUN,
    TR(*fn_sse4a  )(T1,T2), bool SSE4A_RUN,
    TR(*fn_sse4_1 )(T1,T2), bool SSE4_1_RUN,
    enumPrintFormat epf
>
void Test( const CSVLine & csv, const char *name, TEXP exp, T1 a, T2 b )
{
    unsigned int cycles=0;
    PrintName( name, csv.source );
    if(REF_RUN   ){ cycles=0;         TRY( p::Test<TEXP,T1,T2,TR,epf,fn_ref    >( cycles,exp,a,b ) ); } else { PrintSpace(); }
    if(SSE2_RUN  ){ cycles=csv.SSE2;  TRY( p::Test<TEXP,T1,T2,TR,epf,fn_sse2   >( cycles,exp,a,b ) ); } else { PrintSpace(); }
    if(SSE3_RUN  ){ cycles=csv.SSE3;  TRY( p::Test<TEXP,T1,T2,TR,epf,fn_sse3   >( cycles,exp,a,b ) ); } else { PrintSpace(); }
	if(SSSE3_RUN ){ cycles=csv.SSSE3; TRY( p::Test<TEXP,T1,T2,TR,epf,fn_ssse3  >( cycles,exp,a,b ) ); } else { PrintSpace(); }
    if(SSE4A_RUN ){ cycles=csv.SSE4a; TRY( p::Test<TEXP,T1,T2,TR,epf,fn_sse4a  >( cycles,exp,a,b ) ); } else { PrintSpace(); }
    if(SSE4_1_RUN){ cycles=csv.SSE41; TRY( p::Test<TEXP,T1,T2,TR,epf,fn_sse4_1 >( cycles,exp,a,b ) ); } else { PrintSpace(); }  
    PrintErrors( p::errorList );
	MMX_EMPTY;
}


//
// External Test Entry Points
// 
//====================================
template< 
    typename TR, typename T1, 
    TR(*fn_ref    )(T1), bool REF_RUN,
    TR(*fn_sse2   )(T1), bool SSE2_RUN,
	TR(*fn_sse3   )(T1), bool SSE3_RUN,
    TR(*fn_ssse3  )(T1), bool SSSE3_RUN,
    TR(*fn_sse4a  )(T1), bool SSE4A_RUN,
    TR(*fn_sse4_1 )(T1), bool SSE4_1_RUN,
    enumPrintFormat epf
>
void Test( const CSVLine & csv, const char *name, TR exp, T1 a, __m128i expMask=_mm_set1_epi32(0xFFFFFFFF) )
{
    unsigned int cycles=0;
    PrintName( name, csv.source );
    if(REF_RUN   ){ cycles=0;         TRY( p::Test<TR,T1,epf,fn_ref    >( cycles,exp,a,expMask ) ); } else { PrintSpace(); }
    if(SSE2_RUN  ){ cycles=csv.SSE2;  TRY( p::Test<TR,T1,epf,fn_sse2   >( cycles,exp,a,expMask ) ); } else { PrintSpace(); }
    if(SSE3_RUN  ){ cycles=csv.SSE3;  TRY( p::Test<TR,T1,epf,fn_sse3   >( cycles,exp,a,expMask ) ); } else { PrintSpace(); }
	if(SSSE3_RUN ){ cycles=csv.SSSE3; TRY( p::Test<TR,T1,epf,fn_ssse3  >( cycles,exp,a,expMask ) ); } else { PrintSpace(); }
    if(SSE4A_RUN ){ cycles=csv.SSE4a; TRY( p::Test<TR,T1,epf,fn_sse4a  >( cycles,exp,a,expMask ) ); } else { PrintSpace(); }
    if(SSE4_1_RUN){ cycles=csv.SSE41; TRY( p::Test<TR,T1,epf,fn_sse4_1 >( cycles,exp,a,expMask ) ); } else { PrintSpace(); }   
    PrintErrors( p::errorList );
			
	MMX_EMPTY;
}

//====================================

template< 
    typename TR, typename T1, typename T2,
    TR (*fn_ref    )(T1,T2), bool REF_RUN,
    TR (*fn_sse2   )(T1,T2), bool SSE2_RUN,
	TR (*fn_sse3   )(T1,T2), bool SSE3_RUN,
	TR (*fn_ssse3  )(T1,T2), bool SSSE3_RUN,
    TR (*fn_sse4a  )(T1,T2), bool SSE4A_RUN,
    TR (*fn_sse4_1 )(T1,T2), bool SSE4_1_RUN,
    enumPrintFormat epf
>
void Test( const CSVLine & csv, const char *name, TR exp, T1 a, T2 b, __m128i expMask=_mm_set1_epi32(0xFFFFFFFF) )
{
    unsigned int cycles=0;
    PrintName( name, csv.source );
    if(REF_RUN   ){ cycles=0;         TRY( p::Test<TR,T1,T2,epf,fn_ref    >( cycles,exp,a,b,expMask ) ); } else { PrintSpace(); }
    if(SSE2_RUN  ){ cycles=csv.SSE2;  TRY( p::Test<TR,T1,T2,epf,fn_sse2   >( cycles,exp,a,b,expMask ) ); } else { PrintSpace(); }
    if(SSE3_RUN  ){ cycles=csv.SSE3;  TRY( p::Test<TR,T1,T2,epf,fn_sse3   >( cycles,exp,a,b,expMask ) ); } else { PrintSpace(); }
	if(SSSE3_RUN ){ cycles=csv.SSSE3; TRY( p::Test<TR,T1,T2,epf,fn_ssse3  >( cycles,exp,a,b,expMask ) ); } else { PrintSpace(); }
    if(SSE4A_RUN ){ cycles=csv.SSE4a; TRY( p::Test<TR,T1,T2,epf,fn_sse4a  >( cycles,exp,a,b,expMask ) ); } else { PrintSpace(); }
    if(SSE4_1_RUN){ cycles=csv.SSE41; TRY( p::Test<TR,T1,T2,epf,fn_sse4_1 >( cycles,exp,a,b,expMask ) ); } else { PrintSpace(); }  
    PrintErrors( p::errorList );
	MMX_EMPTY;
}

//====================================

template< 
    typename TR, typename T1, typename T2, typename T3, 
    TR(*fn_ref    )(T1,T2,T3), bool REF_RUN,
    TR(*fn_sse2   )(T1,T2,T3), bool SSE2_RUN,
    TR(*fn_sse3   )(T1,T2,T3), bool SSE3_RUN,
	TR(*fn_ssse3  )(T1,T2,T3), bool SSSE3_RUN,
    TR(*fn_sse4a  )(T1,T2,T3), bool SSE4A_RUN,
	TR(*fn_sse4_1 )(T1,T2,T3), bool SSE4_1_RUN,
    enumPrintFormat epf 
>
void Test( const CSVLine & csv, const char *name, TR exp, T1 a, T2 b, T3 c, __m128i expMask=_mm_set1_epi32(0xFFFFFFFF) )
{
    unsigned int cycles=0;
    PrintName( name, csv.source );
    if(REF_RUN   ){ cycles=0;         TRY( p::Test<TR,T1,T2,T3,epf,fn_ref    >( cycles,exp,a,b,c,expMask ) ); } else { PrintSpace(); }
    if(SSE2_RUN  ){ cycles=csv.SSE2;  TRY( p::Test<TR,T1,T2,T3,epf,fn_sse2   >( cycles,exp,a,b,c,expMask ) ); } else { PrintSpace(); }
    if(SSE3_RUN  ){ cycles=csv.SSE3;  TRY( p::Test<TR,T1,T2,T3,epf,fn_sse3   >( cycles,exp,a,b,c,expMask ) ); } else { PrintSpace(); }
	if(SSSE3_RUN ){ cycles=csv.SSSE3; TRY( p::Test<TR,T1,T2,T3,epf,fn_ssse3  >( cycles,exp,a,b,c,expMask ) ); } else { PrintSpace(); }
    if(SSE4A_RUN ){ cycles=csv.SSE4a; TRY( p::Test<TR,T1,T2,T3,epf,fn_sse4a  >( cycles,exp,a,b,c,expMask ) ); } else { PrintSpace(); }
    if(SSE4_1_RUN){ cycles=csv.SSE41; TRY( p::Test<TR,T1,T2,T3,epf,fn_sse4_1 >( cycles,exp,a,b,c,expMask ) ); } else { PrintSpace(); }
    PrintErrors( p::errorList );
	MMX_EMPTY;
}

//====================================

template< 
    typename TR, typename T1, typename T2, typename T3, typename T4,
    TR(*fn_ref    )(T1,T2,T3,T4), bool REF_RUN,
    TR(*fn_sse2   )(T1,T2,T3,T4), bool SSE2_RUN,
    TR(*fn_sse3   )(T1,T2,T3,T4), bool SSE3_RUN,
	TR(*fn_ssse3  )(T1,T2,T3,T4), bool SSSE3_RUN,
    TR(*fn_sse4a  )(T1,T2,T3,T4), bool SSE4A_RUN,
	TR(*fn_sse4_1 )(T1,T2,T3,T4), bool SSE4_1_RUN,
    enumPrintFormat epf 
>
void Test( const CSVLine & csv, const char *name, TR exp, T1 a, T2 b, T3 c, T4 d, __m128i expMask=_mm_set1_epi32(0xFFFFFFFF) )
{
    unsigned int cycles=0;
    PrintName( name, csv.source );
    if(REF_RUN   ){ cycles=0;         TRY( p::Test<TR,T1,T2,T3,T4,epf,fn_ref    >( cycles,exp,a,b,c,d,expMask ) ); } else { PrintSpace(); }
    if(SSE2_RUN  ){ cycles=csv.SSE2;  TRY( p::Test<TR,T1,T2,T3,T4,epf,fn_sse2   >( cycles,exp,a,b,c,d,expMask ) ); } else { PrintSpace(); }
    if(SSE3_RUN  ){ cycles=csv.SSE3;  TRY( p::Test<TR,T1,T2,T3,T4,epf,fn_sse3   >( cycles,exp,a,b,c,d,expMask ) ); } else { PrintSpace(); }
	if(SSSE3_RUN ){ cycles=csv.SSSE3; TRY( p::Test<TR,T1,T2,T3,T4,epf,fn_ssse3  >( cycles,exp,a,b,c,d,expMask ) ); } else { PrintSpace(); }
    if(SSE4A_RUN ){ cycles=csv.SSE4a; TRY( p::Test<TR,T1,T2,T3,T4,epf,fn_sse4a  >( cycles,exp,a,b,c,d,expMask ) ); } else { PrintSpace(); }
    if(SSE4_1_RUN){ cycles=csv.SSE41; TRY( p::Test<TR,T1,T2,T3,T4,epf,fn_sse4_1 >( cycles,exp,a,b,c,d,expMask ) ); } else { PrintSpace(); }
    PrintErrors( p::errorList );
	MMX_EMPTY;
}

//====================================

#endif // __TEST_H__
