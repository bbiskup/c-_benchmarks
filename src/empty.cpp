#include "common.h"

#include <benchmark/benchmark.h>

static void BM_empty_empty(benchmark::State& state)
{
  {
    for (auto _ : state)
      ;
  }
}
BENCHMARK(BM_empty_empty);
