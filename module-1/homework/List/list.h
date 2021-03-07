#pragma once
#include <cstddef>
#include <initializer_list>

namespace task {


class list {

public:

    list();
    list(size_t count, const int& value = int());
    list(const list& other);

    ~list();
    list& operator=(const list& other);


    int& front();
    const int& front() const;

    int& back();
    const int& back() const;


    bool empty() const;
    size_t size() const;
    void clear();


    void push_back(const int& value);
    void pop_back();
    void push_front(const int& value);
    void pop_front();
    void resize(size_t count);
    void swap(list& other);


    void remove(const int& value);
    void unique();
    void sort();


private:
    struct Node {
        Node(const int& data) : data(data), prev(nullptr), next(nullptr) {}
        Node(const int& data, Node* prev, Node* next): data(data), prev(prev), next(next) {}
        ~Node() = default;

        int data;
        Node* prev;
        Node* next;
    };

    Node* head;
    Node* tail;

    size_t m_size;

    void _remove_node_from_list(Node* &node);
    static void _merge_sort(list& left);
    void push_back(Node *node);
    void push_front(Node *node);

    void _remove_node(Node *node);
};

}  // namespace task
