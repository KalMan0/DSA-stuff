#include <iostream>
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<typename T>
struct node {

    T data;
    node<T>* next;

};

template <typename T>
class LinkedListIterator {
    public:
        LinkedListIterator(node<T>* start) : current(start) {}

        T& operator*() 
        {
            return current->data;
        }

        LinkedListIterator<T>& operator++() 
        {
            current = current->next;
            return *this;
        }

        bool operator!=(const LinkedListIterator<T>& other) const 
        {
            return current != other.current;
        }

    private:

        node<T>* current;
};



template<typename T>
class LinkedList {

    private:

        node<T>* head;
        int size;

        void      dstryLst  ();
        size_t    get_size  () const;
        node<T>*  new_node  (const T&); 

    public:

        LinkedList             ();
        virtual ~LinkedList    ();

        void                append      (const T&);
        void                remove      (const T&); 


        LinkedListIterator<T> begin     () const; 
        LinkedListIterator<T> end       ()   const; 
};

template<class T> LinkedList<T>::LinkedList()
{

}

template<class T> LinkedList<T>::~LinkedList()
{
    dstryLst(); delete this->head; 
}

template<class T> LinkedListIterator<T> LinkedList<T>::begin() const 
{
    return LinkedListIterator<T>(head);
}


template<class T> LinkedListIterator<T> LinkedList<T>::end() const 
{
    return LinkedListIterator<T>(nullptr);
}

template<class T> void LinkedList<T>::append(const T& data)
{
    if (this->head == nullptr)
    {
        this->head = new_node(data); 
        size++; 
        return;
    }

    node<T>* tmp = this->head;

    while (tmp->next != nullptr)
    {
        tmp = tmp->next;
    }

    tmp->next = new_node(data); 
    size++; 
}

template<typename T> node<T>* LinkedList<T>::new_node(const T& data)
{
    node<T>* newnode = new node<T>; 
    newnode->data = data; 
    newnode->next = nullptr; 

    return newnode; 
}

template<typename T> void LinkedList<T>::dstryLst()
{
    node<T>* tmp = head->next;

    while (tmp != nullptr)
    {
        size--; node<T>* nextNode = tmp->next; delete tmp; tmp = nextNode;
    }

    head->next = nullptr;
}

template<typename T> void LinkedList<T>::remove(const T& value) 
{ 
    if (head == nullptr) 
        return;
    

    if (head->data == value) 
    {
        node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
        return;
    }

    node<T>* current = head;
    while (current->next != nullptr && current->next->data != value) 
    {
        current = current->next;
    }

    if (current->next != nullptr) 
    {
        node<T>* temp = current->next;
        current->next = current->next->next;
        delete temp;
        size--;
    }
}

template<typename T> size_t LinkedList<T>::get_size() const
{
    return this->size;
}

#endif

