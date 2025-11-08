#include <gtest/gtest.h>
#include "../TreeTemplate.h"
#include "../MyString.h"


TEST(TreeTemplate, EmptyTreePrint) {
    Tree<int> t;
    EXPECT_NO_THROW(t.printTree(std::cout));
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

    EXPECT_NO_THROW(t.printTree(std::cout));
}

TEST(TreeTemplate, FileOutput) {
    Tree<int> t;

    t.add(50);
    t.add(30);
    t.add(70);
    t.add(20);
    t.add(40);
    t.add(60);
    t.add(80);

    const std::string filename = "tree_output.txt";

    {
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        t.printTree(fout);
    }

    std::ifstream fin(filename);
    ASSERT_TRUE(fin.is_open());

    std::string firstLine;
    std::getline(fin, firstLine);
    EXPECT_FALSE(firstLine.empty());

    fin.close();


}

TEST(TreeTemplate, FileOutputWithStrings) {
    Tree<MyString> t;

    t.add(MyString("apple"));
    t.add(MyString("banana"));
    t.add(MyString("cherry"));
    t.add(MyString("date"));
    t.add(MyString("elderberry"));

    const std::string filename = "tree_string_output.txt";

    {
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        t.printTree(fout);
    }

    std::ifstream fin(filename);
    ASSERT_TRUE(fin.is_open());

    std::string content;
    std::string line;
    while (std::getline(fin, line)) {
        content += line + "\n";
    }
    EXPECT_FALSE(content.empty());

    fin.close();


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
    t.printTree(std::cout);
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

    EXPECT_NO_THROW(ti.printTree(std::cout));
    EXPECT_NO_THROW(td.printTree(std::cout));
    EXPECT_NO_THROW(ts.printTree(std::cout));
}
