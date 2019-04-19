#include "name.hpp"

#include <immintrin.h>

void FUNCTION_NAME(jodie)(float* a, float* b, float* c) {
	__m128 row1 = _mm_loadu_ps(&b[0] );
	__m128 row2 = _mm_loadu_ps(&b[4] );
	__m128 row3 = _mm_loadu_ps(&b[8] );
	__m128 row4 = _mm_loadu_ps(&b[12]);

	for (size_t i = 0; i < 16; i+=4) {
		// First element of each column
		__m128 brod1 = _mm_load_ps1(&a[i+0]);
		__m128 brod2 = _mm_load_ps1(&a[i+1]);
		__m128 brod3 = _mm_load_ps1(&a[i+2]);
		__m128 brod4 = _mm_load_ps1(&a[i+3]);

		__m128 row = _mm_mul_ps(row1, brod1);
        row = _mm_fmadd_ps(row2, brod2, row);
		row = _mm_fmadd_ps(row3, brod3, row);
		row = _mm_fmadd_ps(row4, brod4, row);

		_mm_storeu_ps(&c[i], row);
	}
}
