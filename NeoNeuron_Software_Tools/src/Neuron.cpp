#include "Neuron.h"

int NeuroReceptorsWs[NT_TYPES_QTY] = {1,-1,2,-2};

Neuron::Neuron(NeuronConf conf)
{
    ntType = conf.ntType;

    for(int i = 0; i < conf.nrs.size(); i ++){
        synapses.push_back(conf.nrs[i]);
    }
}

Neuron::~Neuron()
{
    //dtor
}

void Neuron::in(int ntInType, int synapseId, int& result){


    if((time(nullptr) - currentTime) <= timeLapse){ //Resting phase
        result = learn(ntInType, synapseId);
        return;

    }else{

        for(int i = 0; i < NT_TYPES_QTY; i++){
            if(i==ntInType){
                voltage += NeuroReceptorsWs[i]*synapses[synapseId][i];
            }
        }

        result = fire();

    }

}

int Neuron::learn(int ntInType, int synapseId){

    cout << "Learning =)" << endl;
    int result = -1;

    for(int i = 0; i < NT_TYPES_QTY; i++){
        if(i==ntInType){
            for(int j = 0; j < learningRate; j++){
                if(synapses[synapseId][i]>=T){
                    result = fire();
                    break;
                }
                synapses[synapseId][i]++;
            }
        }
    }

    return result;
}

int Neuron::fire(){
    if(voltage>=T){ //Action potential AP
        currentTime = time(nullptr);
        cout << "Fired" << endl;
        voltage = 0;
        return ntType;
    }else if(voltage < 0){
        voltage = 0;
        return -1;
    }
}

void Neuron::printInfo(){

    cout << "VOLTAGE: " << voltage << endl;

    for(int i = 0; i < synapses.size(); i++){
        cout << "   There are " << i << " synapses" << endl;
        for(int j = 0; j < NT_TYPES_QTY; j++){
            cout << "       There are " << synapses[i][j] << " of type " << j << " neuroreceptor" << endl;
        }
    }
}
