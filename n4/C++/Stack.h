#pragma once
#include <iostream>
#include <string>
#include "Nodes.h"

using namespace std;

class Stack {
private:
    Node1* top;
    int count;

public:
    Stack() {
        top = nullptr;
        count = 0;
    }

    ~Stack() {
        while (top != nullptr) {
            Node1* temp = top;
            top = top->next;
            delete temp;
        }
    }

    Node1* getTop() const { return top; }

    // Сложность: O(1)
    void push(string value) {
        // создаем новый узел {значение, полученное на входе; указатель на текущую вершину стека}
        Node1* node = new Node1(value); // устанавливаем новый узел поверх стека
        node->next = top;
        top = node; // переносим указатель вершины стека (top) на только что созданный узел
        count++;
    }

    // Сложность: O(1)
    void pop() {
        // сначала проверяем, пуст ли стек
        if (top == nullptr) {
            cout << "Стек пуст!" << endl;
        } else {
            Node1* temp = top; // сохраняем указатель на текущий верхний элемент стека
            
            // перемещаем указатель вершины стека на следующий элемент
            top = top->next; // убираем верхний элемент
            
            delete temp; // освобождаем память, которая была выделена для удаленного элемента
            count--;
        }
    }

    // Сложность: O(n)
    void display() {
        // проверяем, пуст ли стек
        if (top == nullptr) {
            cout << "Стек пуст!" << endl;
        } else {
            Node1* current = top; // указатель для итерации по элементам стека
            
            // цикл продолжается до тех пор, пока не достигнут конец стека
            while (current != nullptr) {
                cout << current->data << " ";
                
                current = current->next; // передвигаем указатель на следующий элемент
            }
            cout << endl;
        }
    }

    // сериализация в бинарный файл
    void serialize(const string& filename) {
        ofstream file(filename, ios::binary);
        if (file.is_open()) {
            int size = count;
            file.write(reinterpret_cast<char*>(&size), sizeof(size));
            Node1* current = top;
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
    void deserialize(const string& filename) {
        ifstream file(filename, ios::binary);
        if (file.is_open()) {
            clear();
            int size;
            file.read(reinterpret_cast<char*>(&size), sizeof(size));
            string* values = new string[size];
            for (int i = 0; i < size; i++) {
                int strLen;
                file.read(reinterpret_cast<char*>(&strLen), sizeof(strLen));
                char* buffer = new char[strLen + 1];
                file.read(buffer, strLen);
                buffer[strLen] = '\0';
                values[i] = string(buffer);
                delete[] buffer;
            }
            // Добавляем элементы в обратном порядке для сохранения порядка стека
            for (int i = size - 1; i >= 0; i--) {
                push(values[i]);
            }
            delete[] values;
            file.close();
        }
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }
};
