#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
//
    ofSetFrameRate(30);
//    //ofEnableSmoothing();
//    ofSetVerticalSync(true);
////    ofEnableAntiAliasing();
//
    calibration.setup();
//
////   webcam.setVerbose(true);
//    //  webcam.initGrabber(320,240);
//
//    // ps3eye.initGrabber(320,240);
//
//    gmBossUfo.loadImage("assets/boss_ufo.png");
//    gmBossUfo.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
//
//
//    gmBackgroundLandscape.loadImage("assets/background_landscape.png");
//    gmBackgroundLandscape.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
//

//   // gui0->addWidgetP


//    warper.setup();
//    warper.activate();

//    lastBlobPos.x = 0;
//    lastBlobPos.y = 0;

//    //game assets

//    cityTex.loadImage("gedung1.png");
//    cityTex.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

//    gedung1.setup(&cityTex);
//    gedung1.position.x = ofGetWidth()/2;
//    gedung1.position.y = 700;
//
    explode.loadSound("sounds/explode.wav");
  //  explode.loadSound("wew");
    //hide_calib = false;
    timer1.setup(2);
     explode.play();
}

//--------------------------------------------------------------
void ofApp::update()
{


    //    bool newWebcamFrame = false;

////    webcam.update();

//    ps3eye.update();

////    newWebcamFrame = webcam.isFrameNew();

//    newWebcamFrame = ps3eye.isFrameNew();

//    if (newWebcamFrame)
//        {
//            colorTracker.setParam(&trackerParam);

//            ps3img.loadData(ps3eye.getPixelsRef());
//            colorTracker.processVidGrabber(&ps3eye);

//            contourFinder.findContours(colorTracker.processedImg, 20, (320*240)/3, 10, true);	// find holes

////            blobTracker.update(colorTracker.processedImg);
//        }
    if(timer1.tick())
    {
        explode.play();
       printf("tick\n");
    }
//printf("elapsed: %f\n", ofGetElapsedTimef());

}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0,0,0);

   // gmBackgroundLandscape.draw(0,ofGetHeight()-79, ofGetWidth() , 79 );


    //ofPushMatrix();
    //ofRotateZ(ofNoise(ofGetElapsedTimef()*1.5) * 200  );
   // gmBossUfo.draw( ofMap( sin(TWO_PI * ofGetElapsedTimef() * 1/10 ), -1,1,0,ofGetWidth()-200) , ofNoise(ofGetElapsedTimef()*1.5) * 200);
    //ofPopMatrix();

    //    ofPoint pos = ofPoint((ofGetWidth()/2)-480,(ofGetHeight()/2)-120);

//    if(!hide_calib){

//    ps3img.draw(pos.x, pos.y, 320,240);
//    colorTracker.processedImg.draw( pos.x + 320,pos.y, 320,240);
//    contourFinder.draw(pos.x + 640, pos.y,320,240);

//    }

//    if (warper.isActive() == false)
//    {
//        ofVec4f warp_coord = warper.fromScreenToWarpCoord(mouseX, mouseY, 1);
//        ofDrawBitmapString("x: " + ofToString(warp_coord.x)  + " " +  "y: " + ofToString(warp_coord.y) , 100,300);

//        ofCircle(warp_coord.x, warp_coord.y, 10);
//        ofCircle(mouseX, mouseY, 2);


//    }

//    for(int i = 0; i < contourFinder.nBlobs; i++) {
//        ofRectangle r = contourFinder.blobs.at(i).boundingRect;

//        ofVec4f screen_warped = warper.fromScreenToWarpCoord(pos.x + r.x, pos.y + r.y, 1);
//        r.x = screen_warped.x;
//        r.y = screen_warped.y;
//        //r.x += 320; r.y += 240;
//        //c.setHsb(i * 64, 255, 255);
//        //ofSetColor(c);
//        //ofRect(r);

////        ofPushMatrix();
////        ofTranslate(r.x,r.y);
////        ofDrawAxis(1.0);
////        ofPopMatrix();

////        ofCircle(r.x,r.y,0.5);
//        ofLine(r.x, 0.0, r.x, ofGetHeight());
//        ofLine(0.0, r.y, ofGetWidth(), r.y);

//       // ofLine(r.x, 0.0, r.x, ofGetHeight());

//        ofRect(r);
//    }


////    blobTracker.draw(pos.x + 640,pos.y);

//    warper.begin();
//    warper.draw();
//    warper.end();

//    gedung1.draw();


//    ofLine(lastBlobPos.x, 0.0, lastBlobPos.x, ofGetHeight());
//    ofLine(0.0, lastBlobPos.y, ofGetWidth(), lastBlobPos.y);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

    switch (key)
        {
        case 't':
            ofToggleFullscreen();
            break;
        default:
            break;
        }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}

//-------------------------------------------------------------



