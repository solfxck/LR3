#include <benchmark/benchmark.h>
#include "containers/Stack.h"
#include <stack>
#include <string>

using namespace std;

static void BM_StackPush(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        Stack stack;
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            stack.push(to_string(i));
        }
    }
}
BENCHMARK(BM_StackPush)->Range(8, 1024);

static void BM_StackPop(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        Stack stack;
        for (int i = 0; i < state.range(0); ++i) {
            stack.push(to_string(i));
        }
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            stack.pop();
        }
    }
}
BENCHMARK(BM_StackPop)->Range(8, 1024);
