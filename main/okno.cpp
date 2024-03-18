#include "okno.h"

okno::okno(int main_window_x, int main_window_y, 
	int okno_x, int okno_y, int okno_offset_x, int okno_offset_y, 
	int okno_R, int okno_G, int okno_B, bool draw_brim) //lista inicjalizacyjna obiektu okno
{
	mainWindowX = main_window_x;
	mainWindowY = main_window_y;
	oknoX = okno_x;
	oknoY = okno_y;
	oknoOffsetX = okno_offset_x;
	oknoOffsetY = okno_offset_y;
	oknoR = okno_R;
	oknoG = okno_G;
	oknoB = okno_B;
	drawBrim = draw_brim;
	oknoBrim.setSize(sf::Vector2f(okno_x + 10, okno_y + 10));
	oknoBrim.setOrigin(sf::Vector2f((okno_x + 10) / 2, (okno_y + 10) / 2));
	oknoBrim.setFillColor(sf::Color::White);
	oknoBrim.setPosition(sf::Vector2f(( okno_offset_x), ( okno_offset_y)));
	oknoShape.setSize(sf::Vector2f(okno_x, okno_y));
	oknoShape.setOrigin(sf::Vector2f(okno_x / 2, okno_y / 2));
	oknoShape.setFillColor(sf::Color(okno_R, okno_G, okno_R));
	oknoShape.setPosition(sf::Vector2f((okno_offset_x), (okno_offset_y)));

}

void okno::draw(sf::RenderTarget& target, sf::RenderStates state) const//metoda rysuj¹ca obiekt na ekranie. Korzysta z metod dostêpnych w bibliotece SFML
{
	if (isHiden)
	{
		if (drawBrim)
			target.draw(this->oknoBrim, state);
		target.draw(this->oknoShape, state);
	}
}