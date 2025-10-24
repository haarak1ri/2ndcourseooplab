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

MyString::MyString(MyString&& otherStr) noexcept : data(otherStr.data), length(otherStr.length) {
    otherStr.data = nullptr;
    otherStr.length = 0;
    //++objectCount;


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

MyString MyString::operator+(const MyString& otherStr) {
    size_t sumLength = this->length + otherStr.length;
    char* sumStr = new char[sumLength + 1];
    strcpy(sumStr,this->data);
    strcat(sumStr,otherStr.data);

    MyString str(sumStr);
    delete [] sumStr;
    return str;
}


MyString& MyString::operator=(const MyString& otherStr) {
    if (this != &otherStr) {
        delete [] data;
        length = otherStr.length;
        data = new char[length + 1];
        strcpy(data,otherStr.data);
    }
    return *this;

}

MyString& MyString::operator=(MyString&& otherStr) {
    if (this == &otherStr) return *this;
    std::cout << "peremesh";
    delete [] data;
    data = otherStr.data;
    length = otherStr.length;

    otherStr.data = nullptr;
    otherStr.length = 0;

    return *this;



}

bool MyString::operator==(const MyString& otherStr) const {
    if (this->length != otherStr.length || strcmp(this->data,otherStr.data) != 0) return false;
    return true;
}

bool MyString::operator!=(const MyString& otherStr) const {
    return !(*this == otherStr);
}

bool MyString::operator<(const MyString& otherStr) const {
    return strcmp(this->data,otherStr.data) < 0;
}

bool MyString::operator>(const MyString& otherStr) const {
    return strcmp(this->data,otherStr.data) > 0;
}



size_t MyString::getSize() const {
    return length;
};

int MyString::getObjectCount() {
    return objectCount;
}

MyString operator+(const char* leftStr, const MyString& rightStr) {
    if (!leftStr) {
        leftStr = "";
    }
    size_t sumLength = strlen(leftStr) + rightStr.length;
    char* sumStr = new char[sumLength + 1];
    strcpy(sumStr,leftStr);
    strcat(sumStr,rightStr.data);

    MyString str(sumStr);
    delete [] sumStr;
    return str;

}

ostream& operator<<(ostream& out, const MyString& str) {
    out << str.data;


    return out;

}

ofstream& wBin(ofstream& out, const MyString& str) {
    out.write((char*)&str.length, sizeof(str.length));
    out.write(str.data, str.length);
    return out;
}


istream& operator>>(istream& in, MyString& str) {
    size_t capacity = 32;
    size_t length = 0;
    char* buffer = new char[capacity];
    char ch;

    while (in.get(ch) && (ch == ' ' || ch == '\n' || ch == '\t')) {}

    if (in) {
        buffer[length++] = ch;
    }

    while (in.get(ch) && ch != '\n') {
        if (length+1 >= capacity) {
            capacity *= 2;
            char* newBuffer = new char[capacity];
            strcpy(newBuffer,buffer);
            delete[] buffer;
            buffer = newBuffer;

        }

        buffer[length++] = ch;
    }
    buffer[length] = '\0';
    delete[] str.data;
    str.data = buffer;
    str.length = length;

    return in;

}

ifstream& rBin(ifstream& in, MyString& str) {
    size_t len;
    in.read((char*)&len, sizeof(len));
    char* buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';
    delete[] str.data;
    str.data = buffer;
    str.length = len;
    return in;
}

MyString readBinObject(std::ifstream& in) {
    size_t len;
    in.read((char*)&len, sizeof(len));

    if (!in || in.eof()) return MyString();

    char* buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';

    MyString temp(buffer);
    delete[] buffer;
    return temp;


}








