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
        length = 0;
        head = new Node(); // dummy head
    tail = new Node(); // dummy tail
    head->next = tail;
    tail->prev = head;
    }

    ~DoublyLinkedList(){
        Node* current = head->next;
    while (current != tail) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    // Sau khi đã xóa hết các nút thật, tiến hành xóa hai nút dummy
    delete head;
    delete tail;
    // Đặt head và tail về nullptr để tránh sử dụng các con trỏ đã bị xóa
    head = nullptr;
    tail = nullptr;
    }

    void insertAtHead(T data) {
        Node* newNode = new Node(data);
    newNode->next = head->next;
    newNode->prev = head;
    head->next->prev = newNode;
    head->next = newNode;
    length++;
    }

    void insertAtTail(T data) {
        Node* newNode = new Node(data);
    newNode->prev = tail->prev;
    newNode->next = tail;
    tail->prev->next = newNode;
    tail->prev = newNode;
    length++;
    }

    void insertAt(int index, T data) {
        if (index < 0 || index > length) {
        throw out_of_range("Index out of range");
    }
    Node* newNode = new Node(data);
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
    length++;
    }

    void deleteAt(int index){
        if (index < 0 || index >= length) {
        throw out_of_range("Index out of range");
    }
    Node* current = head->next;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    length--;
    }
    T &get(int index) const{
        if (index < 0 || index >= length) {
        throw out_of_range("Index out of range");
    }
    Node* current = head->next;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
    }
    int indexOf(T item) const{
        Node* current = head->next;
    int index = 0;
    while (current != tail) {
        if (current->data == item) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1; 
    }
    bool contains(T item) const{
        return indexOf(item) != -1;
    }
    int size() const{
        return length;
    }
    void reverse(){
        Node* current = head;
    Node* temp = nullptr;
    // Swap next and prev for all nodes
    while (current != nullptr) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev; // Move to the next node (which is prev due to swap)
    }
    // Swap head and tail
    temp = head;
    head = tail;
    tail = temp;
    }
    string toString(string (*convert2str)(T &) = 0) const{
        std::string result = "[";
    Node* current = head->next;
    while (current != tail) {
        if (convert2str) {
            result += convert2str(current->data);
        } else {
            if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, char>) {
                result += current->data;
            } else if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>) {
                result += std::to_string(current->data);
            } else {
                // fallback dùng operator<<
                std::ostringstream oss;
                oss << current->data;
                result += oss.str();
            }
        }
        if (current->next != tail) {
            result += ", ";
        }
        current = current->next;
    }
    result += "]";
    return result;
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
            if (current == nullptr || current->next == nullptr) {
                throw cursor_error("Iterator out of bounds: cannot increment past the end.");
            }
            else 
            {
                current = current->next;
                return *this;
            }
        }

        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator &operator--()
        {
            if (current == nullptr || current->prev == nullptr) {
                throw cursor_error("Iterator out of bounds: cannot decrement past the beginning.");
            }
            else 
            {
                current = current->prev;
                return *this;
            }
        }

        Iterator operator--(int)
        {
            Iterator tmp = *this;
            --(*this);
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
