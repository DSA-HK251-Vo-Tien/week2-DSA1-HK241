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
    DoublyLinkedList(){
        head = new Node();  // dummy head
        tail = new Node();  // dummy tail
        head->next = tail;
        tail->prev = head;
        length = 0;
    }
    ~DoublyLinkedList(){
        Node *current = head;
        while (current != nullptr)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }

    void insertAtHead(T data){
        Node *newNode = new Node(data);

        newNode->next = head->next;
        newNode->prev = head;

        head->next->prev = newNode;
        head->next = newNode;

        length++;    
    }
    void insertAtTail(T data);
    void insertAt(int index, T data);
    void deleteAt(int index);
    T &get(int index) const{
        if (index < 0 || index >= length)
            throw std::out_of_range("Index out of range");

        Node *current = head->next;
        for (int i = 0; i < index; ++i)
        {
            current = current->next;
        }

        return current->data;
    }
    int indexOf(T item) const;
    bool contains(T item) const;
    int size() const{
        return length;
    }
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
#endif // __DOUBLY_LINKED_LIST_H__
