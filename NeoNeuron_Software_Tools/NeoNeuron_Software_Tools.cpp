#include <iostream>
#include <deque>
#include <SFML/Graphics.hpp>

#include "Neuron.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    cin.clear();
    fflush(stdin);

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
        fflush(stdin);
    }

    cin.clear();
    fflush(stdin);
    return 0;
}
