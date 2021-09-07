#pragma once

constexpr auto buttonsQtyVeritcalMenu = 3;

#include <SFML/Graphics.hpp>
#include "Button.h"
#include <iostream>
#include <vector>

using namespace std;

class VerticalMenu
{

public:
	VerticalMenu(sf::Font& font);
	VerticalMenu(sf::Vector2f position, string texts[buttonsQtyVeritcalMenu], sf::Font& font);
	void update(sf::Event& event, sf::RenderWindow& window);
	void drawTo(sf::RenderWindow& window);
	void setPosition(sf::Vector2f position);
	bool isMouseOver(sf::RenderWindow& window);

private:
	void Action(int id);

	sf::Vector2f position = { 50.0f, 50.0f };
	//Button buttons[buttonsQty];
	vector<Button> buttons;
	vector<string> texts = { "Open", "Save", "Print"};
	sf::Vector2f btnSize = { 50.0f, 50.0f };
	sf::Font font;
	int offset = 8;
};

