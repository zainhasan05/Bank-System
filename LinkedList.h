#pragma once
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };
    Node* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}
    ~LinkedList() { clear(); }

    void add(const T& data) {
        Node* newNode = new Node(data);
        if (!head) head = newNode;
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
        size++;
    }

    bool remove(const T& data) {
        if (!head) return false;
        if (head->data == data) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }
        Node* current = head;
        while (current->next) {
            if (current->next->data == data) {
                Node* temp = current->next;
                current->next = temp->next;
                delete temp;
                size--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    T* find(const T& key) {
        Node* current = head;
        while (current) {
            if (current->data == key) return &(current->data);
            current = current->next;
        }
        return nullptr;
    }

    int getSize() const { return size; }

    T* getAt(int index) const {
        if (index < 0 || index >= size) return nullptr;
        Node* current = head;
        for (int i = 0; i < index; i++) current = current->next;
        return &(current->data);
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }
};