#include <benchmark/benchmark.h>
#include "containers/Array.h"
#include <string>

using namespace std;

// Бенчмарк для pushEnd
static void BM_ArrayPushEnd(benchmark::State& state) {
    for (auto _ : state) { 
        state.PauseTiming(); // пауза
        Array array;
        state.ResumeTiming(); // продолжение
        for (int i = 0; i < state.range(0) && i < 10; i++) {
            array.pushEnd(to_string(i));
        }
    }
}
BENCHMARK(BM_ArrayPushEnd)->Range(8, 1024);

// Бенчмарк для push (вставка в середину)
static void BM_ArrayPush(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        Array array;
        for (int i = 0; i < state.range(0) && i < 9; i++) {
            array.pushEnd(to_string(i));
        }
        state.ResumeTiming();
        if (array.length() < 10) {
            array.push(array.length() / 2, "test");
        }
    }
}
BENCHMARK(BM_ArrayPush)->Range(8, 1024);

// Бенчмарк для pop (удаление из середины)
static void BM_ArrayPop(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        Array array;
        for (int i = 0; i < state.range(0) && i < 10; i++) {
            array.pushEnd(to_string(i));
        }
        state.ResumeTiming();
        if (array.length() > 0) {
            array.pop(array.length() / 2);
        }
    }
}
BENCHMARK(BM_ArrayPop)->Range(8, 1024);

// Бенчмарк для get (доступ к элементу)
static void BM_ArrayGet(benchmark::State& state) {
    Array array;
    for (int i = 0; i < state.range(0) && i < 10; i++) {
        array.pushEnd(to_string(i));
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(array.get(array.length() / 2));
    }
}
BENCHMARK(BM_ArrayGet)->Range(8, 1024);

// Бенчмарк для replace (замена элемента)
static void BM_ArrayReplace(benchmark::State& state) {
    Array array;
    for (int i = 0; i < state.range(0) && i < 10; i++) {
        array.pushEnd(to_string(i));
    }
    for (auto _ : state) {
        array.replace(array.length() / 2, "test");
    }
}
BENCHMARK(BM_ArrayReplace)->Range(8, 1024);
