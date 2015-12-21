#include <iostream>
#include <map>
#include <string>

using namespace std;

void benchmark_add(int count) { cout << "count: " << count << endl; }

typedef void (*benchmark_ptr)(int);

map<string, benchmark_ptr> commands = {{"add", benchmark_add}};

int main(int argc, char const *argv[]) {
  if (argc < 3) {
    cerr << "usage" << endl;
    exit(1);
  }
  auto cmd_name = argv[1];

  auto cmd_it = commands.find(cmd_name);
  if (cmd_it == commands.end()){
    cerr << "Command '" << cmd_name << "' unknown" << endl;
    exit(1);
  }
  
  cmd_it->second(10);
  return 0;
}