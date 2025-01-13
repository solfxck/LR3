#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include "Nodes.h"

using namespace std;

class HashTable {
private:
    NodeHT** table; // массив указателей на узлы хеш-таблицы
    int size; // размер хеш-таблицы
    int count; // количество элементов в хеш-таблице

    // функция для вычисления хеш-значения
    int hash_function(const string& str) {
        int hash = 0;  // инициализация хеш-значения
        for (char c : str) {
            hash += c;  // суммирование ASCII-кодов символов строки
        }
        return hash % size;  // возврат хеш-значения по модулю размера таблицы
    }

public:
    // Accessor methods
    NodeHT** getTable() const { return table; }
    int getSize() const { return size; }

    // конструктор класса HashTable
    HashTable(int initialSize = 10) {
        size = initialSize;  // инициализация размера таблицы
        count = 0;  // инициализация счетчика элементов
        table = new NodeHT*[size];  // выделение памяти под массив указателей на узлы
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;  // инициализация каждого указателя как nullptr
        }
    }

    ~HashTable() {
        for (int i = 0; i < size; i++) {
            NodeHT* current = table[i];
            while (current != nullptr) {
                NodeHT* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    // Сложность: O(1) (в худшем (если возникают коллизии) - O(n) (n - количество элементов в связанном списке))
    void insert(const string& key, const string& value) {
        int index = hash_function(key);  // вычисление индекса для вставки
        NodeHT* current = table[index];  // получение текущего узла по индексу

        while (current != nullptr) {  // проход по связанному списку
            if (current->key == key) {  // если ключ уже существует
                current->value = value;  // обновление значения
                return;  // выход из функции
            }
            current = current->next;  // переход к следующему узлу
        }

        NodeHT* newNode = new NodeHT(key, value);  // создание нового узла
        newNode->next = table[index];  // новый узел указывает на текущий узел по индексу
        table[index] = newNode;  // новый узел становится текущим узлом по индексу
        count++;  // увеличение счетчика элементов

        // объяснение решения коллизий:
        // в случае коллизии (двух ключей с одинаковым хеш-значением)
        // новый узел добавляется в начало связанного списка по этому индексу
    }

    // Сложность: O(1) (в худшем (если возникают коллизии) - O(n) (n - количество элементов в связанном списке))
    string get(const string& key) {
        int index = hash_function(key);  // вычисление индекса для поиска
        NodeHT* current = table[index];  // получение текущего узла по индексу

        while (current != nullptr) {  // проход по связанному списку
            if (current->key == key) {  // если ключ найден
                return current->value;  // возврат значения
            }
            current = current->next;  // переход к следующему узлу
        }

        return "Ключ не найден!";  // если ключ не найден, возврат сообщения
    }

    // Сложность: O(1) (в худшем (если возникают коллизии) - O(n) (n - количество элементов в связанном списке))
    void remove(const string& key) {
        int index = hash_function(key);  // вычисление индекса для удаления
        NodeHT* current = table[index];  // получение текущего узла по индексу
        NodeHT* prev = nullptr;  // указатель на предыдущий узел

        while (current != nullptr) {  // проход по связанному списку
            if (current->key == key) {  // если ключ найден
                if (prev == nullptr) {  // если это первый узел в списке
                    table[index] = current->next;  // следующий узел становится текущим
                } else {
                    prev->next = current->next;  // предыдущий узел указывает на следующий узел
                }
                delete current;  // удаление текущего узла
                count--;  // уменьшение счетчика элементов
                return;  // выход из функции
            }
            prev = current;  // переход к следующему узлу
            current = current->next;
        }
    }

    // Сложность: O(n)
    void display() {
        for (int i = 0; i < size; i++) {  // проход по всем индексам таблицы
            cout << "Bucket " << i << ": ";
            NodeHT* current = table[i];  // получение текущего узла по индексу
            while (current != nullptr) {  // проход по связанному списку
                cout << "(" << current->key << ", " << current->value << ") ";
                current = current->next;  // переход к следующему узлу
            }
            cout << endl;
        }
    }
};
