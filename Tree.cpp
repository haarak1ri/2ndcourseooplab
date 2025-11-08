#pragma once
#include "Tree.h"


Tree::Tree() : root(nullptr){
}

Tree::~Tree() {
    clear(root);
    root = nullptr;
}

//внутреняя реализация
void Tree::add(Node*& current, MyString* obj) {
    if (!obj) {
        throw std::invalid_argument("Tree::add(): cannot insert null object pointer");
    }
    if (current == nullptr) {
        current = new Node(obj);
        return;
    }

    if(*(obj) < *(current->data)) {
        add(current->left, obj);
    }
    else {
        add(current->right, obj);
    }
}

void Tree::add(MyString* obj) {
    if (!obj) {
        throw std::invalid_argument("Tree::add(): null pointer passed");
    }
    add(root, obj);
}

// void Tree::printTree(Node* node, int level) const {
//     if (!node) return;
//
//
//     const char* leftVal = (node->left) ? node->left->data->c_str() : "";
//     const char* rightVal = (node->right) ? node->right->data->c_str() : "";
//
//
//     std::cout << "Level: " << level << "; ";
//     std::cout << "Value: ";
//     node->data->toString();// для каждого типа объекта свой print - полиморфизм
//     std::cout << "  Left: " << (node->left ? leftVal : "null")
//               << "  Right: " << (node->right ? rightVal : "null") << std::endl;
//
//
//     printTree(node->left, level + 1);
//     printTree(node->right, level + 1);
// }
//
void Tree::printTree(std::ostream& out) const {
    printTree(out, root, 0);
}

void Tree::printTree(std::ostream& out, Node* node, int level) const {
    if (!node) return;

    out << "Level: " << level
        << "; Value: " << node->data->toString()
        << "; Left: " << (node->left ? node->left->data->toString() : "null")
        << "; Right: " << (node->right ? node->right->data->toString() : "null")
        << '\n';

    printTree(out, node->left, level + 1);
    printTree(out, node->right, level + 1);
}


Tree::Node* Tree::findMin(Node* current) const {
    if (current == nullptr) { return nullptr; }
    while (current->left != nullptr) { current = current->left; }
    return current;
}

void Tree::remove(Node*& current, const MyString& key) {
    if (current == nullptr) {
        return;
    }

    if (key < *(current->data)) {
        remove(current->left, key);
    }
    else if (key > *(current->data)) {
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
            remove(current->right, *(temp->data));
        }
    }
}

void Tree::remove(const MyString& key) {
    if (!root) {
        throw std::logic_error("Tree::remove(): cannot remove from empty tree");
    }
    remove(root, key);
}

Tree::Node* Tree::find(Node* current,const MyString& obj) const {
    if (current == nullptr) { return nullptr; }
    if (*(current->data) == obj) { return current; }
    else if (obj < *(current->data)) { return find(current->left, obj); }
    else return find(current->right, obj);
}

MyString* Tree::find(const MyString& key) const {
    if (!root) {
        throw std::logic_error("Tree::find(): tree is empty");
    }
    Node* founObj = find(root, key);
    if (founObj == nullptr) { return nullptr; }
    return founObj->data;
}

void Tree::clear(Node*& current) {
    if (!current) { return; }
    clear(current->left);
    clear(current->right);
    delete current;
    current = nullptr;

}

void Tree::clear() {
    clear(root);
}