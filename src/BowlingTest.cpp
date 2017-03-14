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

    registerMethod(
        "oneSpare",
        *this,
        &BowlingTest::oneSpare);

    registerMethod(
        "oneStrike",
        *this,
        &BowlingTest::oneStrike);

    registerMethod(
        "perfectGame",
        *this,
        &BowlingTest::perfectGame);
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

void BowlingTest::oneSpare()
{
    rollSpare();
    m_g->roll(3);
    rollMany(17, 0);

    CXXTOOLS_UNIT_ASSERT_EQUALS(16, m_g->score());
}

void BowlingTest::oneStrike()
{
    rollStrike();
    m_g->roll(3);
    m_g->roll(4);
    rollMany(16, 0);

    CXXTOOLS_UNIT_ASSERT_EQUALS(24, m_g->score());
}

void BowlingTest::perfectGame()
{
    rollMany(12, 10);
    CXXTOOLS_UNIT_ASSERT_EQUALS(300, m_g->score());
}

void BowlingTest::rollMany(unsigned int _times, unsigned int _pins)
{
    for(unsigned int i=0; i<_times; ++i)
    {
        m_g->roll(_pins);
    }
}

void BowlingTest::rollSpare()
{
    m_g->roll(5);
    m_g->roll(5);
}

void BowlingTest::rollStrike()
{
    m_g->roll(10);
}

cxxtools::unit::RegisterTest<BowlingTest> register_testr;

#include "cxxtools/unit/testmain.h"
