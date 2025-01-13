#include <gtest/gtest.h>
#include "containers/Queue.h"
#include <string>

using namespace std;

class QueueTest : public ::testing::Test {
protected:
    Queue queue;
};

// тест пустой очереди
TEST_F(QueueTest, EmptyQueueTest) {
    EXPECT_EQ(queue.getHead(), nullptr);
    EXPECT_EQ(queue.getTail(), nullptr);
}

// тест добавления элемента в очередь
TEST_F(QueueTest, PushTest) {
    queue.push("1");
    EXPECT_NE(queue.getHead(), nullptr);
    EXPECT_EQ(queue.getHead()->data, "1");
}

// тест удаления элемента из очереди
TEST_F(QueueTest, PopTest) {
    queue.push("1");
    queue.push("2");
    queue.pop();
    EXPECT_EQ(queue.getHead()->data, "2");
}

// тест попа из пустой очереди
TEST_F(QueueTest, EmptyPopTest) {
    testing::internal::CaptureStdout();
    queue.pop();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Очередь пуста!\n");
}
