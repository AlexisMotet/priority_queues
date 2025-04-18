#include "priority_queues/PriorityQueue.hpp"
#include "priority_queues/queue_factory.hpp"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <random>
#include <string>

struct Event {
    void *data = nullptr;
    double priority;

    Event(double priority) : priority{priority} {}

    bool operator<(const Event &other) const {
        return priority < other.priority;
    }

    bool operator>(const Event &other) const {
        return priority > other.priority;
    }

    double get_priority() const {
        return priority;
    }
};

int main() {
    bool failed = false;
    std::mt19937 rng(42);
    std::exponential_distribution<double> exp(1.0);
    std::unique_ptr<priority_queues::PriorityQueue<Event>> queue;
    for (const std::string &queue_type : priority_queues::get_queue_types()) {
        std::cout << queue_type << '\n';
        queue = priority_queues::queue_factory<Event>(queue_type);
        for (std::size_t i = 0; i < 1'000; i++) {
            queue->push(Event(exp(rng)));
        }
        if (queue->size() != 1'000) {
            std::cerr << "test failed for " << queue_type << "\n";
        }
        double old_prio = 0.0;
        for (std::size_t i = 0; i < 500; i++) {
            auto prio = queue->pop().priority;
            if (prio < old_prio) {
                std::cerr << "test failed for " << queue_type << "\n";
                failed = true;
            }
        }
        if (queue->size() != 500) {
            std::cerr << "test failed for " << queue_type << "\n";
        }
        for (std::size_t i = 0; i < 1'000; i++) {
            queue->push(Event(exp(rng)));
        }
        if (queue->size() != 1'500) {
            std::cerr << "test failed for " << queue_type << "\n";
        }
        old_prio = 0.0;
        while (!queue->empty()) {
            auto prio = queue->pop().priority;
            if (prio < old_prio) {
                std::cerr << "test failed for " << queue_type << "\n";
                failed = true;
            }
        }
        if (queue->size() != 0) {
            std::cerr << "test failed for " << queue_type << "\n";
        }
    }
    if (failed) {
        std::exit(1);
    } else {
        std::cout << "test ok!\n";
    }
}