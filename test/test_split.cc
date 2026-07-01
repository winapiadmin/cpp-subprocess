#include <iostream>
#include <cpp-subprocess/subprocess.hpp>

using namespace subprocess;

int main() {

  auto vec = util::split("a b c");
  for (auto elem : vec) { std::cout << elem << std::endl; }

  std::cout << util::join(vec).length() << std::endl;
  return 0;
}
