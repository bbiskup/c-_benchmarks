#include "common.h"

#include <benchmark/benchmark.h>

static void BM_pointer_deref_ptr(benchmark::State& state)
{
  count_t a = 0;
  count_t* b = &a;
  count_t c;
  for (auto _ : state)
  {
    c = *b;
    benchmark::DoNotOptimize(c);
  }
}
BENCHMARK(BM_pointer_deref_ptr);

