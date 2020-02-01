#include <boost/chrono/thread_clock.hpp>

#include <array>
#include <bitset>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace boost::chrono;

typedef long long count_t;

count_t benchmark_empty(count_t count)
{
  for (count_t i = 0; i < count; ++i)
  {
    ;
  }
  return count;
}

count_t benchmark_add(count_t count)
{
  count_t a = 0;
  for (count_t i = 0; i < count; ++i)
  {
    a += i;
  }
  return count;
}

count_t non_inline_func(count_t x)
{
  return x;
}

count_t benchmark_func_call(count_t count)
{
  count_t a = 0;
  for (count_t i = 0; i < count; ++i)
  {
    a += non_inline_func(i);
  }

  cout << "a: " << a << endl;
  return count;
}

inline count_t inline_func(count_t x)
{
  return x;
}

count_t benchmark_inline_func_call(count_t count)
{
  count_t a = 0;
  for (count_t i = 0; i < count; ++i)
  {
    a += inline_func(i);
  }

  cout << "a: " << a << endl;
  return count;
}

count_t benchmark_deref_ptr(count_t count)
{
  count_t a = 0;
  count_t* b = &a;
  count_t c;
  count_t result;
  for (count_t i = 0; i < count; ++i)
  {
    c = *b;
  }
  result = c;
  return result;
}

count_t benchmark_write_64k(count_t count)
{
  const int memSize = 1024 * 64;
  unsigned char mem[memSize];
  for (count_t i = 0; i < count; ++i)
  {
    for (int j = 0; j < memSize; ++j)
    {
      mem[j] = j;
    }
  }
  return mem[memSize - 1];
}

count_t benchmark_read_64k(count_t count)
{
  const int memSize = 1024 * 64;
  unsigned char mem[memSize];
  for (int j = 0; j < memSize; ++j)
  {
    mem[j] = j;
  }

  int result = 1;
  for (count_t i = 0; i < count; ++i)
  {
    for (int j = 0; j < memSize; ++j)
    {
      result &= mem[j];
    }
  }
  return result;
}

count_t benchmark_read_64k_vec(count_t count)
{
  const int memSize = 1024 * 64;
  vector<unsigned char> mem(memSize);
  for (int j = 0; j < memSize; ++j)
  {
    mem[j] = j;
  }

  int result = 1;
  for (count_t i = 0; i < count; ++i)
  {
    for (int j = 0; j < memSize; ++j)
    {
      result &= mem[j];
    }
  }
  return result;
}

count_t benchmark_read_64k_vec_at(count_t count)
{
  const int memSize = 1024 * 64;
  vector<unsigned char> mem(memSize);
  for (int j = 0; j < memSize; ++j)
  {
    mem[j] = j;
  }

  int result = 1;
  for (count_t i = 0; i < count; ++i)
  {
    for (int j = 0; j < memSize; ++j)
    {
      result &= mem.at(j);
    }
  }
  return result;
}

count_t benchmark_read_64k_array_at(count_t count)
{
  const int memSize = 1024 * 64;
  array<unsigned char, memSize> mem;
  for (int j = 0; j < memSize; ++j)
  {
    mem[j] = j;
  }

  int result = 1;
  for (count_t i = 0; i < count; ++i)
  {
    for (int j = 0; j < memSize; ++j)
    {
      result &= mem.at(j);
    }
  }
  return result;
}

count_t benchmark_try_catch(count_t count)
{
  int result = 0;
  for (count_t i = 0; i < count; ++i)
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
  return result;
}

int a_func(int a)
{
  return 2 * a;
}

