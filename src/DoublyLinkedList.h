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

// ===================== Implementation =====================

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(new Node()), tail(new Node()), length(0)
{
    head->next = tail;
    tail->prev = head;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    // delete all real nodes
    Node *curr = head->next;
    while (curr != tail)
    {
        Node *tmp = curr;
        curr = curr->next;
        delete tmp;
    }
    delete head;
    delete tail;
}

template <typename T>
void DoublyLinkedList<T>::insertAtHead(T data)
{
    Node *first = head->next;
    Node *node = new Node(data, head, first);
    head->next = node;
    first->prev = node;
    ++length;
}

template <typename T>
void DoublyLinkedList<T>::insertAtTail(T data)
{
    Node *last = tail->prev;
    Node *node = new Node(data, last, tail);
    last->next = node;
    tail->prev = node;
    ++length;
}

template <typename T>
void DoublyLinkedList<T>::insertAt(int index, T data)
{
    if (index < 0 || index > length)
        throw std::out_of_range("insertAt: index out of range");

    // find node currently at position index (or tail if index == length)
    Node *pos;
    if (index <= length / 2)
    {
        pos = head->next;
        for (int i = 0; i < index; ++i)
            pos = pos->next;
    }
    else
    {
        pos = tail;
        for (int i = length; i > index; --i)
            pos = pos->prev;
    }

    // insert before pos
    Node *prev = pos->prev;
    Node *node = new Node(data, prev, pos);
    prev->next = node;
    pos->prev = node;
    ++length;
}

template <typename T>
void DoublyLinkedList<T>::deleteAt(int index)
{
    if (index < 0 || index >= length)
        throw std::out_of_range("deleteAt: index out of range");

    Node *pos;
    if (index < length / 2)
    {
        pos = head->next;
        for (int i = 0; i < index; ++i)
            pos = pos->next;
    }
    else
    {
        pos = tail->prev;
        for (int i = length - 1; i > index; --i)
            pos = pos->prev;
    }

    Node *prev = pos->prev;
    Node *next = pos->next;
    prev->next = next;
    next->prev = prev;
    delete pos;
    --length;
}

template <typename T>
T &DoublyLinkedList<T>::get(int index) const
{
    if (index < 0 || index >= length)
        throw std::out_of_range("get: index out of range");

    Node *pos;
    if (index < length / 2)
    {
        pos = head->next;
        for (int i = 0; i < index; ++i)
            pos = pos->next;
    }
    else
    {
        pos = tail->prev;
        for (int i = length - 1; i > index; --i)
            pos = pos->prev;
    }

    return pos->data;
}

template <typename T>
int DoublyLinkedList<T>::indexOf(T item) const
{
    int idx = 0;
    for (Node *curr = head->next; curr != tail; curr = curr->next, ++idx)
    {
        if (curr->data == item)
            return idx;
    }
    return -1;
}

template <typename T>
bool DoublyLinkedList<T>::contains(T item) const
{
    return indexOf(item) != -1;
}

template <typename T>
int DoublyLinkedList<T>::size() const
{
    return length;
}

template <typename T>
void DoublyLinkedList<T>::reverse()
{
    if (length < 2) return;
    // Reverse links for all real nodes
    Node *curr = head->next;
    while (curr != tail)
    {
        Node *next = curr->next;
        // swap next/prev
        Node *tmp = curr->next;
        curr->next = curr->prev;
        curr->prev = tmp;
        curr = next;
    }

    // Fix sentinel connections by swapping their next/prev appropriately
    Node *oldFirst = head->next; // this actually points to previous first, but we will rewire below
    Node *oldLast = tail->prev;  // this actually points to previous last, but we will rewire below

    // Swap head<->tail adjacency around inner list
    Node *newFirst = oldLast; // after reversal, last becomes first
    Node *newLast = oldFirst; // after reversal, first becomes last

    // Connect head to newFirst, and tail to newLast
    head->next = newFirst;
    newFirst->prev = head;
    tail->prev = newLast;
    newLast->next = tail;
}

template <typename T>
string DoublyLinkedList<T>::toString(string (*convert2str)(T &)) const
{
    std::ostringstream ss;
    if (convert2str)
    {
        for (Node *curr = head->next; curr != tail; curr = curr->next)
        {
            ss << convert2str(curr->data);
        }
    }
    else
    {
        for (Node *curr = head->next; curr != tail; curr = curr->next)
        {
            ss << curr->data;
        }
    }
    return ss.str();
}
#endif // __DOUBLY_LINKED_LIST_H__
