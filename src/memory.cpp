#include "common.h"

#include <benchmark/benchmark.h>

#include <array>

static void BM_write_64k(benchmark::State& state)
{
  const int memSize = 1024 * 64;
  unsigned char mem[memSize];
  for (auto _ : state)
  {
    for (int j = 0; j < memSize; ++j)
    {
      mem[j] = j;
      benchmark::DoNotOptimize(mem[memSize - 1]);
      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(BM_write_64k);

static void BM_read_64k(benchmark::State& state)
{
  const int memSize = 1024 * 64;
  unsigned char mem[memSize];
  for (int j = 0; j < memSize; ++j)
  {
    mem[j] = j;
    benchmark::DoNotOptimize(mem[j]);
  }
  benchmark::ClobberMemory();

  int result = 1;
  for (auto _ : state)
  {
    for (int j = 0; j < memSize; ++j)
    {
      result &= mem[j];
      benchmark::DoNotOptimize(mem[j]);
    }
  }
}

BENCHMARK(BM_read_64k);

static void BM_read_64k_vec(benchmark::State& state)
{
  const int memSize = 1024 * 64;
  std::vector<unsigned char> mem(memSize);
  for (int j = 0; j < memSize; ++j)
  {
    mem[j] = j;
    benchmark::DoNotOptimize(mem[j]);
  }
  benchmark::ClobberMemory();

  int result = 1;
  for (auto _ : state)
  {
    for (int j = 0; j < memSize; ++j)
    {
      result &= mem[j];
      benchmark::DoNotOptimize(mem[j]);
    }
  }
}
BENCHMARK(BM_read_64k_vec);

static void BM_read_64k_vec_at(benchmark::State& state)
{
  const int memSize = 1024 * 64;
  std::vector<unsigned char> mem(memSize);
  for (int j = 0; j < memSize; ++j)
  {
    mem[j] = j;
    benchmark::DoNotOptimize(mem[j]);
  }
  benchmark::ClobberMemory();

  int result = 1;
  for (auto _ : state)
  {
    for (int j = 0; j < memSize; ++j)
    {
      result &= mem.at(j);
      benchmark::DoNotOptimize(mem.at(j));
    }
  }
}
BENCHMARK(BM_read_64k_vec_at);

static void BM_read_64k_array_at(benchmark::State& state)
{
  const int memSize = 1024 * 64;
  std::array<unsigned char, memSize> mem;
  for (int j = 0; j < memSize; ++j)
  {
    mem[j] = j;
    benchmark::DoNotOptimize(mem[j]);
  }
  benchmark::ClobberMemory();

  int result = 1;
  for (auto _ : state)
  {
    for (int j = 0; j < memSize; ++j)
    {
      result &= mem.at(j);
    }
  }
}
BENCHMARK(BM_read_64k_array_at);

static void BM_try_catch(benchmark::State& state)
{
  int result = 0;
  for (auto _ : state)
  {
    try
    {
      throw std::exception();
    }
    catch (std::exception& e)
    {
      ++result;
    }
  }
  benchmark::DoNotOptimize(result);
}
BENCHMARK(BM_try_catch);

