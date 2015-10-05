/*!
 * \brief  Обёртка потоковой задачи.
 * \author R.N.Velichko rostislav.vel@gmail.com
 * \date   02.03.2013
 */

#pragma once

#include <memory>

#include "base.hpp"


namespace utils {

class Task : public std::enable_shared_from_this<Task> {
  TimePoint _create_time;

protected:
  std::string _data;
  TaskHandle  _task_handle_exec;
  Handle      _handle_exec;
  Handle      _handle_next;

public:
  typedef std::shared_ptr<Task>               TaskPtr;
  typedef std::function<void(const TaskPtr&)> TaskHandle;

  explicit Task(Handle &&handle_exec);
  explicit Task(TaskHandle &&handle_exec);
  ~Task();

  void setNextTaskHandle(Handle &&handle_next);
  void execute(const TaskPtr &task);
  std::string& getData();
  uint64_t getTimeInterval();
};
} // namespace
