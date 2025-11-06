#include <gtest/gtest.h>
#include "../TreeTemplate.h"
#include "../MyString.h"


TEST(TreeTemplate, EmptyTreePrint) {
    Tree<int> t;
    EXPECT_NO_THROW(t.printTree());
}


TEST(TreeTemplate, AddDifferentTypes) {
    Tree<int> ti;
    Tree<double> td;
    Tree<MyString> ts;

    EXPECT_NO_THROW(ti.add(10));
    EXPECT_NO_THROW(td.add(3.14));
    EXPECT_NO_THROW(ts.add(MyString("hello")));

    EXPECT_EQ(*ti.find(10), 10);
    EXPECT_DOUBLE_EQ(*td.find(3.14), 3.14);
    EXPECT_STREQ(ts.find(MyString("hello"))->c_str(), "hello");
}


TEST(TreeTemplate, RemoveElements) {
    Tree<int> t;

    EXPECT_NO_THROW(t.add(4));
    EXPECT_NO_THROW(t.add(2));
    EXPECT_NO_THROW(t.add(6));
    EXPECT_NO_THROW(t.add(1));
    EXPECT_NO_THROW(t.add(3));
    EXPECT_NO_THROW(t.add(5));
    EXPECT_NO_THROW(t.add(7));

    // удаляем лист
    t.remove(7);
    EXPECT_EQ(t.find(7), nullptr);

    // удаляем узел с двумя потомками
    t.remove(2);
    EXPECT_EQ(t.find(2), nullptr);

    // удаляем узел с одним потомком
    t.remove(6);
    EXPECT_EQ(t.find(6), nullptr);

    EXPECT_NO_THROW(t.printTree());
}


TEST(TreeTemplate, ClearTree) {
    Tree<MyString> t;
    t.add(MyString("01"));
    t.add(MyString("0123"));
    t.add(MyString("045"));

    EXPECT_NO_THROW(t.clear());
    EXPECT_THROW(t.find(MyString("01")), std::logic_error);
}


//удаление из пустого дерева

TEST(TreeTemplate, RemoveFromEmptyThrows) {
    Tree<int> t;
    EXPECT_THROW(t.remove(5), std::logic_error);
}


TEST(TreeTemplate, FindInEmptyThrows) {
    Tree<double> t;
    EXPECT_THROW(t.find(3.14), std::logic_error);
}


TEST(TreeTemplate, AddValidValues) {
    Tree<MyString> t;
    EXPECT_NO_THROW(t.add(MyString("abc")));
    EXPECT_NO_THROW(t.add(MyString("def")));
}


//проверка вставки дубликата — идут вправо

TEST(TreeTemplate, DuplicateInsertGoesRight) {
    Tree<int> t;
    t.add(5);
    t.add(5);

    const int* found = t.find(5);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(*found, 5);
    t.printTree();
}


TEST(TreeTemplate, PrintVariousTypes) {
    Tree<int> ti;
    Tree<double> td;
    Tree<MyString> ts;

    ti.add(10);
    ti.add(5);
    ti.add(15);

    td.add(2.71);
    td.add(3.14);
    td.add(1.41);

    ts.add(MyString("alpha"));
    ts.add(MyString("beta"));
    ts.add(MyString("gamma"));

    EXPECT_NO_THROW(ti.printTree());
    EXPECT_NO_THROW(td.printTree());
    EXPECT_NO_THROW(ts.printTree());
}
