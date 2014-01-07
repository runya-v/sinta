/*!
 * \brief  Диспетчер сигналов для управления подписавшимися объектами
 * \author Rostislav Velichko. rostislav.vel@gmail.com
 * \date   18.10.2013
 */

#pragma once

#include <string>
#include <cstddef>
#include <memory>
#include <array>
#include <functional>

#include "base.hpp"
#include "Log.hpp"


namespace base {
    
    class SignalDispatcher
        : public std::enable_shared_from_this<SignalDispatcher>
        , private boost::noncopyable
    {
        IoService _io_service;
        SignalSet _signal_set;
        ThreadPtr _thread;

    public:
        typedef std::function<void()> StopHandle;

        template<class ... Args>
        SignalDispatcher(const Args&... args)
            : _signal_set(_io_service, SIGINT, SIGTERM)
            , _thread(new std::thread(std::bind((IoServiceRunFunc)&IoService::run, &_io_service)))
        {
            std::size_t size = sizeof...(args);
            StopHandle res[sizeof...(args)] = {args...};

            auto stop_func = [size, res] () {
                for (std::uint32_t i = 0; i < size; ++i) {
                    res[i]();
                }
                LOG(INFO) << "Stop modules.";
            };
            _signal_set.async_wait(std::bind(stop_func));
            _thread->join();
        }
    };
} // namespace base
