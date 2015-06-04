#ifndef SCENELEVEL1_H
#define SCENELEVEL1_H

//
//  oFxSceneManager Scene Template
//
//

#include "ofMain.h"
#include "ofxScene.h"

#include "ofxtiming.h"

#include "Obj2D.h"

#include "joglo.h"
#include "ufo_boss.h"

class sceneLevel1 : public ofxScene {
public:
    void setup(ofPtr<ofxScene> pPreviousScene);
    void update();
    void draw();


    //void keyPressed(int key) {}
    //void keyReleased(int key) {}
    //void mouseMoved(int x, int y) {}
    //void mouseDragged(int x, int y, int button) {}
    void mousePressed(int x, int y, int button);
    //void mouseReleased(int x, int y, int button) {}
    //void windowResized(int w, int h) {}
    //void dragEvent(ofDragInfo dragInfo) {}
    //void gotMessage(ofMessage msg) {}

//    virtual void willFadeIn() {}
//    virtual void willDraw() {}
//    virtual void willFadeOut() {}
    void willExit();

private:
    //game assets
    ofImage gmImgTopTitle;
    ofImage gmImgBackgroundLandscape;
    ofImage gmImgBackgroundLandscapeFar;


    ofImage gmImgBossUfo;
    ofImage gmImgJoglo;
    ofImage gmImgPohon;

    ofImage gmImgPabrik;
    ofImage gmImgCrane;
    ofImage gmImgHotel;
    ofImage gmImgBaliho;
    ofImage gmImgMart24;
    ofImage gmImgTraktor;

    ofxTiming tmrBossFire;

    gmUfoBoss ufo;


    //landscape target for boss
    vector <gmJoglo> gmVectorBuildings;

    vector <ofPoint> landscape_border;
    ofPolyline landscape_line;
};

#endif // SCENELEVEL1_H
