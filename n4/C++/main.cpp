#include <iostream>
#include <fstream>
#include <string>
#include "Array.h"
#include "AVL.h"
#include "DubleList.h"
#include "HashTable.h"
#include "List.h"
#include "Queue.h"
#include "Stack.h"
#include "Nodes.h"

using namespace std;

void processCommand(const string& command, Queue& queue, Stack& stack, Array& array, List& list, DubleList& dubleList, HashTable& hashTable, AVL& avl) {
    string key, value;
    int intKey;
    if (command == "EXIT") {
        return;
    }
    else if (command.at(0) == 'Q') { // команды для очереди
        if (command == "QPUSH") {
            cin >> value;
            queue.push(value);
        }
        else if (command == "QPOP") {
            queue.pop();
        }
        else if (command == "QPRINT") {
            queue.display();
        }
        else if (command == "QSAVE") {
            cin >> value; // filename
            queue.serializeBin(value);
        }
        else if (command == "QLOAD") {
            cin >> value; // filename
            queue.deserializeBin(value);
        }
        else {
            cout << "Неверная команда." << endl;
        }
    }
    else if (command.at(0) == 'S') { // команды для стека
        if (command == "SPUSH") {
            cin >> value;
            stack.push(value);
        }
        else if (command == "SPOP") {
            stack.pop();
        }
        else if (command == "SPRINT") {
            stack.display();
        }
        else if (command == "SSAVE") {
            cin >> value; // filename
            stack.serialize(value);
        }
        else if (command == "SLOAD") {
            cin >> value; // filename
            stack.deserialize(value);
        }
        else {
            cout << "Неверная команда." << endl;
        }
    }
    else if (command.at(0) == 'M') { // команды для массива
        if (command == "MPUSH_T") { // добавление в конец
            cin >> value;
            array.pushEnd(value);
        }
        else if (command == "MPUSH_ID") { // добавление по индексу
            int index;
            cin >> index >> value;
            array.push(index, value);
        }
        else if (command == "MGET") { // получение по индексу
            int index;
            cin >> index;
            cout << array.get(index) << endl;
        }
        else if (command == "MPOP_ID") { // удаление по индексу
            int index;
            cin >> index;
            array.pop(index);
        }
        else if (command == "MREP") { // замена по индексу
            int index;
            cin >> index >> value;
            array.replace(index, value);
        }
        else if (command == "MLEN") { // длина массива
            cout << array.length() << endl;
        }
        else if (command == "MPRINT") { // вывод массива
            array.display();
        }
        else if (command == "MSAVE") {
            cin >> value; // filename
            array.serialize(value);
        }
        else if (command == "MLOAD") {
            cin >> value; // filename
            array.deserialize(value);
        }
        else {
            cout << "Неверная команда." << endl;
        }
    }
    else if (command.at(0) == 'L') { // Команды для списка
        if (command == "LPUSH_H") { // Добавление в начало
            cin >> value;
            list.pushHead(value);
        }
        else if (command == "LPUSH_T") { // Добавление в конец
            cin >> value;
            list.pushTail(value);
        }
        else if (command == "LPOP_H") { // Удаление с начала
            list.popHead();
        }
        else if (command == "LPOP_T") { // Удаление с конца
            list.popTail();
        }
        else if (command == "LPOP_V") { // Удаление по значению
            cin >> value;
            list.popValue(value);
        }
        else if (command == "LSEARCH") { // Поиск по значению
            cin >> value;
            if (list.search(value)) {
                cout << "Элемент найден" << endl;
            }
            else {
                cout << "Элемент не найден" << endl;
            }
        }
        else if (command == "LPRINT") { // Вывод списка
            list.display();
        }
        else if (command == "LSAVE") {
            cin >> value; // filename
            list.serializeBin(value);
        }
        else if (command == "LLOAD") {
            cin >> value; // filename
            list.deserializeBin(value);
        }
        else {
            cout << "Неверная команда." << endl;
        }
    }
    else if (command.at(0) == 'D') { // Команды для двусвязного списка
        if (command == "DPUSH_H") { // Добавление в начало
            cin >> value;
            dubleList.pushHead(value);
        }
        else if (command == "DPUSH_T") { // Добавление в конец
            cin >> value;
            dubleList.pushTail(value);
        }
        else if (command == "DPOP_H") { // Удаление с начала
            dubleList.popHead();
        }
        else if (command == "DPOP_T") { // Удаление с конца
            dubleList.popTail();
        }
        else if (command == "DPOP_V") { // Удаление по значению
            cin >> value;
            dubleList.popValue(value);
        }
        else if (command == "DSEARCH") { // Поиск по значению
            cin >> value;
            if (dubleList.search(value)) {
                cout << "Элемент найден" << endl;
            }
            else {
                cout << "Элемент не найден" << endl;
            }
        }
        else if (command == "DPRINT") { // Вывод списка
            dubleList.display();
        }
        else if (command == "DSAVE") {
            cin >> value; // filename
            dubleList.serializeBin(value);
        }
        else if (command == "DLOAD") {
            cin >> value; // filename
            dubleList.deserializeBin(value);
        }
        else {
            cout << "Неверная команда." << endl;
        }
    }
    else if (command.at(0) == 'H') { // Команды для хеш-таблицы
        if (command == "HPUSH") { // Добавление или обновление элемента
            cin >> key >> value;
            hashTable.insert(key, value);
        }
        else if (command == "HGET") { // Получение элемента
            cin >> key;
            cout << hashTable.get(key) << endl;
        }
        else if (command == "HPOP") { // Удаление элемента
            cin >> key;
            hashTable.remove(key);
        }
        else if (command == "HPRINT") { // Вывод хеш-таблицы
            hashTable.display();
        }
        else if (command == "HSAVE") {
            cin >> value; // filename
            hashTable.serializeBin(value);
        }
        else if (command == "HLOAD") {
            cin >> value; // filename
            hashTable.deserializeBin(value);
        }
        else {
            cout << "Неверная команда." << endl;
        }
    }
    else if (command.at(0) == 'T') { // Команды для АВЛ-дерева
        if (command == "TPUSH") { // Добавление элемента
            cin >> intKey;
            avl.insert(intKey);
        }
        else if (command == "TPOP") { // Удаление элемента
            cin >> intKey;
            avl.remove(intKey);
        }
        else if (command == "TSEARCH") { // Поиск элемента
            cin >> intKey;
            if (avl.search(intKey)) {
                cout << "Элемент найден" << endl;
            }
            else {
                cout << "Элемент не найден" << endl;
            }
        }
        else if (command == "TPRINT") { // Вывод дерева
            avl.display();
        }
        else if (command == "TSAVE") {
            cin >> value; // filename
            avl.serializeBin(value);
        }
        else if (command == "TLOAD") {
            cin >> value; // filename
            avl.deserializeBin(value);
        }
        else {
            cout << "Неверная команда." << endl;
        }
    }
    else {
        cout << "Неверная команда." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    Queue queue;
    Stack stack;
    Array array;
    List list;
    DubleList dubleList;
    HashTable hashTable;
    AVL avl;

    string command;

    while (true) {
        cout << "> ";
        cin >> command;
        if (command == "EXIT") {
            break;
        }
        processCommand(command, queue, stack, array, list, dubleList, hashTable, avl);
    }

    return 0;
}