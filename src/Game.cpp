#include "Game.h"

#include <iostream>
#include <stdexcept>

Game::Game()
{
    m_score = 0;
}

Game::~Game()
{
}

void Game::roll(unsigned int _pins)
{
    m_score += _pins;
}

unsigned int Game::score()
{
    return m_score;
}
