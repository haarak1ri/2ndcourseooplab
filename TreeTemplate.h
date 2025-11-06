#pragma once
#include <iostream>

template<typename T>
class Tree {
public:
    Tree();
    ~Tree();
    void add(const T& value);
    void printTree() const;
    void remove(const T& key);
    const T* find(const T& value) const;
    void clear();






private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& value ) : data(value), left(nullptr), right(nullptr) {}
    };
    Node* root;
    void add(Node*& current, const T& value);
    void printTree(Node* node, int level) const;
    void remove(Node*& current,const T& key);
    Node* find(Node* current,const T& value) const;
    Node* findMin(Node* current) const;
    void clear(Node*& current);
};

template<typename T>
Tree<T>::Tree() : root(nullptr) {}

template<typename T>
Tree<T>::~Tree() {
    clear(root);
    root = nullptr;
}

template<typename T>
void Tree<T>::add(Node*& current, const T& value) {
    if (current == nullptr) {
        current = new Node(value);
        return;
    }
    if (value < current->data) {
        add(current->left, value);
    }
    else if (value > current->data) {
        add(current->right, value);
    }
}
template<typename T>
void Tree<T>::add(const T& value) {
    add(root, value);
}

template<typename T>
void Tree<T>::printTree(Node* node, int level) const {
    if (!node) return;
    std::cout << "Level: " << level << "; ";
    std::cout << "Value: " << node->data;
    std::cout << "  Left: " << (node->left ? node->left->data : T{})
              << "  Right: " << (node->right ? node->right->data : T{}) << std::endl;

    printTree(node->left, level + 1);
    printTree(node->right, level + 1);
}

template<typename T>
void Tree<T>::printTree() const {
    printTree(root, 0);
}

template<typename T>
typename Tree<T>::Node* Tree<T>::findMin(Node* current) const {
    if (current == nullptr) { return nullptr; }
    while (current->left != nullptr) { current = current->left; }
    return current;
}

template<typename T>
void Tree<T>::remove(Node*& current, const T& key) {
    if (current == nullptr) {
        return;
    }

    if (key < current->data) {
        remove(current->left, key);
    }
    else if (key > current->data) {
        remove(current->right, key);
    }
    else {  // key == *(current->data)
        if (current->left == nullptr && current->right == nullptr) {
            delete current;
            current = nullptr;
        }
        else if (current->left != nullptr && current->right == nullptr) {
            Node* temp = current;
            current = current->left;
            delete temp;
        }
        else if (current->left == nullptr && current->right != nullptr) {
            Node* temp = current;
            current = current->right;
            delete temp;
        }
        else {  // оба потомка существуют
            Node* temp = findMin(current->right);
            current->data = temp->data;
            remove(current->right, temp->data);
        }
    }
}

template<typename T>
void Tree<T>::remove(const T& key) {
    if (!root) {
        throw std::logic_error("Tree::remove(): cannot remove from empty tree");
    }
    remove(root, key);
}

template<typename T>
typename Tree<T>::Node* Tree<T>::find(Node* current,const T& value) const {
    if (current == nullptr) { return nullptr; }
    if (current->data == value) { return current; }
    else if (value < current->data) { return find(current->left, value); }
    else return find(current->right, value);
}

template<typename T>
const T* Tree<T>::find(const T& key) const {
    if (!root) {
        throw std::logic_error("Tree::find(): tree is empty");
    }
    Node* founObj = find(root, key);
    if (founObj == nullptr) { return nullptr; }
    return &(founObj->data);
}

template<typename T>
void Tree<T>::clear(Node*& current) {
    if (!current) { return; }
    clear(current->left);
    clear(current->right);
    delete current;
    current = nullptr;

}
template<typename T>
void Tree<T>::clear() {
    clear(root);
}