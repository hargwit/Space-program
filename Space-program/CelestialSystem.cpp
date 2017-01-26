#include "CelestialSystem.h"
#include <iostream>
#include "gslroutine.h"



CelestialSystem::CelestialSystem(){
}

CelestialSystem::~CelestialSystem(){
    for(int i=0;i<fBodies.size();i++){
        delete(fBodies[i]);
    }
}

void CelestialSystem::simulate(){
    size_t dim = pow(2,fBodies.size()+1);
    double y[dim];
    double params[fBodies.size()];

    Body* body;
    int pos;
    for(int i=0;i<fBodies.size();i++){
        pos=4*i;
        body=fBodies[i];
        params[i]=body->getMass();
        y[pos]=body->getPosition().getX();
        y[pos+1]=body->getPosition().getY();
        y[pos+2]=body->getVelocity().getX();
        y[pos+3]=body->getVelocity().getY();
    }


    //double * yNew=fourthOrderRK(dim,y,params);
    double * yNew=adaptiveFourthOrderRK(dim,y,params);

    for(int i=0;i<fBodies.size();i++){
        pos=4*i;
        body=fBodies[i];
        body->setPosition(*(yNew+pos),*(yNew+1+pos));
        body->setVelocity(*(yNew+2+pos),*(yNew+3+pos));
    }


}

void CelestialSystem::print(){
    Body* body;
    for(int i=0;i<fBodies.size();i++){
        body=fBodies[i];
        body->print();
    }
}



