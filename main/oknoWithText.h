			#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "okno.h"
class oknoWithText :public okno
{
public:
	oknoWithText() = delete;
	oknoWithText(int main_window_x, int main_window_y,
		int okno_x, int okno_y, int okno_offset_x, int okno_offset_y,
		int okno_R, int okno_G, int okno_B, int okno_transparency, 
		bool draw_brim, std::string text_1, sf::Font font, int size);
	~oknoWithText() = default;

	sf::Font textFont;
	std::string text1;
	int textSize, oknoTransparency;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	void updateText(std::string text_1) { text1 = text_1; }//metoda aktualizuj¹ca wyœwietlany text na przekazany w parametrze
};

