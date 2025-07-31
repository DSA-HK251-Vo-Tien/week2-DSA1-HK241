#include "DoublyLinkedList.h"
#include <stdexcept>
#include <sstream>

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : length(0)
{
    head = new Node(); // dummy head
    tail = new Node(); // dummy tail
    head->next = tail;
    tail->prev = head;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    // Delete all data nodes
    Node *current = head->next;
    while (current != tail)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
    
    // Delete dummy nodes
    delete head;
    delete tail;
}

template <typename T>
void DoublyLinkedList<T>::insertAtHead(T data)
{
    Node *newNode = new Node(data, head, head->next);
    head->next->prev = newNode;
    head->next = newNode;
    length++;
}

template <typename T>
void DoublyLinkedList<T>::insertAtTail(T data)
{
    Node *newNode = new Node(data, tail->prev, tail);
    tail->prev->next = newNode;
    tail->prev = newNode;
    length++;
}

template <typename T>
void DoublyLinkedList<T>::insertAt(int index, T data)
{
    if (index < 0 || index > length)
        throw std::out_of_range("Index is out of range!");
    
    if (index == 0)
    {
        insertAtHead(data);
        return;
    }
    
    if (index == length)
    {
        insertAtTail(data);
        return;
    }
    
    // Find the node at the specified index
    Node *current = head->next;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    
    // Insert new node before current
    Node *newNode = new Node(data, current->prev, current);
    current->prev->next = newNode;
    current->prev = newNode;
    length++;
}

template <typename T>
void DoublyLinkedList<T>::deleteAt(int index)
{
    if (index < 0 || index >= length)
        throw std::out_of_range("Index is out of range!");
    
    // Find the node at the specified index
    Node *current = head->next;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    
    // Remove the node
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    length--;
}

template <typename T>
T &DoublyLinkedList<T>::get(int index) const
{
    if (index < 0 || index >= length)
        throw std::out_of_range("Index is out of range!");
    
    Node *current = head->next;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    
    return current->data;
}

template <typename T>
int DoublyLinkedList<T>::indexOf(T item) const
{
    Node *current = head->next;
    for (int i = 0; i < length; i++)
    {
        if (current->data == item)
            return i;
        current = current->next;
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
    if (length <= 1)
        return;
    
    Node *current = head->next;
    Node *temp = nullptr;
    
    // Swap next and prev pointers for all data nodes
    while (current != tail)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev; // Move to next node (which is now prev due to swap)
    }
    
    // Swap head and tail connections
    temp = head->next;
    head->next = tail->prev;
    tail->prev = temp;
    
    // Update the new first and last nodes
    head->next->prev = head;
    tail->prev->next = tail;
}

template <typename T>
string DoublyLinkedList<T>::toString(string (*convert2str)(T &)) const
{
    std::stringstream ss;
    ss << "[";
    
    Node *current = head->next;
    for (int i = 0; i < length; i++)
    {
        if (i > 0)
            ss << ", ";
        
        if (convert2str != nullptr)
            ss << convert2str(current->data);
        else
            ss << current->data;
        
        current = current->next;
    }
    
    ss << "]";
    return ss.str();
}

// Explicit template instantiation for char, string, int, double, float, and Point
template class DoublyLinkedList<char>;
template class DoublyLinkedList<string>;
template class DoublyLinkedList<int>;
template class DoublyLinkedList<double>;
template class DoublyLinkedList<float>;
template class DoublyLinkedList<Point>;