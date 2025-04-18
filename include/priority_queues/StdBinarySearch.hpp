#pragma once

#include "PriorityQueue.hpp"

#include <cstddef>
#include <functional>
#include <vector>

namespace priority_queues {

template <typename T> class StdBinarySearch : public PriorityQueue<T> {
  public:
    bool empty() const override {
        return data.empty();
    }

    std::size_t size() const override {
        return data.size();
    }

    void push(const T &item) override {
        auto it =
            std::lower_bound(data.begin(), data.end(), item, std::greater<T>());
        data.insert(it, item);
    }

    void push(T &&item) override {
        auto it =
            std::lower_bound(data.begin(), data.end(), item, std::greater<T>());
        data.insert(it, std::move(item));
    }

    const T &top() override {
        return data.back();
    }

    T pop() override {
        T item = data.back();
        data.pop_back();
        return item;
    }

  private:
    std::vector<T> data;
};

} // namespace priority_queues