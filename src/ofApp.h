#pragma once

#include "ofMain.h"
#include "ofxTiming.h"
#include "ofxcustomcontrast.h"

#include "calibration.h"

#include "gedung.h"

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


        ofxUICanvas *gui;

        Calibration calibration;

        ofxTiming timer1;

        //game assets
        ofFbo render_pass;
        ofxCustomContrast fxContrast;

        ofImage gmBossUfo;
        ofImage gmBackgroundLandscape;
        ofImage cityTex;
        //Gedung gedung1;

        //sound

        ofSoundPlayer startup, launch, explode, empty;
        void exit();
};
