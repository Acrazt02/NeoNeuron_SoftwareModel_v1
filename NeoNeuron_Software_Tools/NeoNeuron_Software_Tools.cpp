#include <iostream>
#include <deque>
#include <SFML/Graphics.hpp>

#include "Neuron.h"
#include "Button.h"
#include "GraphicalNeuron.h"
#include "HorizontalMenu.h"
#include "VerticalMenu.h"

using namespace std;

int main() {

    //Te quedaste agregando funciones de boton a las synapsis (funciona) ahora agrega a los demas
    sf::RenderWindow window(sf::VideoMode(900, 900), "Test Button");

    Button btn1("Click Me!", { 200,50 }, 20, sf::Color::Green, sf::Color::Black);
    btn1.setPosition({ 300,300 });
    
    sf::Font font;
    font.loadFromFile("Roboto-Light.ttf");
    btn1.setFont(font);

    HorizontalMenu horizontalMenu(font);
    VerticalMenu verticalMenu(font);
    
    vector<GraphicalNeuron> gNeurons;

    int i = 0;
    int m = 1;

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
                if (btn1.isMouseOver(window)) {
                    btn1.setBackColor(sf::Color::Red);
                }
                else {
                    btn1.setBackColor(sf::Color::Green);
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (btn1.isMouseOver(window)) {
                    cout << "btn1 pressed" << endl;
                }
                else {

                    // get the current mouse position in the window
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

                    // convert it to world coordinates
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                    string s = "A";
                    GraphicalNeuron gNeuron({ (float) sf::Mouse::getPosition(window).x,(float)sf::Mouse::getPosition(window).y }, s, i, m, font);
                    gNeurons.push_back(gNeuron);
                    if (i == 3) {
                        i = 0;
                    }
                    else {
                        i++;
                    }
                    m++;
                }
                break;
            default:
                break;
            }

            horizontalMenu.update(event, window);
            verticalMenu.update(event, window);
            for (int i = 0; i < gNeurons.size(); i++) {
                gNeurons[i].update(event, window);
            }


            window.clear(sf::Color::White);
            //window.draw(shape);
            btn1.drawTo(window);
            horizontalMenu.drawTo(window);
            verticalMenu.drawTo(window);
            for (int i = 0; i < gNeurons.size(); i++) {
                gNeurons[i].drawTo(window);
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
