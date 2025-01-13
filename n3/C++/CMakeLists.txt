cmake_minimum_required(VERSION 3.10)
project(ContainersTest)

# Включаем поддержку тестирования в проекте
enable_testing()

# Устанавливаем стандарт языка C++ на 17 и указываем, что он обязателен
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем флаги компилятора для сбора данных о покрытии кода (code coverage)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

# Ищем и подключаем необходимые пакеты: Google Test (GTest) и библиотеку для бенчмарков (benchmark)
find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

# Добавляем директории для включения заголовочных файлов
include_directories(${GTEST_INCLUDE_DIRS})  # Директории с заголовками GTest
include_directories(${PROJECT_SOURCE_DIR})  # Директория исходного кода проекта

# Создаем исполняемый файл для тестов
add_executable(unit_tests
    tests/test_main.cpp          
    tests/queue_test.cpp         
    tests/stack_test.cpp        
    tests/list_test.cpp          
    tests/array_test.cpp        
    tests/avl_test.cpp          
    tests/duble_list_test.cpp  
    tests/hash_table_test.cpp 
)

# Связываем тестовый исполняемый файл с необходимыми библиотеками
target_link_libraries(unit_tests
    ${GTEST_LIBRARIES}  # Библиотеки Google Test
    pthread             # Библиотека для работы с потоками
    gcov                # Библиотека для сбора данных о покрытии кода
)

# Создаем исполняемый файл для бенчмарков (benchmark_test)
add_executable(benchmark_test
    benchmarks/benchmark_main.cpp       
    benchmarks/queue_benchmark.cpp     
    benchmarks/stack_benchmark.cpp      
    benchmarks/list_benchmark.cpp       
    benchmarks/array_benchmark.cpp      
    benchmarks/avl_benchmark.cpp        
    benchmarks/duble_list_benchmark.cpp 
    benchmarks/hash_table_benchmark.cpp 
)

# Связываем бенчмарк-исполняемый файл с необходимыми библиотеками
target_link_libraries(benchmark_test
    benchmark::benchmark  # Библиотека для бенчмарков
    pthread               # Библиотека для работы с потоками
)
