//
// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
//
#ifndef __TEST_H__
#define __TEST_H__

#include "csvTable.h"
#include "../../../SSEPlus/include/SSEPlus_platform.h"
#include "../../../SSEPlus/include/SSEPlus_CPUID.h"
#include <list>

#if defined(SSP_MSVC)

#include <windows.h>
#include <intrin.h>
#define get_rdtsc __rdtsc

#elif defined(SSP_GNUC)

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

        Timer()
        :start( get_rdtsc() ){}

        double Elapsed()
        {
            ssp_u64 stop = get_rdtsc(); 

            double elapsed = (double)(stop-start) / LOOP_COUNT;     

            if( elapsed > 9999.9 )
                elapsed = 9999.9;

            if( elapsed < 0 )
                elapsed = 0;

            return elapsed;          
        }
    };

    std::string errorList;    

    //
    // Equal
    // 
    

    template< typename T >
    bool Equal_f32( T value, T expected ) // Floating point compare
    {
        if( !memcmp(&value, &expected, sizeof(T)) )
            return true;        

        ssp_m128 V, E;
        V.f = *((__m128*)&value    );   
        E.f = *((__m128*)&expected ); 

		unsigned int elements = sizeof(T)/sizeof(float);
        for( unsigned int i=0; i<elements; ++i )
        {
            if( V.f32[i] > 0 )
            {
                if( (V.f32[i] < E.f32[i] * (1.0f-SSP_F32_ALLOWANCE)) 
                 || (V.f32[i] > E.f32[i] * (1.0f+SSP_F32_ALLOWANCE)) ) return false;
            }
            else
            {
                if( (V.f32[i] > E.f32[i] * (1.0f-SSP_F32_ALLOWANCE)) 
                 || (V.f32[i] < E.f32[i] * (1.0f+SSP_F32_ALLOWANCE)) ) return false;

            } 

            if(  V.f32[i] != V.f32[i] ) return false; //NAN
            if(  E.f32[i] != E.f32[i] ) return false; //NAN
        }
        return true;
    }

    template< typename T >
    bool Equal_f64( T value, T expected ) // Floating point compare
    {
        if( !memcmp(&value, &expected, sizeof(T)) )
            return true;     

        ssp_m128 V, E;
        V.d = *((__m128d*)&value    );   
        E.d = *((__m128d*)&expected ); 

		unsigned int elements = sizeof(T)/sizeof(double);
        for( unsigned int i=0; i<elements; ++i )
        {
            if( V.f64[i] > 0 )
            {
                if( (V.f64[i] < E.f64[i] * (1.0-SSP_F64_ALLOWANCE)) 
                 || (V.f64[i] > E.f64[i] * (1.0+SSP_F64_ALLOWANCE)) ) return false;
            }
            else
            {
                if( (V.f64[i] > E.f64[i] * (1.0-SSP_F64_ALLOWANCE)) 
                 || (V.f64[i] < E.f64[i] * (1.0+SSP_F64_ALLOWANCE)) ) return false;

            }    
			
			if(  V.f64[i] != V.f64[i] ) return false; //NAN
            if(  E.f64[i] != E.f64[i] ) return false; //NAN
        }
        return true;
    }

    template< enumPrintFormat epf, typename T >
    void ReportNotEqual(  T value, T expected )
    {
        std::ostringstream oss;
        oss << "ERROR[ "    << ToStr<epf>(value   ) << " ] ";
        oss << "Expected[ " << ToStr<epf>(expected) << " ]";

        errorList += " " + oss.str();
    }    

     
    template< enumPrintFormat epf, typename T >
    bool Equal( T value, T expected, __m128i expMask )
    {
        bool equal = true;

        if( 16 == sizeof(T) )   
        {
            __m128i tmp = *((__m128i*)&value);      // Apply the mask to the actual value
            tmp = _mm_and_si128( tmp, expMask );
            value = *((T*)&tmp);           

            tmp = *((__m128i*)&expected);           // Apply the mask to the expected value
	        tmp = _mm_and_si128( tmp, expMask );
	        expected = *((T*)&tmp);     

            switch( epf )
            {
                case enum_ssp_f32: equal = Equal_f32( value, expected );                break;
                case enum_ssp_f64: equal = Equal_f64( value, expected );                break;
                default:           equal = (0 == memcmp(&value,&expected,sizeof(T) ));  break;
            }
        } 
        else
        {
            equal = memcmp( &value, &expected, sizeof(T) ) == 0;
        }               
        
        if( !equal )
            ReportNotEqual< epf, T >( value, expected );  

        return equal;
    }  

    template< enumPrintFormat epf >
    bool Equal( __m128i * value, __m128i * expected )
    {
        bool equal = memcmp( value, expected, sizeof(__m128i) ) == 0;

        if( !equal )
           ReportNotEqual< epf, __m128i >( *value, *expected );

        return equal;
    }

    //
    // Test
    //

    ssp_u32 g_no_opt=0;
    #define NO_OPT( a ) g_no_opt = *(ssp_u32*)&a;    

    template< typename TR, typename T1, enumPrintFormat epf, TR(*fn)(T1) >
    double Test( TR exp, T1 a, __m128i expMask )
    {
        TR out = fn( a );
        if( !Equal<epf>( out, exp, expMask ) )
            return -1.0;

        Timer t;    
        for( int i=0; i<LOOP_COUNT; ++i )
            out = fn( out ); 

        double elapsed = t.Elapsed();

        NO_OPT( out );
        return elapsed;        
    }    

    template< typename TR, typename T1, typename T2, enumPrintFormat epf, TR(*fn)(T1,T2) >
    double Test( TR exp, T1 a, T2 b, __m128i expMask )
    {   
        TR out = fn( a,b );
        if( !Equal<epf>( out, exp, expMask ) )
            return -1.0;

        Timer t;    
        for( int i=0; i<LOOP_COUNT; ++i )
            out = fn( out,b );  
        double elapsed = t.Elapsed();

        NO_OPT( out );  
        return elapsed;   
    }   

    template< typename TR, typename T1, typename T2, typename T3, enumPrintFormat epf, TR(*fn)(T1,T2,T3) >
    double Test( TR exp, T1 a, T2 b, T3 c, __m128i expMask )
    {
        TR out = fn( a,b,c );
        if( !Equal<epf>( out, exp, expMask ))
            return -1.0;

        Timer t;    
        for( int i=0; i<LOOP_COUNT; ++i )
            out = fn( out,b,c );  
        double elapsed = t.Elapsed();

        NO_OPT( out );
        return elapsed;   
    }

    template< typename TR, typename T1, typename T2, typename T3, typename T4, enumPrintFormat epf, TR(*fn)(T1,T2,T3,T4) >
    double Test( TR exp, T1 a, T2 b, T3 c, T4 d, __m128i expMask )
    {
        TR out = fn( a,b,c,d );
        if( !Equal<epf>( out, exp, expMask ))
            return -1.0;

        Timer t;    
        for( int i=0; i<LOOP_COUNT; ++i )
            out = fn( out,b,c,d );    
        double elapsed = t.Elapsed();

        NO_OPT( out );
        return elapsed;   
    }

    // Type specific overloads

    template< typename TR, typename T1, enumPrintFormat epf, TR(*fn)(T1) >
    double Test( __m128i exp, int a, __m128i expMask )
    {
        TR out = fn( a );
        if( !Equal<epf>( out, exp, expMask ))
            return -1.0;

        Timer t;    
        for( int i=0; i<LOOP_COUNT; ++i )
        {
            out = fn( a ); 
            out = _mm_xor_si128(out, out);
        }
        double elapsed = t.Elapsed();

        NO_OPT( out );
        return elapsed;   
    }

    template< typename TR, typename T1, enumPrintFormat epf, TR(*fn)(T1) >
    double Test( __m128i exp, unsigned char a, __m128i expMask )
    {
        TR out = fn( a );
        if( !Equal<epf>( out, exp, expMask ))
            return -1.0;

        Timer t;    
        for( int i=0; i<LOOP_COUNT; ++i )
        {
            out = fn( a ); 
            out = _mm_xor_si128(out, out);
        }
        double elapsed = t.Elapsed();

        NO_OPT( out );
        return elapsed;   
    }

    template< typename TR, typename T1, enumPrintFormat epf, TR(*fn)(T1) >
    double Test( TR exp, const __m128i * a, __m128i expMask )//This is a load. TODO: ?
    {
        TR out = fn( a );
        if( !Equal<epf>( out, exp, expMask ))
            return -1.0;

        Timer t;    
        for( int i=0; i<LOOP_COUNT; ++i )
            out = fn( a ); 
        double elapsed = t.Elapsed();

        NO_OPT( out );
        return elapsed;   
    }

    template< typename TR, typename T1, enumPrintFormat epf, TR(*fn)(T1) >
    double Test( TR exp, const double * a, __m128i expMask )//This is a load. TODO: ?
    {
        TR out = fn( a );
        if( !Equal<epf>( out, exp, expMask ))
            return -1.0;

        Timer t;    
        for( int i=0; i<LOOP_COUNT; ++i )
            out = fn( a ); 
        double elapsed = t.Elapsed();

        NO_OPT( out );
        return elapsed;   
    }

    template< typename TR, typename T1, typename T2, enumPrintFormat epf, TR(*fn)(T1,T2) >
    double Test( int exp, T1 a, T2 b, __m128i expMask )
    {
        TR out = fn( a,b );
        if( !Equal<epf>( out, exp, expMask ))
            return -1.0;

        Timer t;    
        for( int i=0; i<LOOP_COUNT; ++i )
            out |= fn( a, b );    
        double elapsed = t.Elapsed();

        NO_OPT( out );
        return elapsed;   
    }

    template< typename TEXP, typename T1, typename T2, typename TR, enumPrintFormat epf, TR(*fn)(T1,T2) >
    double Test( TEXP exp, T1 a, T2 b )
    {   
        fn( a,b );
       
        if( *exp != *a )
            return -1.0;

        Timer t;    
        for( int i=0; i<LOOP_COUNT; ++i )
        {
            *a = *a+1;
            fn( a, b );    
        }
        double elapsed = t.Elapsed();

        return elapsed;   
    } 

    template< typename TR, typename T1, typename T2, enumPrintFormat epf, TR(*fn)(T1,T2) >
    double Test( ssp_s64 exp, T1 a, T2 b, __m128i expMask )
    {
        TR out = fn( a,b );
        if( !Equal<epf>( out, exp, expMask ))
            return -1.0;

        Timer t;  
        for( int i=0; i<LOOP_COUNT; ++i )
            out = fn( a, (T2)out ); 

        double elapsed = t.Elapsed();

        NO_OPT( out );
        return elapsed;   
    }

    //
    // VOID
    //

    template< enumPrintFormat epf, void(*fn)(__m128i*,__m128i*,__m128i*) >
    double Test( __m128i* a_in, __m128i* a_exp, __m128i* b_in, __m128i* b_exp, __m128i* c_in, __m128i* c_exp )
    {
        __m128i a_bak = *a_in; 
        __m128i b_bak = *b_in;
        __m128i c_bak = *c_in;

        fn( a_in,b_in,c_in );

        bool equal  = Equal<epf>( a_in, a_exp );
             equal &= Equal<epf>( b_in, b_exp );
             equal &= Equal<epf>( c_in, c_exp );

        if( !equal ) 
            return -1.0;

        Timer t;    
        for( int i=0; i<LOOP_COUNT; ++i )
            fn( a_in, b_in, c_in );    
        double elapsed = t.Elapsed();

        NO_OPT( a_in );

        *a_in = a_bak;
        *b_in = b_bak;
        *c_in = c_bak;

        return elapsed;   
    }

    template< enumPrintFormat epf, void(*fn)(__m128i*,__m128i*,__m128i*,__m128i*) >
    double Test( __m128i* a_in, __m128i* a_exp, __m128i* b_in, __m128i* b_exp, __m128i* c_in, __m128i* c_exp, __m128i* d_in, __m128i* d_exp )
    {
        __m128i a_bak = *a_in; 
        __m128i b_bak = *b_in;
        __m128i c_bak = *c_in;
        __m128i d_bak = *d_in;

        fn( a_in,b_in,c_in,d_in );

        bool equal  = Equal<epf>( a_in, a_exp );
             equal &= Equal<epf>( b_in, b_exp );
             equal &= Equal<epf>( c_in, c_exp );
             equal &= Equal<epf>( d_in, d_exp );

        if( !equal ) 
            return -1.0;

        Timer t;    
        for( int i=0; i<LOOP_COUNT; ++i )
            fn( a_in, b_in, c_in, d_in );    
        double elapsed = t.Elapsed();

        NO_OPT( a_in );

        *a_in = a_bak;
        *b_in = b_bak;
        *c_in = c_bak;
        *d_in = d_bak;

        return elapsed;   
    }
};

