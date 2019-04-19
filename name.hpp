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
#define FUNCTION_PREDEF_IMPL(name, vers) void CONCAT(name, vers)(float const * __restrict src1, float const * __restrict src2, float* __restrict dst)
#define FUNCTION_PREDEF(name) FUNCTION_PREDEF_IMPL(name, _sse); FUNCTION_PREDEF_IMPL(name, _avx)

FUNCTION_PREDEF(original);
FUNCTION_PREDEF(cwf);
FUNCTION_PREDEF(jodie);
FUNCTION_PREDEF(graphite);
