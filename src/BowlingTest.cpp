#include "BowlingTest.h"

#include <cxxtools/unit/registertest.h>
#include <iostream>
#include <stdexcept>

#include "Game.h"

BowlingTest::BowlingTest() : cxxtools::unit::TestSuite("SIMTest")
{
    std::cout << std::endl << "Test methods:" << std::endl;

    registerMethod(
        "canCreateGame",
        *this,
        &BowlingTest::canCreateGame);

    registerMethod(
        "canRoll",
        *this,
        &BowlingTest::canRoll);
}

BowlingTest::~BowlingTest()
{
}

void BowlingTest::canCreateGame()
{
    Game g;
}

void BowlingTest::canRoll()
{
    Game g;
    g.roll(0);
}

cxxtools::unit::RegisterTest<BowlingTest> register_testr;

#include "cxxtools/unit/testmain.h"
