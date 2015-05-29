#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxMacamPs3Eye.h"


#include "colortracker.h"
#include "ofxPS3EyeGrabber.h"
#include "ofxGLWarper.h"

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

        //gui
        ofxUISuperCanvas *gui0;

        //webcam input
       // ofVideoGrabber webcam;
//       ofxMacamPs3Eye ps3eye;
        ofxPS3EyeGrabber ps3eye;
        ofTexture ps3img;
        //ofImage ps3img;


        //color tracker module
        ColorTracker tracker;
        TrackerParam trackerParam;

        //contour finder/blob
        ofxCvContourFinder 	contourFinder;

        //warper module
        ofxGLWarper warper;
		
};
