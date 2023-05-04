#ifndef TESTS_H
#define TESTS_H
#include <string>
#include <vector>
#include <list>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestCaller.h>
#include "function.h"
#include "Predicate.h"


class Tests : public CppUnit::TestFixture {
public:
    void testString();
    void testVector();
    void testList();
};


#endif
