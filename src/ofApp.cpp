#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofToggleFullscreen();
    ofSetFrameRate(30);

    render_pass.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    fxContrast.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

    calibration.setup();

    gmBossUfo.loadImage("assets/boss_ufo.png");
    gmBossUfo.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

    gmBackgroundLandscape.loadImage("assets/background_landscape.png");
    gmBackgroundLandscape.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

    explode.loadSound("sounds/explode.wav");
    timer1.setup(2);

    gui = new ofxUICanvas("brcosa");
    gui->addSlider("brightness",0,50, &fxContrast.brightness);
    gui->addSlider("contrast",0,5, &fxContrast.contrast);
    gui->addSlider("multiple",0,5, &fxContrast.multiple);
    fxContrast.brightness = 6.5;
    fxContrast.contrast = 1.0;
    fxContrast.multiple = 1.0;

}

void ofApp::exit()
{
    //gui->saveSettings("settings.xml");
    delete gui;
}
//--------------------------------------------------------------
void ofApp::update()
{
    if(timer1.tick())
        {
            explode.play();
            printf("tick\n");
        }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    render_pass.begin();
        ofBackground(0,0,0);
        gmBackgroundLandscape.draw(0,ofGetHeight()-79, ofGetWidth() , 79 );
        gmBossUfo.draw( ofMap( sin(TWO_PI * ofGetElapsedTimef() * 1/10 ), -1,1,0,ofGetWidth()-200) , ofNoise(ofGetElapsedTimef()*1.5) * 200);
    render_pass.end();


    fxContrast.update();
    fxContrast << render_pass;


    fxContrast.draw(0,0);

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



