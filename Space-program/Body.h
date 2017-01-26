#ifndef BODY_H
#define BODY_H

#include "TwoVector.h"
#include "QImage"
#include "string"

class Body
{
public:
    Body(double mass, TwoVector position, TwoVector velocity,const char * filename);

    virtual ~Body();

    inline double getMass();
    inline TwoVector getPosition();
    inline TwoVector getVelocity();
    inline QImage* getImage();

    inline void setPosition(double x, double y);
    inline void setVelocity(double x, double y);

    void print();

private:
    double fMass;
    TwoVector fPosition;
    TwoVector fVelocity;
    QImage* fImage;
};

inline double Body::getMass(){
    return fMass;
}

inline TwoVector Body::getPosition(){
    return fPosition;
}
inline TwoVector Body::getVelocity(){
    return fVelocity;
}
inline QImage* Body::getImage(){
    return fImage;
}

inline void Body::setPosition(double x, double y){fPosition.setXY(x,y);}
inline void Body::setVelocity(double x, double y){fVelocity.setXY(x,y);}

#endif // BODY_H
