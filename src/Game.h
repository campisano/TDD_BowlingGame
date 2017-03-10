#ifndef GAME__H__
#define GAME__H__

class Game
{
public:
    explicit Game();
    virtual ~Game();

    void roll(unsigned int _pins);
    unsigned int score();

    bool isSpare(unsigned int _first_in_frame);

private:
    unsigned int m_rolls[21];
    unsigned int m_current_roll;
};

#endif
