//
//  cParticle.cpp
//  Particles
//
//  Created by Armando Hernandez on 3/25/19.
//  Copyright © 2019 Armando Hernandez. All rights reserved.
//
#include "math.h"
#include "cParticle.hpp"

cParticle::~cParticle()
{
}
cParticle::cParticle(float* pos, bool serv)
{
    float minKd = 0.3f;
    float maxKd = 1.0f;
    float minKa = 0.05f;
    float maxKa = 0.2f;
    float minKs = 0.4f;
    float maxKs = 0.8f;
    
    serving = serv;
    served = false;
    timeServing = 0;
    radius = 0.25;
    mass = 1;
    
    //material begins
    ka = new GLfloat[4];
    originalKa = new GLfloat[3];
    
    originalKa [0] = 0.1f + (0.3f - 0.1f) * (float)rand() / RAND_MAX;
    ka[0] = originalKa[0]; //red
    
    originalKa [1] = minKa + (maxKa - minKa) * (float)rand() / RAND_MAX;
    ka[1] =  originalKa [1]; //green
    
    originalKa [2] = minKa + (maxKa - minKa) * (float)rand() / RAND_MAX;
    ka[2] = originalKa [2]; //blue
    
    ka[3] = 1.0f; //alpha
    
    kd = new GLfloat[4];
    kd[0] = minKd + (maxKd - minKd) * (float)rand() / RAND_MAX;
    kd[1] = minKd + (maxKd - minKd) * (float)rand() / RAND_MAX;
    kd[2] = minKd + (maxKd - minKd) * (float)rand() / RAND_MAX;
    kd[3] = 1.0f; //allways 1
    
    ks = new GLfloat[4];
    ks[0] = minKs + (maxKs - minKs) * (float)rand() / RAND_MAX;
    ks[1] = minKs + (maxKs - minKs) * (float)rand() / RAND_MAX;;
    ks[2] = minKs + (maxKs - minKs) * (float)rand() / RAND_MAX;;
    ks[3] = 1.0f;
    
    alpha = new GLfloat[1];
    alpha[0] = 50.0f;
    // material ends

    position = new float[3];
    position[0] = pos[0];
    position[1] = pos[1];
    position[2] = pos[2];
    
    oldPos = new float[3];
    oldPos[0] = position[0];
    oldPos[1] = position[1];
    oldPos[2] = position[2];
    
}

void cParticle::MoveToServer(float *where)
{
    position[0]=where[0] + 0.75f;
    position[1]=where[1];
    position[2]=where[2];
}

void cParticle::Draw()
{
    glPushMatrix();
    {
        glTranslatef(position[0], position[1], position[2]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, alpha);
        if (!served) glutSolidSphere(radius, 20, 20);
    }
    glPopMatrix();
}
