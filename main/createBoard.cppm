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
export module createBoard;

export void initializeBoard(std::vector<std::vector<buttonWithTexture>>& board, int boardSizeX, int boardSizeY, int main_window_x, int main_window_y)
{
    int playButtonSize = 20, playButtonSpace = 6;
    int b_tmp=0, i_tmp=0;
    i_tmp = board.size();
    if (i_tmp > 0)
        b_tmp = board[0].size();
    else
        b_tmp = 0;
    for (int i = board.size() - 1; i >= 0; i--)//usuwanie starej planszy
    {
        for (int b = board[i].size() - 1; b >= 0; b--)
            board[i].erase(board[i].begin() + b);
        board.erase(board.begin() + i);
    }
    for (i_tmp = 0; i_tmp < boardSizeY; i_tmp++)//wstawianie przycisków do nowej planszy
    {
        board.push_back(std::vector<buttonWithTexture>());
        for (b_tmp = 0; b_tmp < boardSizeX; b_tmp++)
            board[i_tmp].push_back(buttonWithTexture(main_window_x, main_window_y,
                playButtonSize, playButtonSize,
                (main_window_x - boardSizeX * playButtonSize - boardSizeX * playButtonSpace) / 2 + b_tmp * playButtonSize + b_tmp * playButtonSpace + playButtonSize / 2 + playButtonSpace / 2,
                (main_window_y - boardSizeY * playButtonSize - boardSizeY * playButtonSpace) / 2 + i_tmp * playButtonSize + i_tmp * playButtonSpace + playButtonSize / 2 + playButtonSpace / 2,
                92, 255, 89, 255, 0, "mina.png", "flaga.png"));
    }

    for (int i = 0; i < board.size(); i++)//inicjaliza tektu przycisków planszy
    {
        for (int b = 0; b < board[i].size(); b++)
            board[i][b].initializeTexture();
    }
}