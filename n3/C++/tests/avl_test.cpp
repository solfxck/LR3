#include <gtest/gtest.h>
#include "containers/AVL.h"
#include <string>

using namespace std;

class AVLTest : public ::testing::Test {
protected:
    AVL tree;
};

// тест пустого дерева
TEST_F(AVLTest, EmptyTreeTest) {
    EXPECT_EQ(tree.getRoot(), nullptr); 
    testing::internal::CaptureStdout();
    tree.display();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "\n"); // ожидается вывод пустой строки
}

// тест вставки одного элемента
TEST_F(AVLTest, SingleInsertTest) {
    tree.insert(10);
    EXPECT_NE(tree.getRoot(), nullptr); // ожидается, что корень не равен nullptr
    EXPECT_EQ(tree.getRoot()->key, 10); // ожидается, что ключ корня равен 10
    EXPECT_EQ(tree.getRoot()->height, 1); // ожидается, что высота корня равна 1
}

// тест балансировки при вставке (левый-левый случай)
TEST_F(AVLTest, LeftLeftRotationTest) {
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);
    // после балансировки 20 должен быть корнем
    EXPECT_EQ(tree.getRoot()->key, 20);
    EXPECT_EQ(tree.getRoot()->left->key, 10);
    EXPECT_EQ(tree.getRoot()->right->key, 30);
}

// тест балансировки при вставке (правый-правый случай)
TEST_F(AVLTest, RightRightRotationTest) {
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    // после балансировки 20 должен быть корнем
    EXPECT_EQ(tree.getRoot()->key, 20);
    EXPECT_EQ(tree.getRoot()->left->key, 10);
    EXPECT_EQ(tree.getRoot()->right->key, 30);
}

// тест балансировки при вставке (левый-правый случай)
TEST_F(AVLTest, LeftRightRotationTest) {
    tree.insert(30);
    tree.insert(10);
    tree.insert(20);
    // после балансировки 20 должен быть корнем
    EXPECT_EQ(tree.getRoot()->key, 20);
    EXPECT_EQ(tree.getRoot()->left->key, 10);
    EXPECT_EQ(tree.getRoot()->right->key, 30);
}

// тест балансировки при вставке (правый-левый случай)
TEST_F(AVLTest, RightLeftRotationTest) {
    tree.insert(10);
    tree.insert(30);
    tree.insert(20);
    // после балансировки 20 должен быть корнем
    EXPECT_EQ(tree.getRoot()->key, 20);
    EXPECT_EQ(tree.getRoot()->left->key, 10);
    EXPECT_EQ(tree.getRoot()->right->key, 30);
}

// тест поиска существующего элемента
TEST_F(AVLTest, SearchExistingTest) {
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    EXPECT_TRUE(tree.search(20));
}

// тест поиска несуществующего элемента
TEST_F(AVLTest, SearchNonExistingTest) {
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    EXPECT_FALSE(tree.search(40));
}

// тест удаления листа
TEST_F(AVLTest, DeleteLeafTest) {
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.remove(10);
    EXPECT_FALSE(tree.search(10)); // ожидается, что узел с ключом 10 удален
    EXPECT_EQ(tree.getRoot()->key, 20); // ожидается, что ключ корня равен 20
    EXPECT_EQ(tree.getRoot()->right->key, 30); // ожидается, что ключ правого потомка корня равен 30
    EXPECT_EQ(tree.getRoot()->left, nullptr); // ожидается, что левый потомок корня равен nullptr
}

// тест удаления узла с одним потомком
TEST_F(AVLTest, DeleteNodeWithOneChildTest) {
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(40);
    tree.remove(30);
    EXPECT_FALSE(tree.search(30));
    EXPECT_EQ(tree.getRoot()->key, 20);
    EXPECT_EQ(tree.getRoot()->right->key, 40);
}

// тест удаления узла с двумя потомками
TEST_F(AVLTest, DeleteNodeWithTwoChildrenTest) {
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(25);
    tree.insert(40);
    tree.remove(30);
    EXPECT_FALSE(tree.search(30));
    EXPECT_EQ(tree.getRoot()->key, 20);
    EXPECT_EQ(tree.getRoot()->right->key, 40);
    EXPECT_EQ(tree.getRoot()->right->left->key, 25);
}

// тест вывода дерева
TEST_F(AVLTest, DisplayTest) {
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    testing::internal::CaptureStdout();
    tree.display();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "20 10 30 \n");
}

// тест на утечки памяти
TEST_F(AVLTest, MemoryLeakTest) {
    AVL* dynamicTree = new AVL();
    dynamicTree->insert(20);
    dynamicTree->insert(10);
    dynamicTree->insert(30);
    dynamicTree->insert(25);
    dynamicTree->insert(40);
    delete dynamicTree;
    SUCCEED();
}
