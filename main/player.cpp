#include "player.h"

player::player(std::string player_login, std::string player_pass, int player_score, int player_number) //Lista inicjalizacyjna obiektu player. Przyjmuje login,has³o,wynik oraz numer w wektorze.
	:playerLogin(player_login), playerPass(player_pass), playerScore(player_score), playerNumber(player_number) {}

void player::saveToFile(std::ofstream& output_file1, std::ofstream& output_file2, std::ofstream& output_file3)//metoda zapisuj¹ca login,has³o,wynik do plików przekazanych w parametrach
{
	output_file1 << playerLogin << "\n";
	output_file2 << playerPass << "\n";
	output_file3 << playerScore << "\n";
}
