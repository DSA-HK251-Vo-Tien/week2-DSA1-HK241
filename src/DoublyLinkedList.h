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
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insertAtHead(T data);
    void insertAtTail(T data);
    void insertAt(int index, T data);
    void deleteAt(int index);
    T &get(int index) const;
    int indexOf(T item) const;
    bool contains(T item) const;
    int size() const;
    void reverse();
    string toString(string (*convert2str)(T &) = 0) const;

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

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : length(0) {
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->prev = head;
}

template <typename T>
void DoublyLinkedList<T>::insertAtHead(T data) {
    Node *newNode = new Node(data, head, head->next);
    head->next->prev = newNode;
    head->next = newNode;
    length++;
}

template <typename T>
void DoublyLinkedList<T>::insertAtTail(T data) {
    Node *newNode = new Node(data, tail->prev, tail);
    tail->prev->next = newNode;
    tail->prev = newNode;
    length++;
}

template <typename T>
void DoublyLinkedList<T>::insertAt(int index, T data) {
    if (index < 0 || index > length) {
        throw std::out_of_range("Index out of bounds");
    }
    Node *current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    Node *newNode = new Node(data, current, current->next);
    current->next->prev = newNode;
    current->next = newNode;
    length++;
}

template <typename T>
void DoublyLinkedList<T>::deleteAt(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range.");
    }
    Node *current = head->next;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    length--;
}

template <typename T>
T &DoublyLinkedList<T>::get(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range.");
    }
    Node *current = head->next;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
int DoublyLinkedList<T>::indexOf(T item) const {
    Node *current = head->next;
    for (int i = 0; i < length; i++) {
        if (current->data == item) {
            return i;
        }
        current = current->next;
    }
    return -1;
}

template <typename T>
bool DoublyLinkedList<T>::contains(T item) const {
    return indexOf(item) != -1;
}

template <typename T>
int DoublyLinkedList<T>::size() const {
    return length;
}

template <typename T>
void DoublyLinkedList<T>::reverse() {
    Node *current = head;
    Node *temp = nullptr;

    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    temp = head;
    head = tail;
    tail = temp;
}

template <typename T>
string DoublyLinkedList<T>::toString(string (*convert2str)(T &)) const {
    std::ostringstream oss;
    Node *current = head->next;
    oss << "[";
    while (current != tail) {
        oss << convert2str(current->data);
        if (current->next != tail) {
            oss << ", ";
        }
        current = current->next;
    }
    oss << "]";
    return oss.str();
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node *current = head;
    while (current) {
        Node *nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

#endif // __DOUBLY_LINKED_LIST_H__
