#pragma once


#include <thread>
#include <memory>
#include <atomic>
#include <cstdint>

static const std::uint64_t MIN_COUNT = 2;
static const std::uint64_t MAX_COUNT = 1000000;
static const std::uint64_t MAX_VALUE = 10000;
static const int SLEEP_TIME = 100;


class NumberGenerator {
    typedef std::shared_ptr<std::thread> ThreadPtr;

    std::atomic_flag _lock;
    const std::uint64_t _count;
    const int _sleep_timer;
    bool _is_run;
    ThreadPtr _thread;

    void run();

public:
    explicit NumberGenerator(std::uint64_t count, int sleep_timer = SLEEP_TIME);
    virtual ~NumberGenerator();

    operator bool();
};
