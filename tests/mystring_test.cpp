#include <gtest/gtest.h>
#include "../MyString.h"

//тест на конструктор обычный
TEST(MyStringConstructor,DefConstructor) {
    MyString s;
    EXPECT_STREQ(s.c_str(),"");
    EXPECT_EQ(s.getSize(), 0);

}

//тест на конструктор с параметром
TEST(MyStringConstructor,ParamConstructor) {
    MyString s("Hello World");
    EXPECT_STREQ(s.c_str(),"Hello World");
    EXPECT_EQ(s.getSize(), 11);

}
//тест на конструктор копирования
TEST(MyStringConstructor,CopyConstructor) {
    MyString s1("Hello World");
    MyString s2(s1);
    EXPECT_STREQ(s2.c_str(),"Hello World");
    EXPECT_EQ(s2.getSize(), 11);
}


//тест на сеттер
TEST(MyStringWork,Setter) {
    MyString s;
    s.setString("Hello World");
    EXPECT_STREQ(s.c_str(),"Hello World");
    EXPECT_EQ(s.getSize(), 11);
}
//тест на возврат копии
TEST(MyStringWork,GetCopy) {
    MyString s("Hello World");
    char* copy = s.c_str();
    EXPECT_STREQ(copy,"Hello World");
    delete copy;

}
//тест на конкатенацию включая nullptr
TEST(MyStringWork,Concat) {
    MyString s1("Hello");
    MyString s2(" World");
    MyString s3 = s1.concat(s2);
    EXPECT_STREQ(s3.c_str(), "Hello World");
    EXPECT_EQ(s3.getSize(), 11);
    MyString s4(nullptr);
    MyString s5 = s3.concat(s4);
    EXPECT_STREQ(s5.c_str(), "Hello World");
    EXPECT_EQ(s5.getSize(), 11);
}

TEST(MyStringWork,FindSubstring) {
    MyString s1("Hello World");
    EXPECT_EQ(s1.findSubStr("xyz"), -1);
    EXPECT_EQ(s1.findSubStr("World"), 6);
    EXPECT_EQ(s1.findSubStr(""), -1);

}

TEST(MyStringWork,GetLength) {
    MyString s1("Hello World");
    EXPECT_EQ(s1.getSize(), 11);
}

//тест статического счётчика объектов
TEST(MyStringWork, ObjectCount) {
    int before = MyString::getObjectCount();
    {
        MyString s1("one");
        MyString s2("two");
        EXPECT_EQ(MyString::getObjectCount(), before + 2);
    }
    // После выхода из блока объекты уничтожены
    EXPECT_EQ(MyString::getObjectCount(), before);
}

//операторы

TEST(MyStringOperators,PlusOperator) {
    MyString s1("Hello");
    MyString s2("World");
    MyString res1 = s1 + s2;
    EXPECT_STREQ(res1.c_str(), "HelloWorld");

    MyString s4("My");
    MyString s5("Name");
    MyString res2 = s4 + " " + s5 + " " + "is" + " " + "Vlad";
    EXPECT_STREQ(res2.c_str(), "My Name is Vlad");

}

TEST(MyStringOperators, AssignmentOperator) {
    MyString s1("1");
    MyString s2("2");
    MyString s3("3");
    MyString s4 = s1 = s2 = s3;
    EXPECT_STREQ(s4.c_str(), "3");
}

TEST(MyStringOperators,EqualityOperator) {
    MyString s1("apple");
    MyString s2("Apple");
    EXPECT_EQ((s1 == s2), 0);

    MyString s3("dog");
    MyString s4("dog");
    EXPECT_EQ((s3 == s4),1);

    MyString s5("hello");
    MyString s6("dkwokdwokdwok");
    EXPECT_EQ((s5 == s6),0);
}

TEST(MyStringOperators,InequalityOperator) {
    MyString s1("apple");
    MyString s2("Apple");
    EXPECT_EQ((s1 != s2), 1);

    MyString s3("dog");
    MyString s4("dog");
    EXPECT_EQ((s3 != s4),0);

    MyString s5("hello");
    MyString s6("dkwokdwokdwok");
    EXPECT_EQ((s5 != s6),1);
}

