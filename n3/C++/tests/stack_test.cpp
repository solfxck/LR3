#include <gtest/gtest.h>
#include "containers/Stack.h"
#include <string>

using namespace std;

class StackTest : public ::testing::Test {
protected:
    Stack stack;
};

// тест на создание пустого стека
TEST_F(StackTest, EmptyStackTest) {
    EXPECT_EQ(stack.getTop(), nullptr);
}

// тест на добавление элемента в стек
TEST_F(StackTest, PushTest) {
    stack.push("1");
    EXPECT_NE(stack.getTop(), nullptr);
    EXPECT_EQ(stack.getTop()->data, "1");
}

// тест на добавление нескольких элементов в стек
TEST_F(StackTest, MultiplePushTest) {
    stack.push("1");
    stack.push("2");
    stack.push("3");
    EXPECT_EQ(stack.getTop()->data, "3");
    EXPECT_EQ(stack.getTop()->next->data, "2");
}

// тест на удаление элемента из стека
TEST_F(StackTest, PopTest) {
    stack.push("1");
    stack.push("2");
    Node1* oldTop = stack.getTop();
    stack.pop();
    EXPECT_EQ(stack.getTop()->data, "1");
}

// тест на попытку удаления элемента из пустого стека
TEST_F(StackTest, EmptyPopTest) {
    testing::internal::CaptureStdout();
    stack.pop();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Стек пуст!\n");
}

// тест вывода стека
TEST_F(StackTest, DisplayEmptyTest) {
    testing::internal::CaptureStdout();
    stack.display();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Стек пуст!\n");
}

// тест вывода стека
TEST_F(StackTest, DisplayTest) {
    stack.push("1");
    stack.push("2");
    stack.push("3");
    testing::internal::CaptureStdout();
    stack.display();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "3 2 1 \n");
}

// тест на утечки памяти
TEST_F(StackTest, DestructorTest) {
    Stack* dynamicStack = new Stack();
    dynamicStack->push("1");
    dynamicStack->push("2");
    dynamicStack->push("3");
    delete dynamicStack;
    SUCCEED();
}
