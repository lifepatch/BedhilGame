#ifndef CITY
#define CITY


#include "ofMain.h"
#include "Obj2D.h"

class Gedung : public Obj2D{

public:

    Gedung(){
        alive = true;
    }

    void kill(){ alive = false;}
    void revive(){ alive = true;}
    bool isDead(){return !alive;}
    bool isAlive(){return alive;}

    void draw(){
        if(alive){
            Obj2D::draw();
        }else{
            ofSetColor(0,255);
            tex->draw( x, y, width, height );
        }
    }
private:

    bool alive;


};


#endif // CITY