count_t benchmark_func_ptr(count_t count)
{
  int result = 0;
  auto f_ptr = a_func;
  for (count_t i = 0; i < count; ++i)
  {
    result += f_ptr(1);
  }
  return result;
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

count_t benchmark_nonvirt_method(count_t count)
{
  int result = 0;
  C c;
  for (count_t i = 0; i < count; ++i)
  {
    result += c.a_method(1);
  }
  return result;
}

count_t benchmark_virt_method(count_t count)
{
  int result = 0;
  C2 c2;
  for (count_t i = 0; i < count; ++i)
  {
    result += c2.a_virtual_method(1);
  }
  return result;
}

vector<string> many_strings()
{
  return vector<string>(10000, "abcdefghijklmnopqrstuvwxyz");
}

vector<string> many_strings_static()
{
  static vector<string> result(10000, "abcdefghijklmnopqrstuvwxyz");
  return result;
}

count_t benchmark_string_concat_plus(count_t count)
{
  string result;
  for (const string& s : many_strings())
  {
    result += s;
  }
  return result.size();
}

count_t benchmark_string_concat_ostringstream(count_t count)
{
  ostringstream result;
  for (const string& s : many_strings())
  {
    result << s;
  }
  return result.str().size();
}

count_t benchmark_lambda(count_t count)
{
  int result = 0;
  int a;
  for (count_t i = 0; i < count; ++i)
  {
    result += [&a, i]() -> int { return a + i; }();
  }
  return result;
}

count_t benchmark_xor(count_t count)
{
  int result = 0;
  unsigned char c = 1;
  for (count_t i = 0; i < count; ++i)
  {
    c ^= i;
  }
  result = c;
  return result;
}

count_t benchmark_xor_bitset(count_t count)
{
  int result = 0;
  bitset<8> c = 1;
  for (count_t i = 0; i < count; ++i)
  {
    c ^= i;
  }
  result = c.to_ulong();
  return result;
}

typedef count_t (*benchmark_ptr)(count_t);

map<string, benchmark_ptr> commands = {
    {"empty", benchmark_empty},
    {"add", benchmark_add},
    {"func_call", benchmark_func_call},
    {"inline_func_call", benchmark_func_call},
    {"deref_ptr", benchmark_deref_ptr},
    {"write_64k", benchmark_write_64k},
    {"read_64k", benchmark_read_64k},
    {"read_64k_vec", benchmark_read_64k_vec},
    {"read_64k_vec_at", benchmark_read_64k_vec_at},
    {"read_64k_array_at", benchmark_read_64k_array_at},
    {"try_catch", benchmark_try_catch},
    {"func_ptr", benchmark_func_ptr},
    {"nonvirt_method", benchmark_nonvirt_method},
    {"virt_method", benchmark_virt_method},
    {"lambda", benchmark_lambda},
    {"xor", benchmark_xor},
    {"xor_bitset", benchmark_xor_bitset},
    {"benchmark_string_concat_plus", benchmark_string_concat_plus},
    {"benchmark_string_concat_ostringstream", benchmark_string_concat_ostringstream}};

int main(int argc, char const* argv[])
{
  if (argc < 3)
  {
    cerr << "usage" << endl;
    exit(1);
  }
  auto cmd_name = argv[1];
  auto count_str = argv[2];
  count_t count;
  istringstream count_strm(count_str);

  if (!(count_strm >> count))
  {
    cerr << "Invalid count: '" << count_str << endl;
    exit(1);
  }

  auto cmd_it = commands.find(cmd_name);
  if (cmd_it == commands.end())
  {
    cerr << "Command '" << cmd_name << "' unknown" << endl;
    exit(1);
  }

  thread_clock::time_point start = thread_clock::now();
  auto result = cmd_it->second(count);
  thread_clock::time_point stop = thread_clock::now();

  auto duration = duration_cast<nanoseconds>(stop - start).count();
  auto duration_per_call_ns = duration / static_cast<double>(count);
  auto duration_ms = duration / 1000000.;

  std::cout << "Result: " << result << endl;
  std::cout << "duration per call: " << duration_per_call_ns << " ns "
            << "(" << (duration_per_call_ns / 1000.) << " µs) \n";
  std::cout << (1. / duration_per_call_ns * 1000) << " million calls per s\n";
  std::cout << "duration: " << duration_ms << " ms\n";
  return 0;
}
