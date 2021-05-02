#include <benchmark/benchmark.h>
#include <library.hpp>

static void bm_library(benchmark::State& state) {
  for (const auto _ : state) {
    const auto sv = library::test();
    benchmark::DoNotOptimize(sv);
  }
}
BENCHMARK(bm_library);