#ifdef SSP_MSVC

// STATUS_ILLEGAL_INSTRUCTION #include <windows.h> 
#define TRY(  ... )             \
        try                     \
        {                       \
            __VA_ARGS__;        \
        }                       \
        catch( ... )            \
        {                       \
            tmp = -2.0;         \
        }

#endif

#ifdef SSP_GNUC

#define SSP_SIGILL_RET 1
sigjmp_buf env;

void handle_illegal_instruction(int num)
{
	if(num == SIGILL)
	{
		signal(SIGILL, handle_illegal_instruction);
		siglongjmp(env, SSP_SIGILL_RET);
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
	    else if(sj == SSP_SIGILL_RET)                      \
	    {                                                      \
	        tmp = -2.0;                                       \
	    }                                                      \
	    else                                                   \
	    {                                                      \
	        printf("Unhandled setjmp return, exiting ...\n");  \
	        exit(-1);                                          \
	    }                                                      \
        }

#endif

void Setup_Paths( bool enable[ SSP_SSE_COUNT ],
                  bool do_REF,   bool do_SSE,    bool do_SSE2,   bool do_SSE3,   bool do_SSSE3, 
                  bool do_SSE4a, bool do_SSE4_1, bool do_SSE4_2, bool do_SSE5 )
{ 
    enable[SSP_REF    ] = do_REF;
    enable[SSP_SSE    ] = do_SSE    && ssp_is_supported(SSP_SSE   );
    enable[SSP_SSE2   ] = do_SSE2   && ssp_is_supported(SSP_SSE2  );
    enable[SSP_SSE3   ] = do_SSE3   && ssp_is_supported(SSP_SSE3  );
    enable[SSP_SSSE3  ] = do_SSSE3  && ssp_is_supported(SSP_SSSE3 );
    enable[SSP_SSE4a  ] = do_SSSE3  && ssp_is_supported(SSP_SSE4a );
    enable[SSP_SSE4_1 ] = do_SSE4_1 && ssp_is_supported(SSP_SSE4_1);
    enable[SSP_SSE4_2 ] = do_SSE4_2 && ssp_is_supported(SSP_SSE4_2);
    enable[SSP_SSE5   ] = do_SSE5   && ssp_is_supported(SSP_SSE5  );
}


void Cleanup( double res[ SSP_SSE_COUNT ], std::string &errorList, const CSVLine & csv, 
                  bool do_REF,   bool do_SSE,    bool do_SSE2,   bool do_SSE3,   bool do_SSSE3, 
                  bool do_SSE4a, bool do_SSE4_1, bool do_SSE4_2, bool do_SSE5 )
{
    if     ( !do_REF                       ){ PrintSpace    ( csv.REF                  );} 
    else if( -1 == res[SSP_REF]            ){ PrintFail     ( csv.REF                  );}
    else if( -2 == res[SSP_REF]            ){ PrintException( csv.REF                  );}
    else                                    { PrintResult   ( csv.REF, res[SSP_REF]    );}  

    if     ( !do_SSE                       ){ PrintSpace    (csv.SSE                   );} 
    else if( !ssp_is_supported(SSP_SSE    )){ PrintDisabled (csv.SSE                   );} 
    else if( -1 == res[SSP_SSE ]           ){ PrintFail     (csv.SSE                   );}
    else if( -2 == res[SSP_SSE ]           ){ PrintException(csv.SSE                   );}
    else                                    { PrintResult   (csv.SSE ,res[SSP_SSE ]    );}  

    if     ( !do_SSE2                      ){ PrintSpace    (csv.SSE2                  );} 
    else if( !ssp_is_supported(SSP_SSE2   )){ PrintDisabled (csv.SSE2                  );} 
    else if( -1 == res[SSP_SSE2]           ){ PrintFail     (csv.SSE2                  );}
    else if( -2 == res[SSP_SSE2]           ){ PrintException(csv.SSE2                  );}
    else                                    { PrintResult   (csv.SSE2,res[SSP_SSE2]    );}  

    if     ( !do_SSE3                      ){ PrintSpace    (csv.SSE3                  );} 
    else if( !ssp_is_supported(SSP_SSE3   )){ PrintDisabled (csv.SSE3                  );} 
    else if( -1 == res[SSP_SSE3]           ){ PrintFail     (csv.SSE3                  );}
    else if( -2 == res[SSP_SSE3]           ){ PrintException(csv.SSE3                  );}
    else                                    { PrintResult   (csv.SSE3,res[SSP_SSE3]    );}  

    if     ( !do_SSSE3                     ){ PrintSpace    (csv.SSSE3                 );} 
    else if( !ssp_is_supported(SSP_SSSE3  )){ PrintDisabled (csv.SSSE3                 );} 
    else if( -1 == res[SSP_SSSE3]          ){ PrintFail     (csv.SSSE3                 );}
    else if( -2 == res[SSP_SSSE3]          ){ PrintException(csv.SSSE3                 );}
    else                                    { PrintResult   (csv.SSSE3,res[SSP_SSSE3]  );}  

    if     ( !do_SSE4a                     ){ PrintSpace    (csv.SSE4a                 );} 
    else if( !ssp_is_supported(SSP_SSE4a  )){ PrintDisabled (csv.SSE4a                 );} 
    else if( -1 == res[SSP_SSE4a]          ){ PrintFail     (csv.SSE4a                 );}
    else if( -2 == res[SSP_SSE4a]          ){ PrintException(csv.SSE4a                 );}
    else                                    { PrintResult   (csv.SSE4a,res[SSP_SSE4a]  );}   

    if     ( !do_SSE4_1                    ){ PrintSpace    (csv.SSE4_1                );} 
    else if( !ssp_is_supported(SSP_SSE4_1 )){ PrintDisabled (csv.SSE4_1                );} 
    else if( -1 == res[SSP_SSE4_1]         ){ PrintFail     (csv.SSE4_1                );}
    else if( -2 == res[SSP_SSE4_1]         ){ PrintException(csv.SSE4_1                );}
    else                                    { PrintResult   (csv.SSE4_1,res[SSP_SSE4_1]);} 

    if     ( !do_SSE4_2                    ){ PrintSpace    (csv.SSE4_2               );} 
    else if( !ssp_is_supported(SSP_SSE4_2 )){ PrintDisabled (csv.SSE4_2                );} 
    else if( -1 == res[SSP_SSE4_2]         ){ PrintFail     (csv.SSE4_2                );}
    else if( -2 == res[SSP_SSE4_2]         ){ PrintException(csv.SSE4_2                );}
    else                                    { PrintResult   (csv.SSE4_2,res[SSP_SSE4_2]);} 

    if     ( !do_SSE5                      ){ PrintSpace    (csv.SSE5                  );} 
    else if( !ssp_is_supported(SSP_SSE5   )){ PrintDisabled (csv.SSE5                  );} 
    else if( -1 == res[SSP_SSE5]           ){ PrintFail     (csv.SSE5                  );}
    else if( -2 == res[SSP_SSE5]           ){ PrintException(csv.SSE5                  );}
    else                                    { PrintResult   (csv.SSE5,res[SSP_SSE5]    );} 

    PrintErrors( errorList ); 
}   


// Will print either
// nothing      function is disabled
// "-"          function is not supported in hardware 
// "x"          function threw exception
// "123"        cycle time (prints from the destructor of the timer)


//
// External Test Entry Points (void return type)
// 
//====================================
template< 
    typename TEXP, typename T1, typename T2, typename TR,
    bool do_REF   ,TR(*fn_ref    )(T1,T2), 
    bool do_SSE   ,TR(*fn_sse    )(T1,T2), 
    bool do_SSE2  ,TR(*fn_sse2   )(T1,T2), 
	bool do_SSE3  ,TR(*fn_sse3   )(T1,T2), 
	bool do_SSSE3 ,TR(*fn_ssse3  )(T1,T2), 
    bool do_SSE4a ,TR(*fn_sse4a  )(T1,T2), 
    bool do_SSE4_1,TR(*fn_sse4_1 )(T1,T2), 
    bool do_SSE4_2,TR(*fn_sse4_2 )(T1,T2), 
    bool do_SSE5  ,TR(*fn_sse5   )(T1,T2), 
    enumPrintFormat epf
>
void Test( const CSVLine & csv, const char *name, TEXP exp, T1 a, T2 b )
{
    PrintName( name, csv.assembly, csv.source );    
    
    bool   enable[ SSP_SSE_COUNT ];
    double res   [ SSP_SSE_COUNT ], tmp;    // tmp indirection allows use of macro

    Setup_Paths( enable, do_REF, do_SSE, do_SSE2, do_SSE3, do_SSSE3, do_SSE4a, do_SSE4_1, do_SSE4_2, do_SSE5 );      
    
    if( enable[SSP_REF   ] ){ TRY( tmp=p::Test<TEXP,T1,T2,TR,epf,fn_ref    >( exp,a,b ) ); res[SSP_REF   ]=tmp; } 
    if( enable[SSP_SSE   ] ){ TRY( tmp=p::Test<TEXP,T1,T2,TR,epf,fn_sse    >( exp,a,b ) ); res[SSP_SSE   ]=tmp; } 
    if( enable[SSP_SSE2  ] ){ TRY( tmp=p::Test<TEXP,T1,T2,TR,epf,fn_sse2   >( exp,a,b ) ); res[SSP_SSE2  ]=tmp; } 
    if( enable[SSP_SSE3  ] ){ TRY( tmp=p::Test<TEXP,T1,T2,TR,epf,fn_sse3   >( exp,a,b ) ); res[SSP_SSE3  ]=tmp; } 
    if( enable[SSP_SSSE3 ] ){ TRY( tmp=p::Test<TEXP,T1,T2,TR,epf,fn_ssse3  >( exp,a,b ) ); res[SSP_SSSE3 ]=tmp; }
    if( enable[SSP_SSE4a ] ){ TRY( tmp=p::Test<TEXP,T1,T2,TR,epf,fn_sse4a  >( exp,a,b ) ); res[SSP_SSE4a ]=tmp; }
    if( enable[SSP_SSE4_1] ){ TRY( tmp=p::Test<TEXP,T1,T2,TR,epf,fn_sse4_1 >( exp,a,b ) ); res[SSP_SSE4_1]=tmp; }
    if( enable[SSP_SSE4_2] ){ TRY( tmp=p::Test<TEXP,T1,T2,TR,epf,fn_sse4_2 >( exp,a,b ) ); res[SSP_SSE4_2]=tmp; }
    if( enable[SSP_SSE5  ] ){ TRY( tmp=p::Test<TEXP,T1,T2,TR,epf,fn_sse5   >( exp,a,b ) ); res[SSP_SSE5  ]=tmp; }

    Cleanup( res, p::errorList, csv, do_REF, do_SSE, do_SSE2, do_SSE3, do_SSSE3, do_SSE4a, do_SSE4_1, do_SSE4_2, do_SSE5 );    
}


//
// External Test Entry Points
// 
//====================================
template< 
    typename TR, typename T1, 
    bool do_REF   ,TR(*fn_ref    )(T1), 
    bool do_SSE   ,TR(*fn_sse    )(T1), 
    bool do_SSE2  ,TR(*fn_sse2   )(T1), 
	bool do_SSE3  ,TR(*fn_sse3   )(T1), 
    bool do_SSSE3 ,TR(*fn_ssse3  )(T1), 
    bool do_SSE4a ,TR(*fn_sse4a  )(T1), 
    bool do_SSE4_1,TR(*fn_sse4_1 )(T1), 
    bool do_SSE4_2,TR(*fn_sse4_2 )(T1), 
    bool do_SSE5  ,TR(*fn_sse5   )(T1), 
    enumPrintFormat epf
>
void Test( const CSVLine & csv, const char *name, TR exp, T1 a, __m128i expMask=_mm_set1_epi32(0xFFFFFFFF) )
{
    if( g_update && csv.useCount>1) 
        return;

    unsigned int cycles=0;
    PrintName( name, csv.assembly, csv.source );

    bool enable[ SSP_SSE_COUNT ];
    double res [ SSP_SSE_COUNT ], tmp;  // tmp indirection allows use of macro

    Setup_Paths( enable, do_REF, do_SSE, do_SSE2, do_SSE3, do_SSSE3, do_SSE4a, do_SSE4_1, do_SSE4_2, do_SSE5 );      

    if( enable[SSP_REF   ] ){ TRY( tmp=p::Test<TR,T1,epf,fn_ref    >( exp,a,expMask ) ); res[SSP_REF   ]=tmp; } 
    if( enable[SSP_SSE   ] ){ TRY( tmp=p::Test<TR,T1,epf,fn_sse    >( exp,a,expMask ) ); res[SSP_SSE   ]=tmp; } 
    if( enable[SSP_SSE2  ] ){ TRY( tmp=p::Test<TR,T1,epf,fn_sse2   >( exp,a,expMask ) ); res[SSP_SSE2  ]=tmp; } 
    if( enable[SSP_SSE3  ] ){ TRY( tmp=p::Test<TR,T1,epf,fn_sse3   >( exp,a,expMask ) ); res[SSP_SSE3  ]=tmp; } 
	if( enable[SSP_SSSE3 ] ){ TRY( tmp=p::Test<TR,T1,epf,fn_ssse3  >( exp,a,expMask ) ); res[SSP_SSSE3 ]=tmp; } 
    if( enable[SSP_SSE4a ] ){ TRY( tmp=p::Test<TR,T1,epf,fn_sse4a  >( exp,a,expMask ) ); res[SSP_SSE4a ]=tmp; } 
    if( enable[SSP_SSE4_1] ){ TRY( tmp=p::Test<TR,T1,epf,fn_sse4_1 >( exp,a,expMask ) ); res[SSP_SSE4_1]=tmp; }  
    if( enable[SSP_SSE4_2] ){ TRY( tmp=p::Test<TR,T1,epf,fn_sse4_2 >( exp,a,expMask ) ); res[SSP_SSE4_2]=tmp; }  
    if( enable[SSP_SSE5  ] ){ TRY( tmp=p::Test<TR,T1,epf,fn_sse5   >( exp,a,expMask ) ); res[SSP_SSE5  ]=tmp; }  
    
    Cleanup( res, p::errorList, csv, do_REF, do_SSE, do_SSE2, do_SSE3, do_SSSE3, do_SSE4a, do_SSE4_1, do_SSE4_2, do_SSE5 );    
}

//====================================

template< 
    typename TR, typename T1, typename T2,
    bool do_REF   ,TR (*fn_ref    )(T1,T2), 
    bool do_SSE   ,TR (*fn_sse    )(T1,T2), 
    bool do_SSE2  ,TR (*fn_sse2   )(T1,T2), 
	bool do_SSE3  ,TR (*fn_sse3   )(T1,T2), 
	bool do_SSSE3 ,TR (*fn_ssse3  )(T1,T2), 
    bool do_SSE4a ,TR (*fn_sse4a  )(T1,T2), 
    bool do_SSE4_1,TR (*fn_sse4_1 )(T1,T2), 
    bool do_SSE4_2,TR (*fn_sse4_2 )(T1,T2), 
    bool do_SSE5  ,TR (*fn_sse5   )(T1,T2), 
    enumPrintFormat epf
>
void Test( const CSVLine & csv, const char *name, TR exp, T1 a, T2 b, __m128i expMask=_mm_set1_epi32(0xFFFFFFFF) )
{
     if( g_update && csv.useCount>1) 
        return;

    unsigned int cycles=0;
    PrintName( name, csv.assembly, csv.source );

    bool enable[ SSP_SSE_COUNT ];
    double res [ SSP_SSE_COUNT ], tmp;  // tmp indirection allows use of macro

    Setup_Paths( enable, do_REF, do_SSE, do_SSE2, do_SSE3, do_SSSE3, do_SSE4a, do_SSE4_1, do_SSE4_2, do_SSE5 );    

    if( enable[SSP_REF   ] ){ TRY( tmp=p::Test<TR,T1,T2,epf,fn_ref    >( exp,a,b,expMask ) ); res[SSP_REF   ]=tmp; } 
    if( enable[SSP_SSE   ] ){ TRY( tmp=p::Test<TR,T1,T2,epf,fn_sse    >( exp,a,b,expMask ) ); res[SSP_SSE   ]=tmp; } 
    if( enable[SSP_SSE2  ] ){ TRY( tmp=p::Test<TR,T1,T2,epf,fn_sse2   >( exp,a,b,expMask ) ); res[SSP_SSE2  ]=tmp; } 
    if( enable[SSP_SSE3  ] ){ TRY( tmp=p::Test<TR,T1,T2,epf,fn_sse3   >( exp,a,b,expMask ) ); res[SSP_SSE3  ]=tmp; } 
	if( enable[SSP_SSSE3 ] ){ TRY( tmp=p::Test<TR,T1,T2,epf,fn_ssse3  >( exp,a,b,expMask ) ); res[SSP_SSSE3 ]=tmp; } 
    if( enable[SSP_SSE4a ] ){ TRY( tmp=p::Test<TR,T1,T2,epf,fn_sse4a  >( exp,a,b,expMask ) ); res[SSP_SSE4a ]=tmp; } 
    if( enable[SSP_SSE4_1] ){ TRY( tmp=p::Test<TR,T1,T2,epf,fn_sse4_1 >( exp,a,b,expMask ) ); res[SSP_SSE4_1]=tmp; } 
    if( enable[SSP_SSE4_2] ){ TRY( tmp=p::Test<TR,T1,T2,epf,fn_sse4_2 >( exp,a,b,expMask ) ); res[SSP_SSE4_2]=tmp; } 
    if( enable[SSP_SSE5  ] ){ TRY( tmp=p::Test<TR,T1,T2,epf,fn_sse5   >( exp,a,b,expMask ) ); res[SSP_SSE5  ]=tmp; } 
    
    Cleanup( res, p::errorList, csv, do_REF, do_SSE, do_SSE2, do_SSE3, do_SSSE3, do_SSE4a, do_SSE4_1, do_SSE4_2, do_SSE5 );    
}

//====================================

template< 
    typename TR, typename T1, typename T2, typename T3, 
    bool do_REF   ,TR(*fn_ref    )(T1,T2,T3), 
    bool do_SSE   ,TR(*fn_sse    )(T1,T2,T3), 
    bool do_SSE2  ,TR(*fn_sse2   )(T1,T2,T3), 
    bool do_SSE3  ,TR(*fn_sse3   )(T1,T2,T3), 
	bool do_SSSE3 ,TR(*fn_ssse3  )(T1,T2,T3), 
    bool do_SSE4a ,TR(*fn_sse4a  )(T1,T2,T3), 
	bool do_SSE4_1,TR(*fn_sse4_1 )(T1,T2,T3), 
    bool do_SSE4_2,TR(*fn_sse4_2 )(T1,T2,T3), 
    bool do_SSE5  ,TR(*fn_sse5   )(T1,T2,T3), 
    enumPrintFormat epf 
>
void Test( const CSVLine & csv, const char *name, TR exp, T1 a, T2 b, T3 c, __m128i expMask=_mm_set1_epi32(0xFFFFFFFF) )
{
     if( g_update && csv.useCount>1) 
        return;

    unsigned int cycles=0;
    PrintName( name, csv.assembly, csv.source );

    bool enable[ SSP_SSE_COUNT ];
    double res [ SSP_SSE_COUNT ], tmp;  // tmp indirection allows use of macro

    Setup_Paths( enable, do_REF, do_SSE, do_SSE2, do_SSE3, do_SSSE3, do_SSE4a, do_SSE4_1, do_SSE4_2, do_SSE5 );    

    if( enable[SSP_REF   ] ){ TRY( tmp=p::Test<TR,T1,T2,T3,epf,fn_ref    >( exp,a,b,c,expMask ) ); res[SSP_REF   ]=tmp; } 
    if( enable[SSP_SSE   ] ){ TRY( tmp=p::Test<TR,T1,T2,T3,epf,fn_sse    >( exp,a,b,c,expMask ) ); res[SSP_SSE   ]=tmp; } 
    if( enable[SSP_SSE2  ] ){ TRY( tmp=p::Test<TR,T1,T2,T3,epf,fn_sse2   >( exp,a,b,c,expMask ) ); res[SSP_SSE2  ]=tmp; } 
    if( enable[SSP_SSE3  ] ){ TRY( tmp=p::Test<TR,T1,T2,T3,epf,fn_sse3   >( exp,a,b,c,expMask ) ); res[SSP_SSE3  ]=tmp; } 
	if( enable[SSP_SSSE3 ] ){ TRY( tmp=p::Test<TR,T1,T2,T3,epf,fn_ssse3  >( exp,a,b,c,expMask ) ); res[SSP_SSSE3 ]=tmp; } 
    if( enable[SSP_SSE4a ] ){ TRY( tmp=p::Test<TR,T1,T2,T3,epf,fn_sse4a  >( exp,a,b,c,expMask ) ); res[SSP_SSE4a ]=tmp; } 
    if( enable[SSP_SSE4_1] ){ TRY( tmp=p::Test<TR,T1,T2,T3,epf,fn_sse4_1 >( exp,a,b,c,expMask ) ); res[SSP_SSE4_1]=tmp; } 
    if( enable[SSP_SSE4_2] ){ TRY( tmp=p::Test<TR,T1,T2,T3,epf,fn_sse4_2 >( exp,a,b,c,expMask ) ); res[SSP_SSE4_2]=tmp; } 
    if( enable[SSP_SSE5  ] ){ TRY( tmp=p::Test<TR,T1,T2,T3,epf,fn_sse5   >( exp,a,b,c,expMask ) ); res[SSP_SSE5  ]=tmp; } 
    
    Cleanup( res, p::errorList, csv, do_REF, do_SSE, do_SSE2, do_SSE3, do_SSSE3, do_SSE4a, do_SSE4_1, do_SSE4_2, do_SSE5 );    
}

//====================================

template< 
    typename TR, typename T1, typename T2, typename T3, typename T4,
    bool do_REF   ,TR(*fn_ref    )(T1,T2,T3,T4), 
    bool do_SSE   ,TR(*fn_sse    )(T1,T2,T3,T4), 
    bool do_SSE2  ,TR(*fn_sse2   )(T1,T2,T3,T4), 
    bool do_SSE3  ,TR(*fn_sse3   )(T1,T2,T3,T4), 
	bool do_SSSE3 ,TR(*fn_ssse3  )(T1,T2,T3,T4), 
    bool do_SSE4a ,TR(*fn_sse4a  )(T1,T2,T3,T4), 
	bool do_SSE4_1,TR(*fn_sse4_1 )(T1,T2,T3,T4), 
    bool do_SSE4_2,TR(*fn_sse4_2 )(T1,T2,T3,T4), 
    bool do_SSE5  ,TR(*fn_sse5   )(T1,T2,T3,T4), 
    enumPrintFormat epf 
>
void Test( const CSVLine & csv, const char *name, TR exp, T1 a, T2 b, T3 c, T4 d, __m128i expMask=_mm_set1_epi32(0xFFFFFFFF) )
{
     if( g_update && csv.useCount>1) 
        return;

    unsigned int cycles=0;
    PrintName( name, csv.assembly, csv.source );

    bool enable[ SSP_SSE_COUNT ];
    double res [ SSP_SSE_COUNT ], tmp;  // tmp indirection allows use of macro

    Setup_Paths( enable, do_REF, do_SSE, do_SSE2, do_SSE3, do_SSSE3, do_SSE4a, do_SSE4_1, do_SSE4_2, do_SSE5 );    

    if( enable[SSP_REF   ] ){ TRY( tmp=p::Test<TR,T1,T2,T3,T4,epf,fn_ref    >( exp,a,b,c,d,expMask ) ); res[SSP_REF   ]=tmp; } 
    if( enable[SSP_SSE   ] ){ TRY( tmp=p::Test<TR,T1,T2,T3,T4,epf,fn_sse    >( exp,a,b,c,d,expMask ) ); res[SSP_SSE   ]=tmp; } 
    if( enable[SSP_SSE2  ] ){ TRY( tmp=p::Test<TR,T1,T2,T3,T4,epf,fn_sse2   >( exp,a,b,c,d,expMask ) ); res[SSP_SSE2  ]=tmp; } 
    if( enable[SSP_SSE3  ] ){ TRY( tmp=p::Test<TR,T1,T2,T3,T4,epf,fn_sse3   >( exp,a,b,c,d,expMask ) ); res[SSP_SSE3  ]=tmp; } 
	if( enable[SSP_SSSE3 ] ){ TRY( tmp=p::Test<TR,T1,T2,T3,T4,epf,fn_ssse3  >( exp,a,b,c,d,expMask ) ); res[SSP_SSSE3 ]=tmp; } 
    if( enable[SSP_SSE4a ] ){ TRY( tmp=p::Test<TR,T1,T2,T3,T4,epf,fn_sse4a  >( exp,a,b,c,d,expMask ) ); res[SSP_SSE4a ]=tmp; } 
    if( enable[SSP_SSE4_1] ){ TRY( tmp=p::Test<TR,T1,T2,T3,T4,epf,fn_sse4_1 >( exp,a,b,c,d,expMask ) ); res[SSP_SSE4_1]=tmp; } 
    if( enable[SSP_SSE4_2] ){ TRY( tmp=p::Test<TR,T1,T2,T3,T4,epf,fn_sse4_2 >( exp,a,b,c,d,expMask ) ); res[SSP_SSE4_2]=tmp; } 
    if( enable[SSP_SSE5  ] ){ TRY( tmp=p::Test<TR,T1,T2,T3,T4,epf,fn_sse5   >( exp,a,b,c,d,expMask ) ); res[SSP_SSE5  ]=tmp; } 
    
    Cleanup( res, p::errorList, csv, do_REF, do_SSE, do_SSE2, do_SSE3, do_SSSE3, do_SSE4a, do_SSE4_1, do_SSE4_2, do_SSE5 );    
}

//
// VOID functions
//

template< 
    typename T1, typename T2, typename T3,
    bool do_REF   ,void(*fn_ref    )(T1,T2,T3), 
    bool do_SSE   ,void(*fn_sse    )(T1,T2,T3), 
    bool do_SSE2  ,void(*fn_sse2   )(T1,T2,T3), 
    bool do_SSE3  ,void(*fn_sse3   )(T1,T2,T3), 
	bool do_SSSE3 ,void(*fn_ssse3  )(T1,T2,T3), 
    bool do_SSE4a ,void(*fn_sse4a  )(T1,T2,T3), 
	bool do_SSE4_1,void(*fn_sse4_1 )(T1,T2,T3), 
    bool do_SSE4_2,void(*fn_sse4_2 )(T1,T2,T3), 
    bool do_SSE5  ,void(*fn_sse5   )(T1,T2,T3), 
    enumPrintFormat epf 
>
void Test( const CSVLine & csv, const char *name, T1 a_exp, T2 b_exp, T3 c_exp,
                                                  T1 a_in , T2 b_in , T3 c_in  )
{
     if( g_update && csv.useCount>1) 
        return;

    unsigned int cycles=0;
    PrintName( name, csv.assembly, csv.source );

    bool enable[ SSP_SSE_COUNT ];
    double res [ SSP_SSE_COUNT ], tmp;  // tmp indirection allows use of TRY macro

    Setup_Paths( enable, do_REF, do_SSE, do_SSE2, do_SSE3, do_SSSE3, do_SSE4a, do_SSE4_1, do_SSE4_2, do_SSE5 );    

    if( enable[SSP_REF   ] ){ TRY( tmp=p::Test<epf,fn_ref    >( a_in,a_exp,b_in,b_exp,c_in,c_exp ) ); res[SSP_REF   ]=tmp; } 
    if( enable[SSP_SSE   ] ){ TRY( tmp=p::Test<epf,fn_sse    >( a_in,a_exp,b_in,b_exp,c_in,c_exp ) ); res[SSP_SSE   ]=tmp; } 
    if( enable[SSP_SSE2  ] ){ TRY( tmp=p::Test<epf,fn_sse2   >( a_in,a_exp,b_in,b_exp,c_in,c_exp ) ); res[SSP_SSE2  ]=tmp; } 
    if( enable[SSP_SSE3  ] ){ TRY( tmp=p::Test<epf,fn_sse3   >( a_in,a_exp,b_in,b_exp,c_in,c_exp ) ); res[SSP_SSE3  ]=tmp; } 
	if( enable[SSP_SSSE3 ] ){ TRY( tmp=p::Test<epf,fn_ssse3  >( a_in,a_exp,b_in,b_exp,c_in,c_exp ) ); res[SSP_SSSE3 ]=tmp; } 
    if( enable[SSP_SSE4a ] ){ TRY( tmp=p::Test<epf,fn_sse4a  >( a_in,a_exp,b_in,b_exp,c_in,c_exp ) ); res[SSP_SSE4a ]=tmp; } 
    if( enable[SSP_SSE4_1] ){ TRY( tmp=p::Test<epf,fn_sse4_1 >( a_in,a_exp,b_in,b_exp,c_in,c_exp ) ); res[SSP_SSE4_1]=tmp; } 
    if( enable[SSP_SSE4_2] ){ TRY( tmp=p::Test<epf,fn_sse4_2 >( a_in,a_exp,b_in,b_exp,c_in,c_exp ) ); res[SSP_SSE4_2]=tmp; } 
    if( enable[SSP_SSE5  ] ){ TRY( tmp=p::Test<epf,fn_sse5   >( a_in,a_exp,b_in,b_exp,c_in,c_exp ) ); res[SSP_SSE5  ]=tmp; } 
    
    Cleanup( res, p::errorList, csv, do_REF, do_SSE, do_SSE2, do_SSE3, do_SSSE3, do_SSE4a, do_SSE4_1, do_SSE4_2, do_SSE5 );    
}

//====================================

template< 
    typename T1, typename T2, typename T3, typename T4,
    bool do_REF   ,void(*fn_ref    )(T1,T2,T3,T4), 
    bool do_SSE   ,void(*fn_sse    )(T1,T2,T3,T4), 
    bool do_SSE2  ,void(*fn_sse2   )(T1,T2,T3,T4), 
    bool do_SSE3  ,void(*fn_sse3   )(T1,T2,T3,T4), 
	bool do_SSSE3 ,void(*fn_ssse3  )(T1,T2,T3,T4), 
    bool do_SSE4a ,void(*fn_sse4a  )(T1,T2,T3,T4), 
	bool do_SSE4_1,void(*fn_sse4_1 )(T1,T2,T3,T4), 
    bool do_SSE4_2,void(*fn_sse4_2 )(T1,T2,T3,T4), 
    bool do_SSE5  ,void(*fn_sse5   )(T1,T2,T3,T4), 
    enumPrintFormat epf 
>
void Test( const CSVLine & csv, const char *name, T1 a_exp, T2 b_exp, T3 c_exp, T4 d_exp,
                                                  T1 a_in , T2 b_in , T3 c_in , T4 d_in  )
{
     if( g_update && csv.useCount>1) 
        return;

    unsigned int cycles=0;
    PrintName( name, csv.assembly, csv.source );

    bool enable[ SSP_SSE_COUNT ];
    double res [ SSP_SSE_COUNT ], tmp;  // tmp indirection allows use of TRY macro

    Setup_Paths( enable, do_REF, do_SSE, do_SSE2, do_SSE3, do_SSSE3, do_SSE4a, do_SSE4_1, do_SSE4_2, do_SSE5 );    

    if( enable[SSP_REF   ] ){ TRY( tmp=p::Test<epf,fn_ref    >( a_in,a_exp,b_in,b_exp,c_in,c_exp,d_in,d_exp ) ); res[SSP_REF   ]=tmp; } 
    if( enable[SSP_SSE   ] ){ TRY( tmp=p::Test<epf,fn_sse    >( a_in,a_exp,b_in,b_exp,c_in,c_exp,d_in,d_exp ) ); res[SSP_SSE   ]=tmp; } 
    if( enable[SSP_SSE2  ] ){ TRY( tmp=p::Test<epf,fn_sse2   >( a_in,a_exp,b_in,b_exp,c_in,c_exp,d_in,d_exp ) ); res[SSP_SSE2  ]=tmp; } 
    if( enable[SSP_SSE3  ] ){ TRY( tmp=p::Test<epf,fn_sse3   >( a_in,a_exp,b_in,b_exp,c_in,c_exp,d_in,d_exp ) ); res[SSP_SSE3  ]=tmp; } 
	if( enable[SSP_SSSE3 ] ){ TRY( tmp=p::Test<epf,fn_ssse3  >( a_in,a_exp,b_in,b_exp,c_in,c_exp,d_in,d_exp ) ); res[SSP_SSSE3 ]=tmp; } 
    if( enable[SSP_SSE4a ] ){ TRY( tmp=p::Test<epf,fn_sse4a  >( a_in,a_exp,b_in,b_exp,c_in,c_exp,d_in,d_exp ) ); res[SSP_SSE4a ]=tmp; } 
    if( enable[SSP_SSE4_1] ){ TRY( tmp=p::Test<epf,fn_sse4_1 >( a_in,a_exp,b_in,b_exp,c_in,c_exp,d_in,d_exp ) ); res[SSP_SSE4_1]=tmp; } 
    if( enable[SSP_SSE4_2] ){ TRY( tmp=p::Test<epf,fn_sse4_2 >( a_in,a_exp,b_in,b_exp,c_in,c_exp,d_in,d_exp ) ); res[SSP_SSE4_2]=tmp; } 
    if( enable[SSP_SSE5  ] ){ TRY( tmp=p::Test<epf,fn_sse5   >( a_in,a_exp,b_in,b_exp,c_in,c_exp,d_in,d_exp ) ); res[SSP_SSE5  ]=tmp; } 
    
    Cleanup( res, p::errorList, csv, do_REF, do_SSE, do_SSE2, do_SSE3, do_SSSE3, do_SSE4a, do_SSE4_1, do_SSE4_2, do_SSE5 );    
}

//====================================

#endif // __TEST_H__
