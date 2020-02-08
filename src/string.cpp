#include "common.h"

#include <benchmark/benchmark.h>

#include <string>

std::vector<std::string> many_strings()
{
  return std::vector<std::string>(10000, "abcdefghijklmnopqrstuvwxyz");
}

std::vector<std::string> many_strings_static()
{
  static std::vector<std::string> result(10000, "abcdefghijklmnopqrstuvwxyz");
  return result;
}

static void BM_string_concat_plus(benchmark::State& state)
{
  for (auto _ : state)
  {
    std::string result;
    for (const std::string& s : many_strings())
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
    std::ostringstream result;
    for (const std::string& s : many_strings())
    {
      result << s;
    }
    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(BM_string_concat_ostringstream);

