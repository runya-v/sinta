#pragma once

#include <memory>
#include <atomic>


namespace base {

    template<class Instance>
    class Singleton {
        Singleton(const Singleton<Instance>&) = delete;
        Singleton& operator=(const Singleton<Instance>&) = delete;

    public:
        static Instance* get() {
            static Instance instance;
            return &instance;
//            static std::atomic_flag _lock = ATOMIC_FLAG_INIT;
//            _lock.test_and_set(std::memory_order_acquire);
//            if (not _only_one_instance.get()) {
//                _only_one_instance.reset(new T());
//            }
//            _lock.clear(std::memory_order_release);
//            return _only_one_instance.get();
        }
    };
} // namespace base
