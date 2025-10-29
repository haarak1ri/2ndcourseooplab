

#include "MyString.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ios;
using std::cerr;

int main() {

    // запись объектов в текстовый файл
    {
        cout << "Writing objects to text file" << endl;
        MyString s1("one"), s2("two"), s3("three"), s4("four");

        ofstream fout("strings.txt", ios::out | ios::trunc);
        if (!fout) {
            cerr << "Error cannot open file for writing.\n";
            return 1;
        }

        fout << s1 << endl;
        fout << s2 << endl;
        fout << s3 << endl;
        fout << s4 << endl;
        fout.close();

        cout << "Objects successfully written.\n" << endl;
    }

    // чтение объектов из текстового файла
    {
        cout << "Reading objects from text file" << endl;

        ifstream fin("strings.txt", ios::in);
        if (!fin) {
            cerr << "Error cannot open file for reading.\n";
            return 1;
        }

        MyString a, b, c, d;
        fin >> a >> b >> c >> d;
        fin.close();

        cout << "Loaded:\n" << a << "\n" << b << "\n" << c << "\n" << d << endl;
    }

    // запись объектов в бинарный
    {
        cout << "Writing objects to binary file" << endl;
        MyString s1("one"), s2("two"), s3("three"), s4("four");

        ofstream fout("strings1.bin", ios::out | ios::binary | ios::trunc);
        if (!fout) {
            cerr << "Error cannot open file for writing.\n";
            return 1;
        }

        wBin(fout, s1);
        wBin(fout, s2);
        wBin(fout, s3);
        wBin(fout, s4);
        fout.close();

        cout << "Objects successfully written.\n" << endl;
    }

    // чтение объектов
    {
        cout << "reading objects from binary file" << endl;

        ifstream fin("strings1.bin", ios::in | ios::binary);
        if (!fin) {
            cerr << "error cannot open file for reading.\n";
            return 1;
        }

        MyString a = readBinObject(fin);
        MyString b = readBinObject(fin);
        MyString c = readBinObject(fin);
        MyString d = readBinObject(fin);
        fin.close();

        cout << "Loaded:\n" << a << "\n" << b << "\n" << c << "\n" << d << endl;
    }




    cout << "\n=== All tests completed successfully ===" << endl;

    return 0;


}