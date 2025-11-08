#include <gtest/gtest.h>
#include "../Tree.h"
#include "../MyString.h"
#include "../OctString.h"
#include "../DataOctString.h"

TEST(TreeWork,EmptyTreePrint) {
    Tree t;
    EXPECT_NO_THROW(t.printTree(std::cout));
}

TEST(Tree, AddDifferentObjects) {
    Tree t;

    MyString s1("hello");
    OctString s2("0123");
    DataOctString s3("045");

    EXPECT_NO_THROW(t.add(&s1));
    EXPECT_NO_THROW(t.add(&s2));
    EXPECT_NO_THROW(t.add(&s3));
    t.printTree(std::cout);

    EXPECT_STREQ(t.find("hello")->c_str(), "hello");
    EXPECT_STREQ(t.find("0123")->c_str(), "0123");
    EXPECT_STREQ(t.find("045")->c_str(), "045");
}


TEST(Tree, FileOutput) {
    Tree t;
    MyString s1("A");
    OctString s2("012");
    DataOctString s3("077");

    t.add(&s1);
    t.add(&s2);
    t.add(&s3);

    const std::string filename = "tree_output.txt";
    {
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        t.printTree(fout);
    }


}



//проверика на работоспособность octstring
TEST(Tree, OctTest) {
    Tree t;
    t.add(new OctString("0123"));
    t.add(new OctString("045"));

    MyString* temp1 = t.find("0123");
    ASSERT_NE(temp1, nullptr);

    OctString* temp2 = static_cast<OctString*>(temp1);
    EXPECT_EQ(temp2->toDec(), 83);

}

TEST(Tree,REMOVE) {
    Tree t;

    OctString s1("01");
    DataOctString s2("02");
    OctString s3("03");
    DataOctString s4("04");
    OctString s5("05");
    DataOctString s6("06");
    DataOctString s7("07");


    EXPECT_NO_THROW(t.add(&s4));
    EXPECT_NO_THROW(t.add(&s2));
    EXPECT_NO_THROW(t.add(&s6));
    EXPECT_NO_THROW(t.add(&s1));
    EXPECT_NO_THROW(t.add(&s3));
    EXPECT_NO_THROW(t.add(&s5));
    EXPECT_NO_THROW(t.add(&s7));



    t.remove(s7);//лист
    EXPECT_EQ(t.find(s7), nullptr);
    t.remove(s2);// 2 потомка
    EXPECT_EQ(t.find(s2), nullptr);
    t.remove(s3); // 1 потомок
    EXPECT_EQ(t.find(s3), nullptr);

    t.printTree(std::cout);

}

TEST(Tree, ClearTree) {
    Tree t;
    t.add(new MyString("01"));
    t.add(new OctString("0123"));
    t.add(new DataOctString("045"));

    EXPECT_NO_THROW(t.clear());
    EXPECT_THROW(t.find("01"), std::logic_error);
}

TEST(Tree, RemoveFromEmptyThrows) {
    Tree t;
    EXPECT_THROW(t.remove(MyString("abcd")), std::logic_error);
}

TEST(Tree, FindInEmptyThrows) {
    Tree t;
    EXPECT_THROW(t.find("test"), std::logic_error);
}

TEST(Tree, AddNullptrThrows) {
    Tree t;
    EXPECT_THROW(t.add(nullptr), std::invalid_argument);
}
TEST(Tree, DuplicateInsertGoesRight) {
    Tree t;
    MyString s1("abc");
    MyString s2("abc");

    t.add(&s1);
    t.add(&s2);


    MyString* found = t.find("abc");
    ASSERT_NE(found, nullptr);

}

TEST(Tree, PolymorphismCheckPrint) {
    Tree t;
    t.add(new MyString("023"));
    t.add(new OctString("0123"));
    t.add(new DataOctString("045"));



    EXPECT_NO_THROW(t.printTree(std::cout));
}