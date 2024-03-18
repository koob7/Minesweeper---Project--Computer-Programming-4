#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "okno.h"
class button :public okno
{
public:
	button()=delete;
	button(int main_window_x, int main_window_y, 
		int okno_x, int okno_y, int okno_offset_x, int okno_offset_y, 
		int okno_R, int okno_G, int okno_B,bool draw_brim);
	~button() = default;

	bool buttonPressed = 0;
	void loseFocus();
	bool isButtonPressed(sf::Vector2i mousePos, int mousePressed);

};

