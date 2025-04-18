#pragma once

#include "PriorityQueue.hpp"

#include <array>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

namespace priority_queues {

template <typename T>
concept Prioritizable = requires(const T &t) {
    { t.get_priority() } -> std::convertible_to<double>;
};

template <Prioritizable T> class RadixHeapDouble : public PriorityQueue<T> {
  public:
    bool empty() const override {
        return size_ == 0;
    }

    std::size_t size() const override {
        return size_;
    }

    void push(const T &item) override {
        unsigned int k = compute_bucket_index(item.get_priority());
        buckets[k].push_back(item);
        ++size_;
    }

    void push(T &&item) override {
        unsigned int k = compute_bucket_index(item.get_priority());
        buckets[k].push_back(std::move(item));
        ++size_;
    }

    const T &top() override {
        if (buckets[0].empty()) {
            pull();
        }
        double min_prio = buckets[0][0].get_priority();
        std::size_t min_index = 0;
        for (std::size_t i = 1; i < buckets[0].size(); i++) {
            if (buckets[0][i].get_priority() < min_prio) {
                min_prio = buckets[0][i].get_priority();
                min_index = i;
            }
        }
        return buckets[0][min_index];
    }

    T pop() override {
        if (buckets[0].empty()) {
            pull();
        }
        double min_prio = buckets[0][0].get_priority();
        std::size_t min_index = 0;
        for (std::size_t i = 1; i < buckets[0].size(); i++) {
            if (buckets[0][i].get_priority() < min_prio) {
                min_prio = buckets[0][i].get_priority();
                min_index = i;
            }
        }
        auto min_elem = std::move(buckets[0][min_index]);
        std::swap(buckets[0][min_index], buckets[0][buckets[0].size() - 1]);
        buckets[0].pop_back();
        --size_;
        return min_elem;
    }


  private:
    static constexpr unsigned int NUM_BUCKETS = 64;
    std::array<std::vector<T>, NUM_BUCKETS> buckets;
    double pull_min = 0;
    std::size_t size_ = 0;

    void pull() {
        unsigned int k = 1;
        while (buckets[k].empty()) {
            ++k;
        }
        pull_min = buckets[k][0].get_priority();
        for (std::size_t i = 1; i < buckets[k].size(); i++) {
            if (buckets[k][i].get_priority() < pull_min) {
                pull_min = buckets[k][i].get_priority();
            }
        }
        for (std::size_t i = 0; i < buckets[k].size(); i++) {
            auto item = std::move(buckets[k][i]);
            unsigned int j = compute_bucket_index(item.get_priority());
            assert(j < k);
            buckets[j].push_back(std::move(item));
        }
        buckets[k].clear();
    }

    unsigned int compute_bucket_index(double priority) {
        return std::bit_width(std::bit_cast<std::uint64_t>(priority) ^
                              std::bit_cast<std::uint64_t>(pull_min));
    }
};

} // namespace priority_queues