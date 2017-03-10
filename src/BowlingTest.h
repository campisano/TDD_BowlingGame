#ifndef BOWLING_TEST__H__
#define BOWLING_TEST__H__

#include <cxxtools/unit/testsuite.h>

#include "Game.h"

class BowlingTest : public cxxtools::unit::TestSuite
{
public:
    explicit BowlingTest();
    virtual ~BowlingTest();

    virtual void setUp();
    virtual void tearDown();

private:
    void gutterGame();
    void allOnes();

    void rollMany(unsigned int _times, unsigned int _pins);

    Game * m_g;
};

#endif
