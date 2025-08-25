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
    DoublyLinkedList()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
    ~DoublyLinkedList()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void insertAtHead(T data)
    {
        Node *newNode = new Node(data);
        newNode->next = head->next;
        newNode->prev = head;
        head->next->prev = newNode;
        head->next = newNode;
        length++;
    }
    void insertAtTail(T data)
    {
        Node *newNode = new Node(data);
        newNode->next = tail;
        newNode->prev = tail->prev;
        tail->prev->next = newNode;
        tail->prev = newNode;
        length++;
    }
    void insertAt(int index, T data)
    {
        if (index < 0 || index >= length)
            throw std::out_of_range("Index out ouf range!");

        if (index == 1)
        {
            this->insertAtHead(data);
            return;
        }
        if (index == length)
        {
            this->insertAtTail(data);
            return;
        }

        Node *pos = head->next;
        for (int i = 0; i < index; i++)
            pos = pos->next;

        Node *newNode = new Node(data);
        newNode->next = pos;
        newNode->prev = pos->prev;
        pos->prev->next = newNode;
        pos->prev = newNode;
        length++;
    }
    void deleteAt(int index)
    {
        if (index < 0 || index >= length)
            throw std::out_of_range("Index out of range!");

        Node *pos = head->next;
        for (int i = 0; i < index; i++)
            pos = pos->next;

        pos->next->prev = pos->prev;
        pos->prev->next = pos->next;
        delete pos;
        length--;
    }
    T &get(int index) const
    {
        if (index < 0 || index >= length)
            throw std::out_of_range("Index out of range!");

        Node *pos = head->next;
        for (int i = 0; i < length; i++)
            pos = pos->next;

        return pos->data;
    }
    int indexOf(T item) const
    {
        int index = 0;
        for (Iterator it = this->begin(); it != this->end(); it++, index++)
        {
            if (*it == item)
                return index;
        }
        return -1;
    }
    bool contains(T item) const
    {
        if (this->indexOf(item) != -1)
            return true;

        return false;
    }
    int size() const
    {
        return length;
    }
    void reverse()
    {
        Node *cur = head;
        while (cur != nullptr)
        {
            Node *tmp = cur->next;
            cur->next = cur->prev;
            cur->prev = tmp;
            cur = tmp;
        }
        Node *tempHead = head;
        head = tail;
        tail = tempHead;
    }
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

        Iterator operator++(int)
        {
            Iterator tmp = *this;
            current = current->next;
            return tmp;
        }

        Iterator &operator--()
        {
            current = current->prev;
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator tmp = *this;
            current = current->prev;
            return tmp;
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
