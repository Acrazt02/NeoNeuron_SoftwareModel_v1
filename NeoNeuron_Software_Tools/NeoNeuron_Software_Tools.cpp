#include <iostream>
#include <deque>
#include <SFML/Graphics.hpp>

#include "Neuron.h"
#include "Button.h"
#include "GraphicalNeuron.h"
#include "HorizontalMenu.h"
#include "VerticalMenu.h"
#include "Connectome.h"

using namespace std;

int Connectome::currentAxonId = -1;

int main() {

    //Da los toques finales a las conexiones
    sf::RenderWindow window(sf::VideoMode(1200, 1200), "Test Button", sf::Style::Fullscreen);
    
    sf::Font font;
    font.loadFromFile("Roboto-Light.ttf");

    HorizontalMenu horizontalMenu(font);
    VerticalMenu verticalMenu(font);
    
    vector<GraphicalNeuron> gNeurons;

    int i = 0;
    int m = 0;

    Connectome connectionsToSave;
    connectionsToSave.addConnection(0, 1, 0, 1);
    Connectome::isMakingConnection() = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {

            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:

                break;
            case sf::Event::MouseButtonPressed:
                if(/*Canvas.isMouseOver(window)*/!horizontalMenu.isMouseOver(window) && !verticalMenu.isMouseOver(window)) {

                    if (m < 5) {
                        // get the current mouse position in the window
                        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

                        // convert it to world coordinates
                        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                        //string s = "A";
                        GraphicalNeuron gNeuron({ (float)sf::Mouse::getPosition(window).x,(float)sf::Mouse::getPosition(window).y }, to_string(m), i, m+1, font);
                        gNeurons.push_back(gNeuron);
                        if (i == 3) {
                            i = 0;
                        }
                        else {
                            i++;
                        }
                        m++;
                    }
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (Connectome::isMakingConnection()) {
                    Connectome::isMakingConnection() = false;
                    for (int i = 0; i < gNeurons.size(); i++) {
                        for (int j = 0; j < gNeurons[i].getSynapses().size(); j++) {
                            if (gNeurons[i].isMouseOver(gNeurons[i].getSynapses()[j], window)) {
                                //Action(i, window);
                                connectionsToSave.addGConnection(gNeurons[connectionsToSave.currentAxonId].getAxon().getPosition(),gNeurons[i].getSynapses()[j].getPosition());
                                connectionsToSave.addConnection(connectionsToSave.currentAxonId, i, j, 5);
                                gNeurons[connectionsToSave.currentAxonId].resetTempRectangle();
                                goto jump;
                            }
                        }
                    }
                }
            jump: 
                break;
            default:
                break;
            }

            horizontalMenu.update(event, window);
            verticalMenu.update(event, window);
            for (int i = 0; i < gNeurons.size(); i++) {
                gNeurons[i].update(event, window);
            }
            Connectome::update(event, window);

            window.clear(sf::Color::White);
            horizontalMenu.drawTo(window);
            verticalMenu.drawTo(window);
            for (int i = 0; i < gNeurons.size(); i++) {
                gNeurons[i].drawTo(window);
            }
            Connectome::drawTo(window);
            window.display();
        }
    }

    cin.clear();
    //fflush(stdin);

    struct NeuronConf neuronConf;
    int ntType = 0;

    //{synapse{NTs{type0,type1,type2,type3},synapse{NTs{type0,type1,type2,type3},synapse{NTs{type0,type1,type2,type3},synapse{NTs{type0,type1,type2,type3}}
    deque<array<int, 4>> nrs = { {1,1,1,1},{1,1,1,1} };

    neuronConf.ntType = ntType;
    neuronConf.nrs = nrs;

    deque<Neuron> neurons;

    Neuron testNeuron = Neuron(neuronConf);
    neurons.push_back(testNeuron);
    neurons[0].printInfo();

    deque<struct connection> connections;
    connection conn;

    conn.neuronId = 0;
    conn.synapseId[0] = 0;
    conn.synapseId[1] = 0;

    connections.push_back(conn);

    struct NeuronConf neuronConf2;
    int ntType2 = 0;

    //{synapse{NTs{type0,type1,type2,type3},synapse{NTs{type0,type1,type2,type3},synapse{NTs{type0,type1,type2,type3},synapse{NTs{type0,type1,type2,type3}}
    deque<array<int, 4>> nrs2 = { {1,1,1,1},{1,1,1,1} };

    neuronConf2.ntType = ntType2;
    neuronConf2.nrs = nrs2;

    Neuron testNeuron2 = Neuron(neuronConf2);
    neurons.push_back(testNeuron2);
    neurons[1].printInfo();

    connection conn2;

    conn2.neuronId = 0;
    conn2.synapseId[0] = 0;
    conn2.synapseId[1] = 0;

    connections.push_back(conn2);

    int a, b, c, d = 0;
    int result = -1;
    int result2 = -1;

    while (d != 50) {

        cin >> a >> b >> c >> d; cin.clear();

        conn.synapseId[0] = a;
        conn.synapseId[1] = b;

        cout << a << b << c << endl;

        neurons[a].in(c, b/*connections[0].synapseId[1]*/, result);
        neurons[a].printInfo();

        if (result != -1) {
            neurons[a + 1].in(result, 0, result2);
            neurons[a + 1].printInfo();
        }
        else {
            cout << "Result is: " << result << endl;
        }
        cin.clear();
        //fflush(stdin);
    }

    cin.clear();
    //fflush(stdin);
    return 0;
}
