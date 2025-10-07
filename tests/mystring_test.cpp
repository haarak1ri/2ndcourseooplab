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