#include "priority_queues/PriorityQueue.hpp"
#include "priority_queues/queue_factory.hpp"

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <random>

std::uint64_t num_comparisons = 0;

struct Event {
    void *data = nullptr;
    double priority;

    Event(double priority) : priority{priority} {}

    bool operator<(const Event &other) const {
        ++num_comparisons;
        return priority < other.priority;
    }

    bool operator>(const Event &other) const {
        ++num_comparisons;
        return priority > other.priority;
    }

    double get_priority() const {
        return priority;
    }
};

struct RandomIncrement {
    virtual ~RandomIncrement() = default;

    virtual double increment(std::mt19937 &rng) = 0;
};

struct ExponentialIncrement : public RandomIncrement {
    double increment(std::mt19937 &rng) override {
        static std::exponential_distribution<double> exp(1.0);
        return exp(rng);
    }
};

struct BimodalIncrement : public RandomIncrement {
    double increment(std::mt19937 &rng) override {
        static std::uniform_real_distribution<> rand(0.0, 1.0);
        return 9.95238 * rand(rng) + (rand(rng) < 0.1 ? 9.5238 : 0);
    }
};

std::chrono::nanoseconds hold(priority_queues::PriorityQueue<Event> &prio_queue,
                              RandomIncrement &random_incr,
                              std::size_t target_size,
                              unsigned int num_trials = 1'000'000) {
    std::mt19937 rng(42);
    std::uniform_real_distribution<> rand(0.0, 1.0);
    double old_priority = 0.0;
    while (prio_queue.size() < target_size) {
        if (rand(rng) >= 0.6) {
            if (!prio_queue.empty()) {
                old_priority = prio_queue.pop().priority;
            } else {
                old_priority = 0.0;
            }
        } else {
            double priority = old_priority + random_incr.increment(rng);
            prio_queue.push(Event(priority));
        }
    }
    num_comparisons = 0;
    auto start = std::chrono::steady_clock::now();
    for (unsigned int i = 0; i < num_trials; i++) {
        if (prio_queue.empty()) {
            break;
        }
        auto priority = prio_queue.pop().priority + random_incr.increment(rng);
        prio_queue.push(Event(priority));
    }
    auto end = std::chrono::steady_clock::now();
    return end - start;
}

int main(int argc, char **argv) {
    std::unique_ptr<priority_queues::PriorityQueue<Event>> prio_queue =
        priority_queues::queue_factory<Event>(argv[1]);
    std::string increment_type = argv[2];
    std::unique_ptr<RandomIncrement> random_increment;
    if (increment_type == "ExponentialIncrement") {
        random_increment = std::make_unique<ExponentialIncrement>();
    } else if (increment_type == "BimodalIncrement") {
        random_increment = std::make_unique<BimodalIncrement>();
    }
    std::cout << "target_size,time(ns),num_comparisons\n";
    for (std::size_t target_size : {1, 10, 100, 1000, 10000, 100000, 1000000}) {
        std::cout << target_size << ',';
        std::cout << hold(*prio_queue, *random_increment, target_size).count()
                  << ',';
        std::cout << num_comparisons << '\n';
    }
}