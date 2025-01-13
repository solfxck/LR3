#include <gtest/gtest.h>
#include "containers/Array.h"
#include <string>

using namespace std;

// класс для тестирования
class ArrayTest : public ::testing::Test {
protected:
    Array array;
};

// тест пустого массива
TEST_F(ArrayTest, EmptyArrayTest) {
    EXPECT_EQ(array.length(), 0); // проверяем, что длина массива равна 0
    testing::internal::CaptureStdout(); // сохраняем вывод
    array.display(); // выводим массив
    string output = testing::internal::GetCapturedStdout(); // получаем вывод
    EXPECT_EQ(output, "Массив пуст!\n"); // проверяем, что вывод равен "Массив пуст!\n"
}

// тест добавления в конец
TEST_F(ArrayTest, PushEndTest) {
    array.pushEnd("1"); // добавляем элемент в конец
    EXPECT_EQ(array.get(0), "1"); // проверяем, что элемент добавлен правильно
    EXPECT_EQ(array.length(), 1); // проверяем, что длина массива равна 1
}

// тест переполнения при добавлении в конец
TEST_F(ArrayTest, PushEndOverflowTest) {
    for(int i = 0; i < 10; i++) {
        array.pushEnd(std::to_string(i)); // добавляем элементы в конец
    }
    testing::internal::CaptureStdout(); // сохраняем вывод
    array.pushEnd("overflow"); // добавляем элемент, который должен переполнить массив
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Массив переполнен!\n");
}

// тест вставки по индексу
TEST_F(ArrayTest, PushTest) {
    array.pushEnd("1");
    array.pushEnd("3");
    array.push(1, "2");
    EXPECT_EQ(array.get(0), "1");
    EXPECT_EQ(array.get(1), "2");
    EXPECT_EQ(array.get(2), "3");
}

// тест вставки по некорректному индексу
TEST_F(ArrayTest, PushInvalidIndexTest) {
    testing::internal::CaptureStdout();
    array.push(-1, "test");
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Индекс вне диапазона!\n");
}

// тест получения элемента по индексу
TEST_F(ArrayTest, GetTest) {
    array.pushEnd("test");
    EXPECT_EQ(array.get(0), "test");
}

// тест получения элемента по некорректному индексу
TEST_F(ArrayTest, GetInvalidIndexTest) {
    testing::internal::CaptureStdout();
    array.get(-1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Индекс вне диапазона!\n");
}

// тест удаления элемента
TEST_F(ArrayTest, PopTest) {
    array.pushEnd("1");
    array.pushEnd("2");
    array.pushEnd("3");
    array.pop(1);
    EXPECT_EQ(array.length(), 2);
    EXPECT_EQ(array.get(0), "1");
    EXPECT_EQ(array.get(1), "3");
}

// тест удаления по некорректному индексу
TEST_F(ArrayTest, PopInvalidIndexTest) {
    testing::internal::CaptureStdout();
    array.pop(-1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Индекс вне диапазона!\n");
}

// тест замены элемента
TEST_F(ArrayTest, ReplaceTest) {
    array.pushEnd("old");
    array.replace(0, "new");
    EXPECT_EQ(array.get(0), "new");
}

// тест замены по некорректному индексу
TEST_F(ArrayTest, ReplaceInvalidIndexTest) {
    testing::internal::CaptureStdout();
    array.replace(-1, "test");
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Индекс вне диапазона!\n");
}

// тест вывода массива
TEST_F(ArrayTest, DisplayTest) {
    array.pushEnd("1");
    array.pushEnd("2");
    array.pushEnd("3");
    testing::internal::CaptureStdout(); 
    array.display();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "1 2 3 \n");
}

// тест на утечки памяти
TEST_F(ArrayTest, DestructorTest) {
    Array* dynamicArray = new Array(); // создаем динамический массив
    dynamicArray->pushEnd("1"); // добавляем элементы
    dynamicArray->pushEnd("2");
    dynamicArray->pushEnd("3");
    delete dynamicArray; // удаляем массив
    SUCCEED(); // успешно
}