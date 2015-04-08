#ifndef SCENELEVEL1_H
#define SCENELEVEL1_H

//
//  oFxSceneManager Scene Template
//
//

#include "ofxScene.h"

class sceneLevel1 : public ofxScene {
public:
    void setup(ofPtr<ofxScene> pPreviousScene);
    void update();
    void draw();
};

#endif // SCENELEVEL1_H
