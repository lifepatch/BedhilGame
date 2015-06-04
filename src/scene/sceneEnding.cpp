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
    ofSetColor(255, 0, 255);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());

    ofSetColor(200);
    y = (y+2) % ofGetHeight();
    ofRect(0, y, ofGetWidth(), 10);
}
