#include "name.hpp"

#include <mmintrin.h>
#include <xmmintrin.h>

void FUNCTION_NAME(cwf)(float const * __restrict left, float const * __restrict right, float* __restrict ret) {
	float const * a = &left[0];
	float const * b = &right[0];
	float* r = &ret[0];

	__m128 row1 = _mm_loadu_ps(b + 0);
	__m128 row2 = _mm_loadu_ps(b + 4);
	__m128 row3 = _mm_loadu_ps(b + 8);
	__m128 row4 = _mm_loadu_ps(b + 12);

	for (size_t i = 0; i < 4; ++i) {
		// First element of each column
		__m128 brod1 = _mm_load_ps1(a + (4 * i + 0));
		__m128 brod2 = _mm_load_ps1(a + (4 * i + 1));
		__m128 brod3 = _mm_load_ps1(a + (4 * i + 2));
		__m128 brod4 = _mm_load_ps1(a + (4 * i + 3));

		__m128 row = _mm_mul_ps(row1, brod1);
		row = _mm_add_ps(_mm_mul_ps(row2, brod2), row);
		row = _mm_add_ps(_mm_mul_ps(row3, brod3), row);
		row = _mm_add_ps(_mm_mul_ps(row4, brod4), row);

		_mm_storeu_ps(r + (4 * i + 0), row);
	}
}
