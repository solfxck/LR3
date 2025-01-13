#include <benchmark/benchmark.h>
#include "containers/AVL.h"
#include <string>
#include <vector>
#include <random>

using namespace std;

// Бенчмарк для вставки
static void BM_AVLInsert(benchmark::State& state) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000000);
    
    for (auto _ : state) {
        state.PauseTiming();
        AVL tree;
        vector<int> values;
        for (int i = 0; i < state.range(0); ++i) {
            values.push_back(dis(gen));
        }
        state.ResumeTiming();
        
        for (int value : values) {
            tree.insert(value);
        }
    }
}
BENCHMARK(BM_AVLInsert)->Range(8, 1024);

// Бенчмарк для поиска
static void BM_AVLSearch(benchmark::State& state) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000000);
    
    AVL tree;
    vector<int> values;
    for (int i = 0; i < state.range(0); ++i) {
        int value = dis(gen);
        values.push_back(value);
        tree.insert(value);
    }
    
    for (auto _ : state) {
        int index = dis(gen) % values.size();
        benchmark::DoNotOptimize(tree.search(values[index]));
    }
}
BENCHMARK(BM_AVLSearch)->Range(8, 1024);

// Бенчмарк для удаления
static void BM_AVLRemove(benchmark::State& state) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000000);
    
    for (auto _ : state) {
        state.PauseTiming();
        AVL tree;
        vector<int> values;
        for (int i = 0; i < state.range(0); ++i) {
            int value = dis(gen);
            values.push_back(value);
            tree.insert(value);
        }
        state.ResumeTiming();
        
        for (int value : values) {
            tree.remove(value);
        }
    }
}
BENCHMARK(BM_AVLRemove)->Range(8, 1024);
