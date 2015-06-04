#ifndef PARTICLE
#define PARTICLE

#include "ofMain.h"

class Particle {
public:
    void update()
    {
        age++;
    }

    void draw()
    {

    }

private:
    ofVec2f pos;
    ofVec2f acc;
    unsigned int age;
};


class ParticleManager {
public:
    void setup()
    {

    }
    void update()
    {

    }
    void draw()
    {

    }

    void addParticle()
    {

    }

private:
    vector <Particle> particles;
};

#endif // PARTICLE

