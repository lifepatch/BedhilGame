#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{

    ofSetFrameRate(30);

//   webcam.setVerbose(true);
    //  webcam.initGrabber(320,240);

    // ps3eye.initGrabber(320,240);

    ps3eye.setDeviceID(0);
    ps3eye.initGrabber(320,240);


    gui0 = new ofxUISuperCanvas("Color Tracker Parameter");
    //gui0->setDimensions(200,400);
    gui0->addSpacer();
    gui0->addLabel("Hue");
    gui0->addSlider("tHue", 0.0, 1.0, &trackerParam.tHue);
    // gui0->addSpacer();
    gui0->addLabel("Hue Threshold");
    gui0->addSlider("tHueThresh", 0.0, 1.0, &trackerParam.tHueThresh);
    //  gui0->addSpacer();
    gui0->addLabel("Saturation");
    gui0->addSlider("tSat", 0.0, 1.0, &trackerParam.tSat);
    //  gui0->addSpacer();
    gui0->addLabel("Value");
    gui0->addSlider("tValue", 0.0, 1.0, &trackerParam.tValue);
    gui0->autoSizeToFitWidgets();


    warper.setup();
    warper.activate();
}

//--------------------------------------------------------------
void ofApp::update()
{

    bool newWebcamFrame = false;

//    webcam.update();

    ps3eye.update();

//    newWebcamFrame = webcam.isFrameNew();

    newWebcamFrame = ps3eye.isFrameNew();

    if (newWebcamFrame)
        {
            tracker.setParam(&trackerParam);

            ps3img.loadData(ps3eye.getPixelsRef());
            tracker.processVidGrabber(&ps3eye);

            contourFinder.findContours(tracker.processedImg, 20, (320*240)/3, 10, true);	// find holes
        }



}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0,0,0);

    ofPoint pos = ofPoint((ofGetWidth()/2)-480,(ofGetHeight()/2)-120);
    ps3img.draw(pos.x, pos.y);
    tracker.processedImg.draw( pos.x + 320,pos.y);
    //contourFinder.draw(pos.x + 640, pos.y);


//    if (warper.isActive() == false)
//    {
//        ofVec4f warp_coord = warper.fromScreenToWarpCoord(mouseX, mouseY, 1);
//        ofDrawBitmapString("x: " + ofToString(warp_coord.x)  + " " +  "y: " + ofToString(warp_coord.y) , 100,300);

//        ofCircle(warp_coord.x, warp_coord.y, 10);
//        ofCircle(mouseX, mouseY, 2);


//    }

    for(int i = 0; i < contourFinder.nBlobs; i++) {
        ofRectangle r = contourFinder.blobs.at(i).boundingRect;

        ofVec4f screen_warped = warper.fromScreenToWarpCoord(pos.x + r.x, pos.y + r.y, 1);
        r.x = screen_warped.x;
        r.y = screen_warped.y;
        //r.x += 320; r.y += 240;
        //c.setHsb(i * 64, 255, 255);
        //ofSetColor(c);
        //ofRect(r);

        ofLine(r.x, 0.0, r.x, ofGetHeight());
        ofLine(0.0, r.y, ofGetWidth(), r.y);

       // ofLine(r.x, 0.0, r.x, ofGetHeight());

        ofRect(r);
    }


    warper.begin();
    warper.draw();
    warper.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

    switch (key)
        {
        case ' ':
            if (warper.isActive())
                {
                    warper.deactivate(); //once you are done with the Wrapping you should call this method, so it realeses the keyboard and mouse and stop processing the transformation matrixes.
                    // this will reduce the amount of precessing needed.
                }
            else
                {
                    warper.activate();
                }

            break;
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
