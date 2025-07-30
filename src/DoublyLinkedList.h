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
        const DoublyLinkedList<T> *list;

    public:
        Iterator(Node *node, const DoublyLinkedList<T> *list) : current(node), list(list) {}
        // Iterator(Node *node) : current(node) {}

        T &operator*() const
        {
            if(list->length == 0) {throw cursor_error(); }
            return current->data;
        }

        Iterator &operator++()
        {
            if (list->length == 0) { throw cursor_error(); }
            if (current == list->tail /*|| current->next == list->tail*/) { throw cursor_error(); } // Fix: check if at end
            current = current->next;
            return *this;
        }

        Iterator &operator--()
        {
            if(list->length == 0) {throw cursor_error(); }
            if(current->prev == list->head||current == list->head){throw cursor_error(); } 
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
        return Iterator(head->next, this);
    }

    Iterator end() const
    {
        return Iterator(tail, this);
    }
};
#endif // __DOUBLY_LINKED_LIST_H__
