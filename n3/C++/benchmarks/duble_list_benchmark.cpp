#include <benchmark/benchmark.h>
#include "containers/DubleList.h"
#include <string>
#include <vector>
#include <random>

using namespace std;

// Бенчмарк для pushHead
static void BM_DubleListPushHead(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        DubleList list;
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            list.pushHead(to_string(i));
        }
    }
}
BENCHMARK(BM_DubleListPushHead)->Range(8, 1024);

// Бенчмарк для pushTail
static void BM_DubleListPushTail(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        DubleList list;
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            list.pushTail(to_string(i));
        }
    }
}
BENCHMARK(BM_DubleListPushTail)->Range(8, 1024);

// Бенчмарк для popHead
static void BM_DubleListPopHead(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        DubleList list;
        for (int i = 0; i < state.range(0); ++i) {
            list.pushHead(to_string(i));
        }
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            list.popHead();
        }
    }
}
BENCHMARK(BM_DubleListPopHead)->Range(8, 1024);

// Бенчмарк для popTail
static void BM_DubleListPopTail(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        DubleList list;
        for (int i = 0; i < state.range(0); ++i) {
            list.pushTail(to_string(i));
        }
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            list.popTail();
        }
    }
}
BENCHMARK(BM_DubleListPopTail)->Range(8, 1024);

// Бенчмарк для поиска
static void BM_DubleListSearch(benchmark::State& state) {
    DubleList list;
    vector<string> values;
    for (int i = 0; i < state.range(0); ++i) {
        string value = to_string(i);
        values.push_back(value);
        list.pushTail(value);
    }
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, state.range(0) - 1);
    
    for (auto _ : state) {
        int index = dis(gen);
        benchmark::DoNotOptimize(list.search(values[index]));
    }
}
BENCHMARK(BM_DubleListSearch)->Range(8, 1024);

// Бенчмарк для popValue
static void BM_DubleListPopValue(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        DubleList list;
        vector<string> values;
        for (int i = 0; i < state.range(0); ++i) {
            string value = to_string(i);
            values.push_back(value);
            list.pushTail(value);
        }
        state.ResumeTiming();
        
        for (const auto& value : values) {
            list.popValue(value);
        }
    }
}
BENCHMARK(BM_DubleListPopValue)->Range(8, 1024);
