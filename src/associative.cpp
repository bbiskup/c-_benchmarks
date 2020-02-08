
#include "common.h"

#include <benchmark/benchmark.h>

#include <fmt/format.h>

#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::string> largeStringVec()
{
  std::vector<std::string> result;
  for (int i{0}; i < 100000; ++i)
  {
    result.push_back(fmt::format("value_{}", i));
  }
  return result;
}

static void BM_map_insertion(benchmark::State& state)
{
  for (auto _ : state)
  {
    std::map<std::string, int> m;
    int value{0};
    for (const auto& s : largeStringVec())
    {
      m.insert({s, value++});
    }
    benchmark::DoNotOptimize(m.size());
    benchmark::ClobberMemory();
  }
}
BENCHMARK(BM_map_insertion);

static void BM_unordered_map_insertion(benchmark::State& state)
{
  for (auto _ : state)
  {
    std::unordered_map<std::string, int> m;
    int value{0};
    for (const auto& s : largeStringVec())
    {
      m.insert({s, value++});
    }
    benchmark::DoNotOptimize(m.size());
    benchmark::ClobberMemory();
  }
}
BENCHMARK(BM_unordered_map_insertion);

static void BM_map_retrieval(benchmark::State& state)
{
  std::map<std::string, int> m;
  int value{0};
  for (const auto& s : largeStringVec())
  {
    m.insert({s, value++});
  }

  for (auto _ : state)
  {
    for (const auto& s : largeStringVec())
    {
      benchmark::DoNotOptimize(m[s]);
    }
  }
}
BENCHMARK(BM_map_retrieval);

static void BM_unordered_map_retrieval(benchmark::State& state)
{
  std::unordered_map<std::string, int> m;
  int value{0};
  for (const auto& s : largeStringVec())
  {
    m.insert({s, value++});
  }

  for (auto _ : state)
  {
    for (const auto& s : largeStringVec())
    {
      benchmark::DoNotOptimize(m[s]);
    }
  }
}
BENCHMARK(BM_unordered_map_retrieval);
