#include <iostream>
#include <deque>
#include <SFML/Graphics.hpp>

#include "Neuron.h"
#include "Button.h"
#include "GraphicalNeuron.h"
#include "HorizontalMenu.h"
#include "VerticalMenu.h"
#include "Connectome.h"
#include "Handler.h"

using namespace std;

int Connectome::currentAxonId = -1;
int Handler::currentMode = -1;

bool isgNeuronBeingMade = false;

int currentNTType = 0;

map<int, sf::Color> colors = {
    {0, sf::Color::Blue},
    {1, sf::Color::Red},
    {2, sf::Color::Yellow},
    {3, sf::Color::Magenta}
};

vector<GraphicalNeuron> Handler::gNeurons;

sf::RectangleShape feedBackSquare;
void setFeedBackSquare();

int main() {

    //Da los toques finales a las conexiones
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Test Button" /*,sf::Style::Fullscreen*/);
    
    sf::Font font;
    font.loadFromFile("Roboto-Light.ttf");

    HorizontalMenu horizontalMenu(font);
    VerticalMenu verticalMenu(font);
    
    setFeedBackSquare();

    //vector<GraphicalNeuron> gNeurons;

    int i = 0;
    int id = 0;

    Connectome connectionsToSave;
    //connectionsToSave.addConnection(0, 1, 0, 1); //Is just a test
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
                    
                    switch (Handler::currentMode) {
                        case 0:{
                            if (Connectome::isMakingConnection() || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                                break; //A connection is being made
                            }
                            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && Handler::gNeurons.size() != 0) {
                                int index = Handler::gNeurons.size() - 1;
                                if (!Handler::gNeurons[index].isConnected()) {
                                    
                                    sf::Vector2f position = Handler::gNeurons[index].getPosition();
                                    string id2 = Handler::gNeurons[index].getId();
                                    int synapsesQty2 = Handler::gNeurons[index].getSynapaseQty() + 1;

                                    GraphicalNeuron gNeuron2(position, id2, currentNTType, synapsesQty2, font);
                                    Handler::gNeurons.pop_back();
                                    Handler::gNeurons.push_back(gNeuron2);
                                }
                            }
                            else {
                                //Add gNeuron
                                //sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

                                // convert it to world coordinates
                                //sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

                                GraphicalNeuron gNeuron({ (float)sf::Mouse::getPosition(window).x,(float)sf::Mouse::getPosition(window).y }, to_string(id), currentNTType, 1, font);
                                Handler::gNeurons.push_back(gNeuron);
                                id++;
                            }
                        }
                        break;
                        case 1:{}
                            //Delete gNeuron
                            break;
                        case 2:{}
                            //Edit gNeuron
                            break;{}
                        case 3:{}
                            //Add Text
                            break;
                        case 4:{}
                            //Drag gNeuron
                            break;
                        default:{}
                            //Add gNeuron
                            break;
                    }
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (Connectome::isMakingConnection()) {
                    Connectome::isMakingConnection() = false;
                    for (int i = 0; i < Handler::gNeurons.size(); i++) {
                        for (int j = 0; j < Handler::gNeurons[i].getSynapses().size(); j++) {
                            if (Handler::gNeurons[i].isMouseOver(Handler::gNeurons[i].getSynapses()[j], window)) {
                                //Action(i, window);
                                connectionsToSave.addGConnection(Handler::gNeurons[connectionsToSave.currentAxonId].getAxon().getPosition(), Handler::gNeurons[i].getSynapses()[j].getPosition());
                                connectionsToSave.addConnection(connectionsToSave.currentAxonId, i, j, 5);
                                Handler::gNeurons[connectionsToSave.currentAxonId].resetTempRectangle();
                                Handler::gNeurons[connectionsToSave.currentAxonId].setConnectionStatus(true);
                                Handler::gNeurons[i].setConnectionStatus(true);
                                goto jump;
                            }
                        }
                    }
                }
            jump: 
                break;
            case sf::Event::KeyPressed: {
                switch (Handler::currentMode)
                {
                case 0: {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) {
                        currentNTType = 0;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
                        currentNTType = 1;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
                        currentNTType = 2;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {
                        currentNTType = 3;
                    }
                    if (Connectome::isMakingConnection() && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        feedBackSquare.setFillColor(sf::Color::Green);
                        break; //A connection is being made
                    }
                    feedBackSquare.setFillColor(colors[currentNTType]);
                }break;
                default:
                    break;
                }
            }break;

            default:
                break;
            }

            horizontalMenu.update(event, window);
            Handler::currentMode = horizontalMenu.getMode();

            verticalMenu.update(event, window);
            for (int i = 0; i < Handler::gNeurons.size(); i++) {
                Handler::gNeurons[i].update(event, window);
            }
            Connectome::update(event, window);

            window.clear(sf::Color::White);

            for (int i = 0; i < Handler::gNeurons.size(); i++) {
                Handler::gNeurons[i].drawTo(window);
            }
            Connectome::drawTo(window);
            horizontalMenu.drawTo(window);
            verticalMenu.drawTo(window);
            if (Handler::currentMode == 0) {
                window.draw(feedBackSquare);
            }else if (Connectome::isMakingConnection() && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                feedBackSquare.setFillColor(sf::Color::Green);
                window.draw(feedBackSquare);
            }
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

void setFeedBackSquare() {

    feedBackSquare.setPosition({ 800,50 });
    feedBackSquare.setFillColor(colors[currentNTType]);
    feedBackSquare.setSize({ 50,50 });
    feedBackSquare.setOutlineThickness(3);
    feedBackSquare.setOutlineColor(sf::Color::Black);
}