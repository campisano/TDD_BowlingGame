#ifndef BOWLING_TEST__H__
#define BOWLING_TEST__H__

#include <cxxtools/unit/testsuite.h>

class BowlingTest : public cxxtools::unit::TestSuite
{
public:
    explicit BowlingTest();
    virtual ~BowlingTest();

private:
    void canCreateGame();
    void canRoll();
};

#endif
