#pragma once
#include <iostream>
#include <string>
#include "Nodes.h"

using namespace std;

class Queue {
private:
    Node1* head;
    Node1* tail;

public:
    Queue() {
        head = nullptr;
        tail = nullptr;
    }

    ~Queue() {
        while (head != nullptr) {
            Node1* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    // Accessor methods
    Node1* getHead() const { return head; }
    Node1* getTail() const { return tail; }

    // Сложность: O(1)
    void push(string value) {
        // создаем новый узел с заданным значением и указателем на следующий элемент, равным nullptr
        Node1* node = new Node1(value);
        
        // проверяем, пуста ли очередь
        if (head == nullptr) {
            // если пустая, то и голова, и хвост очереди теперь указывают на новый узел
            head = node;
            tail = node;
        } 
        else {
            // если не пустая, то добавляем новый узел в конец очереди
            tail->next = node; // устанавливаем указатель текущего хвоста на новый узел
            tail = node; // обновляем указатель хвоста
        }
    }

    // Сложность: O(1)
    void pop() {
        // проверяем, пуста ли очередь
        if (head == nullptr) {
            cout << "Очередь пуста!" << endl;
        } 
        else {
            Node1* temp = head; // временно сохраняем указатель на текущую голову (первый элемент)
            head = head->next; // перемещаем указатель головы на следующий элемент в очереди
            delete temp; // освобождаем память, занятую удаляемым элементом

            // если после удаления очередь стала пустой
            if (head == nullptr) {
                tail = nullptr; // устанавливаем хвост также равным nullptr
            }
        }
    }

    // Сложность: O(n)
    void display() {
        // проверяем, пуста ли очередь
        if (head == nullptr) {
            cout << "Очередь пуста!" << endl;
        }
        else {
            Node1* current = head; // для итерации по элементам очереди

            // пока не достигнут конец очереди
            while (current != nullptr) {
                cout << current->data << " ";
                current = current->next; // переходим к следующему элементу
            }
            cout << endl;
        }
    }
};
