#pragma once
#include <iostream>
#include <fstream>

class player
{
public:
	player() = delete;
	player(std::string user_login, std::string user_pass, int _score, int player_number);
	~player() = default;
	std::string playerLogin, playerPass;
	int playerScore, playerNumber;
	void saveToFile(std::ofstream &output_file1, std::ofstream &output_file2, std::ofstream &output_file3);
	void setScore(int score) {playerScore = score; }//ustawia wynik gracza na ten przekazany w parametrze
	int returnScore() { return playerScore; }
	int returnPlayerNumber() { return playerNumber; }//metoda zwracaj¹ca numer gracza w wektorze
	std::string returnLogin() { return playerLogin; }//metoda zwracaj¹ca login gracza
	
	
};

