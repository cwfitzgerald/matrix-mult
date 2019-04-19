#pragma once

#if __AVX2__
#define SUFFIX _avx
#elif __SSE4_2__
#define SUFFIX _sse
#else
#error "wha?"
#endif

#define EXPAND(x) x
#define CONCAT_IMPL(lhs, rhs) lhs ## rhs
#define CONCAT(lhs, rhs) CONCAT_IMPL(lhs, rhs)
#define FUNCTION_NAME(name) CONCAT(name, SUFFIX)
#define FUNCTION_PREDEF_IMPL(name, vers) void CONCAT(name, vers)(float* src1, float* src2, float* dst)
#define FUNCTION_PREDEF(name) FUNCTION_PREDEF_IMPL(name, _sse); FUNCTION_PREDEF_IMPL(name, _avx)

FUNCTION_PREDEF(original);
FUNCTION_PREDEF(cwf);
FUNCTION_PREDEF(jodie);
