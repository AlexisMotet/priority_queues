#pragma once

#include <cstddef>

namespace priority_queues {

template <typename T> class PriorityQueue {
  public:
    virtual ~PriorityQueue() = default;

    virtual bool empty() const = 0;

    virtual std::size_t size() const = 0;

    virtual void push(const T &item) = 0;

    virtual void push(T &&item) = 0;

    virtual const T &top() = 0;

    virtual T pop() = 0;
};

} // namespace priority_queues