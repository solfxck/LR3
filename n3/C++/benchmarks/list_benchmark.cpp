#include <benchmark/benchmark.h>
#include "containers/List.h"
#include <list>
#include <string>

using namespace std;

// Бенчмарк для pushHead
static void BM_ListPushHead(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        List list;
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            list.pushHead(to_string(i));
        }
    }
}
BENCHMARK(BM_ListPushHead)->Range(8, 1024);

// Бенчмарк для pushTail
static void BM_ListPushTail(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        List list;
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            list.pushTail(to_string(i));
        }
    }
}
BENCHMARK(BM_ListPushTail)->Range(8, 1024);

// Бенчмарк для popHead
static void BM_ListPopHead(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        List list;
        for (int i = 0; i < state.range(0); ++i) {
            list.pushHead(to_string(i));
        }
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            list.popHead();
        }
    }
}
BENCHMARK(BM_ListPopHead)->Range(8, 1024);

// Бенчмарк для popTail
static void BM_ListPopTail(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        List list;
        for (int i = 0; i < state.range(0); ++i) {
            list.pushHead(to_string(i));
        }
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            list.popTail();
        }
    }
}
BENCHMARK(BM_ListPopTail)->Range(8, 1024);


static void BM_ListSearch(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        List list;
        for (int i = 0; i < state.range(0); ++i) {
            list.pushHead(to_string(i));
        }
        state.ResumeTiming();
        for (int i = 0; i < 100; ++i) {
            list.search(to_string(rand() % state.range(0)));
        }
    }
}
BENCHMARK(BM_ListSearch)->Range(8, 1024);
