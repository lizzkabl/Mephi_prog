#pragma once
#include "ShrdPtr.h"
#include "WeakPtr.h"

template<typename T>
struct Node
{
    T data;
    WeakPtr<Node<T>> prev;
    ShrdPtr<Node<T>> next;

    Node() : data{ T() }, prev{ nullptr }, next{ nullptr } {}
    Node(const T& item) : data{ item }, prev{ nullptr }, next{ nullptr } {}
};

template <class T>
class LinkedList {
private:
    size_t size;
    ShrdPtr<Node<T>> head;
    ShrdPtr<Node<T>> tail;

public:
    ~LinkedList() = default;

    LinkedList() : head{ nullptr }, tail{ nullptr }, size{ 0 } {}

    LinkedList(const LinkedList <T>& other) : size{ other.size }
    {
        ShrdPtr<Node<T>> help = other.head;
        for (size_t i = 0; i < size; ++i) {
            Append(help->data);
            if (help->next != nullptr) {
                help = help->next;
            }
        }
    }

    LinkedList(T* items, size_t count) : size{ 0 }, head{ nullptr }, tail{ nullptr }
    {
        for (size_t i = 0; i < count; ++i) {
            Append(items[i]);
        }
    }

    T GetFirst() const
    {
        if (GetLength() == 0) {
            throw std::out_of_range("Index out of range");
        }
        return head->data;
    }

    T GetLast() const
    {
        if (GetLength() == 0) {
            throw std::out_of_range("Index out of range");
        }
        return tail->data;
    }

    T Get(int index) const
    {
        if (index >= GetLength() || index < 0) {
            throw std::out_of_range("Index out of range");
        }

        ShrdPtr<Node<T>> elem = head;
        for (int i = 0; i < index; ++i) {
            elem = elem->next;
        }
        return elem->data;
    }

    int GetLength() const
    {
        return static_cast<int>(size);
    }

    ShrdPtr<LinkedList<T>> GetSubList(int startIndex, int endIndex) const
    {
        if (startIndex >= GetLength() || startIndex < 0 || endIndex >= GetLength() || endIndex < 0) {
            throw std::out_of_range("Index out of range");
        }

        ShrdPtr<LinkedList<T>> sub_list(new LinkedList<T>());

        ShrdPtr<Node<T>> elem = head;
        for (int i = 0; i <= endIndex; ++i) {
            if (i >= startIndex) {
                sub_list->Append(elem->data);
            }
            elem = elem->next;
        }
        return sub_list;
    }

    void Append(const T& item)
    {
        ShrdPtr<Node<T>> p(new Node<T>(item));
        p->prev = tail;

        if (tail != nullptr) {
            tail->next = p;
        }
        else {
            head = p;
        }
        tail = p;
        ++size;
    }

    void Prepend(const T& item)
    {
        ShrdPtr<Node<T>> p(new Node<T>(item));
        p->next = head;

        if (head != nullptr) {
            head->prev = p;
        }
        else {
            tail = p;
        }
        head = p;
        ++size;
    }

    void InsertAt(const T& item, int index)
    {
        if (index >= GetLength() || index < 0) {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0) {
            Prepend(item);
            return;
        }
        else if (index == GetLength()) {
            Append(item);
            return;
        }

        ShrdPtr<Node<T>> right = head;
        for (int i = 0; i < index; ++i) {
            right = right->next;
        }

        ShrdPtr<Node<T>> left = right->prev.lock();
        ShrdPtr<Node<T>> p(new Node<T>(item));
        p->prev = left;
        p->next = right;

        if (left) left->next = p;
        if (right) right->prev = p;

        ++size;
    }
};
