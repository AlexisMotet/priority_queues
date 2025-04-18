#pragma once

#include "FloydBinaryHeap.hpp"
#include "NaiveBinaryHeap.hpp"
#include "NaiveDaryHeap.hpp"
#include "PriorityQueue.hpp"
#include "RadixHeapDouble.hpp"
#include "StdBinarySearch.hpp"
#include "StdPriorityQueue.hpp"

#include <memory>
#include <string>
#include <vector>

namespace priority_queues {

const std::vector<std::string> &get_queue_types() {
    static std::vector<std::string> queue_types = {
        "StdPriorityQueue", "StdBinarySearch", "NaiveBinaryHeap",
        "Naive4AryHeap",    "Naive8AryHeap",   "Naive16AryHeap",
        "Naive32AryHeap",   "FloydBinaryHeap", "RadixHeapDouble"};
    return queue_types;
}

template <typename T>
std::unique_ptr<PriorityQueue<T>> queue_factory(const std::string &queue_type) {
    if (queue_type == "std_priority_queue") {
        return std::make_unique<StdPriorityQueue<T>>();
    } else if (queue_type == "std_binary_search") {
        return std::make_unique<StdBinarySearch<T>>();
    } else if (queue_type == "binary_heap") {
        return std::make_unique<NaiveBinaryHeap<T>>();
    } else if (queue_type == "4ary_heap") {
        return std::make_unique<NaiveDaryHeap<T, 4>>();
    } else if (queue_type == "8ary_heap") {
        return std::make_unique<NaiveDaryHeap<T, 8>>();
    } else if (queue_type == "16ary_heap") {
        return std::make_unique<NaiveDaryHeap<T, 16>>();
    } else if (queue_type == "32ary_heap") {
        return std::make_unique<NaiveDaryHeap<T, 32>>();
    } else if (queue_type == "floyd_binary_heap") {
        return std::make_unique<FloydBinaryHeap<T>>();
    } else if (queue_type == "radix_heap_double") {
        return std::make_unique<RadixHeapDouble<T>>();
    }
    return nullptr;
}

} // namespace priority_queues