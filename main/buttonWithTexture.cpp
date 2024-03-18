#include "buttonWithTexture.h"


buttonWithTexture::buttonWithTexture(int main_window_x, int main_window_y,
	int okno_x, int okno_y, int okno_offset_x, int okno_offset_y,
	int okno_R, int okno_G, int okno_B, int okno_transparency,
	bool draw_brim, std::string button_texture_name )//lista inicjalizacyjna dla obiektów z jedn¹ tekstur¹
	:button(main_window_x, main_window_y, okno_x, okno_y, okno_offset_x, okno_offset_y,
		okno_R, okno_G, okno_B, draw_brim), oknoTransparency(okno_transparency), buttonTextureName(button_texture_name)	
{
	oknoShape.setFillColor(sf::Color(okno_R, okno_G, okno_R, oknoTransparency));
	if (!buttonTexture.loadFromFile(buttonTextureName))
		std::cout << "koniec programu" << '\n';
	oknoShape.setTexture(&buttonTexture);
}

buttonWithTexture::buttonWithTexture(int main_window_x, int main_window_y,
	int okno_x, int okno_y, int okno_offset_x, int okno_offset_y,
	int okno_R, int okno_G, int okno_B, int okno_transparency,
	bool draw_brim, std::string button_texture_name, std::string button_texture_name_2)//lista inicjalizacyjna dla obitków z dwoma teksturami
	:button(main_window_x, main_window_y, okno_x, okno_y, okno_offset_x, okno_offset_y,
		okno_R, okno_G, okno_B, draw_brim), oknoR(okno_R), oknoG(okno_G), oknoB(okno_B), oknoTransparency(okno_transparency), buttonTextureName(button_texture_name), buttonTextureName2(button_texture_name_2)
{
	oknoShape.setFillColor(sf::Color(okno_R, okno_G, okno_R, oknoTransparency));
}

void buttonWithTexture::initializeTexture()//inicjalizuj teksturê
{
	if (!buttonTexture.loadFromFile(buttonTextureName) || !buttonTexture2.loadFromFile(buttonTextureName2))
			std::cout << "koniec programu" << '\n';
}

int buttonWithTexture::conditionalReturnNumberOfNeighbors(sf::Vector2i mousePos, int mousePressed)//metoda zwracaj¹ca liczbê s¹siaduj¹cych min jeœli przycisk zosta³ klikniêty pierwszy raz. W przeciwnym wypadku zwraca b³¹d: -10000
{
	if (isHiden)
	{
		if (mousePos.x > (oknoShape.getPosition().x - oknoShape.getSize().x / 2)
			&& mousePos.x < (oknoShape.getPosition().x + oknoShape.getSize().x / 2)
			&& mousePos.y >(oknoShape.getPosition().y - oknoShape.getSize().y / 2)
			&& mousePos.y < (oknoShape.getPosition().y + oknoShape.getSize().y / 2)
			&& (mousePressed==1)
			&& buttonPressed == 0)
			return numberOfNeighbors;
	}
		return - 10000;
	
}



int buttonWithTexture::play(sf::Vector2i mousePos, int mousePressed)//metoda "odkrywaj¹ca" zawartoœæ okienka po klikniêcciu. Zwraca liczbê s¹siaduj¹cych min jeœli przycisk zosta³ klikniêty pierwszy raz. W przeciwnym wypadku lub gdy klikniêtyo ppm wypadcku zwraca -10000
{
	if (isHiden)
	{
		if (mousePos.x > (oknoShape.getPosition().x - oknoShape.getSize().x / 2)
			&& mousePos.x < (oknoShape.getPosition().x + oknoShape.getSize().x / 2)
			&& mousePos.y >(oknoShape.getPosition().y - oknoShape.getSize().y / 2)
			&& mousePos.y < (oknoShape.getPosition().y + oknoShape.getSize().y / 2))
		{

			if (mousePressed==1 && buttonLock == 0 && buttonPressed == 0)
			{
				if (numberOfNeighbors < 0)
					oknoShape.setTexture(&buttonTexture);
				else
				{
					oknoShape.setFillColor(sf::Color(49, 89, 61));
					if (numberOfNeighbors == 1)
					{
						buttonTexture3.loadFromFile("1.png");
						oknoShape.setTexture(&buttonTexture3);
					}
					else if (numberOfNeighbors == 2)
					{
						buttonTexture3.loadFromFile("2.png");
						oknoShape.setTexture(&buttonTexture3);
					}
					else if (numberOfNeighbors == 3)
					{
						sf::Texture liczbaTexture;
						buttonTexture3.loadFromFile("3.png");
						oknoShape.setTexture(&buttonTexture3);
					}
					else if (numberOfNeighbors == 4)
					{
						buttonTexture3.loadFromFile("4.png");
						oknoShape.setTexture(&buttonTexture3);
					}
					else if (numberOfNeighbors == 5)
					{
						buttonTexture3.loadFromFile("5.png");
						oknoShape.setTexture(&buttonTexture3);
					}
					else if (numberOfNeighbors == 6)
					{
						buttonTexture.loadFromFile("6.png");
						oknoShape.setTexture(&buttonTexture3);
					}
					else if (numberOfNeighbors == 7)
					{
						sf::Texture liczbaTexture;
						if (!liczbaTexture.loadFromFile("7.png"))
							oknoShape.setTexture(&liczbaTexture);
					}
					else if (numberOfNeighbors == 8)
					{
						sf::Texture liczbaTexture;
						if (!liczbaTexture.loadFromFile("8.png"))
							oknoShape.setTexture(&liczbaTexture);
					}
					else if (numberOfNeighbors == 0)
					{
						buttonTexture3.loadFromFile("0.png");
						oknoShape.setTexture(&buttonTexture3);
					}
				}
				buttonLock = 1;
				return numberOfNeighbors;
			}
			if (mousePressed==2 && buttonLock == 0)
			{

				if (buttonPressed == 0)
				{
					buttonTexture3.loadFromFile(buttonTextureName2);
					oknoShape.setFillColor(sf::Color(255, 255, 255));
					oknoShape.setTexture(&buttonTexture3);
					buttonPressed = 1;
				}
				else
				{
					buttonPressed = 0;
					oknoShape.setFillColor(sf::Color(oknoR, oknoG, oknoR, oknoTransparency));
					oknoShape.setTexture(nullptr);
				}
			}
		}
	}
		return -10000;
}

