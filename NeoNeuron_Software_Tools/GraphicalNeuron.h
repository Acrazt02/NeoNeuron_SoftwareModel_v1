#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

#define PI 3.14159265

using namespace std;

class GraphicalNeuron
{
public:
	GraphicalNeuron(sf::Vector2f position, string id, int ntType, int synapsesQty, sf::Font &font);

	void setPosition(sf::Vector2f position);
	void setId(int id);
	void setSynapsesQty(int synapsesQty);
	void setNtType(int ntType);

	void update(sf::Event& event, sf::RenderWindow& window);
	void drawTo(sf::RenderWindow& window);
	void resetTempRectangle();

	sf::Vector2f getPosition();
	string getId();
	int getSynapaseQty();
	int getNtType();
	vector<sf::CircleShape> getSynapses();
	sf::CircleShape getAxon();

	bool isMouseOver(sf::CircleShape shape, sf::RenderWindow& window);


private:
	sf::Vector2f position;
	string id;
	int ntType = 0;
	int synapsesQty = 0;
	bool tempRectangleFlag = false;

	vector<sf::RectangleShape> gConnectionsToSave;
	sf::Vector2f tempOrigin;
	sf::Vector2f tempEnd;

	sf::CircleShape soma;
	sf::CircleShape axon;
	vector<sf::CircleShape> synapses;
	sf::Text idText;
	sf::Font font;

	sf::RectangleShape tempRectangle;

	map<int, sf::Color> colors = {
		{0, sf::Color::Blue},
		{1, sf::Color::Red},
		{2, sf::Color::Yellow},
		{3, sf::Color::Magenta}
	};

	void Action(int id, sf::RenderWindow& window);

	void AddConnection(sf::RenderWindow& window);
	void setTempRectangle(sf::RenderWindow& window);
};

