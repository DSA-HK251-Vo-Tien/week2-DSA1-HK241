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
    Node *current = head;
    while (current != nullptr)
    {
        Node *nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

template <typename T>
void DoublyLinkedList<T>::insertAtHead(T data) {
    Node* newNode = new Node(data, head, head->next);
    head->next->prev = newNode;
    head->next = newNode;
    length++;
}

template <typename T>
void DoublyLinkedList<T>::insertAtTail(T data) {
    Node* newNode = new Node(data, tail->prev, tail);
    tail->prev->next = newNode;
    tail->prev = newNode;
    length++;
}
template <typename T>
void DoublyLinkedList<T>::insertAt(int index, T data) {
    if (index < 0 || index > length) {
        throw out_of_range("Index is invalid");
    }

    Node* current;
    if (index > length / 2) {
        current = tail;
        for (int i = length; i > index; i--) current = current->prev;
    } else {
        current = head->next;
        for (int i = 0; i < index; i++) current = current->next;
    }

    Node* newNode = new Node(data, current->prev, current);
    current->prev->next = newNode;
    current->prev = newNode;
    length++;
}

template <typename T>
void DoublyLinkedList<T>::deleteAt(int index) {
    if (index < 0 || index >= length) {
        throw out_of_range("Index is invalid");
    }

    Node* current;
    if (index > length / 2) {
        current = tail;
        for (int i = length - 1; i > index; i--) current = current->prev;
    } else {
        current = head->next;
        for (int i = 0; i < index; i++) current = current->next;

    }

    Node* toDelete = current;
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete toDelete;
    length--;
}

template <typename T>
T& DoublyLinkedList<T>::get(int index) const {
    if (index < 0 || index >= length) {
        throw out_of_range("Index is invalid");
    }

    Node* current;
    if (index > length / 2) {
        current = tail->prev;
        for (int i = length - 1; i > index; i--) current = current->prev;
    } else {
        current = head->next;
        for (int i = 0; i < index; i++) current = current->next;
    }

    return current->data;
}

template <typename T>
int DoublyLinkedList<T>::indexOf(T item) const {
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

template <typename T>
bool DoublyLinkedList<T>::contains(T item) const {
    if (indexOf(item) != -1) {
        return true;
    }
    return false;
}

template <typename T>
int DoublyLinkedList<T>::size() const {
    return length;
}

template <typename T>
void DoublyLinkedList<T>::reverse() {
    Node* current = head;
    Node* temp = nullptr;

    while (current != nullptr) {
        temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    }

    swap(head, tail);
    head->prev = nullptr;
    tail->next = nullptr;
}

template <typename T>
string DoublyLinkedList<T>::toString(string (*convert2str)(T &)) const {
    Node* current = head->next;
    ostringstream oss;
    oss << "[";
    while (current != tail) {
        if (convert2str) {
            oss << convert2str(current->data);
        } else {
            oss << current->data;
        }

        if (current->next != tail) {
            oss << ", ";
        }
        current = current->next;
    }
    oss << "]";
    return oss.str();
}

// Explicit template instantiation for char, string, int, double, float, and Point
template class DoublyLinkedList<char>;
template class DoublyLinkedList<string>;
template class DoublyLinkedList<int>;
template class DoublyLinkedList<double>;
template class DoublyLinkedList<float>;
template class DoublyLinkedList<Point>;