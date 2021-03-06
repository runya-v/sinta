/*!
 * \brief  Обёртка потоковой задачи.
 * \author Rostislav Velichko. e: rostislav.vel@gmail.com
 * \date   02.03.2013
 */

#pragma once

#include <memory>
#include <functional>
#include <string>

#include "Timer.hpp"


namespace base {
    class Task;
    typedef std::shared_ptr<Task> TaskPtr;
    typedef std::function<void(const TaskPtr&)> TaskHandle;
    typedef std::function<void()> Handle;


    class Task
        : public std::enable_shared_from_this<Task>
    {
        TimePoint _create_time;

    protected:
        std::string _data;
        TaskHandle  _task_handle_exec;
        Handle      _handle_exec;
        Handle      _handle_next;

    public:
        explicit Task(Handle &&handle_exec);
        explicit Task(TaskHandle &&handle_exec);
        ~Task();

        void setNextTaskHandle(Handle &&handle_next);
        void execute(const TaskPtr &task);
        std::string& getData();
        std::uint64_t getTimeInterval();
    };
} // namespace base
