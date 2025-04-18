#pragma once

#include "PriorityQueue.hpp"

#include <cstddef>
#include <vector>

namespace priority_queues {

template <typename T, unsigned int D>
class NaiveDaryHeap : public PriorityQueue<T> {
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
        auto first_child = D * i + 1; // first child
        while (first_child < data.size()) {
            auto min_child = first_child;
            for (unsigned int j = 1; j < D; j++) {
                if (first_child + j < data.size() &&
                    data[first_child + j] < data[min_child]) {
                    min_child = first_child + j;
                }
            }
            if (data[min_child] < data[i]) {
                std::swap(data[i], data[min_child]);
                i = min_child;
                first_child = D * i + 1;
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
        auto parent = (i - 1) / D;
        while (i != 0) {
            if (data[i] < data[parent]) {
                std::swap(data[i], data[parent]);
                i = parent;
                parent = (i - 1) / D;
                continue;
            }
            break;
        }
    }
};

} // namespace priority_queues