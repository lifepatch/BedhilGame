#include "Obj2D.h"

void Obj2D::setup(ofImage * img ){

    tex = img;
    if (img){
        width = img->width;
        height = img->height;
    }

}


void Obj2D::addGravity(float grav = 20){
    force.y = force.y + grav;
}

void Obj2D::update(float dt){

    speed.x = speed.x + force.x;
    speed.y = speed.y + force.y;

    x += speed.x * dt;
    y += speed.y * dt;

    force.x = 0;
    force.y = 0;
}


bool Obj2D::hitTest( ofVec2f p){
    return inside(p);
}


bool Obj2D::hitTest( ofRectangle r ){
    return inside(r);
}

bool Obj2D::hitTestCircle(ofVec2f center, float radius){

    bool t0 = inside(center);
    if (t0) return true;
    bool t1 = center.distance( getTopLeft() ) < radius;
    if (t1) return true;
    bool t2 = center.distance( getTopRight() ) < radius;
    if (t2) return true;
    bool t3 = center.distance( getBottomLeft() ) < radius;
    if (t3) return true;
    bool t4 = center.distance( getBottomRight() ) < radius;
    if (t4) return true;
    return false;
}
bool Obj2D::isGrounded()
{
            if (position.y <= destY)
            {
                return false;
            }else{
                return true;
            }
}





void Obj2D::addForce(float x, float y)
{
    force.x = force.x + x;
    force.y = force.y + x;
}


void Obj2D::draw(){
    ofSetColor(color);
    if(tex){
        tex->draw( x, y, width, height );
    }else{
        ofRect( x, y, width, height );
    }

}
