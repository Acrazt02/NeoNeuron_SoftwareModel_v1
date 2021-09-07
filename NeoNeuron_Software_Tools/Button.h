#pragma once

#ifndef BOTON_HPP_INCLUDED
#define BOTON_HPP_INCLUDED
#include <SFML/Graphics.hpp>

class Button {
	public:
		Button();
		Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor);

		void setFont(sf::Font& font);

		void setBackColor(sf::Color color);

		void setTextColor(sf::Color color);

		void setPosition(sf::Vector2f newPosition);

		void drawTo(sf::RenderWindow& window);

		bool isMouseOver(sf::RenderWindow& window);

		sf::Vector2f getPosition();

		sf::RectangleShape getBtnShape();

	private:
		sf::RectangleShape button;
		sf::Text text;

		sf::Vector2f round(const sf::Vector2f vector);

};

#endif // BUTTON_HPP_INCLUDED