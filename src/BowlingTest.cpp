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

void BowlingTest::canRoll()
{
    m_g->roll(0);
}

void BowlingTest::gutterGame()
{
    for(int i=0; i<20; ++i)
    {
        m_g->roll(0);
    }

    CXXTOOLS_UNIT_ASSERT_EQUALS(0, m_g->score());
}

void BowlingTest::allOnes()
{
    for(int i=0; i<20; ++i)
    {
        m_g->roll(1);
    }

    CXXTOOLS_UNIT_ASSERT_EQUALS(20, m_g->score());
}

cxxtools::unit::RegisterTest<BowlingTest> register_testr;

#include "cxxtools/unit/testmain.h"
