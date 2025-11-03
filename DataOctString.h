#pragma once
#include "OctString.h"
#include <cstring>
#include <ctime>
#include <cstdio>

class DataOctString : public OctString {
public:
    DataOctString();
    DataOctString(const char* str);
    DataOctString(const DataOctString& otherStr);
    DataOctString(DataOctString&& otherStr) noexcept;
    ~DataOctString() override;

    const char* getDate() const;
    void setString(const char* str);
    DataOctString concat(const DataOctString& otherStr) const;
    DataOctString operator+(const DataOctString& otherStr);
    DataOctString& operator=(const DataOctString& otherStr);
    DataOctString& operator=(DataOctString&& otherStr) noexcept;

    void wBin(ofstream& out) const override;
    void rBin(ifstream& in) override;
    void print() const override;

private:
    char creationDate[20];
};