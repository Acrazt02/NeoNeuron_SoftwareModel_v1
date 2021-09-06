#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

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

	sf::Vector2f getPosition();
	string getId();
	int getSynapaseQty();
	int getNtType();


private:
	sf::Vector2f position;
	string id;
	int ntType = 0;
	int synapsesQty = 0;

	sf::CircleShape soma;
	sf::CircleShape axon;
	vector<sf::CircleShape> synapses;
	sf::Text idText;
	sf::Font font;

	map<int, sf::Color> colors = {
		{0, sf::Color::Blue},
		{1, sf::Color::Red},
		{2, sf::Color::Yellow},
		{3, sf::Color::Magenta}
	};

	bool isMouseOver(sf::CircleShape shape, sf::RenderWindow& window);
	void Action(int id);
};

