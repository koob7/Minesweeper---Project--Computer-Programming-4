#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "button.h"
#include "okno.h"
class buttonWithText : public button
{
public:
	buttonWithText()=delete;
	buttonWithText(int main_window_x, int main_window_y, 
	int okno_x, int okno_y, int okno_offset_x, int okno_offset_y, 
	int okno_R, int okno_G, int okno_B,int okno_transparency, 
	bool draw_brim, std::string text1, std::string text2, sf::Font font, int size);
	~buttonWithText() = default;
	

	int buttonTextSize, oknoTransparency;
	std::string buttonString1, buttonString2;
	sf::Font buttonFont;
	
	

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	void getText(std::string tmpString);
	bool isButtonPressed(sf::Vector2i mousePos, int mousePressed);


};