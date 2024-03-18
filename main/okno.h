#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
class okno :public sf::Drawable
{
public:
	okno() = delete;
	okno(int main_window_x, int main_window_y, int okno_x, 
		int okno_y, int okno_offset_x, int okno_offset_y, 
		int okno_R, int okno_G, int okno_B, bool draw_brim);
	~okno() = default;

	int mainWindowX, mainWindowY, oknoY, oknoX, oknoOffsetX, oknoOffsetY, oknoR, oknoG, oknoB;
	bool drawBrim, isHiden=0;
	sf::RectangleShape oknoShape;
	sf::RectangleShape oknoBrim;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	bool checkIsHiden() { return isHiden; }//zwraca informacjê czy okno jest ukryte
	void setHiden() { isHiden = 0; }//ukrywa okno
	void setNotHiden() { isHiden = 1; }//odkrywa okno

};