//
//  sceneEnding.cpp
//
//

#include "sceneEnding.h"
//#include "FirstScene.h"

void sceneEnding::setup(ofPtr<ofxScene> previousScene) {
    //FirstScene* scene = dynamic_cast<FirstScene *>(previousScene.get());
    //y = scene->y;
}

void sceneEnding::update() {

}

void sceneEnding::draw() {
    ofBackground(0,0,0);
    ofCircle(tes,20);
}


void sceneEnding::mousePressed(int x, int y, int button) {
    tes.x = x;
    tes.y = y;
}
