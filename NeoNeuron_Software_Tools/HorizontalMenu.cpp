#include "HorizontalMenu.h"
#include "Connectome.h"

HorizontalMenu::HorizontalMenu(sf::Font &font) {

	for (int i = 0; i < buttonsQtyHorizontalMenu; i++) {
		Button btn(texts[i], btnSize, 20, sf::Color::White, sf::Color::Black);
		btn.setPosition({ position.x, position.y + (btnSize.y + offset) * (i + 1)});
		btn.setFont(font);
		//buttons[i] = btn;
		buttons.push_back(btn);
	}
}

HorizontalMenu::HorizontalMenu(sf::Vector2f newPosition, string newTexts[buttonsQtyHorizontalMenu], sf::Font &font) {
	position = newPosition;

	for (int i = 0; i < buttonsQtyHorizontalMenu; i++) {
		Button btn(newTexts[i],btnSize, 20,sf::Color::White, sf::Color::Black);
		btn.setPosition({ newPosition.x, newPosition.y + (btnSize.y + offset) * (i + 1) });
		btn.setFont(font);
		//buttons[i] = btn;
		buttons.push_back(btn);
	}
}

void HorizontalMenu::update(sf::Event& event, sf::RenderWindow& window) {
	switch (event.type) {
	case sf::Event::MouseMoved:
		for (int i = 0; i < buttonsQtyHorizontalMenu; i++) {
			if (buttons[i].isMouseOver(window)) {
				buttons[i].setBackColor(sf::Color::Red);
			}
			else {
				buttons[i].setBackColor(sf::Color::White);
			}
		}
		break;
	case sf::Event::MouseButtonPressed:
		for (int i = 0; i < buttonsQtyHorizontalMenu; i++) {
			if (buttons[i].isMouseOver(window)) {
				Action(i);
			}
		}
		break;
	default:
		return;
	}
}

void HorizontalMenu::Action(int id) {
	switch (id) {
	case 0:
		cout << "You pressed btn: 0" << endl;
		Connectome connectionsToSave;
		connectionsToSave.addConnection(1,0, 1, 0);
		break;
	case 1:
		cout << "You pressed btn: 1" << endl;
		break;
	case 2:
		cout << "You pressed btn: 2" << endl;
		break;
	case 3:
		cout << "You pressed btn: 3" << endl;
		break;
	case 4:
		cout << "You pressed btn: 4" << endl;
		break;
	}
}

void HorizontalMenu::drawTo(sf::RenderWindow& window) {
	for (int i = 0; i < buttonsQtyHorizontalMenu; i++) {
		buttons[i].drawTo(window);
	}
}

void HorizontalMenu::setPosition(sf::Vector2f newPosition) {
	position = newPosition;

	for (int i = 0; i < buttonsQtyHorizontalMenu; i++) {
		buttons[i].setPosition({ newPosition.x, newPosition.y + btnSize.y * (i + 1) });
	}
}

bool HorizontalMenu::isMouseOver(sf::RenderWindow& window) {
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	float btnPosX = buttons[0].getPosition().x;
	float btnPosY = buttons[0].getPosition().y;

	/*for (int i = 0; i < buttonsQtyHorizontalMenu; i++) {

		sf::Vector2f getPos = buttons[i].getPosition();

		btnPosX += getPos.x;
		btnPosY += getPos.y;
	}*/

	float btnxPosWidth = buttons[0].getPosition().x + buttons[0].getBtnShape().getLocalBounds().width;
	float btnyPosHeight = buttons[0].getPosition().y + buttons[0].getBtnShape().getLocalBounds().height*buttonsQtyHorizontalMenu;

	if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
		return true;
	}
	else {
		return false;
	}
}