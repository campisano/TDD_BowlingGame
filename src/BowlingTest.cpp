#include "BowlingTest.h"

#include <cxxtools/unit/registertest.h>
#include <iostream>
#include <stdexcept>

BowlingTest::BowlingTest() : cxxtools::unit::TestSuite("SIMTest")
{
    std::cout << std::endl << "Test methods:" << std::endl;
}

BowlingTest::~BowlingTest()
{
}

cxxtools::unit::RegisterTest<BowlingTest> register_test;

#include "cxxtools/unit/testmain.h"
