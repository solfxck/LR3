#include <benchmark/benchmark.h>
#include "containers/HashTable.h"
#include <string>
#include <vector>
#include <random>

using namespace std;

// Оптимизированный генератор случайных строк
class RandomStringGenerator {
private:
    mt19937 gen;
    uniform_int_distribution<> dis;
    static constexpr char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
public:
    RandomStringGenerator() : gen(random_device{}()), dis(0, sizeof(alphanum) - 2) {}
    
    string generate(size_t length = 5) {
        string result;
        result.reserve(length);
        for (size_t i = 0; i < length; ++i) {
            result += alphanum[dis(gen)];
        }
        return result;
    }
};

// Бенчмарк для вставки
static void BM_HashTableInsert(benchmark::State& state) {
    RandomStringGenerator gen;
    vector<string> keys;
    keys.reserve(state.range(0));
    
    // Предварительная генерация ключей
    for (int i = 0; i < state.range(0); ++i) {
        keys.push_back(gen.generate());
    }
    
    for (auto _ : state) {
        state.PauseTiming();
        HashTable table(state.range(0));
        state.ResumeTiming();
        
        for (const auto& key : keys) {
            table.insert(key, "value");
        }
    }
}
BENCHMARK(BM_HashTableInsert)->Range(8, 1024);

// Бенчмарк для поиска
static void BM_HashTableGet(benchmark::State& state) {
    RandomStringGenerator gen;
    HashTable table(state.range(0));
    vector<string> keys;
    keys.reserve(state.range(0));
    
    // предварительная генерация и вставка
    for (int i = 0; i < state.range(0); ++i) {
        string key = gen.generate();
        keys.push_back(key);
        table.insert(key, "value");
    }
    
    uniform_int_distribution<> dis(0, keys.size() - 1);
    mt19937 rng(random_device{}());
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(table.get(keys[dis(rng)]));
    }
}
BENCHMARK(BM_HashTableGet)->Range(8, 1024);

// Бенчмарк для удаления
static void BM_HashTableRemove(benchmark::State& state) {
    RandomStringGenerator gen;
    vector<string> keys;
    keys.reserve(state.range(0));
    
    for (auto _ : state) {
        state.PauseTiming();
        HashTable table(state.range(0));
        // предварительная генерация и вставка
        keys.clear();
        for (int i = 0; i < state.range(0); ++i) {
            string key = gen.generate();
            keys.push_back(key);
            table.insert(key, "value");
        }
        state.ResumeTiming();
        
        for (const auto& key : keys) {
            table.remove(key);
        }
    }
}
BENCHMARK(BM_HashTableRemove)->Range(8, 1024);

// Бенчмарк для вставки с коллизиями
static void BM_HashTableInsertWithCollisions(benchmark::State& state) {
    RandomStringGenerator gen;
    vector<string> keys;
    keys.reserve(state.range(0));
    
    // предварительная генерация ключей
    for (int i = 0; i < state.range(0); ++i) {
        keys.push_back(gen.generate());
    }
    
    for (auto _ : state) {
        state.PauseTiming();
        // создаем маленькую таблицу для гарантированных коллизий
        HashTable table(static_cast<int>(max(1L, state.range(0) / 8)));
        state.ResumeTiming();
        
        for (const auto& key : keys) {
            table.insert(key, "value");
        }
    }
}
BENCHMARK(BM_HashTableInsertWithCollisions)->Range(8, 1024);
