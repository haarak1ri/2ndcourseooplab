

#include "MyString.h"
#include <iostream>

int main() {

    MyString str("World");
    MyString str2("Hello");
    MyString str3("Lox");

    MyString s3 = str + " " + str2 + " " + str3;
    std::cout<<s3.c_str();



    return 0;
}








