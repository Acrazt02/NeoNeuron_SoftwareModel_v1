#ifndef NEURON_H
#define NEURON_H

#include<iostream>
#include <array>
#include <deque>
#include <ctime>
#include <chrono>

#define NT_TYPES_QTY 4

using namespace std;

struct NeuronConf{

    int ntType; //Type of the neuron's output
    deque<array<int, NT_TYPES_QTY>> nrs; // 4 neuroReceptors for each synapse and how many of each type (there are four types)
};

struct connection{
    int neuronId; //Neuron the NT is comming from
    //[DestinationNeuronID, SynapseID]
    int synapseId[2];
};

class Neuron
{
    public:
        Neuron(NeuronConf conf);
        virtual ~Neuron();
        void in(int ntType, int synapseId, int &result);

        int fire();
        int learn(int ntType, int synapseId);

        void printInfo();

    protected:

    private:

        deque<array<int, NT_TYPES_QTY>> synapses;
        int ntType = 0;

        int voltage = 0;
        int T = 5;
        time_t currentTime = 0;
        int timeLapse = 1;
        int learningRate = 1;

};

#endif // NEURON_H
