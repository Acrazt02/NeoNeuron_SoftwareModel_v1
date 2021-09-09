#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Connectome
{
public:
	//Connectome();
	void addConnection(int axonNeuronId, int synapticNeruonId, int synapseId, int synapseStrength);
	void addGConnection(sf::Vector2f origin, sf::Vector2f end);
	static float getAngle(sf::Vector2f origin, sf::Vector2f end);
	static vector<vector<int>>& getConnections();
	static vector<sf::RectangleShape>& getGConnections();

	static void update(sf::Event& event, sf::RenderWindow& window);
	static void drawTo(sf::RenderWindow& window);
	//static void setCurrentAxonId(int id);
	static void updateGSynapticConnections(int id,vector<sf::Vector2f> connectionsPosition);
	static void updateGAxonConnections(int id, sf::Vector2f connectionPosition);

	static bool& isMakingConnection();
	//static int& currentAxonId();

	static int currentAxonId;

private:
	//int tempId;
};

