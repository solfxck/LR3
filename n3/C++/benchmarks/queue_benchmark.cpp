#include <benchmark/benchmark.h>
#include "containers/Queue.h"
#include <queue>
#include <string>

using namespace std;

static void BM_QueuePush(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        Queue queue;
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            queue.push(to_string(i));
        }
    }
}
BENCHMARK(BM_QueuePush)->Range(8, 1024);

static void BM_QueuePop(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        Queue queue;
        for (int i = 0; i < state.range(0); ++i) {
            queue.push(to_string(i));
        }
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            queue.pop();
        }
    }
}
BENCHMARK(BM_QueuePop)->Range(8, 1024);
