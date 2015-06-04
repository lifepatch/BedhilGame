#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    //ofToggleFullscreen();
    ofSetFrameRate(30);

    render_pass.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    fxContrast.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

    //calibration.setup();

    gui = new ofxUICanvas("brcosa");
    gui->addSlider("brightness",0,50, &fxContrast.brightness);
    gui->addSlider("contrast",0,5, &fxContrast.contrast);
    gui->addSlider("multiple",0,5, &fxContrast.multiple);
    gui->addFPS();
    gui->toggleVisible();

    fxContrast.brightness = 6.5;
    fxContrast.contrast = 1.0;
    fxContrast.multiple = 1.0;

    sceneManager.addScene(ofPtr<ofxScene>(new sceneOpening));
    sceneManager.addScene(ofPtr<ofxScene>(new sceneLevel1));
    sceneManager.addScene(ofPtr<ofxScene>(new sceneEnding));
    sceneManager.setTransitionDissolve();
    //sceneManager.setSceneDuration(0,0);
    sceneManager.run();

}

//--------------------------------------------------------------
void ofApp::update()
{
    sceneManager.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{

//render_pass.begin();
sceneManager.draw();
//render_pass.end();

//fxContrast.update();
//fxContrast << render_pass;
//fxContrast.draw(0,0);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

    switch (key)
        {
        case 't':
            ofToggleFullscreen();
            break;
        case 'c':
            gui->toggleVisible();
            break;
    case ' ':
        sceneManager.changeScene();
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

void ofApp::exit()
{
    //gui->saveSettings("settings.xml");
    delete gui;
}


