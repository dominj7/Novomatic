#include "Tests.h"


int main() {
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(new CppUnit::TestCaller<Tests>("string", &Tests::testString));
    runner.addTest(new CppUnit::TestCaller<Tests>("vector", &Tests::testVector));
    runner.addTest(new CppUnit::TestCaller<Tests>("list", &Tests::testList));

    runner.run();


    return 0;
}
