

#include "MyString.h"
#include "OctString.h"
#include "DataOctString.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ios;
using std::cerr;

int main() {

MyString s("123");
OctString s1("012");
DataOctString s2("013");
    s.print();
    s1.print();
    s2.print();
    return 0;


}