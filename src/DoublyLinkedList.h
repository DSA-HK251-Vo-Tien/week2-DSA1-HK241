#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__

#include "main.h"

template <typename T>
class DoublyLinkedList
{
    // TODO: may provide some attributes
private:
    struct Node
    {
        T data;
        Node *prev;
        Node *next;
        Node() : prev(nullptr), next(nullptr) {}
        Node(const T &val, Node *prev = nullptr, Node *next = nullptr) : data(val), prev(prev), next(next) {}
    };

    Node *head; // Dummy head
    Node *tail; // Dummy tail
    int length;

public:
DoublyLinkedList() : length(0)
{
    head = new Node(); // dummy head
    tail = new Node(); // dummy tail
    head->next = tail;
    tail->prev = head;
}

// TODO implement DoublyLinkedList
~DoublyLinkedList() {
    Node* curr = head;
    while (curr != nullptr) {
        Node* tmp = curr;
        curr = curr->next;
        delete tmp;
    }
}

void insertAtHead(T data) {
    Node* newNode = new Node(data, head, head->next);
    head->next->prev = newNode;
    head->next = newNode;
    length++;
}

void insertAtTail(T data) {
    Node* newNode = new Node(data, tail->prev, tail);
    tail->prev->next = newNode;
    tail->prev = newNode;
    length++;
}

void insertAt(int index, T data) {
    if (index < 0 || index > length) throw::out_of_range("Index is invalid!");
    Node* curr = head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    Node* newNode = new Node(data, curr, curr->next);
    curr->next->prev = newNode;
    curr->next = newNode;
    length++;
}

void deleteAt(int index) {
    if (index < 0 || index >= length) throw::out_of_range("Index is invalid!");
    Node* curr = head->next;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    delete curr;
    length--;
}

T& get(int index) const {
    if (index < 0 || index >= length) throw::out_of_range("Index is invalid!");
    Node* curr = head->next;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr->data;
}

int indexOf(T item) const {
    Node* curr = head->next;
    int index = 0;
    while (curr != tail) {
        if (curr->data == item) return index;
        curr = curr->next;
        index++;
    }
    return -1;
}

bool contains(T item) const {
    return indexOf(item) != -1;
}

int size() const {
    return length;
}

void reverse() {
    Node* curr = head;
    
    while (curr != nullptr) {
        Node* tmp = curr->next;
        curr->next = curr->prev;
        curr->prev = tmp;
        curr = tmp; 
    }

    Node* tmp = head;
    head = tail;
    tail = tmp;
}

string toString(string (*convert2str)(T&) ) const {
    stringstream ss;
    ss << "[";
    Node* curr = head->next;
    while (curr != tail) {
        if (convert2str != nullptr) {
            ss << convert2str(curr->data);
        }
        else ss << curr->data;
        if (curr->next != tail) ss << ", ";
        curr = curr->next;
    }
    ss << "]";
    return ss.str();
}

    class Iterator
    {
    private:
        Node *current;

    public:
        Iterator(Node *node) : current(node) {}

        T &operator*() const
        {
            return current->data;
        }

        Iterator &operator++()
        {
            current = current->next;
            return *this;
        }

        Iterator &operator--()
        {
            current = current->prev;
            return *this;
        }

        bool operator==(const Iterator &other) const
        {
            return current == other.current;
        }

        bool operator!=(const Iterator &other) const
        {
            return current != other.current;
        }
    };

    Iterator begin() const
    {
        return Iterator(head->next);
    }

    Iterator end() const
    {
        return Iterator(tail);
    }
};
#endif // __DOUBLY_LINKED_LIST_H__
