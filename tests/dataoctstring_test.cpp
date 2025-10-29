#include <gtest/gtest.h>
#include "../DataOctString.h"
#include <fstream>

// конструктор по умолчанию
TEST(DataOctStringConstructor, DefaultConstructor) {
    DataOctString s;
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_TRUE(s.isValidOct());
    EXPECT_EQ(s.toDec(), 0);
    EXPECT_NE(s.getDate(), nullptr);
}

// конструктор с валидной строкой (один ноль)
TEST(DataOctStringConstructor, ParamConstructorValidSingleZero) {
    DataOctString s("0");
    EXPECT_STREQ(s.c_str(), "0");
    EXPECT_TRUE(s.isValidOct());
    EXPECT_EQ(s.toDec(), 0);
}

// конструктор с валидной восьмеричной строкой
TEST(DataOctStringConstructor, ParamConstructorValidOctal) {
    DataOctString s("012");
    EXPECT_STREQ(s.c_str(), "012");
    EXPECT_TRUE(s.isValidOct());
    EXPECT_EQ(s.toDec(), 10);
}

// конструктор с невалидной строкой (без нуля в начале)
TEST(DataOctStringConstructor, ParamConstructorInvalidNoZero) {
    DataOctString s("89");
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_TRUE(s.isValidOct());
    EXPECT_EQ(s.toDec(), 0);
}

// конструктор с невалидной строкой (несколько нулей)
TEST(DataOctStringConstructor, ParamConstructorInvalidDoubleZero) {
    DataOctString s("007");
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_TRUE(s.isValidOct());
    EXPECT_EQ(s.toDec(), 0);
}

// конструктор копирования
TEST(DataOctStringConstructor, CopyConstructor) {
    DataOctString s1("05");
    DataOctString s2(s1);
    EXPECT_STREQ(s2.c_str(), "05");
    EXPECT_TRUE(s2.isValidOct());
    EXPECT_EQ(s2.toDec(), 5);
    EXPECT_STREQ(s1.getDate(), s2.getDate());
}

// конструктор перемещения
TEST(DataOctStringConstructor, MoveConstructor) {
    DataOctString s1("013");
    DataOctString s2(std::move(s1));
    EXPECT_STREQ(s2.c_str(), "013");
    EXPECT_TRUE(s2.isValidOct());
    EXPECT_EQ(s2.toDec(), 11);
    EXPECT_NE(s2.getDate(), nullptr);
}

// setString с валидной строкой
TEST(DataOctStringWork, SetStringValid) {
    DataOctString s;
    s.setString("06");
    EXPECT_STREQ(s.c_str(), "06");
    EXPECT_TRUE(s.isValidOct());
    EXPECT_EQ(s.toDec(), 6);
}

// setString с невалидной строкой
TEST(DataOctStringWork, SetStringInvalid) {
    DataOctString s;
    s.setString("123");
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_TRUE(s.isValidOct());
    EXPECT_EQ(s.toDec(), 0);
}

// конкатенация двух валидных строк
TEST(DataOctStringWork, ConcatValid) {
    DataOctString s1("01");
    DataOctString s2("02");
    DataOctString s3 = s1.concat(s2);
    EXPECT_STREQ(s3.c_str(), "0102");
    EXPECT_TRUE(s3.isValidOct());
    EXPECT_EQ(s3.toDec(), 66);
}

// конкатенация с невалидной строкой
TEST(DataOctStringWork, ConcatWithInvalid) {
    DataOctString s1("01");
    DataOctString s2("99");
    DataOctString s3 = s1.concat(s2);
    EXPECT_STREQ(s3.c_str(), "01");
    EXPECT_TRUE(s3.isValidOct());
    EXPECT_EQ(s3.toDec(), 1);
}

// конкатенация создающая невалидную строку
TEST(DataOctStringWork, ConcatCreatesInvalid) {
    DataOctString s1("0");
    DataOctString s2("0");
    DataOctString s3 = s1.concat(s2);
    EXPECT_STREQ(s3.c_str(), "");
    EXPECT_TRUE(s3.isValidOct());
    EXPECT_EQ(s3.toDec(), 0);
}

// оператор сложения
TEST(DataOctStringOperators, PlusOperator) {
    DataOctString s1("03");
    DataOctString s2("04");
    DataOctString s3 = s1 + s2;
    EXPECT_STREQ(s3.c_str(), "0304");
    EXPECT_TRUE(s3.isValidOct());
    EXPECT_EQ(s3.toDec(), 196);
}

// оператор присваивания копированием
TEST(DataOctStringOperators, AssignmentCopy) {
    DataOctString s1("07");
    DataOctString s2;
    s2 = s1;
    EXPECT_STREQ(s2.c_str(), "07");
    EXPECT_TRUE(s2.isValidOct());
    EXPECT_EQ(s2.toDec(), 7);
    EXPECT_STREQ(s1.getDate(), s2.getDate());
}

// оператор присваивания перемещением
TEST(DataOctStringOperators, AssignmentMove) {
    DataOctString s1("020");
    DataOctString s2;
    s2 = std::move(s1);
    EXPECT_STREQ(s2.c_str(), "020");
    EXPECT_TRUE(s2.isValidOct());
    EXPECT_EQ(s2.toDec(), 16);
    EXPECT_NE(s2.getDate(), nullptr);
}

// преобразование из десятичной системы
TEST(DataOctStringWork, FromDecToDec) {
    DataOctString s;
    s.fromDec(64);
    EXPECT_STREQ(s.c_str(), "0100");
    EXPECT_TRUE(s.isValidOct());
    EXPECT_EQ(s.toDec(), 64);
}

// преобразование нуля из десятичной системы
TEST(DataOctStringWork, FromDecZero) {
    DataOctString s;
    s.fromDec(0);
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_TRUE(s.isValidOct());
    EXPECT_EQ(s.toDec(), 0);
}

// запись и чтение в бинарный файл
TEST(DataOctStringIO, BinaryWriteRead) {
    const char* filename = "dataoct_test.bin";
    {
        std::ofstream out(filename, std::ios::binary);
        ASSERT_TRUE(out.is_open());
        DataOctString s("07");
        s.wBin(out);
    }
    {
        std::ifstream in(filename, std::ios::binary);
        ASSERT_TRUE(in.is_open());
        DataOctString s;
        s.rBin(in);
        EXPECT_STREQ(s.c_str(), "07");
        EXPECT_TRUE(s.isValidOct());
        EXPECT_EQ(s.toDec(), 7);
        EXPECT_NE(s.getDate(), nullptr);
    }
}

// проверка даты
TEST(DataOctStringWork, DateTest) {
    DataOctString s("025");
    const char* date = s.getDate();
    EXPECT_NE(date, nullptr);
    EXPECT_GT(strlen(date), 0);
}