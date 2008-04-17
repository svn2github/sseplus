This project reads a CSV file with the following format: 


Intrinsic Name	Instruction Set	REF	SSE	SSE2	SSE3	SSSE3	SSE4A	SSE4_1	SSE4_2	SSE5
_mm_abs_epi16	SSSE3	X		X		X				
_mm_abs_epi32	SSSE3	X		X		X				
_mm_abs_epi8	SSSE3	X		X		X				
_mm_add_epi16	SSE2			X						


It outputs a text file that can be read by Doxygen to generate a table. 