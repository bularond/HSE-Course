#include <stdexcept>
#include "list.h"

task::list::list() : head(nullptr), tail(nullptr), m_size(0) {};

task::list::list(size_t count, const int& value) : task::list() {
    for (size_t i = 0; i < count; i++) {
        push_back(value);
    }
}

task::list::list(const list& other) {
    tail = head = nullptr;
    m_size = 0;
    Node* copy_pointer = other.head;
    while (copy_pointer != nullptr) {
        push_back(copy_pointer->data);
        copy_pointer = copy_pointer->next;
    }
}

task::list::~list() {
    clear();
}

task::list& task::list::operator=(const list& other) {
    clear();
    Node* copy_pointer = other.head;
    while (copy_pointer != nullptr) {
        push_back(copy_pointer->data);
        copy_pointer = copy_pointer->next;
    }
    return *this;
}

size_t task::list::size() const {
    return m_size;
}

bool task::list::empty() const {
    return m_size == 0;
}

void task::list::clear() {
    while (size()) {
        _remove_node(head);
    }
    head = tail = nullptr;
}

void task::list::push_back(Node* node) {
    node->next = nullptr;
    node->prev = tail;
    if (head == nullptr) {
        head = node;
    }
    if (tail != nullptr) {
        tail->next = node;
    }
    tail = node;
    m_size++;
}

void task::list::push_back(const int& val) {
    Node* new_node = new task::list::Node(val, tail, nullptr);
    push_back(new_node);
}

void task::list::push_front(Node* node) {
    node->next = head;
    node->prev = nullptr;
    if (tail == nullptr) {
        tail = node;
    }
    if (head != nullptr) {
        head->prev = node;
    }
    head = node;
    m_size++;
}

void task::list::push_front(const int &val) {
    Node* new_node = new task::list::Node(val, nullptr, head);
    push_front(new_node);
}

void task::list::pop_back() {
    if (tail == nullptr) {
        throw std::out_of_range("Invalid operation \"pop_back\": list is empty");
    }
    _remove_node(tail);
}

void task::list::pop_front() {
    if (head == nullptr) {
        throw std::out_of_range("Invalid operation \"pop_front\": list is empty");
    }
    _remove_node(head);
}

int& task::list::front() {
    if (head == nullptr) {
        throw std::out_of_range("Invalid operation \"front\": list is empty");
    }
    return head->data;
}

const int& task::list::front() const {
    if (head == nullptr) {
        throw std::out_of_range("Invalid operation \"front\": list is empty");
    }
    return head->data;
}

int& task::list::back() {
    if (tail == nullptr) {
        throw std::out_of_range("Invalid operation \"back\": list is empty");
    }
    return tail->data;
}

const int& task::list::back() const {
    if (tail == nullptr) {
        throw std::out_of_range("Invalid operation \"back\": list is empty");
    }
    return tail->data;
}

void task::list::resize(size_t count) {
    while (m_size > count) {
        pop_back();
    }
    while (m_size < count) {
        push_back(0);
    }
}

void task::list::swap(list &other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(m_size, other.m_size);
}

void task::list::_remove_node_from_list(Node* &node) {
    if (node == nullptr) {
        return;
    }

    if (node->next != nullptr) {
        node->next->prev = node->prev;
    }
    if (node->prev != nullptr) {
        node->prev->next = node->next;
    }

    if (node == head) {
        head = node->next;
    }
    if (node == tail) {
        tail = node->prev;
    }

    m_size--;
}

void task::list::_remove_node(Node* node) {
    _remove_node_from_list(node);
    delete node;
}

void task::list::_merge_sort(task::list& left) {
    if (left.size() == 1) {
        return;
    }

    list right;
    while (left.size() > right.size()) {
        Node* tmp = left.tail;
        left._remove_node_from_list(tmp);
        right.push_front(tmp);
    }

    _merge_sort(left);
    _merge_sort(right);

    list out;
    while (left.size() || right.size()) {
        if (right.empty() || left.size() && left.head->data < right.head->data) {
            Node* tmp = left.head;
            left._remove_node_from_list(tmp);
            out.push_back(tmp);
        }
        else {
            Node* tmp = right.head;
            right._remove_node_from_list(tmp);
            out.push_back(tmp);
        }
    }

    left.swap(out);
}

void task::list::sort() {
    _merge_sort(*this);
}

void task::list::remove(const int& value) {
    Node* cur = head;
    int val = value;
    while (cur != nullptr) {
        Node *tmp = cur;
        cur = cur->next;
        if (tmp->data == val) {
            _remove_node(tmp);
        }
    }
}

void task::list::unique() {
    sort();

    Node* cur = head;
    while (cur != nullptr) {
        while (cur->next != nullptr && cur->data == cur->next->data) {
            _remove_node(cur->next);
        }
        cur = cur->next;
    }
}
