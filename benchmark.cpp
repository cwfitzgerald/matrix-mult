#include "name.hpp"
#include <benchmark/benchmark.h>
#include <cstring>
#include <numeric>

#define BENCHMARK_IMPL(name) EXPAND(BENCHMARK(name))
#define BENCHMARKED_FUNC(name, ext)                                            \
  void CONCAT(BM_, CONCAT(name, ext))(benchmark::State & state) {              \
    int64_t const size = state.range(0);                                       \
    float *array1 = new float[size * 16];                                      \
    float *array2 = new float[size * 16];                                      \
    float *dest = new float[size * 16];                                        \
                                                                               \
    for (std::int64_t i = 0; i < size; ++i) {                                  \
      std::iota(array1 + 16 * i, array1 + 16 * (i + 1), 0);                    \
      std::iota(array2 + 16 * i, array2 + 16 * (i + 1), 0);                    \
    }                                                                          \
                                                                               \
    std::memset(dest, 0, 4 * 16 * size);                                       \
                                                                               \
    for (auto _ : state) {                                                     \
      for (std::int64_t i = 0; i < size; ++i) {                                \
        CONCAT(name, ext)(array1 + 16 * i, array2 + 16 * i, dest + 16 * i);    \
      }                                                                        \
    }                                                                          \
                                                                               \
    state.counters["matmuls"] = benchmark::Counter(                            \
        size * state.iterations(), benchmark::Counter::kIsRate);               \
    state.SetBytesProcessed(3 * 4 * 16 * size * state.iterations());           \
                                                                               \
    delete[] array1;                                                           \
    delete[] array2;                                                           \
    delete[] dest;                                                             \
  }                                                                            \
  BENCHMARK_IMPL(CONCAT(BM_, CONCAT(name, ext)))->Range(512, 512);

BENCHMARKED_FUNC(original, _sse)
BENCHMARKED_FUNC(original, _avx)
BENCHMARKED_FUNC(cwf, _sse)
BENCHMARKED_FUNC(cwf, _avx)
BENCHMARKED_FUNC(jodie, _avx)
BENCHMARKED_FUNC(graphite, _sse)
BENCHMARKED_FUNC(graphite, _avx)
