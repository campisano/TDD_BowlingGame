#include "BowlingTest.h"

#include <cxxtools/unit/registertest.h>
#include <iostream>
#include <stdexcept>

BowlingTest::BowlingTest() : cxxtools::unit::TestSuite("SIMTest")
{
    std::cout << std::endl << "Test methods:" << std::endl;

    registerMethod(
        "canRoll",
        *this,
        &BowlingTest::canRoll);
}

BowlingTest::~BowlingTest()
{
}

void BowlingTest::setUp()
{
    m_g = new Game();
}

void BowlingTest::tearDown()
{
    delete m_g;
}

void BowlingTest::canRoll()
{
    m_g->roll(0);
}

cxxtools::unit::RegisterTest<BowlingTest> register_testr;

#include "cxxtools/unit/testmain.h"
