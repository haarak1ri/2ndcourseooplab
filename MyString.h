#pragma once
#include <iostream>


class MyString {
public:
    MyString(); // констуктор по умолчанию
    MyString(const char* str); //констуктор с параметром
    MyString(const MyString& otherStr); // конструктор копирования

    ~MyString(); // деструктор

    void setString(const char* str) ;//изменение строки
    char* c_str() const; // получение копии строки
    MyString concat(const MyString& otherStr) const; // объеденение двух строк
    int findSubStr(const char* substr) const; // поиск подроски
    size_t getSize() const; // возвращение длины строки

    static int getObjectCount();

    //Лабороторная работа номер 2: Перегрузка операторов и друж. функции
    MyString operator+(const MyString& otherStr);
    MyString& operator=(const MyString& otherStr);
    bool operator==(const MyString& otherStr) const;
    bool operator!=(const MyString& otherStr) const;
    bool operator<(const MyString& otherStr) const;
    bool operator>(const MyString& otherStr) const;


    //friend метод
    friend MyString operator+(const char* leftStr, const MyString& rightStr);






private:
    char* data;
    size_t length;
    static int objectCount;
};


