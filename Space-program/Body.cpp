#include "Body.h"
#include<iostream>
Body::Body(double mass, TwoVector position, TwoVector velocity, const char * filename):
        fMass(mass),
        fPosition(position),
        fVelocity(velocity),
        fImage(new QImage(filename)){}

Body::~Body(){}

void Body::print(){
    std::cout<<"Mass: "<<fMass<<std::endl;
    std::cout<<"Position: ";
    fPosition.print();
    std::cout<<std::endl;
    std::cout<<"Velocity: ";
    fVelocity.print();
    std::cout<<std::endl;
}
