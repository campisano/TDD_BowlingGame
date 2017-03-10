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

    for(unsigned int i=0; i<m_current_roll; ++i)
    {
        score += m_rolls[i];
    }

    return score;
}
