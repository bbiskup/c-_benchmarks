#include "common.h"

#include <benchmark/benchmark.h>

namespace
{
// A single call is to fast
constexpr int methodRepeatCount{100000};
}

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
  C c;
  for (auto _ : state)
  {
    int result = 0;
    for (int i{0}; i < methodRepeatCount; ++i)
    {
      result += c.a_method(1);
    }
    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(BM_nonvirt_method);

static void BM_virt_method(benchmark::State& state)
{
  C2 c2;
  for (auto _ : state)
  {
    int result = 0;
    for (int i{0}; i < methodRepeatCount; ++i)
    {
      result += c2.a_virtual_method(1);
    }
    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(BM_virt_method);

static void BM_virt_method_via_ptr(benchmark::State& state)
{
  C2 c2;
  C* c{&c2};
  for (auto _ : state)
  {
    int result = 0;
    for (int i{0}; i < methodRepeatCount; ++i)
    {
      result += c->a_virtual_method(1);
    }
    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(BM_virt_method_via_ptr);
