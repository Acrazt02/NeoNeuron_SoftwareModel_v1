#include "Connectome.h"

#include <iostream>
#include <math.h>

#define PI 3.14159265 

using namespace std;

vector<vector<int>>& Connectome::getConnections() {
	static vector<vector<int>> connections;
	return connections;
}

void Connectome::addConnection(int axonNeuronId, int synapticNeruonId, int synapseId, int synapseStrength) {

	vector<vector<int>>& connections = getConnections();

	connections.push_back({ axonNeuronId ,synapticNeruonId, synapseId, synapseStrength });
	for (int i = 0; i < connections.size(); i++) {
		cout << "Got: " << connections[i][0] << connections[i][1] << connections[i][2] << connections[i][3] << endl;
	}
}

vector<sf::RectangleShape>& Connectome::getGConnections() {
	static vector<sf::RectangleShape> gConnections;
	return gConnections;
}

bool& Connectome::isMakingConnection() {
	static bool makingStatus;
	return makingStatus;
}

/*int& Connectome::currentAxonId() {
	static int id = tempId;
	return id;
}


void Connectome::setCurrentAxonId(int id) {
	tempId = currentAxonId();
}*/

void Connectome::addGConnection(sf::Vector2f origin, sf::Vector2f end){

	vector<sf::RectangleShape>& gConnections = getGConnections();

	sf::RectangleShape gConnection;


	if (origin.x == 0 || origin.y == 0) {
		return;
	}

	sf::Vector2f vectorA = { end.x - origin.x,end.y - origin.y };
	float vectorAMagnitude = sqrt(pow(vectorA.x, 2) + pow(vectorA.y, 2));

	sf::Vector2f vectorB = { 0, vectorAMagnitude };

	float vectorBMagnitude = sqrt(pow(vectorB.x, 2) + pow(vectorB.y, 2));

	float h = 5;

	float dotProduct = vectorA.x * vectorB.x + vectorA.y * vectorB.y;

	float angle = acos(dotProduct / (vectorAMagnitude * vectorBMagnitude)) * 180.0 / PI;

	if (vectorA.x > 0) {
		angle = 360.0f - angle;
	}

	gConnection.setFillColor(sf::Color::Black);
	gConnection.setSize({ h,vectorAMagnitude });
	gConnection.setPosition(origin);
	gConnection.setOrigin({ h / 2,0 });
	gConnection.setRotation(angle);

	gConnections.push_back(gConnection);
}

float Connectome::getAngle(sf::Vector2f origin, sf::Vector2f end) {

	if (origin.x == 0 || origin.y == 0) {
		return -99999;
	}

	sf::Vector2f vectorA = { end.x - origin.x,end.y - origin.y };
	float vectorAMagnitude = sqrt(pow(vectorA.x, 2) + pow(vectorA.y, 2));

	sf::Vector2f vectorB = { 0, vectorAMagnitude };

	float vectorBMagnitude = sqrt(pow(vectorB.x, 2) + pow(vectorB.y, 2));

	float h = 5;

	float dotProduct = vectorA.x * vectorB.x + vectorA.y * vectorB.y;

	float angle = acos(dotProduct / (vectorAMagnitude * vectorBMagnitude)) * 180.0 / PI;

	if (vectorA.x > 0) {
		angle = 360.0f - angle;
	}

	return angle;
}

void Connectome::update(sf::Event& event, sf::RenderWindow& window) {

}

void Connectome::drawTo(sf::RenderWindow& window) {

	vector<sf::RectangleShape>& gConnections = getGConnections();

	for (int i = 0; i < gConnections.size(); i++) {
		window.draw(gConnections[i]);
	}
}