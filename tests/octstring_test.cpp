#include <gtest/gtest.h>
#include "../OctString.h"
#include <fstream>
#include <sstream>

// конструктор по умолчанию
TEST(OctStringConstructor, DefaultConstructor) {
    OctString s;
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_EQ(s.getSize(), 0);
    EXPECT_TRUE(s.isValidOct());
    EXPECT_EQ(s.toDec(), 0);
}

// валидная восьмеричная строка (начинается с 0)
TEST(OctStringConstructor, ParamConstructorValid) {
    OctString s("07");
    EXPECT_STREQ(s.c_str(), "07");
    EXPECT_TRUE(s.isValidOct());
    EXPECT_EQ(s.toDec(), 7);
}

// невалидная строка не с нуля
TEST(OctStringConstructor, ParamConstructorInvalidStart) {
    OctString s("89");
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_TRUE(s.isValidOct());
    EXPECT_EQ(s.toDec(), 0);
}

// невалидная строка с несколькими начальными нулями
TEST(OctStringConstructor, ParamConstructorInvalidDoubleZero) {
    OctString s("000");
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_TRUE(s.isValidOct());
    EXPECT_EQ(s.toDec(), 0);
}

// конструктор копирования
TEST(OctStringConstructor, CopyConstructor) {
    OctString s1("05");
    OctString s2(s1);
    EXPECT_STREQ(s2.c_str(), "05");
    EXPECT_TRUE(s2.isValidOct());
    EXPECT_EQ(s2.toDec(), 5);
}

// конструктор перемещения
TEST(OctStringConstructor, MoveConstructor) {
    OctString s1("012");
    OctString s2(std::move(s1));
    EXPECT_STREQ(s2.c_str(), "012");
    EXPECT_TRUE(s2.isValidOct());
    EXPECT_EQ(s2.toDec(), 10);
}

// setString с валидной строкой
TEST(OctStringWork, SetStringValid) {
    OctString s;
    s.setString("06");
    EXPECT_STREQ(s.c_str(), "06");
    EXPECT_TRUE(s.isValidOct());
    EXPECT_EQ(s.toDec(), 6);
}

// setString с невалидной строкой
TEST(OctStringWork, SetStringInvalid) {
    OctString s;
    s.setString("123");
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_TRUE(s.isValidOct());
    EXPECT_EQ(s.toDec(), 0);
}

// конкатенация двух валидных строк
TEST(OctStringWork, ConcatValid) {
    OctString s1("01");
    OctString s2("02");
    OctString s3 = s1.concat(s2);
    EXPECT_STREQ(s3.c_str(), "0102");
    EXPECT_TRUE(s3.isValidOct());
    EXPECT_EQ(s3.toDec(), 66);
}

// конкатенация с невалидной (после очистки)
TEST(OctStringWork, ConcatWithInvalid) {
    OctString s1("01");
    OctString s2("99");
    OctString s3 = s1.concat(s2);
    EXPECT_STREQ(s3.c_str(), "01");
    EXPECT_TRUE(s3.isValidOct());
    EXPECT_EQ(s3.toDec(), 1);
}

// оператор +
TEST(OctStringOperators, PlusOperator) {
    OctString s1("03");
    OctString s2("04");
    OctString s3 = s1 + s2;
    EXPECT_STREQ(s3.c_str(), "0304");
    EXPECT_TRUE(s3.isValidOct());
    EXPECT_EQ(s3.toDec(), 196);
}

// копирующее присваивание
TEST(OctStringOperators, AssignmentCopy) {
    OctString s1("07");
    OctString s2;
    s2 = s1;
    EXPECT_STREQ(s2.c_str(), "07");
    EXPECT_TRUE(s2.isValidOct());
    EXPECT_EQ(s2.toDec(), 7);
}

// перемещающее присваивание
TEST(OctStringOperators, AssignmentMove) {
    OctString s1("013");
    OctString s2;
    s2 = std::move(s1);
    EXPECT_STREQ(s2.c_str(), "013");
    EXPECT_TRUE(s2.isValidOct());
    EXPECT_EQ(s2.toDec(), 11);
}

// toDec и fromDec
TEST(OctStringWork, FromDecToDec) {
    OctString s;
    s.fromDec(64);
    EXPECT_STREQ(s.c_str(), "0100");
    EXPECT_TRUE(s.isValidOct());
    EXPECT_EQ(s.toDec(), 64);
}

TEST(OctStringWork, FromInvDecToStr) {
    try {
        OctString s;
        s.fromDec(-12);
        FAIL() << "Expected logic_error exception";
    }
    catch (std::logic_error& e) {
        EXPECT_STREQ(e.what(), "OctString::fromDec():logic_error negative number not allowed");
    }
    catch (std::exception& e) {
        FAIL() << "Expected logic_error exception, but got: " << e.what();
    }
    catch (...) {
        FAIL() << "Expected fromDec() logic_error exception, but got unknown exception type";
    }

}

TEST(OctStringWork, InvalidStringBecomesEmpty) {
    OctString s("123");   // невалидно, поэтому должно превратиться в ""
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_EQ(s.toDec(), 0);
}

// fromDec(0) даёт пустую строку
TEST(OctStringWork, FromDecZero) {
    OctString s;
    s.fromDec(0);
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_TRUE(s.isValidOct());
    EXPECT_EQ(s.toDec(), 0);
}

// бинарные операции
TEST(OctStringIO, BinaryWriteRead) {
    const char* filename = "octstring_test.bin";

    {   // запись
        std::ofstream out(filename, std::ios::binary);
        ASSERT_TRUE(out.is_open());
        OctString s("07");
        s.wBin(out);
    }

    {   // чтение
        std::ifstream in(filename, std::ios::binary);
        ASSERT_TRUE(in.is_open());
        OctString s;
        s.rBin(in);
        EXPECT_STREQ(s.c_str(), "07");
        EXPECT_TRUE(s.isValidOct());
        EXPECT_EQ(s.toDec(), 7);
    }
}

