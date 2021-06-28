#pragma once

#define PHYS75_MIN_SIMD_LVL 1

#ifdef __AVX2__
	#define PHYS75_INSTR_LVL 4
#elif defined ( __AVX__ )
	#define PHYS75_INSTR_LVL 3
#elif (defined(_M_AMD64) || defined(_M_X64))
	#define PHYS75_INSTR_LVL 2
#elif _M_IX86_FP == 2
	#define PHYS75_INSTR_LVL 2
#elif _M_IX86_FP == 1
	#define PHYS75_INSTR_LVL 1
#else
	#define PHYS75_INSTR_LVL 0
#endif

#if PHYS75_INSTR_LVL >= PHYS75_MIN_SIMD_LVL
	
#else

#endif // Use SSE instructions 



