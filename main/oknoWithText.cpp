#include "oknoWithText.h"

oknoWithText::oknoWithText(int main_window_x, int main_window_y,
	int okno_x, int okno_y, int okno_offset_x, int okno_offset_y,
	int okno_R, int okno_G, int okno_B, int okno_transparency, bool draw_brim, std::string text_1, sf::Font font, int size)//lista inicjalizacyjna obiektu oknoWithText
	:okno(main_window_x, main_window_y,
	okno_x, okno_y, okno_offset_x, okno_offset_y,
	okno_R, okno_G, okno_B, draw_brim), oknoTransparency(okno_transparency), 
	text1(text_1), textFont(font), textSize(size)
			{
				oknoShape.setFillColor(sf::Color(okno_R, okno_G, okno_R, oknoTransparency));
			}

void oknoWithText::draw(sf::RenderTarget& target, sf::RenderStates state) const//Metoda rysuj¹ca obiekt na ekranie. Korzysta z metod dostêpnych w bibliotece SFML.
{
	if (drawBrim)
		target.draw(this->oknoBrim, state);
	target.draw(this->oknoShape, state);
	sf::Text napis;
	napis.setFont(textFont);
	napis.setCharacterSize(textSize);
	napis.setFillColor(sf::Color::White);
	napis.setString(text1);
	napis.setPosition(sf::Vector2f((oknoOffsetX - oknoX / 2), (oknoOffsetY - oknoY / 2)));
	target.draw(napis, state);
}