void buttonWithTexture::loseFocus()//metoda zwalniaj¹ca przycisk od "naciœniêcia" i przywracaj¹ca oryginalny kolor
{
	buttonPressed = 0;
	oknoShape.setFillColor(sf::Color(oknoR, oknoG, oknoB, oknoTransparency));
}

bool buttonWithTexture::isButtonPressed(sf::Vector2i mousePos, int mousePressed) //metoda zwracaj¹ca true, oraz cieniuje przycisk jeœli zosta³ naciœniêty
{
	if (isHiden)
	{
		if (mousePos.x > (oknoShape.getPosition().x - oknoShape.getSize().x / 2)
			&& mousePos.x < (oknoShape.getPosition().x + oknoShape.getSize().x / 2)
			&& mousePos.y >(oknoShape.getPosition().y - oknoShape.getSize().y / 2)
			&& mousePos.y < (oknoShape.getPosition().y + oknoShape.getSize().y / 2))
		{
			if (mousePressed==1 && buttonPressed == 0 && buttonLock == 0)
			{
				buttonPressed = 1;
				oknoShape.setFillColor(sf::Color(49, 89, 61));
			}
		}
		else if (mousePressed==1 && buttonPressed == 1 && buttonLock == 0)
			this->loseFocus();
	}
	return buttonPressed;
}


int buttonWithTexture::buttonOpen()//Metoda "odkrywaj¹ca" zawartoœæ pola jeœli jeszcze nie zosta³o odkryte. Zwraca liczbê s¹siaduj¹cych min.
{
	if (buttonLock==0 && buttonPressed == 0)
	{
		if (numberOfNeighbors < 0)
			oknoShape.setTexture(&buttonTexture);
		else
		{
			oknoShape.setFillColor(sf::Color(49, 89, 61));
			if (numberOfNeighbors == 1)
			{
				buttonTexture3.loadFromFile("1.png");
				oknoShape.setTexture(&buttonTexture3);
			}
			else if (numberOfNeighbors == 2)
			{
				buttonTexture3.loadFromFile("2.png");
				oknoShape.setTexture(&buttonTexture3);
			}
			else if (numberOfNeighbors == 3)
			{
				buttonTexture3.loadFromFile("3.png");
				oknoShape.setTexture(&buttonTexture3);
			}
			else if (numberOfNeighbors == 4)
			{
				buttonTexture3.loadFromFile("4.png");
				oknoShape.setTexture(&buttonTexture3);
			}
			else if (numberOfNeighbors == 5)
			{

				buttonTexture3.loadFromFile("5.png");
				oknoShape.setTexture(&buttonTexture3);
			}
			else if (numberOfNeighbors == 6)
			{
				buttonTexture3.loadFromFile("6.png");
				oknoShape.setTexture(&buttonTexture3);
			}
			else if (numberOfNeighbors == 7)
			{
				buttonTexture3.loadFromFile("7.png");
				oknoShape.setTexture(&buttonTexture3);
			}
			else if (numberOfNeighbors == 8)
			{
				buttonTexture3.loadFromFile("8.png");
				oknoShape.setTexture(&buttonTexture3);
			}
			else if (numberOfNeighbors == 0)
			{
				buttonTexture3.loadFromFile("0.png");
				oknoShape.setTexture(&buttonTexture3);
			}
		}
		buttonLock = 1;
	}
	return numberOfNeighbors;
}
