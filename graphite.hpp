#include "name.hpp"
#include <xmmintrin.h> // SSE2

#define _mm_pshufd(xmm, mask) \
  _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(xmm), mask))

#if defined(__GNUC__)
#define gm_force_inline \
  __attribute__((always_inline)) inline
#else
#define gm_force_inline inline
#endif

struct vec4 {
  constexpr vec4(__m128 _m) : m(_m) {}
  template<size_t X, size_t Y, size_t Z, size_t W>
  gm_force_inline vec4 swizzle() const { return _mm_pshufd(m, _MM_SHUFFLE(W, Z, Y, X)); }
  template<size_t N>
  gm_force_inline vec4 splat() const { return swizzle<N, N, N, N>(); }
  gm_force_inline vec4 operator*(const vec4& _v) const { return _mm_mul_ps(_v.m, m); }
  gm_force_inline vec4 operator+(const vec4& _v) const { return _mm_add_ps(_v.m, m); }
  union {
    struct { float x, y, z, w; };
    __m128 m;
  };
};

struct mat4 {
  constexpr mat4(const vec4& _a, const vec4& _b, const vec4& _c, const vec4& _d) : a{_a}, b{_b}, c{_c}, d{_d} { }
  gm_force_inline mat4 operator*(const mat4& _m) const {
    return { _m.a*a.splat<0>() + _m.b*a.splat<1>() + _m.c*a.splat<2>() + _m.d*a.splat<3>(),
             _m.a*b.splat<0>() + _m.b*b.splat<1>() + _m.c*b.splat<2>() + _m.d*b.splat<3>(),
             _m.a*c.splat<0>() + _m.b*c.splat<1>() + _m.c*c.splat<2>() + _m.d*c.splat<3>(),
             _m.a*d.splat<0>() + _m.b*d.splat<1>() + _m.c*d.splat<2>() + _m.d*d.splat<3>() };
  }
  vec4 a, b, c, d;
};

void FUNCTION_NAME(graphite)(const float *__restrict src1, const float *__restrict src2, float *__restrict dst) {
  const mat4 &__restrict m_src1 = *(const mat4 *__restrict)src1;
  const mat4 &__restrict m_src2 = *(const mat4 *__restrict)src2;
  mat4& __restrict m_dst = *(mat4 *__restrict)dst;
  m_dst = m_src1 * m_src2;
}
