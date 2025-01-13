#pragma once
#include <iostream>
#include <string>
#include "Nodes.h"

using namespace std;

class Array {
private:
    string* data;
    int size;
    int capacity;

public:
    // конструктор класса
    // Сложность: O(1)
    Array() : size(0), capacity(10) {
        data = new string[capacity];  // выделяем память для массива строк
    }

    ~Array() {
        delete[] data;  // освобождаем выделенную память
    }

    // Сложность: O(1)
    void pushEnd(string value) {
        if (size == capacity) {  // проверяем, не переполнен ли массив
            cout << "Массив переполнен!" << endl;
            return;
        }
        data[size++] = value;  // добавляем элемент в конец и увеличиваем размер массива
    }

    // Сложность: O(n)
    void push(int index, string value) {
        if (index < 0 || index > size) {  // проверяем, находится ли индекс в допустимом диапазоне
            cout << "Индекс вне диапазона!" << endl;
            return;
        }
        if (size == capacity) {  // проверяем, не переполнен ли массив
            cout << "Массив переполнен!" << endl;
            return;
        }
        for (int i = size; i > index; i--) {  // сдвигаем элементы вправо, начиная с указанного индекса
            data[i] = data[i - 1];
        }
        data[index] = value;  // вставляем новый элемент по указанному индексу
        size++;  // увеличиваем размер массива
    }

    // Сложность: O(1)
    string get(int index) {
        if (index < 0 || index >= size) {  // проверяем, находится ли индекс в допустимом диапазоне
            cout << "Индекс вне диапазона!" << endl;
            return "";
        }
        return data[index];  // возвращаем элемент по указанному индексу
    }

    // Сложность: O(n)
    void pop(int index) {
        if (index < 0 || index >= size) {  // проверяем, находится ли индекс в допустимом диапазоне
            cout << "Индекс вне диапазона!" << endl;
            return;
        }
        for (int i = index; i < size - 1; i++) {  // сдвигаем элементы влево, начиная с указанного индекса
            data[i] = data[i + 1];
        }
        size--;  // уменьшаем размер массива
    }

    // замена по индексу
    // Сложность: O(1)
    void replace(int index, string value) {
        if (index < 0 || index >= size) {  // проверяем, находится ли индекс в допустимом диапазоне
            cout << "Индекс вне диапазона!" << endl;
            return;
        }
        data[index] = value;  // заменяем элемент по указанному индексу
    }

    // Сложность: O(1)
    int length() {
        return size;  // возвращаем текущий размер массива
    }

    // Сложность: O(n)
    void display() {
        if (size == 0) {  // проверяем, пуст ли массив
            cout << "Массив пуст!" << endl;
            return;
        }
        for (int i = 0; i < size; i++) {  // выводим каждый элемент массива
            cout << data[i] << " ";
        }
        cout << endl;
    }
};
