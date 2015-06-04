//
//  sceneOpening.cpp
//
//

#include "sceneOpening.h"
//#include "FirstScene.h"

void sceneOpening::setup(ofPtr<ofxScene> previousScene) {
    //FirstScene* scene = dynamic_cast<FirstScene *>(previousScene.get());
    //y = scene->y;
    gmOpening.loadImage("assets/scene/scene_1_opening.png");
}

void sceneOpening::update() {

}

void sceneOpening::draw() {
    ofBackground(0,0,0);
    gmOpening.draw(0,0);
}

void sceneOpening::mousePressed(int x, int y, int button)
{
    exitScene();
}
