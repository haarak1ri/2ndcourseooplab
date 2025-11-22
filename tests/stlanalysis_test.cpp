#include <gtest/gtest.h>
#include "..\MyString.h"
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <filesystem>
#include <queue>
#include <set>
#include <unordered_set>

using namespace std;
using namespace chrono;

vector<int> getNRange() {
    vector<int> nRange;
    for(int i = 100000; i <= 5000000; i += 100000) {
        nRange.push_back(i);
    }
    return nRange;
}


void clearOutputFile() {
    ofstream output("output.csv", ios::trunc);
    if (output.is_open()) {
        output << "Name of Container,Number of N (elements),Add element,Find element,Delete element\n";
        output.close();
        cout << "Файл output.csv очищен" << endl;
    }
}
TEST(StlContainers, ClearFile) {
    clearOutputFile();
}
void writeToFile(const string& stlContName, int N, double addTime, double findTime,
                 double deleteTime ) {

    bool fileExistence = filesystem::exists("output.csv");
    ofstream output("output.csv", ios::app);

    if (!fileExistence) {
        output << "Name of Container,Number of N (elements),Add element,Find element,Delete element\n";
    }

    output << "\"" << stlContName << "\","
           << N << ","
           << fixed << setprecision(9)
           << addTime << ","
           << findTime << ","
           << deleteTime << "\n";
}


TEST(StlContainers, QueueInt) {
    vector<int> nRange = getNRange();
    for (int n : nRange) {
        cout << "\n" << "Queue<int>; N: " << n << endl;


        queue<int> intQueue;


        // ADD
        auto s1 = high_resolution_clock::now();
        for (int i = 0; i < n; ++i) intQueue.push(i);
        auto e1 = high_resolution_clock::now();
        double addTime = duration_cast<nanoseconds>(e1 - s1).count() * 1e-9;

        // очередь не имеет поиска, делаем перебор
        auto s2 = high_resolution_clock::now();
        {
            queue<int> copy = intQueue;
            int target = -1;
            bool found = false;

            while (!copy.empty()) {
                if (copy.front() == target) { found = true; break; }
                copy.pop();
            }
        }
        auto e2 = high_resolution_clock::now();
        double findTime = duration_cast<nanoseconds>(e2 - s2).count() * 1e-9;

        // DELETE
        auto s3 = high_resolution_clock::now();
        while (!intQueue.empty()) intQueue.pop();
        auto e3 = high_resolution_clock::now();
        double deleteTime = duration_cast<nanoseconds>(e3 - s3).count() * 1e-9;

        cout << "addTime: " << addTime << endl;
        cout << "findTime: " << findTime << endl;
        cout << "deleteTime: "<< deleteTime << endl;
        writeToFile("Queue<int>", n, addTime, findTime, deleteTime);
    }
}

TEST(StlContainers, QueueMyString) {
    vector<int> nRange = getNRange();
    for (int n : nRange) {
        cout << "\n" << "Queue<MyString>; N: " << n << endl;

        queue<MyString> strQueue;

        //add
        auto s1 = high_resolution_clock::now();
        for (int i = 0; i < n; ++i) {
            string temp = "string";
            temp += to_string(i);
            strQueue.push(MyString(temp.c_str()));
        }
        auto e1 = high_resolution_clock::now();
        double addTime = duration_cast<nanoseconds>(e1 - s1).count() * 1e-9;

        // опять ручной find
        auto s2 = high_resolution_clock::now();
        {
            queue<MyString> copy = strQueue;
            MyString target("not_existing_string"); // гарантированно отсутствует
            bool found = false;

            while (!copy.empty()) {
                if (copy.front() == target) { found = true; break; }
                copy.pop();
            }
        }
        auto e2 = high_resolution_clock::now();
        double findTime = duration_cast<nanoseconds>(e2 - s2).count() * 1e-9;

        // delete
        auto s3 = high_resolution_clock::now();
        while (!strQueue.empty()) strQueue.pop();
        auto e3 = high_resolution_clock::now();
        double deleteTime = duration_cast<nanoseconds>(e3 - s3).count() * 1e-9;


        cout << "addTime: " << addTime << endl;
        cout << "findTime: " << findTime << endl;
        cout << "deleteTime: " << deleteTime << endl;

        writeToFile("Queue<MyString>", n, addTime, findTime, deleteTime);
    }
}

TEST(StlContainers, SetInt) {
    vector<int> nRange = getNRange();
    for (int n : nRange) {
        cout << "\n" << "Set<int>; N: " << n << endl;

        set<int> intSet;


        auto s1 = high_resolution_clock::now();
        for (int i = 0; i < n; ++i) intSet.insert(i);
        auto e1 = high_resolution_clock::now();
        double addTime = duration_cast<nanoseconds>(e1 - s1).count() * 1e-9;

        //find
        auto s2 = high_resolution_clock::now();
        int target = n - 1;
        auto it = intSet.find(target);
        auto e2 = high_resolution_clock::now();
        double findTime = duration_cast<nanoseconds>(e2 - s2).count() * 1e-9;

        // DELETE
        auto s3 = high_resolution_clock::now();
        intSet.clear();
        auto e3 = high_resolution_clock::now();
        double deleteTime = duration_cast<nanoseconds>(e3 - s3).count() * 1e-9;

        cout << "addTime: "   << addTime   << endl;
        cout << "findTime: "  << findTime  << endl;
        cout << "deleteTime: "<< deleteTime << endl;

        writeToFile("Set<int>", n, addTime, findTime, deleteTime);
    }
}

