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

    // Сериализация в бинарный файл
    void serialize(const string& filename) {
        ofstream file(filename, ios::binary); // открываем бинарный файл
        if (file.is_open()) { // проверяем, открыт ли файл
            int count = size; // получаем размер массива
            file.write(reinterpret_cast<char*>(&count), sizeof(count)); // записываем размер массива
            for (int i = 0; i < count; i++) { // сериализуем каждый элемент массива
                int strLen = data[i].length(); // получаем длину строки
                file.write(reinterpret_cast<char*>(&strLen), sizeof(strLen)); // записываем длину строки
                file.write(data[i].c_str(), strLen); // записываем строку
            }
            file.close(); // закрываем файл
        }
    }

    // Десериализация из бинарного файла
    void deserialize(const string& filename) { 
        ifstream file(filename, ios::binary); // открываем бинарный файл
        if (file.is_open()) { // проверяем, открыт ли файл
            clear(); // очищаем текущий массив
            int size; // объявляем переменную для хранения размера массива
            file.read(reinterpret_cast<char*>(&size), sizeof(size)); // читаем размер массива
            for (int i = 0; i < size; i++) { // десериализуем каждый элемент массива
                int strLen; // объявляем переменную для хранения длины строки
                file.read(reinterpret_cast<char*>(&strLen), sizeof(strLen)); // читаем длину строки
                char* buffer = new char[strLen + 1]; // выделяем память для строки
                file.read(buffer, strLen); // читаем строку
                buffer[strLen] = '\0'; // добавляем завершающий нулевой байт
                pushEnd(string(buffer)); // добавляем строку в конец массива
                delete[] buffer; // освобождаем выделенную память
            }
            file.close(); // закрываем файл
        }
    }

    void clear() {
        size = 0;
    }
};
