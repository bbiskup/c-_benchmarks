#include "common.h"

#include <benchmark/benchmark.h>

#include <fmt/format.h>

// See discussion at
// https://stackoverflow.com/questions/40122141/preventing-compiler-optimizations-while-benchmarking
// about correct use of benchmark::DoNotOptimize and benchmark::ClobberMemory

BENCHMARK_MAIN();
