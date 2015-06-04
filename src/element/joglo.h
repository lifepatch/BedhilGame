#ifndef JOGLO
#define JOGLO

#include "Obj2D.h"

class gmJoglo : public Obj2D{
public:
    void setDestination(float y)
    {
        destY = y - height;
    }

    void update(float dt)
    {
        if (position.y <= destY)
            Obj2D::update(dt);

    }

private:
    float destY;
};

#endif // JOGLO

