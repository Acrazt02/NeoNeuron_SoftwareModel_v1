#pragma once

#ifndef HORIZONTALMENU_HPP_INCLUDED
#define HORIZONTALMENU_HPP_INCLUDED

constexpr auto buttonsQtyHorizontalMenu = 5;

#include <SFML/Graphics.hpp>
#include "Button.h"
#include <iostream>
#include <vector>

using namespace std;

class HorizontalMenu {

public:
	HorizontalMenu(sf::Font &font);
	HorizontalMenu(sf::Vector2f position, string texts[buttonsQtyHorizontalMenu], sf::Font &font);
	void update(sf::Event& event, sf::RenderWindow& window);
	void drawTo(sf::RenderWindow& window);
	void setPosition(sf::Vector2f position);
	bool isMouseOver(sf::RenderWindow& window);
	int getMode();

private:
	void Action(int id);

	sf::Vector2f position = { 50.0f, 50.0f };
	//Button buttons[buttonsQty];
	vector<Button> buttons;
	vector<string> texts = { "Add", "Del", "Edit", "Text", "Drag" };
	sf::Vector2f btnSize = { 50.0f, 50.0f };
	sf::Font font;
	int offset = 8;
	int mode = -1;
}; 

#endif // HORIZONTALMENU_HPP_INCLUDED

