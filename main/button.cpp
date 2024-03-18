#include "button.h"

button::button(int main_window_x, int main_window_y, 
	int okno_x, int okno_y, int okno_offset_x, int okno_offset_y, 
	int okno_R, int okno_G, int okno_B, bool draw_brim)//lista inicjalizacyjna obiektów button
	:okno(main_window_x, main_window_y, 
	okno_x, okno_y, okno_offset_x, okno_offset_y,
	okno_R, okno_G, okno_B, draw_brim) {}

bool button::isButtonPressed(sf::Vector2i mousePos, int mousePressed)//metoda zwracaj¹ca true oraz cieniuj¹ca przycisk jeœli zosta³ naciœniêty
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
				oknoShape.setFillColor(sf::Color (49, 89, 61));
			}
		}
		else if (mousePressed==1 && buttonPressed == 1)
			this->loseFocus();
	}
	return buttonPressed;
}
void button::loseFocus()//metoda zwalniaj¹ca przycisk od "naciœniêcia" i przywracaj¹ca oryginalny kolor
{
	buttonPressed = 0;
	oknoShape.setFillColor(sf::Color(oknoR, oknoG, oknoB));
}