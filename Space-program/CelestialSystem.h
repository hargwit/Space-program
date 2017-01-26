#ifndef CELESTIALSYSTEM_H
#define CELESTIALSYSTEM_H

#include "Body.h"
//Vector
#include <vector>
#include <cmath>

class CelestialSystem
{
public:
    CelestialSystem();
    virtual ~CelestialSystem();

    inline std::vector<Body *> getBodies();
    inline void setBodies(std::vector<Body *> bodies);


    void simulate();
    int fourthOrderRungeKutta();
    int func (double t, const double y[], double f[],
          void *params);

    void print();

private:
    std::vector<Body *> fBodies;
};

inline std::vector<Body *> CelestialSystem::getBodies(){return fBodies;}
inline void CelestialSystem::setBodies(std::vector<Body *> bodies){fBodies=bodies;}

#endif // CELESTIALSYSTEM_H
