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
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }

    ~DoublyLinkedList()
    {
        Node *curr = head;
        while (curr)
        {
            Node *temp = curr->next;
            delete curr;
            curr = temp;
        }

        head = tail = nullptr;
        length = 0;
    }

    void insertAtHead(T data)
    {
        Node *temp = head->next;
        head->next = new Node(data, head, head->next);
        temp->prev = head->next;
        length++;
    }

    void insertAtTail(T data)
    {
        Node *temp = tail->prev;
        tail->prev = new Node(data, tail->prev, tail);
        temp->next = tail->prev;
        length++;
    }

    void insertAt(int index, T data)
    {
        if (index < 0 || index > length)
        {
            throw std::out_of_range("Index is invalid!");
        }

        int idx = 0;
        Node *curr = head->next;

        while (idx < index)
        {
            curr = curr->next;
            idx++;
        }

        Node *newNode = new Node(data, curr->prev, curr);
        curr->prev->next = newNode;
        curr->prev = newNode;

        length++;
    }

    void deleteAt(int index)
    {
        if (index < 0 || index >= length)
        {
            throw std::out_of_range("Index is invalid!");
        }

        Node *curr = head->next;
        int idx = 0;

        while (idx < index)
        {
            curr = curr->next;
            idx++;
        }

        Node *prevNode = curr->prev;
        Node *nextNode = curr->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        delete curr; // giải phóng node
        length--;    // cập nhật kích thước
    }

    T &get(int index) const
    {
        // Throw exception
        if (index < 0 || index >= length)
        {
            throw std::out_of_range("Index is invalid!");
        }

        // Move idx to the correct position
        int idx = 0;
        Node *curr = head->next;

        while (idx < index)
        {
            curr = curr->next;
            idx++;
        }

        // Return data
        return curr->data;
    }

    int indexOf(T item) const
    {
        int idx = 0;
        Node *curr = head->next;

        while (curr != tail)
        {
            if (curr->data == item)
            {
                return idx;
            }
            ++idx;
            curr = curr->next;
        }

        return -1;
    }

    bool contains(T item) const
    {
        Node *curr = head->next;

        while (curr != tail)
        {
            if (curr->data == item)
            {
                return true;
            }
            curr = curr->next;
        }

        return false;
    }

    int size() const
    {
        return length;
    }

    void reverse()
    {
        Node *curr = head;
        while (curr)
        {
            Node *nextNode = curr->next;
            curr->next = curr->prev;
            curr->prev = nextNode;
            curr = nextNode;
        }

        Node *temp = head;
        head = tail;
        tail = temp;
    }

    string toString(string (*convert2str)(T &) = 0) const
    {
        stringstream ss;
        ss << "[";

        Node *curr = head->next;
        while (curr != tail)
        {
            if (convert2str)
            {
                ss << convert2str(curr->data);
            }
            else
            {
                ss << curr->data;
            }

            curr = curr->next;
            if (curr != tail)
            {
                ss << ", ";
            }
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
