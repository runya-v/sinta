#pragma once


namespace base {

    class Timer {
        ThreadPtr _timer_thread;

    public:
        template<class Callable, class... Arguments>
        Timer(int after, bool async, Callable &&f, Arguments&&... args) {
            typedef std::function<typename std::result_of<Callable(Arguments...)>::type()> TimerTask;

            TimerTask task(std::bind(std::forward<Callable>(f), std::forward<Arguments>(args)...));

            if (async) {
                auto timer_run = [after, task]() {
                    std::this_thread::sleep_for(std::chrono::milliseconds(after));
                    task();
                };

                _timer_thread = std::make_shared<std::thread>(imer_run);
                _timer_thread->detach();
            }
            else {
                std::this_thread::sleep_for(std::chrono::milliseconds(after));
                task();
            }
        }
    };
} // namespace base
