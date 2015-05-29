#ifndef SCENEENDING_H
#define SCENEENDING_H

//
// oFxSceneManager Scene Template
// usage add ofxSceneManager
//
// FirstScene* firstScene = new FirstScene;
// firstScene->setSceneDuration(0.5, 1.5, 0.5);
//
// SecondScene* secondScene = new SecondScene;
// secondScene->setSceneDuration(0.5, 3.0, 0.5);
//
// sceneManager.addScene(ofPtr<ofxScene>(firstScene));
// sceneManager.addScene(ofPtr<ofxScene>(secondScene));
// sceneManager.setExitByTime(true);
//
// sceneManager.setTransitionDissolve();
// sceneManager.setTransitionFade();
//
// sceneManager.run();
//

#include "ofxScene.h"

class sceneEnding : public ofxScene {
public:
    void setup(ofPtr<ofxScene> pPreviousScene);
    void update();
    void draw();
};

#endif // SCENEENDING_H
