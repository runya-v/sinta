#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Log.hpp"
#include "Timer.hpp"
#include "NumberGenerator.hpp"


void NumberGenerator::run() {
    LOG(DEBUG);
    std::srand(std::time(0));
    for(int i = 0; i < _count and not _lock.test_and_set(std::memory_order_acquire); ++i) {
        std::uint64_t num = std::rand() % MAX_VALUE;
        std::cout << num << "\n" << std::flush;
        _lock.clear(std::memory_order_release);
        std::this_thread::sleep_for(std::chrono::milliseconds(_sleep_timer));
    }
    _is_run = false;
}


NumberGenerator::NumberGenerator(std::uint64_t count, int sleep_timer)
    : _lock(ATOMIC_FLAG_INIT)
    , _count((MIN_COUNT <= count and MAX_COUNT >= count) ? count : (MAX_COUNT * 0.5))
    , _sleep_timer(sleep_timer)
    , _is_run(true)
    , _thread(std::make_shared<std::thread>(std::bind(&NumberGenerator::run,  this)))
{
    LOG(DEBUG);
}


NumberGenerator::~NumberGenerator() {
    LOG(DEBUG);
    if (_thread) {
        _lock.test_and_set(std::memory_order_acquire);
        _thread->join();
    }
}


NumberGenerator::operator bool() {
    LOG(DEBUG) << (_is_run ? "TRUE" : "FALSE");
    return _is_run;
}
