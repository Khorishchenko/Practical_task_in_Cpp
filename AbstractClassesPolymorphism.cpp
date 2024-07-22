#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
#include <iostream>
using namespace std;



// Программа на языке C++ для реализации кэша с использованием абстрактных классов и полиморфизма.
// Класс Node представляет узел двусвязного списка.
// Класс Cache - абстрактный класс с методами set и get.
// Класс LRUCache наследуется от класса Cache и реализует методы set и get для кэша с использованием LRU-алгоритма.
// В функции main создается объект LRUCache и выполняется ввод команд "get" и "set" для работы с кэшем.



struct Node {
    Node* next;
    Node* prev;
    int value;
    int key;
    Node(Node* p, Node* n, int k, int val) : prev(p), next(n), key(k), value(val) {};
    Node(int k, int val) : prev(nullptr), next(nullptr), key(k), value(val) {};
};

class Cache {
protected:
    std::map<int, Node*> mp; //map the key to the node in the linked list
    int cp;  //capacity
    Node* tail; // double linked list tail pointer
    Node* head; // double linked list head pointer
    virtual void set(int, int) = 0; //set function
    virtual int get(int) = 0; //get function
public:
    virtual ~Cache() {
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            delete it->second;
        }
    }
};

class LRUCache : public Cache {
public:
    LRUCache(int capacity) {
        cp = capacity;
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    void set(int key, int value) override {
        if (mp.find(key) != mp.end()) {
            // Update existing node
            Node* node = mp[key];
            node->value = value;
        } else {
            // Create new node
            Node* newNode = new Node(head, head->next, key, value);
            head->next->prev = newNode;
            head->next = newNode;
            mp[key] = newNode;

            // Check and remove oldest node if capacity exceeded
            if (mp.size() > cp) {
                Node* oldest = tail->prev;
                mp.erase(oldest->key);
                tail->prev = oldest->prev;
                oldest->prev->next = tail;
                delete oldest;
            }
        }
    }

    int get(int key) override {
        if (mp.find(key) != mp.end()) {
            Node* node = mp[key];
            // Update node order in the list
            node->prev->next = node->next;
            node->next->prev = node->prev;
            node->next = head->next;
            node->prev = head;
            head->next->prev = node;
            head->next = node;
            return node->value;
        } else {
            return -1;
        }
    }
}; 

int main() {
    int n, capacity, i;
    std::cin >> n >> capacity;
    LRUCache l(capacity);
    for (i = 0; i < n; i++) {
        std::string command;
        std::cin >> command;
        if (command == "get") {
            int key;
            std::cin >> key;
            std::cout << l.get(key) << std::endl;
        } else if (command == "set") {
            int key, value;
            std::cin >> key >> value;
            l.set(key, value);
        }
    }
    return 0;
}