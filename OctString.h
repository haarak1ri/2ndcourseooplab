#pragma once
#include "MyString.h"
#include <sstream>

class OctString : public MyString {
public:
    OctString();
    OctString(const char* str);
    OctString(const OctString& otherStr);
    OctString(OctString&& otherStr) noexcept;
    ~OctString() override;

    bool isValidOct() const;
    void setString(const char* str) ;//изменение строки
    OctString concat(const OctString& otherStr) const;
    OctString operator+(const OctString& otherStr);
    OctString& operator=(const OctString& otherStr);
    OctString& operator=(OctString&& otherStr);


    int toDec();
    void fromDec(int value);

    void wBin(ofstream& out) const override;
    void rBin(ifstream& in) override;
    //void print() const override;
    std::string toString() const override;

protected:
    bool valid;
    int decValue;


};