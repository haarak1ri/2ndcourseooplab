#pragma once
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include "MyString.h"
#include "OctString.h"
#include "DataOctString.h"

class Tree {
public:
    Tree();
    ~Tree();
    void add(MyString* obj);
    void printTree() const;
    void remove(const MyString& key);
    MyString* find(const MyString& obj) const;
    void clear();



private:
    struct Node {
        MyString* data;
        Node* left;
        Node* right;

        Node(MyString* tdata) : data(tdata), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void add(Node*& current,MyString* obj);
    void printTree(Node* node, int level) const;
    void remove(Node*& current,const MyString& key);
    Node* find(Node* current,const MyString& obj) const;
    Node* findMin(Node* current) const;
    void clear(Node*& current);

};