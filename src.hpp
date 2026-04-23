#include <iostream>
using namespace std;

template<typename T>
class LinkedList {
protected:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& val) : data(val), next(nullptr), prev(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int length;
    
public:
    LinkedList() : head(nullptr), tail(nullptr), length(0) {}
    
    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), length(0) {
        Node* current = other.head;
        while (current != nullptr) {
            pushBack(current->data);
            current = current->next;
        }
    }
    
    virtual ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    void pushFront(T val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        length++;
    }
    
    void pushBack(T val) {
        Node* newNode = new Node(val);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        length++;
    }
    
    T popFront() {
        if (head == nullptr) {
            return T();
        }
        Node* temp = head;
        T val = temp->data;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        length--;
        return val;
    }
    
    T popBack() {
        if (tail == nullptr) {
            return T();
        }
        Node* temp = tail;
        T val = temp->data;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        length--;
        return val;
    }
    
    int size() const {
        return length;
    }
    
    void print() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " ";
            }
            current = current->next;
        }
        cout << endl;
    }
    
    virtual const char* name() { return "LinkedList"; }
    virtual T peak() { return T(); }
    virtual T pop() { return T(); }
    virtual void push(T val) {}
};

template<typename T>
class Stack : public LinkedList<T> {
public:
    const char* name() override {
        return "Stack";
    }
    
    T peak() override {
        return this->head->data;
    }
    
    T pop() override {
        return this->popFront();
    }
    
    void push(T val) override {
        this->pushFront(val);
    }
};

template<typename T>
class Queue : public LinkedList<T> {
public:
    const char* name() override {
        return "Queue";
    }
    
    T peak() override {
        return this->head->data;
    }
    
    T pop() override {
        return this->popFront();
    }
    
    void push(T val) override {
        this->pushBack(val);
    }
};
