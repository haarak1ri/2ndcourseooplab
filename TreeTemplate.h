#pragma once
#include <iostream>

template<typename T>
class Tree {
public:
    Tree();
    ~Tree();
    void add(const T& value);
    void printTree(std::ostream& out) const;
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
    void printTree(std::ostream& out,Node* node, int level) const;
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
void Tree<T>::printTree(std::ostream& out) const {
    printTree(out, root, 0);
}
template<typename T>
void Tree<T>::printTree(std::ostream& out, Node* node, int level) const {
    if (!node) return;

    out << "Level: " << level
        << "; Value: " << node->data
        << "; Left: " << (node->left ? node->left->data : T{})
        << "; Right: " << (node->right ? node->right->data : T{})
        << '\n';

    printTree(out, node->left, level + 1);
    printTree(out, node->right, level + 1);
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
class Tree<const char*> {
public:
    Tree();
    ~Tree();
    void add(const char* value);
    void printTree(std::ostream& out) const;
    void remove(const char* key);
    const char* find(const char* value) const;
    void clear();






private:
    struct Node {
        char* data;
        Node* left;
        Node* right;
        Node(const char* value ) :  left(nullptr), right(nullptr) {
            data = new char[strlen(value) + 1];
            strcpy(data, value);
        }
        ~Node() {
            delete [] data;
        }
    };
    Node* root;

    void add(Node*& current, const char* value);
    void printTree(std::ostream& out,Node* node, int level) const;
    void remove(Node*& current,const char* key);
    Node* find(Node* current,const char* value) const;
    Node* findMin(Node* current) const;
    void clear(Node*& current);
};


Tree<const char*>::Tree() : root(nullptr) {}


Tree<const char*>::~Tree() {
    clear(root);
    root = nullptr;
}

void Tree<const char*>::add(Node*& current, const char* value) {
    if (current == nullptr) {
        current = new Node(value);
        return;
    }
    int cmp = strcmp(value, current->data);
    if (cmp < 0) {
        add(current->left, value);
    }
    else if (cmp > 0) {
        add(current->right, value);
    }
}

void Tree<const char*>::add(const char* value) {
    add(root, value);
}


void Tree<const char*>::printTree(std::ostream& out) const {
    printTree(out, root, 0);
}

void Tree<const char*>::printTree(std::ostream& out, Node* node, int level) const {
    if (!node) return;

    out << "Level: " << level
        << "; Value: " << node->data
        << "; Left: " << (node->left ? node->left->data : "")
        << "; Right: " << (node->right ? node->right->data : "")
        << '\n';

    printTree(out, node->left, level + 1);
    printTree(out, node->right, level + 1);
}

typename Tree<const char*>::Node* Tree<const char*>::findMin(Node* current) const {
    if (current == nullptr) { return nullptr; }
    while (current->left != nullptr) { current = current->left; }
    return current;
}

void Tree<const char*>::remove(const char* key) {
    if (!root) {
        throw std::logic_error("Tree::remove(): cannot remove from empty tree");
    }
    remove(root, key);
}

void Tree<const char*>::remove(Node*& current,const char* key) {
    if (current == nullptr) {
        return;
    }
    int cmp = strcmp(key, current->data);
    if (cmp < 0) {
        remove(current->left, key);
    }
    else if (cmp > 0) {
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
            Node* min = findMin(current->right);
            char* temp = new char[strlen(min->data) + 1];
            strcpy(temp, min->data);

            delete[] current->data;
            current->data = temp;


            remove(current->right, min->data);
        }
    }
}

typename Tree<const char*>::Node* Tree<const char*>::find(Node* current,const char* value) const {
    if (current == nullptr) { return nullptr; }
    int cmp = strcmp(value, current->data);
    if (cmp == 0) {return current;}
    else if (cmp < 0) {
        return find(current->left, value);
    }
    else if (cmp > 0) {
        return find(current->right, value);
    }
}

const char* Tree<const char*>::find(const char* key) const {
    if (!root) {
        throw std::logic_error("Tree::find(): tree is empty");
    }
    Node* founObj = find(root, key);
    if (founObj == nullptr) { return nullptr; }
    return (founObj->data);
}

void Tree<const char*>::clear(Node*& current) {
    if (!current) { return; }
    clear(current->left);
    clear(current->right);
    delete current;
    current = nullptr;
}

void Tree<const char*>::clear() {
    clear(root);
}