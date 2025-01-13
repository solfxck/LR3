#pragma once
#include <string>

using namespace std;

// Queue, Stack, and List
struct Node1 {
    string data;
    Node1* next;
    Node1(const string& value) : data(value), next(nullptr) {}
};

// DubleList
struct Node {
    string data;
    Node* next;
    Node* prev;
    Node(const string& value, Node* nextNode = nullptr, Node* prevNode = nullptr)
        : data(value), next(nextNode), prev(prevNode) {}
};

// HashTable
struct NodeHT {
    string key;
    string value;
    NodeHT* next;
    NodeHT(const string& k, const string& v) : key(k), value(v), next(nullptr) {}
};

// AVL
struct NodeAVL {
    int key;
    NodeAVL* left;
    NodeAVL* right;
    int height;
    NodeAVL(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};
