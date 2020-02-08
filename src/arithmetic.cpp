#include "common.h"

#include <benchmark/benchmark.h>

static void BM_arithmetic_add(benchmark::State& state)
{
  count_t a = 0;

  for (auto _ : state)
  {
    a += 1;
  }

  benchmark::DoNotOptimize(a);
}
BENCHMARK(BM_arithmetic_add);
