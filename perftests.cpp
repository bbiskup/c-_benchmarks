#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <boost/chrono/thread_clock.hpp>

using namespace std;
using namespace boost::chrono;

void benchmark_add(int count) {
  for (int i = 0; i < count; ++i) {
    ;;
  }
}

typedef void (*benchmark_ptr)(int);

map<string, benchmark_ptr> commands = {{"add", benchmark_add}};

int main(int argc, char const *argv[]) {
  if (argc < 3) {
    cerr << "usage" << endl;
    exit(1);
  }
  auto cmd_name = argv[1];
  auto count_str = argv[2];
  int count;
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
  cmd_it->second(count);
  thread_clock::time_point stop = thread_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start).count();
  std::cout << "duration per call: " << duration / static_cast<float>(count) * 1000000 << " ns\n";
  std::cout << "duration: " << duration << " ms\n";
  return 0;
}