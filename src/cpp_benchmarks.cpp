#include <benchmark/benchmark.h>

#include <array>
#include <bitset>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using count_t = long long;

// See discussion at
// https://stackoverflow.com/questions/40122141/preventing-compiler-optimizations-while-benchmarking
// about correct use of benchmark::DoNotOptimize and benchmark::ClobberMemory

static void BM_empty(benchmark::State& state)
{
  {
    for (auto _ : state)
      ;
  }
}
BENCHMARK(BM_empty);

static void BM_add(benchmark::State& state)
{
  count_t a = 0;

  for (auto _ : state)
  {
    a += 1;
  }

  benchmark::DoNotOptimize(a);
}
BENCHMARK(BM_add);

count_t non_inline_func(count_t x)
{
  return x;
}

static void BM_func_call(benchmark::State& state)
{
  count_t a = 0;
  count_t i{0};
  for (auto _ : state)
  {
    a += non_inline_func(i++);
  }

  benchmark::DoNotOptimize(a);
}
BENCHMARK(BM_func_call);

inline count_t inline_func(count_t x)
{
  return x;
}

static void BM_inline_func_call(benchmark::State& state)
{
  count_t a{0};
  count_t i{0};
  for (auto _ : state)
  {
    a += inline_func(i++);
  }

  benchmark::DoNotOptimize(a);
}
BENCHMARK(BM_inline_func_call);

static void BM_deref_ptr(benchmark::State& state)
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
BENCHMARK(BM_deref_ptr);

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
  vector<unsigned char> mem(memSize);
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
  vector<unsigned char> mem(memSize);
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
  array<unsigned char, memSize> mem;
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
      throw exception();
    }
    catch (exception& e)
    {
      ++result;
    }
  }
  benchmark::DoNotOptimize(result);
}
BENCHMARK(BM_try_catch);

int a_func(int a)
{
  return 2 * a;
}

static void BM_func_ptr(benchmark::State& state)
{
  int result = 0;
  auto f_ptr = a_func;
  for (auto _ : state)
  {
    result += f_ptr(1);
  }
  benchmark::DoNotOptimize(result);
}
BENCHMARK(BM_func_ptr);

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

vector<string> many_strings()
{
  return vector<string>(10000, "abcdefghijklmnopqrstuvwxyz");
}

vector<string> many_strings_static()
{
  static vector<string> result(10000, "abcdefghijklmnopqrstuvwxyz");
  return result;
}

static void BM_string_concat_plus(benchmark::State& state)
{
  for (auto _ : state)
  {
    string result;
    for (const string& s : many_strings())
    {
      result += s;
    }
    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(BM_string_concat_plus);

static void BM_string_concat_ostringstream(benchmark::State& state)
{
  for (auto _ : state)
  {
    ostringstream result;
    for (const string& s : many_strings())
    {
      result << s;
    }
    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(BM_string_concat_ostringstream);

static void BM_lambda(benchmark::State& state)
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
BENCHMARK(BM_lambda);

static void BM_xor(benchmark::State& state)
{
  unsigned char c = 1;
  int i{0};
  for (auto _ : state)
  {
    c ^= i++;
  }
  benchmark::DoNotOptimize(c);
}
BENCHMARK(BM_xor);

void BM_xor_bitset(benchmark::State& state)
{
  bitset<8> c = 1;
  int i{0};
  for (auto _ : state)
  {
    c ^= i++;
  }
  benchmark::DoNotOptimize(c.to_ulong());
}
BENCHMARK(BM_xor_bitset);

BENCHMARK_MAIN();