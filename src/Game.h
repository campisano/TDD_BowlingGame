#ifndef GAME__H__
#define GAME__H__

class Game
{
public:
    explicit Game();
    virtual ~Game();

    void roll(unsigned int _pins);
    unsigned int score();

private:
    unsigned int m_score;
};

#endif
