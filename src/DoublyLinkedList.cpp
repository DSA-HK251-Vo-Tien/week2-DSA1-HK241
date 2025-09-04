#include "DoublyLinkedList.h"
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
    Node* curr = this->head;
    while(curr){
        Node* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
}

// TODO implement DoublyLinkedList
template <typename T>
void DoublyLinkedList<T>::insertAtHead(T data)
{
    Node* node  = new Node(data);

    node->prev = head;
    node->next = head->next;

    head->next = node;
    head->next->prev = node;

    this->length++;
}

template <typename T>
void DoublyLinkedList<T>::insertAtTail(T data)
{
    Node* node = new Node(data);
        
    node->next = tail;
    node->prev = tail->prev;

    tail->prev->next = node;
    tail->prev = node;
    this->length++;
}

template <typename T>
void DoublyLinkedList<T>::insertAt(int index, T data)
{
    Node* node = new Node(data);
    Node* curr = head->next;
    if( index >= 0 && index < this->length){
        if(index == 0){
            insertAtHead(data);
            return;
        } else if( index == this->length){
            insertAtTail(data);
            return;
        } else{
            for(int i = 0; i < index; i++){
                curr = curr->next;
            }
            node->next = curr;
            node->prev = curr->prev;

            curr->prev->next = node;
            curr->prev = node;

            this->length++;
        }
    }
    else{throw out_of_range ("Index is invalid");}
}

template <typename T>
void DoublyLinkedList<T>::deleteAt(int index)
{
    Node* curr = head->next;
    if( index >= 0 && index < this->length){
        for(int i = 0; i < index; i++){
            curr = curr->next;
        }
        curr->next->prev = curr->prev;
        curr->prev->next = curr->next;
        delete curr;
        this->length--;
    }
    else{throw out_of_range ("Index is invalid");}
    }

template <typename T>
T &DoublyLinkedList<T>::get(int index) const
{
   Node* curr = head->next;
    if( index >= 0 && index < this->length){
        for(int i = 0; i < index; i++){
        curr = curr->next;
        }
        return curr->data;
    }
    else{throw out_of_range ("Index is invalid");}
}

template <typename T>
int DoublyLinkedList<T>::indexOf(T item) const
{
    Node* curr = head->next;
    int count = 0;
    while(curr != tail){
        if(curr->data == item){
            return count;
        }
        curr = curr->next;
        count++;
    }
    return -1;
}

template <typename T>
bool DoublyLinkedList<T>::contains(T item) const
{
    Node* curr = head->next;
    while(curr != tail){
        if(curr->data == item){
            return true;
        }
        curr = curr->next;
    }
    return false;
}

template <typename T>
int DoublyLinkedList<T>::size() const
{
    return this->length;
}

template <typename T>
void DoublyLinkedList<T>::reverse()
{
    Node* curr = head;
    while(curr != nullptr){
        Node* temp = curr->next;
        curr->next = curr->prev;
        curr->prev = temp;
        curr = temp;
    }
    // hoán đổi head và tail
    Node* temp = head;
    head = tail;
    tail = temp;
}

template <typename T>
string DoublyLinkedList<T>::toString(string (*convert2str)(T &) /*= 0*/) const
{
    stringstream ss;
    ss << "[";
    Node* curr = head->next;
    bool first = true;
    while(curr != tail) {
        if(!first) ss << ", ";
        else first = false;
        if (convert2str != nullptr){
            ss << convert2str(curr->data);
        } else{
            ss << curr->data;
        }
        curr = curr->next;
    }
    ss << ']';
    return ss.str();
}

// Explicit template instantiation for char, string, int, double, float, and Point
template class DoublyLinkedList<char>;
template class DoublyLinkedList<string>;
template class DoublyLinkedList<int>;
template class DoublyLinkedList<double>;
template class DoublyLinkedList<float>;
template class DoublyLinkedList<Point>;