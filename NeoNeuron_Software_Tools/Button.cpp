#include "Button.h"
#include<iostream>

using namespace std;

Button::Button() {

}

Button::Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {

	text.setString(t);
	text.setFillColor(textColor);
	text.setCharacterSize(charSize);

	button.setSize(size);
	button.setFillColor(bgColor);
	button.setOutlineColor(sf::Color::Black);
	button.setOutlineThickness(3.0f);
}

void Button::setFont(sf::Font& font) {
	text.setFont(font);
}

void Button::setBackColor(sf::Color color) {
	button.setFillColor(color);
}

void Button::setTextColor(sf::Color color) {
	text.setFillColor(color);
}

void Button::setPosition(sf::Vector2f newPosition) {
	button.setPosition(newPosition);

	/*cout << "left: " << text.getLocalBounds().left << endl;
	cout << "width: " << text.getLocalBounds().width << endl;
	cout << "top: " << text.getLocalBounds().top << endl;
	cout << "height: " << text.getLocalBounds().height << endl;
	cine mag
	cout << "hmm: " << text.getCharacterSize()* text.getString().getSize() << endl;*/

	//text.setOrigin({ (text.getCharacterSize() * text.getString().getSize()) / 2.0f,text.getCharacterSize() / 2.0f });

	float xPos = newPosition.x;// / 2 + button.getGlobalBounds().width;// / 2;// -(text.getLocalBounds().width / 2) * 2;
	float yPos = newPosition.y;//*0.75 + button.getGlobalBounds().height;// / 2;// -(text.getLocalBounds().height / 2) * 2;
	/*
	auto center = text.getGlobalBounds().getSize() / 2.f;
	text.getGlobalBounds().
	auto localBounds = center + text.getLocalBounds().getPosition();
	auto rounded = round(localBounds);

	text.setOrigin(rounded);*/
	text.setPosition({ xPos, yPos });

}

sf::Vector2f Button::round(const sf::Vector2f vector)
{
	return sf::Vector2f{ std::round(vector.x), std::round(vector.y) };
}


void Button::drawTo(sf::RenderWindow& window) {
	window.draw(button);
	window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow& window) {
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	float btnPosX = button.getPosition().x;
	float btnPosY = button.getPosition().y;

	float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
	float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

	if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
		return true;
	}
	else {
		return false;
	}
}

sf::Vector2f Button::getPosition() {
	return button.getPosition();
}

sf::RectangleShape Button::getBtnShape() {
	return button;
}