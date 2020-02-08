#include "common.h"

#include <benchmark/benchmark.h>

#include <fmt/format.h>

#include <sstream>
#include <string>

static void BM_string_formatting_string_formatting_fmt_positional(benchmark::State& state)
{
  count_t i{0};
  std::string s;
  for (auto _ : state)
  {
    s = fmt::format(
        "{} {} {} {} {} {} {} {} {} {}", i, i + 1, i + 2, i + 3, i + 4, i + 5, i + 6, i + 7, i + 8,
        i + 9);
    benchmark::DoNotOptimize(s);
  }
}
BENCHMARK(BM_string_formatting_string_formatting_fmt_positional);

static void BM_string_formatting_string_formatting_fmt_named_args(benchmark::State& state)
{
  using namespace fmt::literals;
  int i{0};
  std::string s;
  for (auto _ : state)
  {
    s = fmt::format(
        "{zero} {one} {two} {three} {four} {five} {six} {seven} {eight} {nine}", "zero"_a = i,
        "one"_a = i + 1, "two"_a = i + 2, "three"_a = i + 3, "four"_a = i + 4, "five"_a = i + 5,
        "six"_a = i + 6, "seven"_a = i + 7, "eight"_a = i + 8, "nine"_a = i + 9);
    benchmark::DoNotOptimize(s);
  }
}
BENCHMARK(BM_string_formatting_string_formatting_fmt_named_args);

static void BM_string_formatting_string_formatting_ostringstream(benchmark::State& state)
{
  using namespace fmt::literals;
  int i{0};
  std::string s;
  for (auto _ : state)
  {
    std::ostringstream strm;
    strm << (i + 1) << " " << (i + 2) << " " << (i + 3) << " " << (i + 4) << " " << (i + 5) << " "
         << (i + 6) << " " << (i + 7) << " " << (i + 8) << " " << (i + 9);
    s = strm.str();
    benchmark::DoNotOptimize(s);
  }
}
BENCHMARK(BM_string_formatting_string_formatting_ostringstream);

static void BM_string_formatting_string_formatting_sprintf(benchmark::State& state)
{
  using namespace fmt::literals;
  int i{0};
  char s[1024];
  for (auto _ : state)
  {
    int status = sprintf(
        s, "%d %d %d %d %d %d %d %d %d %d ", (i + 0), (i + 1), (i + 2), (i + 3), (i + 4), (i + 5),
        (i + 6), (i + 7), (i + 8), (i + 9));
    benchmark::DoNotOptimize(status);
    benchmark::DoNotOptimize(s);
  }
}
BENCHMARK(BM_string_formatting_string_formatting_sprintf);

