#include "Tests.h"


void Tests::testString() {
    std::string s = "  LOREM ipsum dolor sit amet, consectetur adipiscing elit. aliquam euismod ";
    cutString(&s, isWhitespace());
    CPPUNIT_ASSERT_EQUAL(0, s.compare("LOREM ipsum dolor sit amet, consectetur adipiscing elit. aliquam euismod"));
    cutString(&s, isWhitespace());
    CPPUNIT_ASSERT_EQUAL(0, s.compare("LOREM ipsum dolor sit amet, consectetur adipiscing elit. aliquam euismod"));
    cutString(&s, isUppercase());
    CPPUNIT_ASSERT_EQUAL(0, s.compare(" ipsum dolor sit amet, consectetur adipiscing elit. aliquam euismod"));
    cutString(&s, isWhitespace());
    CPPUNIT_ASSERT_EQUAL(0, s.compare("ipsum dolor sit amet, consectetur adipiscing elit. aliquam euismod"));
    cutString(&s, isLowercase());
    CPPUNIT_ASSERT_EQUAL(0, s.compare(" dolor sit amet, consectetur adipiscing elit. aliquam "));
    cutString(&s, isWhitespace());
    CPPUNIT_ASSERT_EQUAL(0, s.compare("dolor sit amet, consectetur adipiscing elit. aliquam"));
    cutString(&s, isLowercase());
    CPPUNIT_ASSERT_EQUAL(0, s.compare(" sit amet, consectetur adipiscing elit. "));
    cutString(&s, isWhitespace());
    CPPUNIT_ASSERT_EQUAL(0, s.compare("sit amet, consectetur adipiscing elit."));
    cutString(&s, [](char c){return c == '.';});
    CPPUNIT_ASSERT_EQUAL(0, s.compare("sit amet, consectetur adipiscing elit"));
    cutString(&s, isWhitespace());
    CPPUNIT_ASSERT_EQUAL(0, s.compare("sit amet, consectetur adipiscing elit"));
}


void Tests::testVector() {
    std::vector<char> v1 = {'l', 'o', 'R', 'e', 'm'};
    std::vector<char> v2= {'R'};
    std::vector<char> v3= {};


    CPPUNIT_ASSERT(v1 != v2);
    CPPUNIT_ASSERT(v1 != v3);
    CPPUNIT_ASSERT(v2 != v3);
    cutString(&v1, isLowercase());
    CPPUNIT_ASSERT(v1 == v2);
    CPPUNIT_ASSERT(v1 != v3);
    CPPUNIT_ASSERT(v2 != v3);
    cutString(&v1, isUppercase());
    CPPUNIT_ASSERT(v1 != v2);
    CPPUNIT_ASSERT(v1 == v3);
    CPPUNIT_ASSERT(v2 != v3);
    cutString(&v2, isUppercase());
    CPPUNIT_ASSERT(v1 == v2);
    CPPUNIT_ASSERT(v1 == v3);
    CPPUNIT_ASSERT(v2 == v3);
}


void Tests::testList() {
    std::list<char> l1 = {'i', 'p', 'S', 'u', 'm'};
    std::list<char> l2 = {' ', 'i', 'p', 'S', 'u', 'm'};
    std::list<char> l3 = {'.', '.', '.', '.', '.', '.', '.', '.', '.'};

    CPPUNIT_ASSERT(l1 != l2);
    CPPUNIT_ASSERT(l1 != l3);
    CPPUNIT_ASSERT(l2 != l3);
    cutString(&l2, isWhitespace());
    CPPUNIT_ASSERT(l1 == l2);
    CPPUNIT_ASSERT(l1 != l3);
    CPPUNIT_ASSERT(l2 != l3);
    cutString(&l1, isLowercase());
    CPPUNIT_ASSERT(l1 != l2);
    CPPUNIT_ASSERT(l1 != l3);
    CPPUNIT_ASSERT(l2 != l3);
    cutString(&l2, isLowercase());
    CPPUNIT_ASSERT(l1 == l2);
    CPPUNIT_ASSERT(l1 != l3);
    CPPUNIT_ASSERT(l2 != l3);
    cutString(&l1, isUppercase());
    CPPUNIT_ASSERT(l1 != l2);
    CPPUNIT_ASSERT(l1 != l3);
    CPPUNIT_ASSERT(l2 != l3);
    cutString(&l3, [](char c){return c == '.';});
    CPPUNIT_ASSERT(l1 != l2);
    CPPUNIT_ASSERT(l1 == l3);
    CPPUNIT_ASSERT(l2 != l3);
    cutString(&l2, isUppercase());
    CPPUNIT_ASSERT(l1 == l2);
    CPPUNIT_ASSERT(l1 == l3);
    CPPUNIT_ASSERT(l2 == l3);
}


void Tests::testArray() {
    std::array<char, 3> a1({',', '\0', '.'});
    std::array<char, 3> a2({' ', 'X', '.'});
    std::array<char, 3> a3({'s', 'S', '.'});

    CPPUNIT_ASSERT(a1 != a2);
    CPPUNIT_ASSERT(a1 != a3);
    CPPUNIT_ASSERT(a2 != a3);
    cutString(&a3, isLowercase());
    CPPUNIT_ASSERT(a1 != a2);
    CPPUNIT_ASSERT(a1 != a3);
    CPPUNIT_ASSERT(a2 != a3);
    cutString(&a3, isUppercase());
    CPPUNIT_ASSERT(a1 != a2);
    CPPUNIT_ASSERT(a1 != a3);
    CPPUNIT_ASSERT(a2 != a3);
    cutString(&a2, isWhitespace());
    CPPUNIT_ASSERT(a1 != a2);
    CPPUNIT_ASSERT(a1 != a3);
    CPPUNIT_ASSERT(a2 != a3);
    cutString(&a2, isUppercase());
    CPPUNIT_ASSERT(a1 != a2);
    CPPUNIT_ASSERT(a1 != a3);
    CPPUNIT_ASSERT(a2 == a3);
    cutString(&a2, [](char c){return c == '.';});
    CPPUNIT_ASSERT(a1 != a2);
    CPPUNIT_ASSERT(a1 != a3);
    CPPUNIT_ASSERT(a2 != a3);
    cutString(&a1, [](char c){return c == '.' or c == ',';});
    CPPUNIT_ASSERT(a1 == a2);
    CPPUNIT_ASSERT(a1 != a3);
    CPPUNIT_ASSERT(a2 != a3);
    cutString(&a3, [](char c){return c == '.' or c == ',';});
    CPPUNIT_ASSERT(a1 == a2);
    CPPUNIT_ASSERT(a1 == a3);
    CPPUNIT_ASSERT(a2 == a3);

}

