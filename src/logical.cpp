#include "common.h"

#include <benchmark/benchmark.h>

#include <bitset>

static void BM_logical_xor(benchmark::State& state)
{
  unsigned char c = 1;
  int i{0};
  for (auto _ : state)
  {
    c ^= i++;
  }
  benchmark::DoNotOptimize(c);
}
BENCHMARK(BM_logical_xor);

void BM_logical_xor_bitset(benchmark::State& state)
{
  std::bitset<8> c = 1;
  int i{0};
  for (auto _ : state)
  {
    c ^= i++;
  }
  benchmark::DoNotOptimize(c.to_ulong());
}
BENCHMARK(BM_logical_xor_bitset);

