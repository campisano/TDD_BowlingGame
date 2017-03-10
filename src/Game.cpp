#include "Game.h"

#include <iostream>
#include <stdexcept>

Game::Game()
{
    m_current_roll = 0;
}

Game::~Game()
{
}

void Game::roll(unsigned int _pins)
{
    m_rolls[m_current_roll++] = _pins;
}

unsigned int Game::score()
{
    unsigned int score = 0;
    unsigned int first_in_frame = 0;

    for(unsigned int frame=0; frame<10; ++frame)
    {
        if(isSpare(first_in_frame))
        {
            score += 10 + m_rolls[first_in_frame + 2];
        }
        else
        {
            score += m_rolls[first_in_frame] + m_rolls[first_in_frame + 1];
        }

        first_in_frame += 2;
    }

    return score;
}

bool Game::isSpare(unsigned int _first_in_frame)
{
    return m_rolls[_first_in_frame] + m_rolls[_first_in_frame + 1] == 10;
}
