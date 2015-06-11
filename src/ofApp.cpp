#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    //ofToggleFullscreen();
    ofSetFrameRate(30);

    render_pass.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    fxContrast.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

    calibration.setup(this);

    gui = new ofxUICanvas("brcosa");
    gui->addSlider("brightness",0,50, &fxContrast.brightness);
    gui->addSlider("contrast",0,5, &fxContrast.contrast);
    gui->addSlider("multiple",0,5, &fxContrast.multiple);
    gui->addFPS();
    gui->toggleVisible();

    fxContrast.brightness = 6.5;
    fxContrast.contrast = 1.0;
    fxContrast.multiple = 1.0;


    sceneSequenceImg[0].loadImage("assets/cutscene/1start.png");
    sceneSequenceImg[1].loadImage("assets/cutscene/2selamatdatang.png");
    sceneSequenceImg[2].loadImage("assets/cutscene/3cerita1.png");
    sceneSequenceImg[3].loadImage("assets/cutscene/4cerita2.png");
    sceneSequenceImg[4].loadImage("assets/cutscene/5cerita3.png");
    sceneSequenceImg[5].loadImage("assets/cutscene/6cerita4.png");
    sceneSequenceImg[6].loadImage("assets/cutscene/7cerita5.png");
    sceneSequenceImg[7].loadImage("assets/cutscene/8akhir.png");

    sceneSequence[0] = new sceneGeneric(); //start

    sceneSequence[1] = new sceneGeneric(5);
    sceneSequence[2] = new sceneGeneric(10);
    sceneSequence[3] = new sceneGeneric(10);
    sceneSequence[4] = new sceneGeneric(12);
    sceneSequence[5] = new sceneGeneric(12);
    sceneSequence[6] = new sceneGeneric(12);
    sceneSequence[7] = new sceneGeneric(12);



    sceneSequence[0]->setImg(&sceneSequenceImg[0]);
    sceneSequence[1]->setImg(&sceneSequenceImg[1]);
    sceneSequence[2]->setImg(&sceneSequenceImg[2]);
    sceneSequence[3]->setImg(&sceneSequenceImg[3]);
    sceneSequence[4]->setImg(&sceneSequenceImg[4]);
    sceneSequence[5]->setImg(&sceneSequenceImg[5]);
    sceneSequence[6]->setImg(&sceneSequenceImg[6]);
    sceneSequence[7]->setImg(&sceneSequenceImg[7]);


    sceneManager.addScene(ofPtr<ofxScene> (sceneSequence[0])); //start
    sceneManager.addScene(ofPtr<ofxScene> (sceneSequence[1])); //selamat datnng

    sceneManager.addScene(ofPtr<ofxScene> (sceneSequence[2]));
    sceneManager.addScene(ofPtr<ofxScene> (sceneSequence[3]));
    sceneManager.addScene(ofPtr<ofxScene> (sceneSequence[4]));
    sceneManager.addScene(ofPtr<ofxScene> (sceneSequence[5]));
    sceneManager.addScene(ofPtr<ofxScene> (sceneSequence[6]));

//    sceneManager.addScene(ofPtr<ofxScene>(new sceneOpening));
    sceneManager.addScene(ofPtr<ofxScene>(new sceneLevel1));
    //sceneManager.addScene(ofPtr<ofxScene>(new sceneEnding));
    sceneManager.addScene(ofPtr<ofxScene> (sceneSequence[7]));



    sceneManager.setTransitionDissolve();
//    sceneManager.setSceneDuration(0,0);
    sceneManager.run();

    playBg = true;
    gmBgSnd.loadSound("bgmusic_intro.mp3");
    gmBgSnd.setLoop(true);
    gmBgSnd.play();



    calibration.loadSettings();
    calibration.toggleVisible();
    calibration.setBEnableSendMouseEvent(true);


    ofSetWindowPosition(1880,0);
    ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::update()
{

    if (sceneManager.sceneIndex() == 7)
    {
        if (playBg)
        {
            playBg = false;
            gmBgSnd.stop();
            printf("bgplay\n");
        }
    }else if (!playBg)
    {
        playBg = true;
        gmBgSnd.play();
        printf("bgplay\n");

    }

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


