#include <gtest/gtest.h>
#include "containers/HashTable.h"
#include <string>

using namespace std;

class HashTableTest : public ::testing::Test {
protected:
    HashTable table;
};

// тест пустой таблицы
TEST_F(HashTableTest, EmptyTableTest) {
    EXPECT_EQ(table.getSize(), 10); // размер таблицы
    for (int i = 0; i < table.getSize(); i++) {
        EXPECT_EQ(table.getTable()[i], nullptr);
    }
}

// тест вставки одного элемента
TEST_F(HashTableTest, SingleInsertTest) {
    table.insert("key1", "value1");
    EXPECT_EQ(table.get("key1"), "value1");
}

// тест обновления значения по существующему ключу
TEST_F(HashTableTest, UpdateValueTest) {
    table.insert("key1", "value1");
    table.insert("key1", "value2");
    EXPECT_EQ(table.get("key1"), "value2");
}

// тест вставки нескольких элементов
TEST_F(HashTableTest, MultipleInsertTest) {
    table.insert("key1", "value1");
    table.insert("key2", "value2");
    table.insert("key3", "value3");
    EXPECT_EQ(table.get("key1"), "value1");
    EXPECT_EQ(table.get("key2"), "value2");
    EXPECT_EQ(table.get("key3"), "value3");
}

// тест коллизий
TEST_F(HashTableTest, CollisionTest) {
    // создаем таблицу размером 1, чтобы гарантировать коллизии
    HashTable smallTable(1);
    smallTable.insert("key1", "value1");
    smallTable.insert("key2", "value2");
    EXPECT_EQ(smallTable.get("key1"), "value1");
    EXPECT_EQ(smallTable.get("key2"), "value2");
}

// тест получения несуществующего ключа
TEST_F(HashTableTest, GetNonExistingKeyTest) {
    EXPECT_EQ(table.get("nonexistent"), "Ключ не найден!");
}

// тест удаления элемента
TEST_F(HashTableTest, RemoveTest) {
    table.insert("key1", "value1");
    table.remove("key1");
    EXPECT_EQ(table.get("key1"), "Ключ не найден!");
}

// тест удаления первого элемента в цепочке
TEST_F(HashTableTest, RemoveFirstInChainTest) {
    HashTable smallTable(1);
    smallTable.insert("key1", "value1");
    smallTable.insert("key2", "value2");
    smallTable.remove("key1");
    EXPECT_EQ(smallTable.get("key1"), "Ключ не найден!");
    EXPECT_EQ(smallTable.get("key2"), "value2");
}

// тест удаления последнего элемента в цепочке
TEST_F(HashTableTest, RemoveLastInChainTest) {
    HashTable smallTable(1);
    smallTable.insert("key1", "value1");
    smallTable.insert("key2", "value2");
    smallTable.remove("key2");
    EXPECT_EQ(smallTable.get("key1"), "value1");
    EXPECT_EQ(smallTable.get("key2"), "Ключ не найден!");
}

// тест удаления несуществующего ключа
TEST_F(HashTableTest, RemoveNonExistingKeyTest) {
    table.remove("nonexistent");
    EXPECT_EQ(table.get("nonexistent"), "Ключ не найден!");
}

// тест вывода пустой таблицы
TEST_F(HashTableTest, DisplayEmptyTest) {
    testing::internal::CaptureStdout();
    table.display();
    string output = testing::internal::GetCapturedStdout();
    string expected;
    for (int i = 0; i < 10; i++) {
        expected += "Bucket " + to_string(i) + ": \n";
    }
    EXPECT_EQ(output, expected);
}

// тест вывода таблицы с данными
TEST_F(HashTableTest, DisplayTest) {
    table.insert("key1", "value1");
    table.insert("key2", "value2");
    testing::internal::CaptureStdout();
    table.display();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("key1"), string::npos);
    EXPECT_NE(output.find("value1"), string::npos);
    EXPECT_NE(output.find("key2"), string::npos);
    EXPECT_NE(output.find("value2"), string::npos);
}

// тест на утечки памяти
TEST_F(HashTableTest, MemoryLeakTest) {
    HashTable* dynamicTable = new HashTable(5);
    dynamicTable->insert("key1", "value1");
    dynamicTable->insert("key2", "value2");
    dynamicTable->insert("key3", "value3");
    delete dynamicTable;
    SUCCEED();
}