TEST(StlContainers, SetMyString) {
    vector<int> nRange = getNRange();
    for (int n : nRange) {
        cout << "\n"<< "Set<MyString>; N: " << n << endl;

        set<MyString> strSet;

        // ADD
        auto s1 = high_resolution_clock::now();
        for (int i = 0; i < n; ++i) {
            string temp = "txt";
            temp += to_string(i);
            strSet.insert(MyString(temp.c_str()));
        }
        auto e1 = high_resolution_clock::now();
        double addTime = duration_cast<nanoseconds>(e1 - s1).count() * 1e-9;

        // FIND
        MyString target(("txt" + to_string(n - 1)).c_str());

        auto s2 = high_resolution_clock::now();
        auto it = strSet.find(target);
        auto e2 = high_resolution_clock::now();
        double findTime = duration_cast<nanoseconds>(e2 - s2).count() * 1e-9;

        // DELETE
        auto s3 = high_resolution_clock::now();
        strSet.clear();
        auto e3 = high_resolution_clock::now();
        double deleteTime = duration_cast<nanoseconds>(e3 - s3).count() * 1e-9;

        cout << "addTime: "   << addTime   << endl;
        cout << "findTime: "  << findTime  << endl;
        cout << "deleteTime: "<< deleteTime << endl;

        writeToFile("Set<MyString>", n, addTime, findTime, deleteTime);
    }
}

TEST(StlContainers, UnorderedSetInt) {
    vector<int> nRange = getNRange();
    for (int n : nRange) {
        cout << "\n" << "UnorderedSet<int>; N: " << n << endl;

        unordered_set<int> intUnorderedSet;

        // ADD
        auto s1 = high_resolution_clock::now();
        for (int i = 0; i < n; ++i) intUnorderedSet.insert(i);
        auto e1 = high_resolution_clock::now();
        double addTime = duration_cast<nanoseconds>(e1 - s1).count() * 1e-9;

        // FIND
        auto s2 = high_resolution_clock::now();
        int target = n - 1;
        auto it = intUnorderedSet.find(target);
        auto e2 = high_resolution_clock::now();
        double findTime = duration_cast<nanoseconds>(e2 - s2).count() * 1e-9;

        // DELETE
        auto s3 = high_resolution_clock::now();
        intUnorderedSet.clear();
        auto e3 = high_resolution_clock::now();
        double deleteTime = duration_cast<nanoseconds>(e3 - s3).count() * 1e-9;

        cout << "addTime: " << addTime << endl;
        cout << "findTime: " << findTime << endl;
        cout << "deleteTime: "<< deleteTime << endl;
        writeToFile("UnorderedSet<int>", n, addTime, findTime, deleteTime);
    }
}

TEST(StlContainers, UnorderedSetMyString) {
    vector<int> nRange = getNRange();
    for (int n : nRange) {
        cout << "\n"<< "UnorderedSet<MyString>; N: " << n << endl;

        struct MyStringHash {
            size_t operator()(const MyString& s) const {

                const char* str = s.c_str();
                size_t hash = 0;
                for (size_t i = 0; str[i] != '\0'; ++i) {
                    hash = hash * 31 + str[i];
                }
                return hash;
            }
        };
        unordered_set<MyString, MyStringHash> strUnorderedSet;

        // ADD
        auto s1 = high_resolution_clock::now();
        for (int i = 0; i < n; ++i) {
            string temp = "txt";
            temp += to_string(i);
            strUnorderedSet.insert(MyString(temp.c_str()));
        }
        auto e1 = high_resolution_clock::now();
        double addTime = duration_cast<nanoseconds>(e1 - s1).count() * 1e-9;

        // FIND
        MyString target(("txt" + to_string(n - 1)).c_str());
        auto s2 = high_resolution_clock::now();
        auto it = strUnorderedSet.find(target);
        auto e2 = high_resolution_clock::now();
        double findTime = duration_cast<nanoseconds>(e2 - s2).count() * 1e-9;

        // DELETE
        auto s3 = high_resolution_clock::now();
        strUnorderedSet.clear();
        auto e3 = high_resolution_clock::now();
        double deleteTime = duration_cast<nanoseconds>(e3 - s3).count() * 1e-9;

        cout << "addTime: " << addTime << endl;
        cout << "findTime: " << findTime << endl;
        cout << "deleteTime: "<< deleteTime << endl;

        writeToFile("UnorderedSet<MyString>", n, addTime, findTime, deleteTime);
    }
}
