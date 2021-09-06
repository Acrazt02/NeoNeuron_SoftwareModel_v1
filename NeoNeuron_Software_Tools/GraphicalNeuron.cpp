#include "GraphicalNeuron.h"

GraphicalNeuron::GraphicalNeuron(sf::Vector2f newPosition, string newId, int newNtType, int newSynapsesQty, sf::Font &newFont) {

	position = newPosition;
	id = newId;
	ntType = newNtType;
	synapsesQty = newSynapsesQty;
	font = newFont;

	//soma.setRadius(150*0.05*synapsesQty);
	soma.setRadius(30);
	soma.setOrigin({ soma.getRadius(),soma.getRadius()});
	soma.setPosition(position);
	soma.setFillColor(sf::Color::White);
	soma.setOutlineColor(sf::Color::Black);
	soma.setOutlineThickness(3);

	axon.setRadius(soma.getRadius() * 0.5);
	axon.setOrigin({ 0, axon.getRadius()});
	axon.setPosition({ soma.getPosition().x + soma.getRadius()/2, soma.getPosition().y });
	axon.setFillColor(colors[ntType]);
	axon.setOutlineColor(sf::Color::Black);
	axon.setOutlineThickness(3);

	idText.setString(id);
	idText.setFillColor(sf::Color::Black);
	idText.setFont(newFont);
	idText.setCharacterSize(20);
	
	unsigned int count = 0;
	for (int i = 0; id[i] != '\0'; i++) {
		count++;
	}

	//idText.setOrigin({ (float) (idText.getCharacterSize() * count), 0});
	idText.setOrigin({ 10, 10 });
	idText.setPosition(position);

	float synapseRadius = soma.getRadius() * 0.2;
	float angle = 180 / synapsesQty + 90;

	if (synapsesQty == 1) {
		angle = 180;
	}
	else if(synapsesQty == 2) {
		angle = 180 / synapsesQty + 45;
	}

	for (int m = 0; m < synapsesQty; m++) {
		sf::CircleShape synapse;
		synapse.setRadius(synapseRadius);
		synapse.setOrigin({ synapse.getRadius(),synapse.getRadius()});
		synapse.setFillColor(sf::Color::White);
		synapse.setOutlineColor(sf::Color::Black);
		synapse.setOutlineThickness(3);

		float i = soma.getRadius() * cos(angle * (3.1416 / 180)) + soma.getPosition().x;
		float j = soma.getRadius() * sin(angle * (3.1416 / 180)) + soma.getPosition().y;

		synapse.setPosition({ i,j });

		angle += 180/synapsesQty;
		synapses.push_back(synapse);
	}
}

void GraphicalNeuron::setPosition(sf::Vector2f position) {

}

void GraphicalNeuron::setId(int id) {

}

void GraphicalNeuron::setSynapsesQty(int synapsesQty) {

}

void GraphicalNeuron::setNtType(int ntType) {

}

void GraphicalNeuron::update(sf::Event& event, sf::RenderWindow& window) {
	switch (event.type) {
	case sf::Event::MouseMoved:
		for (int i = 0; i < synapsesQty; i++) {
			if (isMouseOver(synapses[i], window)) {
				synapses[i].setFillColor(sf::Color::Red);
			}
			else {
				synapses[i].setFillColor(sf::Color::White);
			}
		}
		break;
	case sf::Event::MouseButtonPressed:
		for (int i = 0; i < synapsesQty; i++) {
			if (isMouseOver(synapses[i], window)) {
				Action(i);
			}
		}
		break;
	default:
		return;
	}
}

void GraphicalNeuron::Action(int id) {
	/*switch (id) {
	case 0:
		cout << "You pressed btn: 0" << endl;
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
	}*/
	cout << "You pressed synapse: " << id << endl;
}

void GraphicalNeuron::drawTo(sf::RenderWindow& window) {
	window.draw(soma);
	window.draw(idText);
	window.draw(axon);
	for (int i = 0; i < synapsesQty; i++) {
		window.draw(synapses[i]);
	}
}

sf::Vector2f GraphicalNeuron::getPosition() {
	return position;
}

string GraphicalNeuron::getId() {
	return "";
}

int GraphicalNeuron::getSynapaseQty() {
	return 0;
}

int GraphicalNeuron::getNtType() {
	return 0;
}

bool GraphicalNeuron::isMouseOver(sf::CircleShape shape ,sf::RenderWindow& window) {
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	float radius = shape.getRadius();

	float btnPosX = shape.getPosition().x - radius;
	float btnPosY = shape.getPosition().y - radius;

	float btnxPosWidth = shape.getPosition().x + radius;
	float btnyPosHeight = shape.getPosition().y + radius;

	if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
		return true;
	}
	else {
		return false;
	}
}