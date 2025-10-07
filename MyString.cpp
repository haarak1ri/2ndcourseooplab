#include "MyString.h"
#include "cstring"

int MyString::objectCount = 0;

//конструктор по умолчанию
MyString::MyString() {
    data = new char[1];
    data[0] = '\0';
    length = 0;
    ++objectCount;
}

//констуктор с параметром
MyString::MyString(const char *str) {
    if (!str) {
        data = new char[1];
        data[0] = '\0';
        length = 0;
    }
    else {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data,str);

    }
    ++objectCount;
}

//констуктор копирования
MyString::MyString(const MyString& otherStr) {
    length = otherStr.length;
    data = new char[length + 1];
    strcpy(data,otherStr.data);
    ++objectCount;

}



//Деструктор
MyString::~MyString() {
    delete [] data;
    --objectCount;
}
//изменение строки
void MyString::setString(const char* str) {
    delete [] data;
    if (!str) {
        data = new char[1];
        data[0] = '\0';
        length = 0;
    }
    else {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data,str);
    }
}
// возвращение копии строки
char* MyString::c_str() const {

    char* strCopy = new char[length + 1];
    strcpy(strCopy,data);
    return strCopy;
}

MyString MyString::concat(const MyString& otherStr) const {
    size_t tempLen = length + otherStr.length;
    char* tempStr = new char[tempLen + 1];
    strcpy(tempStr,data);
    strcat(tempStr,otherStr.data);

    MyString str(tempStr);
    delete [] tempStr;
    return str;
}

int MyString::findSubStr(const char* substr) const {
    if (!substr || substr[0] == '\0') return -1;
    char* pos = strstr(data,substr);
    if (!pos) return -1;
    return (int)(pos - data);

}

size_t MyString::getSize() const {
    return length;
};

int MyString::getObjectCount() {
    return objectCount;
}
