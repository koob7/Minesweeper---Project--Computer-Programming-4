

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include <thread>
#include <vector>
#include <random>
#include <regex>
#include <fstream>
#include <ranges>

#include "player.h"
#include "okno.h"
#include "button.h"
#include "buttonWithText.h"
#include "buttonWithTexture.h"
#include "oknoWithText.h"

import createBoard;
import openEmptyButton;
import insertMines;

bool comparator(const player& obj1, const player& obj2)//funkcja zwracająca wartość true jeśli pierwszy gracz ma lepszy (mniejszy) wynik
{ return obj1.playerScore < obj2.playerScore; }

int main()
{
    bool wait = false, waitBeforeEnd=false;
    sf::Time elapsed;
    int gameisLostWon = 0;
    int lastButtonsToOpen=1;
    int newGame = 0, gameIsStarted=0;
    int mainMenuNavigation=0, menuNavigation=0;
    int main_window_x = 1500, main_window_y = 900;
    int logowanieButtonX = 200, logowanieButtonY = 50;
    int main_window_R = 49, main_window_G = 89, main_window_B = 61;
    int boardSizeX = 10, boardSizeY = 10, minesNumber = 5;
    std::regex wzorzecLogin(".{5}");
    sf::Vector2i mousePos;
    sf::Font font;
    int font_size = 30;
    int playTime = 0;
    int mousePressed = 0;
    int navigation = 0;
    bool loseFocus = true;
    if (!font.loadFromFile("font.ttf"))
        std::cout << "koniec programu" << '\n'; 
    std::vector<std::vector<buttonWithTexture>> board;
    std::vector<std::string> userLogins;
    std::vector<std::string> userPasswords;
    std::vector<int> userPlayTime;
    std::string inputMines;
    std::string inputSizeX;
    std::string inputSizeY;
    std::string rejestracjaLogin="";
    std::string rejestracjaPass="";
    std::string logowanieLogin = "";
    std::string logowaniePass = "";
    std::string odczyt;
    int odczytInt;
    std::regex wzorzecPass("^(?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{5,}$"); //wzorzec wykorzystywany przy tworzeniu hasła do rejestracji
    int positionCounter = 0;
    int zalogowano = -1;
    std::ifstream input_file1("login.txt", std::ios::in);//odczyt z pliku loginów użytkowników
    if (input_file1.is_open())
    {
        while (getline(input_file1, odczyt))
            userLogins.push_back(odczyt);
        input_file1.close();
    }

    std::ifstream input_file2("pass.txt", std::ios::in);//odczyt z pliku haseł użytkowników
    if (input_file2.is_open())
    {
        while (getline(input_file2, odczyt))
            userPasswords.push_back(odczyt);
        input_file2.close();
    }

    std::ifstream input_file3("playTime.txt", std::ios::in);//odczyt z pliku najlepszych wyników użytkowników
    if (input_file3.is_open())
    {
        while (input_file3>> odczytInt)
            userPlayTime.push_back(odczytInt);
        input_file3.close();
    }
    std::ofstream output_file1("login.txt");
    std::ofstream output_file2("pass.txt");
    std::ofstream output_file3("playTime.txt");
    std::vector<std::string>::iterator it = std::ranges::find(userLogins.begin(), userLogins.end(), logowanieLogin);
    std::vector<player> players;
    auto itLogins = userLogins.begin();
    auto itPasswords = userPasswords.begin();
    auto itPlayTime = userPlayTime.begin();
    int playerCounter = 0;
    for (; itLogins != userLogins.end(); ++itLogins, ++itPasswords, ++itPlayTime)//zapis użytkowników do wektora
    {
        players.push_back(player(*itLogins, *itPasswords, *itPlayTime, playerCounter));
        playerCounter++;
    }
    sf::Clock clock;
#pragma region inicjalizacjaPrzyciskow



     //zmieniając oknoX i oknoY zmieniamy rozmiar przycisku
    //ustawiając offset zmieniamy położenie przycisku   
    oknoWithText timerWindow(main_window_x, main_window_y,
        100, 40, main_window_x / 2+20, 20,
        100, 100, 100, 0, 0, "timer", font, font_size);
    oknoWithText bigTimerWindow(main_window_x, main_window_y,
        300, 150, main_window_x / 2+50, 200,
        100, 100, 100, 0, 0, "timer", font, 100);
    oknoWithText endGameWindow(main_window_x, main_window_y,
        300, 150, main_window_x / 2+50, 380,
        100, 100, 100, 0, 0, "Win", font, 100);
    oknoWithText logowanieMenu(main_window_x, main_window_y,
        100, 40, main_window_x / 2 - 180, 40,
        100, 100, 100, 0, 0, "Logowanie", font, 100);
    buttonWithText loginButton(main_window_x, main_window_y, 
        logowanieButtonX, logowanieButtonY, main_window_x/2, (main_window_y/2-logowanieButtonY / 2 - 20),
        0, 255, 0,255,1,"podaj login","login", font, font_size);
    buttonWithText passButton(main_window_x, main_window_y, 
        logowanieButtonX, logowanieButtonY, main_window_x/2, (main_window_y/2+logowanieButtonY / 2 + 20), 
        0, 255, 0,255,1,"podaj haslo", "haslo",font,font_size);
    buttonWithText zalogujButton(main_window_x, main_window_y,
        logowanieButtonX, logowanieButtonY, main_window_x / 2, (main_window_y / 2 + logowanieButtonY / 2 + 110),
        0, 255, 0, 255, 1, "zaloguj", "loading", font, font_size);
    buttonWithText rejestracjaButton(main_window_x, main_window_y,
        logowanieButtonX+60, logowanieButtonY, main_window_x / 2, (main_window_y / 2 + logowanieButtonY / 2 + 200),
        0, 255, 0, 255, 1, "Utworz konto", "Loading", font, font_size);
    oknoWithText menu(main_window_x, main_window_y,
        100, 40, main_window_x / 2 - 105, 40,
        100, 100, 100, 0, 0, "SAPER", font, 100);
    buttonWithText playButton(main_window_x, main_window_y,
        logowanieButtonX, logowanieButtonY, main_window_x / 2, (main_window_y / 2 - logowanieButtonY / 2 - 20),
        0, 255, 0, 255, 1, "Play", "Loading", font, font_size);
    buttonWithText logowanieButton(main_window_x, main_window_y,
        logowanieButtonX, logowanieButtonY, main_window_x / 2, (main_window_y / 2 + logowanieButtonY / 2 + 290),
        0, 255, 0, 255, 1, "Zaloguj", "Loading", font, font_size);
    buttonWithText wynikiButton(main_window_x, main_window_y,
        logowanieButtonX, logowanieButtonY, main_window_x / 2, (main_window_y / 2 + logowanieButtonY/2 + 110),
        0, 255, 0, 255, 1, "Wyniki", "Loading", font, font_size);
    buttonWithText settingsButton(main_window_x, main_window_y,
        logowanieButtonX, logowanieButtonY, main_window_x / 2, (main_window_y / 2 + logowanieButtonY / 2 + 20),
        0, 255, 0, 255, 1, "Ustawienia", "Loading", font, font_size);
    buttonWithText wylogujButton(main_window_x, main_window_y,
        logowanieButtonX, logowanieButtonY, main_window_x / 2, (main_window_y / 2 + logowanieButtonY / 2 + 380),
        0, 255, 0, 255, 1, "Wyloguj", "Loading", font, font_size);
    buttonWithText wyjscieButton(main_window_x, main_window_y,
        logowanieButtonX, logowanieButtonY, main_window_x / 2, (main_window_y / 2 + logowanieButtonY / 2 + 200),
        0, 255, 0, 255, 1, "Wyjscie", "Zamykanie", font, font_size);
    oknoWithText zalogowanoMenu(main_window_x, main_window_y,
        450, logowanieButtonY, main_window_x / 2 , (main_window_y / 2 + logowanieButtonY / 2 + 290),
        0, 255, 0, 255, 1, "Zalogowano", font, font_size);
    oknoWithText wynikiMenu(main_window_x, main_window_y,
        100, 40, main_window_x / 2 - 110, 40,
        100, 100, 100, 0, 0, "Wyniki", font, 100);
    oknoWithText wynik1(main_window_x, main_window_y,
        600, logowanieButtonY, main_window_x / 2, (main_window_y / 2 + logowanieButtonY / 2 - 70),
        0, 255, 0, 255, 1, "Wynik 1", font, font_size);
    oknoWithText wynik2(main_window_x, main_window_y,
        600, logowanieButtonY, main_window_x / 2, (main_window_y / 2 + logowanieButtonY / 2 + 20),
        0, 255, 0, 255, 1, "Wynik 2", font, font_size);
    oknoWithText wynik3(main_window_x, main_window_y,
        600, logowanieButtonY, main_window_x / 2, (main_window_y / 2 + logowanieButtonY / 2 + 110),
        0, 255, 0, 255, 1, "Wynik 3", font, font_size);   
    buttonWithTexture nextButton(main_window_x, main_window_y,
        logowanieButtonY, logowanieButtonY, (main_window_x / 2 + logowanieButtonX / 2), (main_window_y / 2 + logowanieButtonY / 2 + 190),
        255, 255, 255, 255, 0, "next.png");
    buttonWithTexture previousButton(main_window_x, main_window_y,
        logowanieButtonY, logowanieButtonY, main_window_x/2, (main_window_y / 2 + logowanieButtonY / 2 + 190), 
        255, 255, 255, 255, 0, "previous.png");
    buttonWithTexture backButton(main_window_x, main_window_y,
        50, 50, main_window_x -100, main_window_y -100,
        255, 255, 255, 255, 0, "back2.png");
    buttonWithText playingButton(main_window_x, main_window_y,
        400, 200, main_window_x / 2, (main_window_y / 2),
        0, 255, 0, 255, 1, "Rozpoczynanie\nGry", "Czekaj", font, 50);
    oknoWithText settingsMenuButton(main_window_x, main_window_y,
        100, 40, main_window_x / 2 - 200, 40,
        100, 100, 100, 0, 0, "Ustawienia", font, 100);
    buttonWithTexture resumeButton(main_window_x, main_window_y,
        480, 480, main_window_x/2, main_window_y/2,
        255, 255, 255, 255, 0, "play.png");
    buttonWithTexture stopButton(main_window_x, main_window_y,
        50, 50, main_window_x - 100, main_window_y - 100,
        255, 255, 255, 255, 0, "stop.png");
    buttonWithText liczbaMinButton(main_window_x, main_window_y,
        logowanieButtonX+60, logowanieButtonY, main_window_x / 2, (main_window_y / 2 - logowanieButtonY / 2 - 70),
        0, 255, 0, 255, 1, "podaj liczbe min", std::to_string(minesNumber), font, font_size);
    buttonWithText sizeXButton(main_window_x, main_window_y,
        logowanieButtonX+60, logowanieButtonY, main_window_x / 2, (main_window_y / 2 - logowanieButtonY / 2 + 20),
        0, 255, 0, 255, 1, "podaj rozmiar X", std::to_string(boardSizeX), font, font_size);
    buttonWithText sizeYButton(main_window_x, main_window_y,
        logowanieButtonX+60, logowanieButtonY, main_window_x / 2, (main_window_y / 2 - logowanieButtonY / 2 + 110),
        0, 255, 0, 255, 1, "podaj rozmiar Y", std::to_string(boardSizeY), font, font_size);
    buttonWithText rejestracjaLoginButton(main_window_x, main_window_y,
        logowanieButtonX, logowanieButtonY, main_window_x / 2, (main_window_y / 2 - logowanieButtonY / 2 - 20),
        0, 255, 0, 255, 1, "podaj login", "login", font, font_size);
    buttonWithText rejestracjaPassButton(main_window_x, main_window_y,
        logowanieButtonX, logowanieButtonY, main_window_x / 2, (main_window_y / 2 + logowanieButtonY / 2 + 20),
        0, 255, 0, 255, 1, "podaj haslo", "haslo", font, font_size);
    buttonWithText rejestrujButton(main_window_x, main_window_y,
        logowanieButtonX, logowanieButtonY, main_window_x / 2, (main_window_y / 2 + logowanieButtonY / 2 + 110),
        0, 255, 0, 255, 1, "utworz konto", "loading", font, font_size);
    oknoWithText oknoInformacyjne(main_window_x, main_window_y,
        700, 300, main_window_x / 2, (main_window_y / 2 + logowanieButtonY / 2 ),
        0, 255, 0, 255, 1, "Wprowadzono bledne dane\n pamietaj ze login moze zawierac tylko litery i cyfr\n a haslo musi zawierac przynajmniej:\n -jedna mala litera\n -jedna duza litera\n -jedna cyfra\n -minimium piec znakow", font, font_size);
    oknoWithText oknoInformacyjne2(main_window_x, main_window_y,
        600, 200, main_window_x / 2, (main_window_y / 2 + logowanieButtonY / 2),
        0, 255, 0, 255, 1, "Wprowadzono bledne parametry planszy\n max rozmiar planszsy to 30x30\n min rozmiar planszy to 5x5\n liczba min nie moze byc mniejsza niz 10\n oraz nie wieksza niz X*Y", font, font_size);
#pragma endregion

    std::string userLogin, userPass, userPassword;
    sf::Event event;
    sf::RenderWindow main_window(sf::VideoMode(main_window_x, main_window_y), "Saper by Konrad Kobielus");
        while (main_window.isOpen())//główna pętla programu
        {
            if (gameisLostWon == 2)//zapis wyniku zalogowanemu graczowi jeśli wygrał
            {
                if (zalogowano != -1)
                {
                    if (players[zalogowano].returnScore() > playTime)
                        players[zalogowano].setScore(playTime);
                }
                gameisLostWon = 0;
            }    
        if(newGame==1)//tworzenie nowej planszy oraz rozlosowanie pozycji min jeśli użytkownik tworzy nową grę
        {
            initializeBoard(board, boardSizeX, boardSizeY, main_window_x, main_window_y);
            insertMines(board, minesNumber, boardSizeX, boardSizeY);
            newGame--;
            elapsed = sf::Time::Zero;
        }

        main_window.clear(sf::Color(main_window_R, main_window_G, main_window_B));
        main_window.pollEvent(event);
        mousePos = sf::Mouse::getPosition(main_window);
        if (event.type == sf::Event::Closed)//obsługa przycisku "X" okna programu jeśli kliknięty
        {
            for (auto it = players.begin(); it != players.end(); ++it)
                it->saveToFile(output_file1, output_file2, output_file3);
            main_window.close();
        }
        if (mousePressed == 0||mainMenuNavigation==12)//obsługa położenia oraz przycisków myszy jeśli mysz nie jest kliknięta
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                mousePressed = 1;
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                mousePressed = 2;
            else
                mousePressed = 0;
#pragma region ukryjPrzyciski
                menu.setHiden();
                playButton.setHiden();
                logowanieButton.setHiden();
                settingsButton.setHiden();
                wynikiButton.setHiden();
                logowanieMenu.setHiden();
                loginButton.setHiden();
                passButton.setHiden();
                rejestracjaButton.setHiden();
                backButton.setHiden();
                wynikiMenu.setHiden();
                wynik1.setHiden();
                wynik2.setHiden();
                wynik3.setHiden();
                playingButton.setHiden();
                stopButton.setHiden();
                resumeButton.setHiden();
                timerWindow.setHiden();
                bigTimerWindow.setHiden();
                endGameWindow.setHiden();
                liczbaMinButton.setHiden();
                sizeXButton.setHiden();
                sizeYButton.setHiden();
                zalogujButton.setHiden();
                rejestracjaLoginButton.setHiden();
                rejestracjaPassButton.setHiden();
                rejestrujButton.setHiden();
                oknoInformacyjne.setHiden();
                wyjscieButton.setHiden();
                zalogowanoMenu.setHiden();
                wylogujButton.setHiden();
                oknoInformacyjne2.setHiden();
                for (int i = 0; i < board.size(); i++)
                {
                    for (int b = 0; b < board[i].size(); b++)
                        board[i][b].setHiden();
                }
#pragma endregion
                switch (mainMenuNavigation) //menu gry saper
                {
                case 0://strona startowa gry saper
#pragma region menu
                    menu.setNotHiden();
                    playButton.setNotHiden();
                    wynikiButton.setNotHiden();
                    settingsButton.setNotHiden();
                    wyjscieButton.setNotHiden();
                    main_window.draw(menu);
                    if (playButton.isButtonPressed(mousePos, mousePressed))
                    {
                        loseFocus = false;
                        mainMenuNavigation = 1;
                    }
                    main_window.draw(playButton);
                    if (zalogowano == -1)
                    {
                        logowanieButton.setNotHiden();
                        if (logowanieButton.isButtonPressed(mousePos, mousePressed))
                            mainMenuNavigation = 2;
                        main_window.draw(logowanieButton);
                    }
                    else
                    {
                        zalogowanoMenu.setNotHiden();
                        zalogowanoMenu.updateText("zalogowano jako user " + players[zalogowano].returnLogin());
                        main_window.draw(zalogowanoMenu);
                    }
                    if (wynikiButton.isButtonPressed(mousePos, mousePressed))
                        mainMenuNavigation = 13;
                    main_window.draw(wynikiButton);
                    if (settingsButton.isButtonPressed(mousePos, mousePressed))
                    {
                        mainMenuNavigation = 4;
                        liczbaMinButton.getText("podaj liczbe min");
                        sizeXButton.getText("podaj rozmiar X");
                        sizeYButton.getText("podaj rozmiar Y");
                        inputSizeX = "";
                        inputSizeY = "";
                        inputMines = "";
                    }
                    main_window.draw(settingsButton);
                    if (wyjscieButton.isButtonPressed(mousePos, mousePressed))
                        mainMenuNavigation = 10;
                    main_window.draw(wyjscieButton);
                    if (zalogowano != -1)
                    {
                        wylogujButton.setNotHiden();
                        if (wylogujButton.isButtonPressed(mousePos, mousePressed))
                        {
                            zalogowano = -1;
                            rejestracjaLogin = "";
                            userLogin = "";
                            userPass = "";
                            userPassword = "";
                            rejestracjaLoginButton.getText("podaj login");
                            rejestracjaPassButton.getText("podaj haslo");
                            loginButton.getText("podaj login");
                            passButton.getText("podaj haslo");
                            rejestracjaPass = "";
                        }
                        main_window.draw(wylogujButton);
                    }
                    clock.restart(); 
#pragma endregion
                    break;
                case 1://główny mechanizm rozgrywki 
#pragma region gra
                    if (gameIsStarted == 0)
                    {
                        menu.setNotHiden();
                        playButton.setNotHiden();
                        wynikiButton.setNotHiden();
                        settingsButton.setNotHiden();
                        wyjscieButton.setNotHiden();
                        main_window.draw(menu);
                        main_window.draw(playButton);
                        main_window.draw(wynikiButton);
                        main_window.draw(settingsButton);
                        main_window.draw(wyjscieButton);
                        if (zalogowano == -1)
                        {
                            logowanieButton.setNotHiden();
                            if (logowanieButton.isButtonPressed(mousePos, mousePressed))
                                mainMenuNavigation = 2;
                            main_window.draw(logowanieButton);
                        }
                        else
                        {
                            zalogowanoMenu.setNotHiden();
                            zalogowanoMenu.updateText("zalogowano jako user nr: " + players[zalogowano].returnLogin());
                            main_window.draw(zalogowanoMenu);
                        }
                        gameIsStarted = 1;
                        newGame = 1;
                    }
                    else {
                        stopButton.setNotHiden();
                        if (stopButton.isButtonPressed(mousePos, mousePressed))
                            mainMenuNavigation = 5;
                        main_window.draw(stopButton);
                        lastButtonsToOpen = (boardSizeX * boardSizeY) - minesNumber;
                        for (int l = 0; l < board.size(); l++)
                        {
                            for (int c = 0; c < board[l].size(); c++)
                            {
                                board[l][c].setNotHiden();
                                main_window.draw(board[l][c]);
                                if (!board[l][c].isButtonLock())
                                {
                                    if (board[l][c].play(mousePos, mousePressed) < 0 && board[l][c].conditionalReturnNumberOfNeighbors(mousePos, mousePressed) > -100)
                                    {
                                        endGameWindow.updateText("Lose");
                                        gameIsStarted = 0;
                                        wait = true;
                                        gameisLostWon = 1;
                                        mainMenuNavigation = 6;
                                        main_window.draw(board[l][c]);
                                    }
                                    if (board[l][c].conditionalReturnNumberOfNeighbors(mousePos, mousePressed) >= 0)
                                        std::jthread(open, std::ref(board), l, c);
                                }
                                else
                                {
                                    if (board[l][c].returnNumberOfNeighbors() >= 0)
                                        lastButtonsToOpen--;
                                }
                            }
                        }
                        elapsed += clock.getElapsedTime();
                        timerWindow.setNotHiden();
                        playTime = static_cast<int>(elapsed.asSeconds());
                        timerWindow.updateText(std::to_string(playTime / 60 / 60 % 24)
                            + ":" + std::to_string(playTime / 60 % 60)
                            + ":" + std::to_string(playTime % 60));
                        main_window.draw(timerWindow);
                        clock.restart();
                        if (lastButtonsToOpen == 0)
                        {
                            gameIsStarted = 0;
                            mainMenuNavigation = 6;
                            gameisLostWon = 2;
                            wait = true;
                            endGameWindow.updateText("Win");
                        }
                    }
#pragma endregion
                    break;
                case 2://okno logowania
#pragma region logowanie
                    logowanieMenu.setNotHiden();
                    loginButton.setNotHiden();
                    passButton.setNotHiden();
                    rejestracjaButton.setNotHiden();
                    backButton.setNotHiden();
                    if (loginButton.isButtonPressed(mousePos, mousePressed))
                    {
                        while (main_window.pollEvent(event))
                        {
                            if (event.type == sf::Event::TextEntered)
                            {
                                if (event.text.unicode == '\b' && userLogin.size() > 0)
                                    userLogin.erase(userLogin.size() - 1, 1);
                                else if (event.text.unicode == '\r')
                                    loginButton.loseFocus();
                                else if (event.text.unicode < 255 && event.text.unicode >32)
                                    userLogin += static_cast<char>(event.text.unicode);
                                loginButton.getText(userLogin);
                            }
                        }
                    }
                    if (passButton.isButtonPressed(mousePos, mousePressed))
                    {
                        while (main_window.pollEvent(event))
                        {
                            if (event.type == sf::Event::TextEntered)
                            {
                                if (event.text.unicode == '\b' && userPass.size() > 0)
                                {
                                    userPass.erase(userPass.size() - 1, 1);
                                    userPassword.erase(userPassword.size() - 1, 1);
                                    passButton.getText(userPass);
                                }
                                else if (event.text.unicode == '\r')
                                {
                                    userPass.back() = '*';
                                    passButton.getText(userPass);
                                    passButton.loseFocus();
                                }
                                else if (event.text.unicode < 255 && event.text.unicode > 32)
                                {
                                    userPass += static_cast<char>(event.text.unicode);
                                    userPassword += static_cast<char>(event.text.unicode);
                                }
                                if (userPass.length() > 0)
                                {
                                    int counter = userPass.length();
                                    std::string gwiazdka = "*";
                                    char lastSign = userPass.back();
                                    userPass = "";
                                    for (int i = 0; i < counter - 1; i++)
                                        userPass += gwiazdka;
                                    userPass += lastSign;
                                    passButton.getText(userPass);
                                }
                            }
                        }
                    }
                    main_window.draw(logowanieMenu);
                    main_window.draw(loginButton);
                    main_window.draw(passButton);
                    if (rejestracjaButton.isButtonPressed(mousePos, mousePressed))
                        mainMenuNavigation = 8;
                    main_window.draw(rejestracjaButton);
                    if (backButton.isButtonPressed(mousePos, mousePressed))
                    {
                        mainMenuNavigation = 0;
                    }
                    main_window.draw(backButton);
                    zalogujButton.setNotHiden();
                    if (zalogujButton.isButtonPressed(mousePos, mousePressed))
                        mainMenuNavigation = 7;
                    main_window.draw(zalogujButton);
#pragma endregion
                    break;
                case 3://okno z wynikami wyświetlające listę najlepszych wyników
#pragma region wyniki
                    wynikiMenu.setNotHiden();
                    wynik1.setNotHiden();
                    wynik2.setNotHiden();
                    wynik3.setNotHiden();

                    if (players.size() > 0)
                    {
                        if (navigation ==0)
                        {
                            nextButton.setNotHiden();
                            if (players.size() > 3)
                            {
                                if (nextButton.isButtonPressed(mousePos, mousePressed))
                                    navigation++;
                                main_window.draw(nextButton);
                            }
                            wynik1.updateText("gracz " + players[navigation].returnLogin() + " uzyskal wynik " + std::to_string(players[navigation].returnScore() / 60) + "min " + std::to_string(players[navigation].returnScore() % 60) + "s");
                            if (navigation + 1 < players.size())
                            {
                                wynik2.updateText("gracz " + players[navigation + 1].returnLogin() + " uzyskal wynik " + std::to_string(players[navigation+1].returnScore() / 60) + "min " + std::to_string(players[navigation+1].returnScore() % 60) + "s");
                                if (navigation + 2 < players.size())
                                    wynik3.updateText("gracz " + players[navigation+2].returnLogin() + " uzyskal wynik " + std::to_string(players[navigation+2].returnScore() / 60) + "min " + std::to_string(players[navigation+2].returnScore() % 60) + "s");
                                else
                                    wynik3.updateText("wynik 3");
                            }
                            else
                            {
                                wynik2.updateText("wynik 2");
                                wynik3.updateText("wynik 3");
                            }         
                            main_window.draw(wynik1);
                            main_window.draw(wynik2);
                            main_window.draw(wynik3);
                        }
                        else if (navigation == players.size()-3)
                        {
                            previousButton.setNotHiden();
                            if (previousButton.isButtonPressed(mousePos, mousePressed))
                                navigation--;
                            main_window.draw(previousButton);
                            wynik1.updateText("gracz " + players[navigation].returnLogin() + " uzyskal wynik " + std::to_string(players[navigation].returnScore() / 60) + "min " + std::to_string(players[navigation].returnScore() % 60) + "s");
                            wynik2.updateText("gracz " + players[navigation+1].returnLogin() + " uzyskal wynik " + std::to_string(players[navigation+1].returnScore() / 60) + "min " + std::to_string(players[navigation+1].returnScore() % 60) + "s");
                            wynik3.updateText("gracz " + players[navigation+2].returnLogin() + " uzyskal wynik " + std::to_string(players[navigation+2].returnScore() / 60) + "min " + std::to_string(players[navigation+2].returnScore() % 60) + "s");
                            main_window.draw(wynik1);
                            main_window.draw(wynik2);
                            main_window.draw(wynik3);
                        }
                        else
                        {
                            nextButton.setNotHiden();
                            previousButton.setNotHiden();
                            if (previousButton.isButtonPressed(mousePos, mousePressed))
                                navigation--;
                            else if (nextButton.isButtonPressed(mousePos, mousePressed))
                                navigation++;
                            main_window.draw(previousButton);
                            main_window.draw(nextButton);
                            wynik1.updateText("gracz " + players[navigation].returnLogin() + " uzyskal wynik " +std::to_string(players[navigation].returnScore() / 60) + "min " + std::to_string(players[navigation].returnScore() % 60) + "s");
                            if (navigation + 1 < players.size())
                            {
                                wynik2.updateText("gracz " + players[navigation + 1].returnLogin() + " uzyskal wynik " + std::to_string(players[navigation+1].returnScore() / 60) + "min " + std::to_string(players[navigation+1].returnScore() % 60) + "s");
                                if (navigation + 2 < players.size())
                                    wynik3.updateText("gracz " + players[navigation + 2].returnLogin() + " uzyskal wynik " + std::to_string(players[navigation+2].returnScore() / 60) + "min " + std::to_string(players[navigation+2].returnScore() % 60) + "s");
                                else
                                    wynik3.updateText("wynik 3");
                            }
                            else
                            {
                                wynik2.updateText("wynik 2");
                                wynik3.updateText("wynik 3");
                            }
                            main_window.draw(wynik1);
                            main_window.draw(wynik2);
                            main_window.draw(wynik3);
                        }
                    }
                    else
                    {
                        main_window.draw(wynik1);
                        main_window.draw(wynik2);
                        main_window.draw(wynik3);
                    }
                    
                    backButton.setNotHiden();
                    main_window.draw(wynikiMenu);
                    if (backButton.isButtonPressed(mousePos, mousePressed))
                        mainMenuNavigation = 0;
                    main_window.draw(backButton);
#pragma endregion
                    break;
                case 4://menu ustawień rozgrywki (rozmiar planszy, liczba min)
#pragma region ustawienia
                    settingsMenuButton.setNotHiden();
                    liczbaMinButton.setNotHiden();
                    sizeXButton.setNotHiden();
                    sizeYButton.setNotHiden();
                    backButton.setNotHiden();
                    if (liczbaMinButton.isButtonPressed(mousePos, mousePressed))
                    {
                        while (main_window.pollEvent(event))
                        {
                            if (event.type == sf::Event::TextEntered)
                            {
                                if (event.text.unicode == '\b' && inputMines.size() > 0)
                                    inputMines.erase(inputMines.size() - 1, 1);
                                else if (event.text.unicode == '\r')
                                    liczbaMinButton.loseFocus();
                                else if (event.text.unicode < 58 && event.text.unicode > 47)
                                    inputMines += static_cast<char>(event.text.unicode);
                                liczbaMinButton.getText(inputMines);
                                if (inputMines.size() > 0)
                                {
                                    if ((boardSizeX * boardSizeY) > std::stoi(inputMines))
                                    {
                                            minesNumber = std::stoi(inputMines);
                                    }
                                    else
                                    {
                                        mainMenuNavigation = 12;
                                        minesNumber = (boardSizeX * boardSizeY) / 3;
                                        liczbaMinButton.getText(std::to_string((boardSizeX * boardSizeY) / 3));
                                        inputMines = std::to_string((boardSizeX * boardSizeY) / 3);
                                    }
                                }
                            }
                        }
                    }
                    if (sizeXButton.isButtonPressed(mousePos, mousePressed))
                    {
                        while (main_window.pollEvent(event))
                        {
                            if (event.type == sf::Event::TextEntered)
                            {
                                if (event.text.unicode == '\b' && inputSizeX.size() > 0)
                                    inputSizeX.erase(inputSizeX.size() - 1, 1);
                                else if (event.text.unicode == '\r')
                                    sizeXButton.loseFocus();
                                else if (event.text.unicode < 58 && event.text.unicode > 47)
                                    inputSizeX += static_cast<char>(event.text.unicode);
                                sizeXButton.getText(inputSizeX);
                                if (inputSizeX.size() > 0)
                                {
                                    if (std::stoi(inputSizeX) < 31)
                                    {
                                            boardSizeX = std::stoi(inputSizeX);
                                    }
                                    else
                                    {
                                        mainMenuNavigation = 12;
                                        sizeXButton.getText("30");
                                        boardSizeX = 30;
                                        inputSizeX = "30";
                                    }
                                }
                            }
                        }
                    }
                    if (sizeYButton.isButtonPressed(mousePos, mousePressed))
                    {
                        while (main_window.pollEvent(event))
                        {
                            if (event.type == sf::Event::TextEntered)
                            {
                                if (event.text.unicode == '\b' && inputSizeY.size() > 0)
                                    inputSizeY.erase(inputSizeY.size() - 1, 1);
                                else if (event.text.unicode == '\r')
                                    sizeYButton.loseFocus();
                                else if (event.text.unicode < 58 && event.text.unicode > 47)
                                    inputSizeY += static_cast<char>(event.text.unicode);
                                sizeYButton.getText(inputSizeY);
                                if (inputSizeY.size() > 0)
                                {
                                    if (std::stoi(inputSizeY) < 31)
                                    {
                                            boardSizeY = std::stoi(inputSizeY);
                                    }
                                    else
                                    {
                                        mainMenuNavigation = 12;
                                        sizeYButton.getText("30");
                                        boardSizeY = 30;
                                        inputSizeY = "30";
                                    }
                                }
                            }

                        }
                    }
                    main_window.draw(liczbaMinButton);
                    main_window.draw(sizeXButton);
                    main_window.draw(sizeYButton);
                    main_window.draw(settingsMenuButton);
                    if (backButton.isButtonPressed(mousePos, mousePressed))
                        mainMenuNavigation = 0;
                    main_window.draw(backButton);
#pragma endregion
                    break;
                case 5://pauzowanie rozgrywki oraz zliczanego czasu
#pragma region pauza
                    resumeButton.setNotHiden();
                    if (resumeButton.isButtonPressed(mousePos, mousePressed))
                        mainMenuNavigation = 1;
                    main_window.draw(resumeButton);
                    clock.restart();
#pragma endregion
                    break;
                case 6://wyświetl czas rozgrywki oraz rezultat (wygrana/przegrana)
#pragma region koniecGry
                    bigTimerWindow.setNotHiden();
                    bigTimerWindow.updateText(std::to_string(playTime / 60 / 60 % 24)
                        + ":" + std::to_string(playTime / 60 % 60)
                        + ":" + std::to_string(playTime % 60));
                    main_window.draw(bigTimerWindow);
                    backButton.setNotHiden();
                    if (backButton.isButtonPressed(mousePos, mousePressed))
                    {
                        mainMenuNavigation = 0;
                        backButton.loseFocus();
                    }
                    main_window.draw(backButton);
                    endGameWindow.setNotHiden();
                    main_window.draw(endGameWindow);
                    break;
#pragma endregion
                case 7://mechanizm logowania użytkowników (sprawdzenie poprawności login-hasło)
#pragma region logowanieCheck
                    it = std::ranges::find(userLogins, userLogin);
                    if (it != std::ranges::end(userLogins))
                    {
                        std::size_t position = std::distance(std::begin(userLogins), it);
                        if (userPasswords[position] == userPassword)
                        {
                            zalogowano = position;
                            mainMenuNavigation = 0;
                        }
                        else
                            mainMenuNavigation = 11;
                    }
                    else
                        mainMenuNavigation =11;
#pragma endregion
                    break;
                case 8://okno rejestracji
#pragma region rejestracja
                    logowanieMenu.setNotHiden();
                    main_window.draw(logowanieMenu);
                    backButton.setNotHiden();
                    if (backButton.isButtonPressed(mousePos, mousePressed))
                        mainMenuNavigation = 0;
                    main_window.draw(backButton);
                    rejestracjaLoginButton.setNotHiden();
                    rejestracjaPassButton.setNotHiden();
                    rejestrujButton.setNotHiden();
                    if (rejestracjaLoginButton.isButtonPressed(mousePos, mousePressed))
                    {
                        while (main_window.pollEvent(event))
                        {
                            if (event.type == sf::Event::TextEntered)
                            {
                                if (event.text.unicode == '\b' && rejestracjaLogin.size() > 0)
                                    rejestracjaLogin.erase(rejestracjaLogin.size() - 1, 1);
                                else if (event.text.unicode == '\r')
                                    rejestracjaLoginButton.loseFocus();
                                else if (event.text.unicode < 255 && event.text.unicode > 32)
                                    rejestracjaLogin += static_cast<char>(event.text.unicode);
                                rejestracjaLoginButton.getText(rejestracjaLogin);
                            }
                        }
                    }
                    if (rejestracjaPassButton.isButtonPressed(mousePos, mousePressed))
                    {
                        while (main_window.pollEvent(event))
                        {
                            if (event.type == sf::Event::TextEntered)
                            {
                                if (event.text.unicode == '\b' && rejestracjaPass.size() > 0)
                                    rejestracjaPass.erase(rejestracjaPass.size() - 1, 1);
                                else if (event.text.unicode == '\r')
                                    rejestracjaPassButton.loseFocus();
                                else if (event.text.unicode < 255 && event.text.unicode > 32)
                                    rejestracjaPass += static_cast<char>(event.text.unicode);
                                rejestracjaPassButton.getText(rejestracjaPass);

                            }
                        }
                    }
                    main_window.draw(rejestracjaLoginButton);
                    main_window.draw(rejestracjaPassButton);
                    if (rejestrujButton.isButtonPressed(mousePos, mousePressed))
                        mainMenuNavigation = 9;
                    main_window.draw(rejestrujButton);
#pragma endregion
                    break;
                case 9://mechanizm sprawdzania poprawności loginu oraz hasła przy rejestracji
#pragma region rejestracjaCheck
                    if (std::regex_search(rejestracjaPass, wzorzecPass) && std::regex_search(rejestracjaPass, wzorzecLogin))
                    {
                        mainMenuNavigation = 0;
                        players.push_back(player(rejestracjaLogin, rejestracjaPass, 9999, playerCounter));
                        zalogowano = players.size()-1;
                    }
                    else
                    {
                        mainMenuNavigation = 8;
                        oknoInformacyjne.setNotHiden();
                        main_window.draw(oknoInformacyjne);
                        wait = true;
                    }  
#pragma endregion
                break;
                case 10://okno zamykania programu po wybraniu opcji wyjście
#pragma region koniecProgramu
                    menu.setNotHiden();
                    playButton.setNotHiden();
                    logowanieButton.setNotHiden();
                    wynikiButton.setNotHiden();
                    settingsButton.setNotHiden();
                    wyjscieButton.setNotHiden();
                    main_window.draw(menu);
                    main_window.draw(playButton);
                    main_window.draw(logowanieButton);
                    main_window.draw(wynikiButton);
                    main_window.draw(settingsButton);
                    main_window.draw(wyjscieButton);
                    for (auto it = players.begin(); it != players.end(); ++it)
                        it->saveToFile(output_file1, output_file2, output_file3);
                    waitBeforeEnd = true;
#pragma endregion
                    break;
                case 11://okno informacyjne o błędnych danych logowania
#pragma region bledneLogowanie
                    mainMenuNavigation = 2;
                    oknoInformacyjne.setNotHiden();
                    main_window.draw(oknoInformacyjne);
                    wait = true;
#pragma endregion
                    break;
                case 12://okno informacyjne o błędnych parametrach ustawień
#pragma region bledneUstawienia
                    oknoInformacyjne2.setNotHiden();
                    main_window.draw(oknoInformacyjne2);
                    wait = true;
                    mainMenuNavigation = 4;
#pragma endregion
                    break;
                case 13://algorytm sortujący wyniki od najlepszych do najgorszych
#pragma region sortowanieWynikow
                    mainMenuNavigation = 3;
                    int tmp=-1;
                    if(zalogowano ==-1)
                        std::sort(players.begin(), players.end(), comparator);
                    else
                    {
                        tmp = players[zalogowano].returnPlayerNumber();
                        std::sort(players.begin(), players.end(), comparator);
                        for (int i = 0; i < players.size(); ++i) {
                            if (players[i].playerNumber == tmp) {
                                zalogowano = i;
                            }
                        }
                    }
#pragma endregion
                    break;
                }
                main_window.display();
                if (wait)//oczekiwanie przed zamknięciem okna informacyjnego jeśli otwarte
                {
                    wait = false;
                    std::chrono::milliseconds duration(5000);
                    std::this_thread::sleep_for(duration);   
                }
                if (waitBeforeEnd)//oczekiwanie przed zamknięciem program jeśli kliknięty przycisk wyjście
                {
                    std::chrono::milliseconds duration(3000);
                    std::this_thread::sleep_for(duration);
                    main_window.close();
                }                        
        }

            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right))//zwolnienie naciśnietych przycisków jeśli przycisk myszy nie jest kliknięty
            {
                mousePressed = 0;
                if (loseFocus) 
                    playButton.loseFocus();               
                else               
                    loseFocus = true;
            logowanieButton.loseFocus();
            settingsButton.loseFocus();
            wynikiButton.loseFocus();
            backButton.loseFocus();
            playingButton.loseFocus();
            stopButton.loseFocus();
            resumeButton.loseFocus();
            rejestrujButton.loseFocus();
            zalogujButton.loseFocus();
            wylogujButton.loseFocus();
            rejestracjaButton.loseFocus();
            nextButton.loseFocus();
            previousButton.loseFocus();

            } 
    }
    return 0;
}
