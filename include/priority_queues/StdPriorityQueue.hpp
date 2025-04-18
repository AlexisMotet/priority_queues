#pragma once

#include "PriorityQueue.hpp"

#include <cstddef>
#include <functional>
#include <queue>
#include <vector>

namespace priority_queues {

template <typename T> class StdPriorityQueue : public PriorityQueue<T> {
  public:
    bool empty() const override {
        return pqueue.empty();
    }

    std::size_t size() const override {
        return pqueue.size();
    }

    void push(const T &item) override {
        pqueue.push(item);
    }

    void push(T &&item) override {
        pqueue.push(std::move(item));
    }

    const T &top() override {
        return pqueue.top();
    }

    T pop() override {
        auto min = pqueue.top();
        pqueue.pop();
        return min;
    }

  private:
    std::priority_queue<T, std::vector<T>, std::greater<T>> pqueue;
};


} // namespace priority_queues