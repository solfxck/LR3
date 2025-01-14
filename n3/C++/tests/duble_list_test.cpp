#include <gtest/gtest.h>
#include "containers/DubleList.h"
#include <string>

using namespace std;

class DubleListTest : public ::testing::Test {
protected:
    DubleList list;
};

// Тест пустого списка
TEST_F(DubleListTest, EmptyListTest) {
    EXPECT_EQ(list.getHead(), nullptr);
    EXPECT_EQ(list.getTail(), nullptr);
    testing::internal::CaptureStdout();
    list.display();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Список пуст!\n");
}

// Тест добавления в начало
TEST_F(DubleListTest, PushHeadTest) {
    list.pushHead("test");
    EXPECT_EQ(list.getHead()->data, "test");
    EXPECT_EQ(list.getTail()->data, "test");
    EXPECT_EQ(list.getHead(), list.getTail());
}

// Тест добавления в конец
TEST_F(DubleListTest, PushTailTest) {
    list.pushTail("test");
    EXPECT_EQ(list.getHead()->data, "test");
    EXPECT_EQ(list.getTail()->data, "test");
    EXPECT_EQ(list.getHead(), list.getTail());
}

// Тест множественного добавления
TEST_F(DubleListTest, MultiplePushTest) {
    list.pushHead("1");
    list.pushTail("2");
    list.pushHead("0");
    EXPECT_EQ(list.getHead()->data, "0");
    EXPECT_EQ(list.getTail()->data, "2");
    EXPECT_EQ(list.getHead()->next->data, "1");
}

// Тест удаления из начала
TEST_F(DubleListTest, PopHeadTest) {
    list.pushHead("1");
    list.pushHead("0");
    list.popHead();
    EXPECT_EQ(list.getHead()->data, "1");
    EXPECT_EQ(list.getTail()->data, "1");
}

// Тест удаления из начала пустого списка
TEST_F(DubleListTest, EmptyPopHeadTest) {
    testing::internal::CaptureStdout();
    list.popHead();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Список пуст!\n");
}

// Тест удаления из конца
TEST_F(DubleListTest, PopTailTest) {
    list.pushTail("1");
    list.pushTail("2");
    list.popTail();
    EXPECT_EQ(list.getHead()->data, "1");
    EXPECT_EQ(list.getTail()->data, "1");
}

// Тест удаления из конца пустого списка
TEST_F(DubleListTest, EmptyPopTailTest) {
    testing::internal::CaptureStdout();
    list.popTail();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Список пуст!\n");
}

// Тест удаления по значению
TEST_F(DubleListTest, PopValueTest) {
    list.pushTail("1");
    list.pushTail("2");
    list.pushTail("3");
    EXPECT_TRUE(list.popValue("2"));
    EXPECT_EQ(list.getHead()->next->data, "3");
}

// Тест удаления несуществующего значения
TEST_F(DubleListTest, PopValueNotFoundTest) {
    list.pushTail("1");
    list.pushTail("2");
    testing::internal::CaptureStdout();
    EXPECT_FALSE(list.popValue("3"));
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
}

// Тест поиска существующего значения
TEST_F(DubleListTest, SearchExistingTest) {
    list.pushTail("1");
    list.pushTail("2");
    list.pushTail("3");
    EXPECT_TRUE(list.search("2"));
}

// Тест поиска несуществующего значения
TEST_F(DubleListTest, SearchNonExistingTest) {
    list.pushTail("1");
    list.pushTail("2");
    EXPECT_FALSE(list.search("3"));
}

// Тест вывода пустого списка
TEST_F(DubleListTest, DisplayEmptyTest) {
    testing::internal::CaptureStdout();
    list.display();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Список пуст!\n");
}

// Тест вывода списка
TEST_F(DubleListTest, DisplayTest) {
    list.pushTail("1");
    list.pushTail("2");
    list.pushTail("3");
    testing::internal::CaptureStdout();
    list.display();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "1 2 3 \n");
}

// Тест на утечки памяти
TEST_F(DubleListTest, MemoryLeakTest) {
    DubleList* dynamicList = new DubleList();
    dynamicList->pushTail("1");
    dynamicList->pushTail("2");
    dynamicList->pushTail("3");
    delete dynamicList;
    SUCCEED();
}
