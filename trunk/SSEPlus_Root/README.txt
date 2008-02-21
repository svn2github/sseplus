Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
This software is subject to the Apache v2.0 License.

-------------------------------------------------------------------------
SSEPlus 1.0 pre-alpha
-------------------------------------------------------------------------

GENERAL INFORMATION
=================================================

SSEPlus is a C/C++ API of Streaming SIMD Extensions, optimized for 
multiple instruction sets.


FOLDER HIERARCHY
=================================================
./Documentation/
./SSEPlus/
    include/
        arithmetic/*.h
        emulation/*.h
        logical/*.h
        map/*.h
        native/*.h
        number/*.h
        *.h
./SSEPlus_Test/
    C_Sanity/
        main.c
        Makefile
        (MSVC project files)
    UnitTest/
        src/
            main.cpp
            Makefile
        include/*.h
        Makefile
        (MSVC project files)
        test.csv


HOW TO BUILD WITH GCC
=================================================

Requirements:

	1. Any GCC compiler with at lease SSE3 support (or) GCC 4.3
	2. GNU binutils 2.18
	3. GNU make

Build Steps:

	1. Setup the path for the right GCC compiler and the binutils.
	2. Change directory to SSEPlus_Root
	3. Invoke make with appropriate arguments, as noted below.
	4. The executable (UnitTest) is built in SSEPlus_Root/SSEPlus_Test/UnitTest/

	A. 32-bit build with support up to SSE3
	
	make "BITNESS=32" "CP_FLAGS=-msse3"
	
	B. 64-bit build with support up to SSE3
	
	make "BITNESS=64" "CP_FLAGS=-msse3"
	
	C. 32-bit build with GCC 4.3
	
	make "BITNESS=32" "CP_FLAGS=-msse4a -msse4.1"
	
	D. 64-bit build with GCC 4.3
	
	make "BITNESS=64" "CP_FLAGS=-msse4a -msse4.1"

    
FAQ
=================================================
Q: What is the purpose of the C_Sanity project?
A: C_Sanity project ensures that the SSEPlus 
    project can be compiled with C and C++ code.

Q: How do I interpret the out put of the UnitTest application?
A:
(1)                 (2)    (3)
NAME                ,SRC  ,   REF    ,  SSE2    ,  SSE3    , SSSE3    , SSE4A    ,SSE4.1    ,
ssp_fn              ,[S3 ],9999.9    ,  12.3    ,  12.3|45 ,     x|0  ,          ,          ,
...

* (1) Function Name
* (2) Source SSE instruction set (SSEn)
    n = 1   - SSE1
        2   - SSE2
        3   - SSE3
        S3  - SSSE3
        4a  - SSE4A
        4.1 - SSE4.1
        4.2 - SSE4.2
        ssp - SSEPlus utility functions
* (3) Number of consumed cycles by respective implementation 
* An output of "9999.9" means during the run, that function took >1000 cycles
* Output Format "a|b"
    - a: actual number of consumed cycles
        - "x" - function threw an exception
    - b: expected number of consumed cycles 
        - This value is not displayed if no expected value is specified.
        - Expected number of cycles are listed in SSEPlus_Test\UnitTest\test.csv
    



