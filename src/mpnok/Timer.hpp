/*!
 * \brief  Обёртка для работы с таймером.
 * \author Rostislav Velichko. e: rostislav.vel@gmail.com
 * \date   02.03.2013
 */

#pragma once

#include <chrono>
#include <thread>
#include <memory>

namespace base {
    typedef std::chrono::high_resolution_clock HighResolutionClock;
    typedef HighResolutionClock::time_point    TimePoint;
    typedef std::chrono::nanoseconds  Nano;
    typedef std::chrono::microseconds Micro;
    typedef std::chrono::milliseconds Milli;
    typedef std::chrono::seconds      Secs;
    typedef std::chrono::minutes      Mins;
    typedef std::chrono::hours        Hours;
    typedef std::shared_ptr<std::thread> ThreadPtr;


    class Timer {
        ThreadPtr _timer_thread;

    public:
        static std::uint64_t currentMillisecs() {
            auto now = std::chrono::system_clock::now();
            auto duration = now.time_since_epoch();
            return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        }


        template<class Callable, class... Arguments>
        Timer(int after, bool async, Callable &&f, Arguments&&... args) {
            typedef std::function<typename std::result_of<Callable(Arguments...)>::type()> TimerTask;

            TimerTask task(std::bind(std::forward<Callable>(f), std::forward<Arguments>(args)...));

            if (async) {
                auto timer_run = [after, task]() {
                    std::this_thread::sleep_for(std::chrono::milliseconds(after));
                    task();
                };

                _timer_thread = std::make_shared<std::thread>(timer_run);
                _timer_thread->detach();
            }
            else {
                std::this_thread::sleep_for(std::chrono::milliseconds(after));
                task();
            }
        }
    };

    typedef std::shared_ptr<Timer> TimerPtr;
} // namespace base
