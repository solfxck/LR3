#pragma once
#include <iostream>
#include <string>
#include "Nodes.h"

using namespace std;

class Queue {
private:
    Node1* head;
    Node1* tail;
    int count;

public:
    Queue() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    ~Queue() {
        while (head != nullptr) {
            Node1* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

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
        count++;
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
            count--;
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

    // сериализация в бинарный файл
    void serializeBin(const string& filename) {
        ofstream file(filename, ios::binary);
        if (file.is_open()) {
            int size = count;
            file.write(reinterpret_cast<char*>(&size), sizeof(size));
            Node1* current = head;
            while (current != nullptr) {
                int strLen = current->data.length();
                file.write(reinterpret_cast<char*>(&strLen), sizeof(strLen));
                file.write(current->data.c_str(), strLen);
                current = current->next;
            }
            file.close();
        }
    }

    // десериализация из бинарного файла
    void deserializeBin(const string& filename) {
        ifstream file(filename, ios::binary);
        if (file.is_open()) {
            while (head != nullptr) {
                Node1* temp = head;
                head = head->next;
                delete temp;
            }
            tail = nullptr;
            count = 0;

            int size;
            file.read(reinterpret_cast<char*>(&size), sizeof(size));
            for (int i = 0; i < size; i++) {
                int strLen;
                file.read(reinterpret_cast<char*>(&strLen), sizeof(strLen));
                char* buffer = new char[strLen + 1];
                file.read(buffer, strLen);
                buffer[strLen] = '\0';
                push(string(buffer));
                delete[] buffer;
            }
            file.close();
        }
    }
};
