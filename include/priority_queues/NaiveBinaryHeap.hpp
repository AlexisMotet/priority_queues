#pragma once

#include "PriorityQueue.hpp"

#include <cstddef>
#include <vector>

namespace priority_queues {

template <typename T> class NaiveBinaryHeap : public PriorityQueue<T> {
  public:
    bool empty() const override {
        return data.empty();
    }

    std::size_t size() const override {
        return data.size();
    }

    void push(const T &item) override {
        auto i = data.size();
        data.push_back(item);
        sift_up(i);
    }

    void push(T &&item) override {
        auto i = data.size();
        data.push_back(std::move(item));
        sift_up(i);
    }

    const T &top() override {
        return data[0];
    }

    T pop() override {
        auto min = data[0];
        if (data.size() == 1) {
            data.pop_back();
            return min;
        }
        std::size_t i = 0;
        data[0] = std::move(data.back());
        auto child = 2 * i + 1; // left child
        while (child < data.size()) {
            if (child + 1 < data.size() && data[child + 1] < data[child]) {
                child = child + 1; // right child
            }
            if (data[child] < data[i]) {
                std::swap(data[i], data[child]);
                i = child;
                child = 2 * i + 1;
                continue;
            }
            break;
        }
        data.pop_back();
        return min;
    }

  private:
    std::vector<T> data;

    void sift_up(std::size_t i) {
        auto parent = (i - 1) / 2;
        while (i != 0) {
            if (data[i] < data[parent]) {
                std::swap(data[i], data[parent]);
                i = parent;
                parent = (i - 1) / 2;
                continue;
            }
            break;
        }
    }
};


} // namespace priority_queues