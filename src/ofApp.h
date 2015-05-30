#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxMacamPs3Eye.h"


#include "colortracker.h"
#include "ofxPS3EyeGrabber.h"
#include "ofxGLWarper.h"
#include "ofxBlobTracker.h"


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



        void blobAdded(ofxBlob &_blob);
        void blobMoved(ofxBlob &_blob);
        void blobDeleted(ofxBlob &_blob);

        //gui
        ofxUISuperCanvas *gui0;

        //webcam input
       // ofVideoGrabber webcam;
//       ofxMacamPs3Eye ps3eye;
        ofxPS3EyeGrabber ps3eye;
        ofTexture ps3img;
        //ofImage ps3img;


        //color tracker module
        ColorTracker colorTracker;
        TrackerParam trackerParam;

        //contour finder/blob
        ofxCvContourFinder 	contourFinder;
        //blob tracker
        ofxBlobTracker blobTracker;

        //warper module
        ofxGLWarper warper;
		
        ofVec2f lastBlobPos;

        //game assets

        ofImage cityTex;
        Gedung gedung1;

        //sound

        ofSoundPlayer startup, launch, explode, empty;
};
