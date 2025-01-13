#pragma once
#include <iostream>
#include <string>
#include "Nodes.h"

using namespace std;

class Stack {
private:
    Node1* top;

public:
    Stack() {
        top = nullptr;
    }

    ~Stack() {
        while (top != nullptr) {
            Node1* temp = top;
            top = top->next;
            delete temp;
        }
    }

    // Accessor method
    Node1* getTop() const { return top; }

    // Сложность: O(1)
    void push(string value) {
        // создаем новый узел {значение, полученное на входе; указатель на текущую вершину стека}
        Node1* node = new Node1(value); // устанавливаем новый узел поверх стека
        node->next = top;
        top = node; // переносим указатель вершины стека (top) на только что созданный узел
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
};
