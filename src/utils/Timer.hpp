/*!
 * \brief  Обёртка для работы с таймером.
 * \author R.N.Velichko rostislav.vel@gmail.com
 * \date   02.03.2013
 */

#pragma once

#include <chrono>
#include <thread>


namespace chr  = std::chrono;

namespace utils {

class Timer {
  std::atomic_flag             is_run_; ///< Атомарный флаг
  std::shared_ptr<std::thread> thread_; ///< Поток цклического таймера

public:
  template<class Callable, class... Arguments>
  Timer(chr::milliseconds sleep, bool async, Callable &&f, Arguments&&... args) {
    auto task(std::bind(std::forward<Callable>(f), std::forward<Arguments>(args)...));
    auto weit = [&]() {
      std::this_thread::sleep_for(sleep);
      task();
    }

    if (async) {
      auto run = [this, sleep, task]() {
        while (is_run_.test_and_set(std::memory_order_acquire)) {
          weit();
        }
      };
      is_run_.test_and_set(std::memory_order_acquire);
      thread_ = std::make_shared<std::thread>(run);
    }
    else {
      weit();
    }
  }

  ~Timer() {
    is_run_.clear(std::memory_order_release);
    thread_->join();
  }
};
} // namespace
