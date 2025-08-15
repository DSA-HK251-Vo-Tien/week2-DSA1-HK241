#include "DoublyLinkedList.h"

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : length(0)
{
    head = new Node(); // dummy head
    tail = new Node(); // dummy tail
    head->next = tail;
    tail->prev = head;
}

// TODO implement DoublyLinkedList
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    length = 0;
}

template <typename T>
void DoublyLinkedList<T>::insertAtHead(T data) {
    if (head == nullptr) {
        head = tail = new Node(data);
    }
    else {
        Node* newNode = new Node(data, nullptr, head);
        head->prev = newNode;
        head = newNode;
    }
    ++length;
}

template <typename T>
void DoublyLinkedList<T>::insertAtTail(T data) {
    if (tail == nullptr || length == 0) {
        tail = head = new Node(data);
    }
    else{
        Node* newNode = new Node(data, tail);
        tail->next = newNode;
        tail = newNode;
    } 
    ++length;
}

template <typename T>
void DoublyLinkedList<T>::insertAt(int index, T data) {
    if (index < 0 || index > length) {
        throw out_of_range("Index is invalid!");
        return;
    }

    // Chèn vào đầu
    if (index == 0) {
        insertAtHead(data);
        return;
    }
    // Chèn vào cuối
    if (index == length) {
        insertAtTail(data);
        return;
    }

    // Chèn vào giữa
    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    Node* newNode = new Node(data);
    newNode->prev = current->prev;
    newNode->next = current;

    current->prev->next = newNode;
    current->prev = newNode;

    ++length;
}

template <typename T>
void DoublyLinkedList<T>::deleteAt(int index) {
    if (index < 0 || index >= length) {
        throw out_of_range("Index is invalid!");
        return;
    }

    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current=current->next;
    }

    if (current->prev != nullptr) current->prev->next = current->next;
    else {
        head = head->next;
        head->prev = nullptr;
    }
    if (current->next != nullptr) current->next->prev = current->prev;
    else {
        tail = tail->prev;
        tail->next = nullptr;
    }

    delete current;
    --length;
}

template <typename T>
T& DoublyLinkedList<T>::get(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index is invalid!");
    }

    Node* current = head;
    for (int i = 0; i < index; ++i){
        current = current->next;
    }
    return current->data;
}


template <typename T>
int DoublyLinkedList<T>::indexOf(T item) const{
    int count = 0;
    Node* current = head;

    while (current != nullptr){
        if (current->data == item) return count;
        ++count;
        current = current->next;
    }
    return -1;
}

template <typename T>
bool DoublyLinkedList<T>::contains(T item) const{
    if (indexOf(item) != -1) return true;
    return false;
}

template <typename T>
int DoublyLinkedList<T>::size() const{
    return length;
}

template <typename T>
void DoublyLinkedList<T>::reverse() {
    Node* current = head;
    while (current != nullptr) {
        swap(current->next, current->prev);
        current = current->prev; // vì next/prev đã hoán đổi
    }
    swap(head, tail);
}

template <typename T>
string DoublyLinkedList<T>::toString(string (*convert2str)(T &)) const{
    stringstream ss;
    ss << "[";
    Node* current = head;

    while (current != tail) {
        ss << convert2str(current->data) << ", ";
        current = current->next;
    }

    ss << convert2str(tail->data) << "]";

    return ss.str();
}
// Explicit template instantiation for char, string, int, double, float, and Point
template class DoublyLinkedList<char>;
template class DoublyLinkedList<string>;
template class DoublyLinkedList<int>;
template class DoublyLinkedList<double>;
template class DoublyLinkedList<float>;
template class DoublyLinkedList<Point>;
