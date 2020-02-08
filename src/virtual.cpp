#include "common.h"

#include <benchmark/benchmark.h>

class C
{
public:
  int a_method(int a) { return 2 * a; }
  virtual int a_virtual_method(int a) { return 2 * a; }
};

class C2 : public C
{
public:
  virtual int a_virtual_method(int a) { return 3 * a; }
};

static void BM_nonvirt_method(benchmark::State& state)
{
  int result = 0;
  C c;
  for (auto _ : state)
  {
    result += c.a_method(1);
  }
  benchmark::DoNotOptimize(result);
}
BENCHMARK(BM_nonvirt_method);

static void BM_virt_method(benchmark::State& state)
{
  int result = 0;
  C2 c2;
  for (auto _ : state)
  {
    result += c2.a_virtual_method(1);
  }
  benchmark::DoNotOptimize(result);
}
BENCHMARK(BM_virt_method);
