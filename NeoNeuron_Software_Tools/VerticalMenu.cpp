#include "VerticalMenu.h"

VerticalMenu::VerticalMenu(sf::Font& font) {

	for (int i = 0; i < buttonsQtyVeritcalMenu; i++) {
		Button btn(texts[i], btnSize, 20, sf::Color::White, sf::Color::Black);
		btn.setPosition({ position.x + (btnSize.x + offset) * (i + 1), position.y });
		btn.setFont(font);
		//buttons[i] = btn;
		buttons.push_back(btn);
	}
}

VerticalMenu::VerticalMenu(sf::Vector2f newPosition, string newTexts[buttonsQtyVeritcalMenu], sf::Font& font) {
	position = newPosition;

	for (int i = 0; i < buttonsQtyVeritcalMenu; i++) {
		Button btn(newTexts[i], btnSize, 20, sf::Color::White, sf::Color::Black);
		btn.setPosition({ newPosition.x + (btnSize.x + offset) * (i + 1), newPosition.y});
		btn.setFont(font);
		//buttons[i] = btn;
		buttons.push_back(btn);
	}
}

void VerticalMenu::update(sf::Event& event, sf::RenderWindow& window) {
	switch (event.type) {
	case sf::Event::MouseMoved:
		for (int i = 0; i < buttonsQtyVeritcalMenu; i++) {
			if (buttons[i].isMouseOver(window)) {
				buttons[i].setBackColor(sf::Color::Red);
			}
			else {
				buttons[i].setBackColor(sf::Color::White);
			}
		}
		break;
	case sf::Event::MouseButtonPressed:
		for (int i = 0; i < buttonsQtyVeritcalMenu; i++) {
			if (buttons[i].isMouseOver(window)) {
				Action(i);
			}
		}
		break;
	default:
		return;
	}
}

void VerticalMenu::Action(int id) {
	switch (id) {
	case 0:
		cout << "You pressed btn: 0" << endl;
		break;
	case 1:
		cout << "You pressed btn: 1" << endl;
		break;
	case 2:
		cout << "You pressed btn: 2" << endl;
		break;
	}
}

void VerticalMenu::drawTo(sf::RenderWindow& window) {
	for (int i = 0; i < buttonsQtyVeritcalMenu; i++) {
		buttons[i].drawTo(window);
	}
}

void VerticalMenu::setPosition(sf::Vector2f newPosition) {
	position = newPosition;

	for (int i = 0; i < buttonsQtyVeritcalMenu; i++) {
		buttons[i].setPosition({ newPosition.x, newPosition.y + btnSize.y * (i + 1) });
	}
}