#include "DataOctString.h"

DataOctString::DataOctString() : OctString() {
    time_t t = time(NULL);
    tm* timeinfo = localtime(&t);
    snprintf(creationDate, sizeof(creationDate),
         "%04d-%02d-%02d %02d:%02d",
         timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
         timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min);
}

DataOctString::DataOctString(const char* str) : OctString(str) {
    time_t t = time(NULL);
    tm* timeinfo = localtime(&t);
    snprintf(creationDate, sizeof(creationDate),
         "%04d-%02d-%02d %02d:%02d",
         timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
         timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min);
}

DataOctString::DataOctString(const DataOctString& otherStr) : OctString(otherStr) {
    strcpy(creationDate, otherStr.creationDate);
}

DataOctString::DataOctString(DataOctString&& otherStr) noexcept : OctString(std::move(otherStr)) {
    strcpy(creationDate, otherStr.creationDate);
}

DataOctString::~DataOctString() {

}

const char* DataOctString::getDate() const {
    return creationDate;
}

void DataOctString::setString(const char* str) {
    OctString::setString(str);
}

DataOctString DataOctString::concat(const DataOctString& otherStr) const {
    OctString temp = OctString::concat(otherStr);
    DataOctString result(temp.c_str());
    return result;
}

DataOctString DataOctString::operator+(const DataOctString& otherStr) {
    return this->concat(otherStr);
}

DataOctString& DataOctString::operator=(const DataOctString& otherStr) {
    if (this != &otherStr) {
        OctString::operator=(otherStr);
        strcpy(this->creationDate, otherStr.creationDate);
    }
    return *this;
}

DataOctString& DataOctString::operator=(DataOctString&& otherStr) noexcept {
    if (this != &otherStr) {
        OctString::operator=(std::move(otherStr));
        strcpy(this->creationDate, otherStr.creationDate);
    }
    return *this;
}

void DataOctString::wBin(ofstream& out) const {
    OctString::wBin(out);
    out.write(creationDate, sizeof(creationDate));
}

void DataOctString::rBin(ifstream& in) {
    OctString::rBin(in);
    in.read(creationDate, sizeof(creationDate));
}

std::string DataOctString::toString() const {
    std::ostringstream oss;
    oss << OctString::toString();
    oss << " | created: " << creationDate;
    return oss.str();
}