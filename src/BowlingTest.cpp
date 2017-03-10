#include "BowlingTest.h"

#include <cxxtools/unit/registertest.h>
#include <iostream>
#include <stdexcept>

BowlingTest::BowlingTest() : cxxtools::unit::TestSuite("SIMTest")
{
    std::cout << std::endl << "Test methods:" << std::endl;

    registerMethod(
        "gutterGame",
        *this,
        &BowlingTest::gutterGame);

    registerMethod(
        "allOnes",
        *this,
        &BowlingTest::allOnes);
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

void BowlingTest::gutterGame()
{
    rollMany(20, 0);

    CXXTOOLS_UNIT_ASSERT_EQUALS(0, m_g->score());
}

void BowlingTest::allOnes()
{
    rollMany(20, 1);

    CXXTOOLS_UNIT_ASSERT_EQUALS(20, m_g->score());
}

void BowlingTest::rollMany(unsigned int _times, unsigned int _pins)
{
    for(unsigned int i=0; i<_times; ++i)
    {
        m_g->roll(_pins);
    }
}

cxxtools::unit::RegisterTest<BowlingTest> register_testr;

#include "cxxtools/unit/testmain.h"
