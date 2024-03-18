#include "buttonWithText.h"
#include "button.h"
#include "okno.h"
#include <thread>
#include <chrono>

buttonWithText::buttonWithText(int main_window_x, int main_window_y, 
	int okno_x, int okno_y, int okno_offset_x, int okno_offset_y, 
	int okno_R, int okno_G, int okno_B, int okno_transparency,
	bool draw_brim, std::string text1, std::string text2, sf::Font font, int size)//lista inicjalizacyjna obiektu buttonWithText
	:button(main_window_x, main_window_y, okno_x, okno_y, okno_offset_x, okno_offset_y, 
	okno_R, okno_G, okno_B, draw_brim), 
	buttonString1(text1), buttonString2(text2), buttonFont(font), buttonTextSize(size), oknoTransparency(okno_transparency) 
{
	oknoShape.setFillColor(sf::Color(okno_R, okno_G, okno_R, oknoTransparency));
}

void buttonWithText::draw(sf::RenderTarget& target, sf::RenderStates state) const//Metoda rysuj¹ca obiekt na ekranie. Korzysta z metod dostêpnych w bibliotece SFML
{
	if (isHiden)
	{
		if (drawBrim)
			target.draw(oknoBrim, state);
		target.draw(oknoShape, state);
		sf::Text oknoText;
		oknoText.setFont(buttonFont);
		oknoText.setCharacterSize(buttonTextSize);
		oknoText.setPosition(sf::Vector2f((oknoOffsetX - oknoX / 2), (oknoOffsetY - oknoY / 2)));
		if (!buttonPressed)
			oknoText.setString(buttonString1);
		else
			oknoText.setString(buttonString2);
		oknoText.setFillColor(sf::Color::White);
		target.draw(oknoText, state);
	}
}


void buttonWithText::getText(std::string tmpString)//metoda aktualizuj¹ca wyœwietlany tekst na przekazany w parametrze metody
{
	buttonString1 = tmpString;
	buttonString2 = tmpString;
}

bool buttonWithText::isButtonPressed(sf::Vector2i mousePos, int mousePressed)//metoda zwracaj¹ca true oraz cieniuj¹ca przycisk jeœli zosta³ naciœniêty
{
	if (isHiden)
	{
		if (mousePos.x > (oknoShape.getPosition().x - oknoShape.getSize().x / 2)
			&& mousePos.x < (oknoShape.getPosition().x + oknoShape.getSize().x / 2)
			&& mousePos.y >(oknoShape.getPosition().y - oknoShape.getSize().y / 2)
			&& mousePos.y < (oknoShape.getPosition().y + oknoShape.getSize().y / 2))
		{
			if (mousePressed==1 && buttonPressed == 0)
			{
				buttonPressed = 1;
				oknoShape.setFillColor(sf::Color(49, 89, 61));
			}
		}
		else if (mousePressed==1 && buttonPressed == 1)
			this->loseFocus();
	}
	return buttonPressed;
}
