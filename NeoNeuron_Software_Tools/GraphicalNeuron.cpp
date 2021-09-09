#include "GraphicalNeuron.h"
#include "Connectome.h"
#include "Handler.h"

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
	axon.setOrigin({ axon.getRadius(), axon.getRadius()});
	axon.setPosition({ soma.getPosition().x + soma.getRadius()/2 + axon.getRadius(), soma.getPosition().y });
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

void GraphicalNeuron::setPosition(sf::Vector2f newPosition) {
	position = newPosition;
	soma.setPosition(newPosition);
	axon.setPosition({ soma.getPosition().x + soma.getRadius() / 2 + axon.getRadius(), soma.getPosition().y });
	idText.setPosition(position);

	float synapseRadius = soma.getRadius() * 0.2;
	float angle = 180 / synapsesQty + 90;

	if (synapsesQty == 1) {
		angle = 180;
	}
	else if (synapsesQty == 2) {
		angle = 180 / synapsesQty + 45;
	}

	for (int m = 0; m < synapsesQty; m++) {

		float i = soma.getRadius() * cos(angle * (3.1416 / 180)) + soma.getPosition().x;
		float j = soma.getRadius() * sin(angle * (3.1416 / 180)) + soma.getPosition().y;

		synapses[m].setPosition({ i,j });

		angle += 180 / synapsesQty;
	}
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
		if (isMoving) {
			setPosition({ (float)sf::Mouse::getPosition(window).x,(float)sf::Mouse::getPosition(window).y });
			if (isConnected()) {
				vector<sf::Vector2f> connectionsPosition;
				for (int i = 0; i < synapsesQty; i++) {
					connectionsPosition.push_back(synapses[i].getPosition());
				}
				Connectome::updateGSynapticConnections(stoi(id), connectionsPosition);
				if (isAxonConnected) {
					Connectome::updateGAxonConnections(stoi(id),axon.getPosition());
				}
			}
			break;
		}
		if (Connectome::isMakingConnection() && (Connectome::currentAxonId == stoi(id)) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			setTempRectangle(window); 
		}
		if (isMouseOver(axon, window)) {
			axon.setFillColor(sf::Color::Green);
		}
		else {
			axon.setFillColor(colors[ntType]);
		}
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
		if (!Connectome::isMakingConnection() && isMouseOver(axon,window) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {

			cout << "Got in!" << endl;

			tempRectangleFlag = true;
			AddConnection(window);
			isAxonConnected = true;
		}
		if (isMouseOver(soma, window) && Handler::currentMode == 4) { //Clicked on soma
			switch (Handler::currentMode) {
			case 1:
				//vector<GrHandler::gNeurons.erase(id); Add erase neuron
				break;
			case 4:
				Handler::currentMode = 5;
				isMoving = true;
				break;
			}
		}
		
		break;
	case sf::Event::MouseButtonReleased: //Has to go thru all neurons not just this one
		/*if (Connectome::isMakingConnection()) {

			// get the current mouse position in the window
			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

			// convert it to world coordinates
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
			tempEnd = { (float)sf::Mousse::getPosition(window).x,(float)sf::Mouse::getPosition(window).y };

			Connectome connectionsToSave;

			connectionsToSave.addGConnection(tempOrigin, tempEnd);
			Connectome::isMakingConnection() = false;
		}*/
		if (isMoving) { //Clicked on soma
			Handler::currentMode = 4;
			isMoving = false;
			setPosition({ (float)sf::Mouse::getPosition(window).x,(float)sf::Mouse::getPosition(window).y });
			if (isConnected()) {
				vector<sf::Vector2f> connectionsPosition;
				for (int i = 0; i < synapsesQty; i++) {
					connectionsPosition.push_back(synapses[i].getPosition());
				}
				Connectome::updateGSynapticConnections(stoi(id), connectionsPosition);
				if (isAxonConnected) {
					Connectome::updateGAxonConnections(stoi(id), axon.getPosition());
				}
			}
			break;
		}
	default:
		return;
	}
}

void GraphicalNeuron::AddConnection(sf::RenderWindow& window) {
	//Connectome::setCurrentAxonId(id);
	Connectome connections;
	connections.currentAxonId = stoi(id);
	//Connectome::currentAxonId = id;
	Connectome::isMakingConnection() = true;

	tempOrigin = axon.getPosition();

	if (!tempRectangleFlag) {
		setTempRectangle(window);
	}

}

/*void GraphicalNeuron::Action(int id, sf::RenderWindow& window) {

	cout << "You pressed synapse: " << id << endl;

	//Connectome::setCurrentAxonId(id);
	Connectome connections;
	connections.currentAxonId = id;
	//Connectome::currentAxonId = id;
	Connectome::isMakingConnection() = true;

	tempOrigin = synapses[id].getPosition();

	setTempRectangle(window);

}*/

void GraphicalNeuron::setTempRectangle(sf::RenderWindow& window) {

	// get the current mouse position in the window
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

	// convert it to world coordinates
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	tempEnd = { (float)sf::Mouse::getPosition(window).x,(float)sf::Mouse::getPosition(window).y };

	if (tempOrigin.x == 0 || tempOrigin.y == 0) {
		return;
	}

	sf::Vector2f vectorA = { tempEnd.x - tempOrigin.x,tempEnd.y - tempOrigin.y };
	float vectorAMagnitude = sqrt(pow(vectorA.x, 2) + pow(vectorA.y, 2));

	sf::Vector2f vectorB = { 0, vectorAMagnitude };

	float vectorBMagnitude = sqrt(pow(vectorB.x, 2) + pow(vectorB.y, 2));

	float h = 5;

	float dotProduct = vectorA.x * vectorB.x + vectorA.y * vectorB.y;

	float angle = acos(dotProduct / (vectorAMagnitude * vectorBMagnitude)) * 180.0 / PI;

	if (vectorA.x > 0) {
		angle = 360.0f - angle;
	}

	tempRectangle.setFillColor(sf::Color::Green);
	tempRectangle.setSize({ h,vectorAMagnitude });
	tempRectangle.setPosition(tempOrigin);
	tempRectangle.setOrigin({ h / 2,0 });
	tempRectangle.setRotation(angle);
}

void GraphicalNeuron::drawTo(sf::RenderWindow& window) {
	window.draw(soma);
	window.draw(idText);
	window.draw(axon);
	for (int i = 0; i < synapsesQty; i++) {
		window.draw(synapses[i]);
	}
	if (Connectome::isMakingConnection()) {
		window.draw(tempRectangle);
	}
}

sf::Vector2f GraphicalNeuron::getPosition() {
	return position;
}

string GraphicalNeuron::getId() {
	return id;
}

int GraphicalNeuron::getSynapaseQty() {
	return synapsesQty;
}

int GraphicalNeuron::getNtType() {
	return ntType;
}

sf::CircleShape GraphicalNeuron::getAxon(){
	return axon;
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

vector<sf::CircleShape> GraphicalNeuron::getSynapses() {
	return synapses;
}

void GraphicalNeuron::resetTempRectangle() {

	tempRectangleFlag = true;
}

void GraphicalNeuron::setConnectionStatus(bool newStatus) {
	connectionState = newStatus;
}

bool GraphicalNeuron::isConnected() {
	return connectionState;
}
