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

///////////////////////////////////////////////////////////////////////////////////////////
TEST(TreeTemplateConstChar, EmptyTreePrint) {
    Tree<const char*> t;
    EXPECT_NO_THROW(t.printTree(std::cout));
}

TEST(TreeTemplateConstChar, AddStrings) {
    Tree<const char*> t;

    EXPECT_NO_THROW(t.add("apple"));
    EXPECT_NO_THROW(t.add("banana"));
    EXPECT_NO_THROW(t.add("cherry"));

    EXPECT_STREQ(t.find("apple"), "apple");
    EXPECT_STREQ(t.find("banana"), "banana");
    EXPECT_STREQ(t.find("cherry"), "cherry");
}

TEST(TreeTemplateConstChar, RemoveStrings) {
    Tree<const char*> t;

    EXPECT_NO_THROW(t.add("date"));
    EXPECT_NO_THROW(t.add("banana"));
    EXPECT_NO_THROW(t.add("fig"));
    EXPECT_NO_THROW(t.add("apple"));
    EXPECT_NO_THROW(t.add("cherry"));
    EXPECT_NO_THROW(t.add("elderberry"));
    EXPECT_NO_THROW(t.add("grape"));

    // удаляем лист
    t.remove("grape");
    EXPECT_EQ(t.find("grape"), nullptr);

    // удаляем узел с двумя потомками
    t.remove("banana");
    EXPECT_EQ(t.find("banana"), nullptr);

    // удаляем узел с одним потомком
    t.remove("fig");
    EXPECT_EQ(t.find("fig"), nullptr);

    EXPECT_NO_THROW(t.printTree(std::cout));
}

TEST(TreeTemplateConstChar, FileOutputWithStrings) {
    Tree<const char*> t;

    t.add("apple");
    t.add("banana");
    t.add("cherry");
    t.add("date");
    t.add("elderberry");

    const std::string filename = "tree_const_char_output.txt";

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

TEST(TreeTemplateConstChar, ClearTree) {
    Tree<const char*> t;
    t.add("one");
    t.add("two");
    t.add("three");

    EXPECT_NO_THROW(t.clear());
    EXPECT_THROW(t.find("one"), std::logic_error);
}

TEST(TreeTemplateConstChar, RemoveFromEmptyThrows) {
    Tree<const char*> t;
    EXPECT_THROW(t.remove("test"), std::logic_error);
}

TEST(TreeTemplateConstChar, FindInEmptyThrows) {
    Tree<const char*> t;
    EXPECT_THROW(t.find("hello"), std::logic_error);
}

TEST(TreeTemplateConstChar, AddValidStrings) {
    Tree<const char*> t;
    EXPECT_NO_THROW(t.add("abc"));
    EXPECT_NO_THROW(t.add("def"));
    EXPECT_NO_THROW(t.add(""));
}

TEST(TreeTemplateConstChar, DuplicateInsertIgnored) {
    Tree<const char*> t;
    t.add("hello");
    t.add("hello"); // дубликат должен игнорироваться

    const char* found = t.find("hello");
    ASSERT_NE(found, nullptr);
    EXPECT_STREQ(found, "hello");
}

TEST(TreeTemplateConstChar, PrintStrings) {
    Tree<const char*> t;

    t.add("alpha");
    t.add("beta");
    t.add("gamma");
    t.add("delta");

    EXPECT_NO_THROW(t.printTree(std::cout));
}

TEST(TreeTemplateConstChar, CaseSensitiveComparison) {
    Tree<const char*> t;

    t.add("Apple");
    t.add("apple");
    t.add("BANANA");
    t.add("banana");

    EXPECT_STREQ(t.find("Apple"), "Apple");
    EXPECT_STREQ(t.find("apple"), "apple");
    EXPECT_STREQ(t.find("BANANA"), "BANANA");
    EXPECT_STREQ(t.find("banana"), "banana");

    EXPECT_EQ(t.find("APPLE"), nullptr); // разный регистр
}

TEST(TreeTemplateConstChar, SpecialCharacters) {
    Tree<const char*> t;

    EXPECT_NO_THROW(t.add("hello world"));
    EXPECT_NO_THROW(t.add("test@email.com"));
    EXPECT_NO_THROW(t.add("123 numbers"));


    EXPECT_STREQ(t.find("hello world"), "hello world");
    EXPECT_STREQ(t.find("test@email.com"), "test@email.com");
    EXPECT_STREQ(t.find("123 numbers"), "123 numbers");
}