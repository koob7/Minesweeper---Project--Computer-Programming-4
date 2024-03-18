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
export module openEmptyButton;

export void open(std::vector<std::vector<buttonWithTexture>>& board, int j, int b)//otwórz przyciski dooko³a przycisku, który nie ma ¿adnych min w s¹siedztwie
{
    if (board[j][b].buttonOpen() == 0 && !board[j][b].isButtonOpenedOnce())
    {
        if (j == 0)
        {
            if (b == 0)
            {
                std::jthread(open, std::ref(board), j + 1, b + 1);
                std::jthread(open, std::ref(board), j + 1, b);
                std::jthread(open, std::ref(board), j, b + 1);
            }
            else if (b == board[j].size() - 1)
            {
                std::jthread(open, std::ref(board), j + 1, b - 1);
                std::jthread(open, std::ref(board), j + 1, b);
                std::jthread(open, std::ref(board), j, b - 1);
            }
            else
            {
                std::jthread(open, std::ref(board), j + 1, b + 1);
                std::jthread(open, std::ref(board), j + 1, b - 1);
                std::jthread(open, std::ref(board), j + 1, b);
                std::jthread(open, std::ref(board), j, b + 1);
                std::jthread(open, std::ref(board), j, b - 1);
            }
        }
        else if (j == board.size() - 1)
        {
            if (b == 0)
            {
                std::jthread(open, std::ref(board), j - 1, b + 1);
                std::jthread(open, std::ref(board), j - 1, b);
                std::jthread(open, std::ref(board), j, b + 1);
            }
            else if (b == board[j].size() - 1)
            {
                std::jthread(open, std::ref(board), j - 1, b - 1);
                std::jthread(open, std::ref(board), j - 1, b);
                std::jthread(open, std::ref(board), j, b - 1);
            }
            else
            {
                std::jthread(open, std::ref(board), j - 1, b + 1);
                std::jthread(open, std::ref(board), j - 1, b - 1);
                std::jthread(open, std::ref(board), j - 1, b);
                std::jthread(open, std::ref(board), j, b + 1);
                std::jthread(open, std::ref(board), j, b - 1);
            }

        }
        else if (b == 0)
        {
            std::jthread(open, std::ref(board), j - 1, b + 1);
            std::jthread(open, std::ref(board), j, b + 1);
            std::jthread(open, std::ref(board), j + 1, b + 1);
            std::jthread(open, std::ref(board), j - 1, b);
            std::jthread(open, std::ref(board), j + 1, b);
        }
        else if (b == board[j].size() - 1)
        {
            std::jthread(open, std::ref(board), j - 1, b - 1);
            std::jthread(open, std::ref(board), j, b - 1);
            std::jthread(open, std::ref(board), j + 1, b - 1);
            std::jthread(open, std::ref(board), j - 1, b);
            std::jthread(open, std::ref(board), j + 1, b);
        }
        else
        {
            std::jthread(open, std::ref(board), j - 1, b + 1);
            std::jthread(open, std::ref(board), j, b + 1);
            std::jthread(open, std::ref(board), j + 1, b + 1);
            std::jthread(open, std::ref(board), j - 1, b - 1);
            std::jthread(open, std::ref(board), j, b - 1);
            std::jthread(open, std::ref(board), j + 1, b - 1);
            std::jthread(open, std::ref(board), j - 1, b);
            std::jthread(open, std::ref(board), j + 1, b);
        }
    }
}