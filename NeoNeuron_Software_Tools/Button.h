#pragma once

#ifndef BOTON_HPP_INCLUDED
#define BOTON_HPP_INCLUDED
#include <SFML/Graphics.hpp>

class Button {
public:
	Button();
	Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {

		text.setString(t);
		text.setFillColor(textColor);
		text.setCharacterSize(charSize);

		button.setSize(size);
		button.setFillColor(bgColor);
	}

	void setFont(sf::Font& font) {
		text.setFont(font);
	}

	void setBackColor(sf::Color color){
		button.setFillColor(color);
	}

	void setTextColor(sf::Color color) {
		text.setFillColor(color);
	}

	void setPosition(sf::Vector2f newPosition) {
		button.setPosition(newPosition);

		float xPos = (newPosition.x + button.getLocalBounds().width/2) - (text.getLocalBounds().width/2);
		float yPos = (newPosition.y + button.getLocalBounds().height/2) - (text.getLocalBounds().height/2);
		/*
		auto center = text.getGlobalBounds().getSize() / 2.f;
		auto localBounds = center + text.getLocalBounds().getPosition();
		auto rounded = round(localBounds);
		
		text.setOrigin(rounded);*/
		text.setPosition({ xPos, yPos });

	}

	void drawTo(sf::RenderWindow &window) {
		window.draw(button);
		window.draw(text);
	}

	bool isMouseOver(sf::RenderWindow &window) {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;

		float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
		float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

		if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
			return true;
		}
		else{
				return false;
		}
	}

	private:
		sf::RectangleShape button;
		sf::Text text;
};


#endif // BUTTON_HPP_INCLUDED