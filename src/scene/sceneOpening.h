#ifndef SCENEOPENING_H
#define SCENEOPENING_H

//
//  oFxSceneManager Scene Template
//
//

#include "ofxScene.h"

class sceneOpening : public ofxScene {
        public:
        void setup(ofPtr<ofxScene> pPreviousScene);
void update();
void draw();
};

#endif // SCENEOPENING_H
