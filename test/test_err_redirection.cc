#include <cpp-subprocess/subprocess.hpp>
#include <iostream>

using namespace subprocess;

void test_redirect() {
    auto p = Popen("./write_err.sh", output{ "write_err.txt" }, error{ STDOUT });
    auto poll_res = p.poll();
    std::cout << (poll_res.has_value() ? std::to_string(*poll_res) : "running") << std::endl;
}

int main() {
#ifndef __USING_WINDOWS__
    test_redirect();
#endif
    return 0;
}
