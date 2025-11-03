#include "OctString.h"
#include <cstring>

OctString::OctString() : MyString(), valid(true), decValue(0) {}

OctString::OctString(const char* str) : MyString(str) {
    valid = isValidOct();
    if (valid) {
        toDec();
    } else {
        // невалидная строка превращается в пустую валидную
        MyString::setString("");
        valid = true;
        decValue = 0;
    }
}

OctString::OctString(const OctString& otherStr) : MyString(otherStr),
    valid(otherStr.valid),decValue(otherStr.decValue){}

OctString::OctString(OctString&& otherStr) noexcept : MyString(std::move(otherStr)), valid(otherStr.valid),
    decValue(otherStr.decValue)
{
    otherStr.valid = false;
    otherStr.decValue = 0;
}

OctString::~OctString() {
}

bool OctString::isValidOct() const {
    if (length == 0) {
        return true;  // пустая строка -  валидная
    }

    // восьмеричное число должно начинаться с '0'
    if (data[0] != '0') {
        return false;
    }

    // запрет на 00 000
    if (length > 1 && data[1] == '0') {
        return false;
    }

    // 0-7
    for (int i = 1; i < length; i++) {
        if (data[i] < '0' || data[i] > '7') {
            return false;
        }
    }

    return true;
}

void OctString::setString(const char* str) {
    MyString::setString(str);
    if (!isValidOct()) {
        // невалидная строка превращается в пустую валидную
        MyString::setString("");
        valid = true;
        decValue = 0;
    }
    else {
        valid = true;
        toDec();
    }
}

OctString OctString::concat(const OctString& otherStr) const {
    OctString result;
    result.setString((MyString::concat(otherStr)).c_str());
    return result;
}

OctString OctString::operator+(const OctString& otherStr) {
    return this->concat(otherStr);
}

OctString& OctString::operator=(const OctString& otherStr) {
    if (this != &otherStr) {
        MyString::operator=(otherStr);
        valid = otherStr.valid;
        decValue = otherStr.decValue;
    }
    return *this;
}

OctString& OctString::operator=(OctString&& otherStr) {
    if (this != &otherStr) {
        MyString::operator=(std::move(otherStr));
        valid = otherStr.valid;
        decValue = otherStr.decValue;
        otherStr.valid = false;
        otherStr.decValue = 0;
    }
    return *this;
}

int OctString::toDec() {
    int result = 0;
    if (!valid || length == 0) {
        decValue = 0;
        return 0;  // пустая строка - 0
    }


    for (int i = 1; i < length; i++) {
        result = result * 8 + (data[i] - '0');
    }
    decValue = result;
    return result;
}

void OctString::fromDec(int value) {
    this->decValue = value;
    if (value == 0) {
        setString("");  // 0 - пустая строка
        return;
    }

    size_t length = 0;
    size_t capacity = 2;
    char *buffer = new char[capacity];


    while (value > 0) {
        if (length >= capacity) {
            capacity *= 2;
            char* newBuffer = new char[capacity];
            for (int j = 0; j < length; j++) {
                newBuffer[j] = buffer[j];
            }
            delete[] buffer;
            buffer = newBuffer;
        }
        buffer[length++] = (value % 8) + '0';
        value /= 8;
    }

    buffer[length] = '\0';


    for (int i = 0; i < length/2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[length-1-i];
        buffer[length-1-i] = temp;
    }


    char* octBuffer = new char[length + 2];  // +1 для '0' +1 для '\0'
    octBuffer[0] = '0';
    strcpy(octBuffer + 1, buffer);

    setString(octBuffer);
    delete[] buffer;
    delete[] octBuffer;
}

void OctString::wBin(ofstream& out) const {
    MyString::wBin(out);
    out.write((char*)&valid, sizeof(valid));
    out.write((char*)&decValue, sizeof(decValue));
}

void OctString::rBin(ifstream& in) {
    MyString::rBin(in);
    in.read((char*)&valid, sizeof(valid));
    in.read((char*)&decValue, sizeof(decValue));
}

void OctString::print() const {
    std::cout << data << " " << decValue << std::endl;
}