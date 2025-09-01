#include "DoublyLinkedList.h"

#include <iostream>
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : length(0) {
  head = new Node();  // dummy head
  tail = new Node();  // dummy tail
  head->next = tail;
  tail->prev = head;
}

// TODO implement DoublyLinkedList
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  Node* current = head->next;
  while (current != tail) {
    Node* next_node = current->next;
    delete current;
    current = next_node;
  }
  delete head;
  delete tail;
}

template <typename T>
void DoublyLinkedList<T>::insertAtHead(T data) {
  Node* new_node = new Node(data, head, head->next);
  head->next->prev = new_node;
  head->next = new_node;
  length++;
}
// test123123

template <typename T>
void DoublyLinkedList<T>::insertAtTail(T data) {
  Node* new_node = new Node(data, tail->prev, tail);
  tail->prev->next = new_node;
  tail->prev = new_node;
  length++;
}

template <typename T>
void DoublyLinkedList<T>::insertAt(int index, T data) {
  if (index < 0 || index > length) {
    throw std::out_of_range("Index is invalid!");
  }
  if (index == 0) {
    insertAtHead(data);
    return;
  }
  if (index == length) {
    insertAtTail(data);
    return;
  }

  Node* current;

  if (index < length / 2) {
    current = head->next;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }
  } else {
    current = tail;
    for (int i = length; i > index; --i) {
      current = current->prev;
    }
  }

  Node* new_node = new Node(data, current->prev, current);
  current->prev->next = new_node;
  current->prev = new_node;
  length++;
}

template <typename T>
void DoublyLinkedList<T>::deleteAt(int index) {
  if (index < 0 || index >= length) {
    throw std::out_of_range("Index is invalid!");
  }

  Node* node_to_delete;

  if (index < length / 2) {
    node_to_delete = head->next;
    for (int i = 0; i < index; ++i) {
      node_to_delete = node_to_delete->next;
    }
  } else {
    node_to_delete = tail;
    for (int i = length; i > index; --i) {
      node_to_delete = node_to_delete->prev;
    }
  }

  node_to_delete->prev->next = node_to_delete->next;
  node_to_delete->next->prev = node_to_delete->prev;
  delete node_to_delete;
  length--;
}

template <typename T>
T& DoublyLinkedList<T>::get(int index) const {
  if (index < 0 || index >= length) {
    throw std::out_of_range("Index is invalid!");
  }

  Node* current;

  if (index < length / 2) {
    current = head->next;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }
  } else {
    current = tail;
    for (int i = length; i > index; --i) {
      current = current->prev;
    }
  }
  return current->data;
}

template <typename T>
int DoublyLinkedList<T>::indexOf(T item) const {
  Node* current = head->next;
  for (int i = 0; i < length; ++i) {
    if (current->data == item) return i;
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
  return this->length;
}

template <typename T>
void DoublyLinkedList<T>::reverse() {
  if (length <= 1) return;
  Node* current = head;
  while (current != nullptr) {
    Node* temp = current->next;
    current->next = current->prev;
    current->prev = temp;
    current = current->prev;
  }
  Node* temp = head;
  head = tail;
  tail = temp;
}

template <typename T>
string DoublyLinkedList<T>::toString(string (*convert2str)(T&)) const {
  stringstream ss;
  ss << "[";
  Node* current = head->next;
  for (int i = 0; i < length; ++i) {
    if (convert2str) {
      ss << convert2str(current->data);
    } else {
      ss << current->data;
    }
    if (i < length - 1) {
      ss << ", ";
    }
    current = current->next;
  }
  ss << "]";
  return ss.str();
}
// Explicit template instantiation for char, string, int, double, float, and
// Point
template class DoublyLinkedList<char>;
template class DoublyLinkedList<string>;
template class DoublyLinkedList<int>;
template class DoublyLinkedList<double>;
template class DoublyLinkedList<float>;
template class DoublyLinkedList<Point>;