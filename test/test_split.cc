#include <cpp-subprocess/subprocess.hpp>
#include <iostream>

using namespace subprocess;

int main() {

    auto vec = util::split("a b c");
    for (auto elem : vec) {
        std::cout << elem << std::endl;
    }

    std::cout << util::join(vec).length() << std::endl;
    return 0;
}
