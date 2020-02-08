#include "common.h"

#include <benchmark/benchmark.h>

count_t non_inline_func(count_t x)
{
  return x;
}

static void BM_function_func_call(benchmark::State& state)
{
  count_t a = 0;
  count_t i{0};
  for (auto _ : state)
  {
    a += non_inline_func(i++);
  }

  benchmark::DoNotOptimize(a);
}
BENCHMARK(BM_function_func_call);

inline count_t inline_func(count_t x)
{
  return x;
}

static void BM_function_inline_func_call(benchmark::State& state)
{
  count_t a{0};
  count_t i{0};
  for (auto _ : state)
  {
    a += inline_func(i++);
  }

  benchmark::DoNotOptimize(a);
}
BENCHMARK(BM_function_inline_func_call);

int a_func(int a)
{
  return 2 * a;
}

static void BM_function_func_ptr(benchmark::State& state)
{
  int result = 0;
  auto f_ptr = a_func;
  for (auto _ : state)
  {
    result += f_ptr(1);
  }
  benchmark::DoNotOptimize(result);
}
BENCHMARK(BM_function_func_ptr);

static void BM_function_lambda(benchmark::State& state)
{
  long result{0};
  long a{0};
  long i{0};
  auto lambda = [](long x, long y) -> long { return x + y; };
  for (auto _ : state)
  {
    result += lambda(a, i);
    ++a;
    ++i;
  }
  benchmark::DoNotOptimize(result);
}
BENCHMARK(BM_function_lambda);
