#include <gtest/gtest.h>
#include "containers/List.h"
#include <string>

using namespace std;

class ListTest : public ::testing::Test {
protected:
    List list;
};

// тест пустого списка
TEST_F(ListTest, EmptyListTest) {
    EXPECT_EQ(list.getHead(), nullptr);
    EXPECT_EQ(list.getTail(), nullptr);
}

// тест добавления в список
TEST_F(ListTest, PushHeadTest) {
    list.pushHead("1");
    EXPECT_NE(list.getHead(), nullptr);
    EXPECT_EQ(list.getHead()->data, "1");
    EXPECT_EQ(list.getTail()->data, "1");
}

// тест добавления в конец
TEST_F(ListTest, PushTailTest) {
    list.pushTail("1");
    EXPECT_NE(list.getTail(), nullptr);
    EXPECT_EQ(list.getTail()->data, "1");
    EXPECT_EQ(list.getHead()->data, "1");
}

// тест множественного добавления
TEST_F(ListTest, MultiplePushTest) {
    list.pushHead("1");
    list.pushHead("2");
    list.pushTail("3");
    EXPECT_EQ(list.getHead()->data, "2");
    EXPECT_EQ(list.getHead()->next->data, "1");
    EXPECT_EQ(list.getTail()->data, "3");
}

// тест удаления
TEST_F(ListTest, PopHeadTest) {
    list.pushHead("1");
    list.pushHead("2");
    list.popHead();
    EXPECT_EQ(list.getHead()->data, "1");
    EXPECT_EQ(list.getTail()->data, "1");
}

// тест удаления головы
TEST_F(ListTest, EmptyPopHeadTest) {
    testing::internal::CaptureStdout();
    list.popHead();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Список пуст!\n");
}

// тест удаления хвоста
TEST_F(ListTest, PopTailTest) {
    list.pushHead("1");
    list.pushHead("2");
    list.pushHead("3");
    list.popTail();
    EXPECT_EQ(list.getTail()->data, "2");
    EXPECT_EQ(list.getHead()->data, "3");
}

// тест удаления хвоста
TEST_F(ListTest, EmptyPopTailTest) {
    testing::internal::CaptureStdout();
    list.popTail();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Список пуст!\n");
}

// тест удаления значения
TEST_F(ListTest, PopValueTest) {
    list.pushHead("1");
    list.pushHead("2");
    list.pushHead("3");
    EXPECT_TRUE(list.popValue("2"));
    EXPECT_EQ(list.getHead()->data, "3");
    EXPECT_EQ(list.getTail()->data, "1");
}

// тест удаления значения
TEST_F(ListTest, PopValueNotFoundTest) {
    list.pushHead("1");
    list.pushHead("2");
    testing::internal::CaptureStdout();
    EXPECT_FALSE(list.popValue("3"));
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Элемент не найден!\n");
}

// тест поиска
TEST_F(ListTest, SearchTest) {
    list.pushHead("1");
    list.pushHead("2");
    list.pushHead("3");
    EXPECT_TRUE(list.search("2"));
    EXPECT_FALSE(list.search("4"));
}

// тест вывода
TEST_F(ListTest, DisplayEmptyTest) {
    testing::internal::CaptureStdout();
    list.display();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Список пуст!\n");
}

// тест вывода
TEST_F(ListTest, DisplayTest) {
    list.pushHead("3");
    list.pushHead("2");
    list.pushHead("1");
    testing::internal::CaptureStdout();
    list.display();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "1 2 3 \n");
}

// тест деструктор
TEST_F(ListTest, DestructorTest) {
    List* dynamicList = new List();
    dynamicList->pushHead("1");
    dynamicList->pushHead("2");
    dynamicList->pushHead("3");
    delete dynamicList;
    SUCCEED();
}
