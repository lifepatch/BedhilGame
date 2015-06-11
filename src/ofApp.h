#pragma once

#include "ofMain.h"
#include "ofxTiming.h"
#include "ofxcustomcontrast.h"
#include "ofxSceneManager.h"

#include "calibration.h"

#include "gedung.h"


#include "sceneOpening.h"
#include "sceneLevel1.h"
#include "sceneEnding.h"
#include "sceneintro.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void exit();

    private:
        ofSoundPlayer gmBgSnd;

        //tracking calibration
        Calibration calibration;

        //render pass brcosa settings
        ofxUICanvas *gui;
        ofFbo render_pass;
        ofxCustomContrast fxContrast;        

        ofImage sceneSequenceImg[8];
        sceneGeneric * sceneSequence[8];


        //sound
        ofSoundPlayer startup, launch, explode, empty;
        ofxTiming timer1;


        //scene
        ofxSceneManager sceneManager;

        bool playBg;


};
