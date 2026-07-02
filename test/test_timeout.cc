#include <cpp-subprocess/subprocess.hpp>
#include <iostream>

#ifdef __USING_WINDOWS__
#include <Windows.h>
#endif

namespace sp = subprocess;

void test_wait_timeout_expired() {
    std::cout << "Test::test_wait_timeout_expired" << std::endl;
#ifdef __USING_WINDOWS__
    auto p = sp::Popen({ "cmd.exe", "/c", "ping", "-n", "30", "127.0.0.1" });
#else
    auto p = sp::Popen({ "sleep", "30" });
#endif
    bool caught = false;
    try {
        p.wait(100);
    } catch (sp::TimeoutExpired &e) {
        std::cout << "Caught TimeoutExpired (expected): " << e.what() << std::endl;
        caught = true;
    }
    assert(caught);
    // Clean up the still-running process
    p.kill();
    p.wait();
}

void test_wait_no_timeout() {
    std::cout << "Test::test_wait_no_timeout" << std::endl;
#ifdef __USING_WINDOWS__
    auto p = sp::Popen({ "cmd.exe", "/c", "echo", "hi" });
#else
    auto p = sp::Popen({ "echo", "hi" });
#endif
    int ret = p.wait(5000);
    assert(ret == 0);
}

void test_communicate_timeout_expired() {
    std::cout << "Test::test_communicate_timeout_expired" << std::endl;
#ifdef __USING_WINDOWS__
    auto p = sp::Popen({ "cmd.exe", "/c", "ping", "-n", "30", "127.0.0.1" }, sp::output{ sp::PIPE });
#else
    auto p = sp::Popen({ "sleep", "30" }, sp::output{ sp::PIPE });
#endif
    bool caught = false;
    try {
        p.communicate(100);
    } catch (sp::TimeoutExpired &e) {
        std::cout << "Caught TimeoutExpired (expected): " << e.what() << std::endl;
        caught = true;
    }
    assert(caught);
}

void test_communicate_no_timeout() {
    std::cout << "Test::test_communicate_no_timeout" << std::endl;
#ifdef __USING_WINDOWS__
    auto p = sp::Popen({ "cmd.exe", "/c", "echo", "hello" }, sp::output{ sp::PIPE });
#else
    auto p = sp::Popen({ "echo", "hello" }, sp::output{ sp::PIPE });
#endif
    auto res = p.communicate(5000);
    assert(p.retcode() == 0);
    std::cout << "Output: " << res.first.buf.data() << std::endl;
}

int main() {
    test_wait_timeout_expired();
    test_wait_no_timeout();
    test_communicate_timeout_expired();
    test_communicate_no_timeout();
    std::cout << "All timeout tests passed!" << std::endl;
    return 0;
}
