//
//  cHandler.cpp
//  QueuesSimulation
//
//  Created by Luis Eduardo Brime Gomez on 5/3/19.
//  Copyright © 2019 Luis Eduardo Brime Gomez. All rights reserved.
//

#include "cHandler.hpp"

using namespace std;

cHandler::~cHandler() {
    
}

// Si no hay clientLimit, entonces mandar 0.
cHandler::cHandler(int hS, int hC, float aT, int cL) {
    howManyServers = hS;
    howManyClients = hC;
    averageTime = aT;
    
    if (cL == 0)
        clientLimit = howManyClients;
    else
        clientLimit = cL;
    
    globalCount = 0;
    canI = true;
    
    cParticle* p;
    float* pos = new float[3];
    pos[0] = 0;
    pos[1] = 0;
    pos[2] = 0;
    
    for (int i = 0; i < howManyClients; i++) {
        pos[0] = i;
        bool serv = false;
        p = new cParticle(pos, serv);
        Clients.push_back(p);
    }
    
    //servers
    int half = 1;
    pos[0] = -2;
    pos[1] = 0;
    pos[2] = 0;
    
    if(howManyServers>2)
    {
        half = howManyServers/2;
    }
    else
    {
        half = 1;
    }
    for(int j = 0; j < howManyServers; j++)
    {
        pos[1] = j - half;
        bool serv = false;
        p = new cParticle(pos, serv);  // position, mass, radius
        p->ka[0] = 0.0f;
        p->ka[1] = 1.0f;
        p->ka[2] = 0.0f;
        Servers.push_back(p);
    }
}

void cHandler::draw() {
    for(int i = 0; i < howManyClients; i++)
    {
        Clients[i]->Draw();
    }
    for(int i = 0; i < howManyServers; i++)
    {
        Servers[i]->Draw();
    }
}

void cHandler::update() {
    if(canI){
        for (int i=0; i<howManyServers; i++) {
            // Si el servidor no está sirviendo y si no se ha excedido el límite:
            if(!Servers[i]->serving && canI){
                // Si se excedió el límite salir alv:
                if(globalCount>=clientLimit || ((globalCount - howManyClients) == 0)){
                    canI = false;
                    break;
                }
                
                // Mover el cliente que sigue al servidor que está libre y marcarlo como ocupado.
                Clients[globalCount]->MoveToServer(Servers[i]->position);
                Servers[i]->serving = true;
                
                if(globalCount<=clientLimit)
                {
                    globalCount++;
                }
                
                for (int j = globalCount; j < howManyClients; j++) {
                    Clients[j]->position[0] -= 1;
                }
            }
        }
    }
    
    for (int i = 0; i<globalCount; i++) {
        if(Clients[i]->timeServing >= averageTime)
        {
            for (int j = 0; j < howManyServers; j++) {
                if (Clients[i]->position[1] == Servers[j]->position[1])
                {
                    Servers[j]->serving = false;
                    
                }
            }
            float nu[3];
            nu[0] = 99.0f;
            nu[1] = 99.0f;
            nu[2] = 99.0f;
            Clients[i]->MoveToServer(nu);
        }
        else {
            Clients[i]->timeServing += 0.5;
        }
    }
}
