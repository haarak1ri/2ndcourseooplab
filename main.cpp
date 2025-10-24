

#include "MyString.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ios;
using std::cerr;

int main() {
    // === Тест 1: запись объектов ===
    {
        cout << "=== Writing objects to binary file ===" << endl;
        MyString s1("one"), s2("two"), s3("three"), s4("four");

        ofstream fout("strings1.bin", ios::out | ios::binary | ios::trunc);
        if (!fout) {
            cerr << "Error: cannot open file for writing.\n";
            return 1;
        }

        wBin(fout, s1);
        wBin(fout, s2);
        wBin(fout, s3);
        wBin(fout, s4);
        fout.close();

        cout << "Objects successfully written.\n" << endl;
    }

    // === Тест 2: чтение объектов ===
    {
        cout << "=== Reading objects from binary file ===" << endl;

        ifstream fin("strings1.bin", ios::in | ios::binary);
        if (!fin) {
            cerr << "Error: cannot open file for reading.\n";
            return 1;
        }

        MyString a = readBinObject(fin);
        MyString b = readBinObject(fin);
        MyString c = readBinObject(fin);
        MyString d = readBinObject(fin);
        fin.close();

        cout << "Loaded:\n" << a << "\n" << b << "\n" << c << "\n" << d << endl;
    }

    // === Тест 3: одинаковые объекты ===
    {
        cout << "\n=== Creating identical objects ===" << endl;

        ifstream fin("strings1.bin", ios::in | ios::binary);
        MyString first = readBinObject(fin);
        fin.close();

        MyString a = first, b = first, c = first, d = first;

        cout << "All contain: " << a << ", " << b << ", " << c << ", " << d << endl;
    }

    cout << "\n=== All tests completed successfully ===" << endl;

    return 0;


}