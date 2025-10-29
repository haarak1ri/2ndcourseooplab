#pragma once
#include "MyString.h"

class OctString : public MyString {
public:
    OctString();
    OctString(const char* str);
    OctString(const OctString& otherStr);
    OctString(OctString&& otherStr) noexcept;

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

protected:
    bool valid;
    int decValue;


};