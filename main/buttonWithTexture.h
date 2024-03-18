#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <dos.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "button.h"

class buttonWithTexture :public button
{
public:
	buttonWithTexture()=delete;
	buttonWithTexture(int main_window_x, int main_window_y,
		int okno_x, int okno_y, int okno_offset_x, int okno_offset_y,
		int okno_R, int okno_G, int okno_B, int okno_transparency,
		bool draw_brim, std::string button_texture_name);
	buttonWithTexture(int main_window_x, int main_window_y,
		int okno_x, int okno_y, int okno_offset_x, int okno_offset_y,
		int okno_R, int okno_G, int okno_B, int okno_transparency,
		bool draw_brim, std::string button_texture_name, std::string button_texture_name_2);
	~buttonWithTexture() = default;

	
	int oknoTransparency;
	std::string buttonTextureName;
	std::string buttonTextureName2;
	sf::Texture buttonTexture;
	sf::Texture buttonTexture2;
	sf::Texture buttonTexture3;
	int numberOfNeighbors = 0;
	int oknoR, oknoG, oknoB;
	int buttonState = 0;
	int buttonLock = 0;																
	bool buttonOpenedOnce = false;
	void initializeTexture();
	int play(sf::Vector2i mousePos, int mousePressed);
	bool isButtonLock() { return buttonLock; }//zwraca informacj� czy przycisk jest otwarty (odwracalne - mo�na przycisk zakry� powrotnie)
	void setNumberOfNeighbors(int i) {numberOfNeighbors = i; }//ustawia liczb� s�siaduj�cych min na warto�� przekazan� w parametrze
	int returnNumberOfNeighbors() { return numberOfNeighbors; }//zwraca liczb� s�siaduj�cych min
	int conditionalReturnNumberOfNeighbors(sf::Vector2i mousePos, int mousePressed);
	void incrementNumberOfNeighbors() { numberOfNeighbors++; }//zwi�ksza liczb� s�siednich min o 1
	bool isButtonOpenedOnce() { if (!buttonOpenedOnce) { buttonOpenedOnce = true; return false; } else return true; }//zwraca informacj� czy przycisk zosta� otwarty (nieodwracalne)
	void resetNumberOfNeighbours() { numberOfNeighbors = 0; }//ustawia liczbe s�siaduj�cych min na 0
	bool isButtonPressed(sf::Vector2i mousePos, int mousePressed);
	void loseFocus();
	void setNumberOfNeighbors();
	int buttonOpen();

};