TEST(MyStringOperators, LessThanOperator) {
    MyString s1("banana");
    MyString s2("carrot");
    EXPECT_EQ((s1 < s2), 1);

    MyString s3("house");
    MyString s4("window");
    EXPECT_EQ((s3 < s4), 1);

    MyString s5("orange");
    MyString s6("apple");
    EXPECT_EQ((s5 < s6), 0);

    MyString s7("cat");
    MyString s8("dog");
    EXPECT_EQ((s7 < s8), 1);

    MyString s9("sun");
    MyString s10("moon");
    EXPECT_EQ((s9 < s10), 0);

    MyString s11("book");
    MyString s12("book");
    EXPECT_EQ((s11 < s12), 0);
}

TEST(MyStringOperators, GreaterThanOperator) {
    MyString s1("apple");
    MyString s2("Apple");
    EXPECT_EQ((s1 > s2), 1);

    MyString s3("dog");
    MyString s4("DOG");
    EXPECT_EQ((s3 > s4), 1);

    MyString s5("Korn");
    MyString s6("Hello");
    EXPECT_EQ((s5 > s6), 1);

    MyString s7("zoo");
    MyString s8("animal");
    EXPECT_EQ((s7 > s8), 1);

    MyString s9("test");
    MyString s10("");
    EXPECT_EQ((s9 > s10), 1);

    MyString s11("equal");
    MyString s12("equal");
    EXPECT_EQ((s11 > s12), 0);
}

//тест на <<
TEST(MyStringIO,OutputStream) {
    MyString s1("apple");
    std::ostringstream out;
    out << s1;
    EXPECT_STREQ("apple", out.str().c_str());
}

//тест на >>
TEST(MyStringIO, InputStream) {
    std::istringstream in("Team Spirit!");
    MyString s1;
    in >> s1;
    EXPECT_STREQ(s1.c_str(), "Team Spirit!");
    EXPECT_EQ(s1.getSize(), 12);
}

//тест записи и чтения двоичный

TEST(MyStringIO, BinaryWR) {
    const char* fileName = "test_bin.dat";
    {
        std::ofstream out(fileName, std::ios::binary | std::ios::trunc | std::ios::out);
        ASSERT_TRUE(out.is_open());
        MyString s1("FaZe");
        MyString s2("NaVi");
        MyString s3("NIP");
        wBin(out, s1);
        wBin(out, s2);
        wBin(out, s3);
    }
    {
        std::ifstream in(fileName, std::ios::binary | std::ios::in);
        ASSERT_TRUE(in.is_open());
        MyString s1;
        MyString s2;
        MyString s3;
        rBin(in, s1);
        rBin(in, s2);
        rBin(in, s3);
        EXPECT_STREQ(s1.c_str(), "FaZe");
        EXPECT_STREQ(s2.c_str(), "NaVi");
        EXPECT_STREQ(s3.c_str(), "NIP");
        EXPECT_EQ(s1.getSize(), 4);
        EXPECT_EQ(s2.getSize(), 4);
        EXPECT_EQ(s3.getSize(), 3);

    }
}

// тест на вспомогательную функцию readBinObject
TEST(MyStringIO, ReadBinObjectFunction) {
    const char* filename = "test_bin2.dat";

    {
        std::ofstream out(filename, std::ios::binary | std::ios::trunc | std::ios::out);
        MyString s1("One");
        MyString s2("Two");
        wBin(out, s1);
        wBin(out, s2);
    }

    {
        std::ifstream in(filename, std::ios::binary | std::ios::in);
        MyString s1 = readBinObject(in);
        MyString s2 = readBinObject(in);
        EXPECT_STREQ(s1.c_str(), "One");
        EXPECT_STREQ(s2.c_str(), "Two");
    }
}

// тест на пустую строку при бинарном вводе/выводе
TEST(MyStringIO, EmptyStringBinaryIO) {
    const char* filename = "test_empty.dat";
    {
        std::ofstream out(filename, std::ios::binary);
        MyString s("");
        wBin(out, s);
    }

    {
        std::ifstream in(filename, std::ios::binary);
        MyString s = readBinObject(in);
        EXPECT_STREQ(s.c_str(), "");
        EXPECT_EQ(s.getSize(), 0);
    }
}

// тест ввода с ведущими пробелами
TEST(MyStringIO, InputWithSpaces) {
    std::istringstream in("   Hello\n");
    MyString s;
    in >> s;
    EXPECT_STREQ(s.c_str(), "Hello");
    EXPECT_EQ(s.getSize(), 5);
}