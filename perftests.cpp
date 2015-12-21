#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <boost/chrono/thread_clock.hpp>

using namespace std;
using namespace boost::chrono;

typedef long long count_t;

count_t benchmark_empty(count_t count) {
  for (count_t i = 0; i < count; ++i) {
    ;
  }
  return count;
}

count_t benchmark_add(count_t count) {
  count_t a = 0;
  for (count_t i = 0; i < count; ++i) {
    a += i;
  }
  return count;
}

count_t non_inline_func(count_t x) { return x; }

count_t benchmark_func_call(count_t count) {
  count_t a = 0;
  for (count_t i = 0; i < count; ++i) {
    a += non_inline_func(i);
  }

  cout << "a: " << a << endl;
  return count;
}

inline count_t inline_func(count_t x) { return x; }

count_t benchmark_inline_func_call(count_t count) {
  count_t a = 0;
  for (count_t i = 0; i < count; ++i) {
    a += inline_func(i);
  }

  cout << "a: " << a << endl;
  return count;
}

count_t benchmark_deref_ptr(count_t count) {
  count_t a = 0;
  count_t* b = &a;
  count_t c;
  count_t result;
  for (count_t i = 0; i < count; ++i) {
    c = *b;
  }
  result = c;
  return count;
}

typedef count_t (*benchmark_ptr)(count_t);

map<string, benchmark_ptr> commands = {
    {"empty", benchmark_empty},
    {"add", benchmark_add},
    {"func_call", benchmark_func_call},
    {"inline_func_call", benchmark_func_call},
    {"deref_ptr", benchmark_deref_ptr},
};

int main(int argc, char const* argv[]) {
  if (argc < 3) {
    cerr << "usage" << endl;
    exit(1);
  }
  auto cmd_name = argv[1];
  auto count_str = argv[2];
  count_t count;
  istringstream count_strm(count_str);

  if (!(count_strm >> count)) {
    cerr << "Invalid count: '" << count_str << endl;
    exit(1);
  }

  auto cmd_it = commands.find(cmd_name);
  if (cmd_it == commands.end()) {
    cerr << "Command '" << cmd_name << "' unknown" << endl;
    exit(1);
  }

  thread_clock::time_point start = thread_clock::now();
  auto result = cmd_it->second(count);
  thread_clock::time_point stop = thread_clock::now();

  auto duration = duration_cast<milliseconds>(stop - start).count();
  auto duration_per_call_ns = duration / static_cast<float>(count) * 1000000;

  std::cout << "Result: " << result << endl;
  std::cout << "duration per call: " << duration_per_call_ns << " ns\n";
  std::cout << 1 / duration_per_call_ns * 1000 << " million calls per s\n";
  std::cout << "duration: " << duration << " ms\n";
  return 0;
}