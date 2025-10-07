#include <coroutine>
#include <iostream>

struct SimpleCoroutine {
  struct promise_type {
    SimpleCoroutine get_return_object() { return {}; }
    std::suspend_always initial_suspend() { return {}; } // Suspend at the start
    std::suspend_always final_suspend() noexcept {
      return {};
    } // Suspend at the end
    void return_void() {}
    void unhandled_exception() { std::terminate(); }
  };
};

SimpleCoroutine coroutineWithSuspension() {
  std::cout << "Coroutine started\n";
  co_await std::suspend_always{}; // Suspend here, and the coroutine can be
                                  // resumed later
  std::cout << "Coroutine resumed\n";
  co_return;
}

int main() {
  auto coro =
      coroutineWithSuspension(); // Start coroutine, it will suspend immediately
  std::cout << "Coroutine is suspended\n";
  coro.co
}
