#pragma once

#include "PriorityQueue.hpp"

#include <cstddef>
#include <vector>

namespace priority_queues {

template <typename T> class FloydBinaryHeap : public PriorityQueue<T> {
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
        auto last = std::move(data.back());
        data.pop_back();
        std::size_t hole = 0;
        std::size_t min_child = 1;
        while (min_child < data.size()) { // hole is a leaf
            if (min_child + 1 < data.size() &&
                data[min_child + 1] < data[min_child]) {
                ++min_child;
            }
            std::swap(data[hole], data[min_child]);
            hole = min_child;
            min_child = 2 * min_child + 1;
        }
        data[hole] = std::move(last);
        sift_up(hole);
        return min;
    }

  private:
    std::vector<T> data;

    void sift_up(std::size_t i) {
        std::size_t parent = (i - 1) / 2;
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