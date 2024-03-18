#include <iostream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "okno.h"
#include "button.h"
#include "buttonWithText.h"
#include "buttonWithTexture.h"
#include "oknoWithText.h"
#include <chrono>
#include <thread>
#include <vector>
#include <random>
#include <atomic>
export module insertMines;

export void insertMines(std::vector<std::vector<buttonWithTexture>>& board, int minesNumber, int boardSizeX, int boardSizeY)//losowe wstawianie min do planszy
{
    int random1, random2, ii = 0;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distributionX(0, boardSizeX - 1);
    std::uniform_int_distribution<int> distributionY(0, boardSizeY - 1);
    if ((boardSizeX * boardSizeY) > minesNumber)
    {
        while (ii < minesNumber)
        {
            random1 = distributionY(generator);
            random2 = distributionX(generator);
            if (board[random1][random2].returnNumberOfNeighbors() >= 0 && random1 >= 0 && random2 >= 0)
            {
                board[random1][random2].setNumberOfNeighbors(-10);
                ii++;
                if (random1 > 0 && random2 > 0 && random1 < boardSizeY - 1 && random2 < boardSizeX - 1)
                {
                    board[random1 - 1][random2 - 1].incrementNumberOfNeighbors();
                    board[random1 - 1][random2].incrementNumberOfNeighbors();
                    board[random1 - 1][random2 + 1].incrementNumberOfNeighbors();
                    board[random1][random2 - 1].incrementNumberOfNeighbors();
                    board[random1][random2 + 1].incrementNumberOfNeighbors();
                    board[random1 + 1][random2 - 1].incrementNumberOfNeighbors();
                    board[random1 + 1][random2].incrementNumberOfNeighbors();
                    board[random1 + 1][random2 + 1].incrementNumberOfNeighbors();
                }
                else if (random1 == 0 && random2 == 0)
                {
                    board[random1][random2 + 1].incrementNumberOfNeighbors();
                    board[random1 + 1][random2].incrementNumberOfNeighbors();
                    board[random1 + 1][random2 + 1].incrementNumberOfNeighbors();
                }
                else if (random1 == 0 && random2 == boardSizeX - 1)
                {
                    board[random1][random2 - 1].incrementNumberOfNeighbors();
                    board[random1 + 1][random2].incrementNumberOfNeighbors();
                    board[random1 + 1][random2 - 1].incrementNumberOfNeighbors();
                }
                else if (random1 == boardSizeY - 1 && random2 == boardSizeX - 1)
                {
                    board[random1 - 1][random2 - 1].incrementNumberOfNeighbors();
                    board[random1 - 1][random2].incrementNumberOfNeighbors();
                    board[random1][random2 - 1].incrementNumberOfNeighbors();
                }
                else if (random1 == boardSizeY - 1 && random2 == 0)
                {
                    board[random1 - 1][random2].incrementNumberOfNeighbors();
                    board[random1 - 1][random2 + 1].incrementNumberOfNeighbors();
                    board[random1][random2 + 1].incrementNumberOfNeighbors();
                }
                else if (random1 == 0)
                {
                    board[random1][random2 - 1].incrementNumberOfNeighbors();
                    board[random1][random2 + 1].incrementNumberOfNeighbors();
                    board[random1 + 1][random2 - 1].incrementNumberOfNeighbors();
                    board[random1 + 1][random2].incrementNumberOfNeighbors();
                    board[random1 + 1][random2 + 1].incrementNumberOfNeighbors();
                }
                else if (random1 == boardSizeY - 1)
                {
                    board[random1][random2 - 1].incrementNumberOfNeighbors();
                    board[random1][random2 + 1].incrementNumberOfNeighbors();
                    board[random1 - 1][random2 - 1].incrementNumberOfNeighbors();
                    board[random1 - 1][random2].incrementNumberOfNeighbors();
                    board[random1 - 1][random2 + 1].incrementNumberOfNeighbors();
                }
                else if (random2 == 0)
                {
                    board[random1 - 1][random2].incrementNumberOfNeighbors();
                    board[random1 + 1][random2].incrementNumberOfNeighbors();
                    board[random1 - 1][random2 + 1].incrementNumberOfNeighbors();
                    board[random1][random2 + 1].incrementNumberOfNeighbors();
                    board[random1 + 1][random2 + 1].incrementNumberOfNeighbors();
                }
                else if (random2 == boardSizeX - 1)
                {
                    board[random1 - 1][random2].incrementNumberOfNeighbors();
                    board[random1 + 1][random2].incrementNumberOfNeighbors();
                    board[random1 - 1][random2 - 1].incrementNumberOfNeighbors();
                    board[random1][random2 - 1].incrementNumberOfNeighbors();
                    board[random1 + 1][random2 - 1].incrementNumberOfNeighbors();
                }

            }
        }
    }
}