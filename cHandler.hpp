//
//  cHandler.hpp
//  QueuesSimulation
//
//  Created by Luis Eduardo Brime Gomez on 5/3/19.
//  Copyright © 2019 Luis Eduardo Brime Gomez. All rights reserved.
//
#include "cParticle.hpp"
#include <vector>

using namespace std;
using std::vector;

class cHandler {
public:
    int howManyServers;
    int howManyClients;
    float averageTime;
    int clientLimit;
    bool canI;
    int globalCount;
    
    vector<cParticle*> Clients;
    vector<cParticle*> Servers;
    //cParticle* Clients;
    //cParticle* Servers;
    
    // HowManyServers, HowManyClients, AverageTime, ClientLimit.
    cHandler(int hS, int hC, float aT, int cL);
    ~cHandler();
    void draw();
    void update();
};
