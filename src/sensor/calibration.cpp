#include "calibration.h"


void Calibration::setup()
{

    enableAppEventCallbacks();
    enableKeyEventCallbacks();
    enableBlobEventCallbacks();


    ps3eye.setDeviceID(0);
    ps3eye.initGrabber(320,240);
    ps3eye.setAutogain(false);
    ps3eye.setAutoWhiteBalance(false);
    ps3eye.setGain(0);

    ps3_gain = ps3eye.getGain();
    ps3_brightness = ps3eye.getBrightness();
    ps3_contrast = ps3eye.getContrast();
    ps3_redbalance = ps3eye.getRedBalance();
    ps3_bluebalance = ps3eye.getBlueBalance();

    ps3_ui_processed_img.setup(&colorTracker.processedImg, &blobTracker);
    ps3_ui_texture.setTexture(&ps3eye_texture);


    setupGui1();
    setupGui2();

    enableGuiEventCallbacks();


    windowCenter.x = ofGetWidth()/2;
    windowCenter.y = ofGetHeight()/2;


}


void Calibration::setupGui1()
{
    ofxUiCustomCanvas *gui = new ofxUiCustomCanvas("PS3EYECAM");

    gui->setDrawBack(false);
    gui->setName("ps3eyecam_gui");
    //gui->addLabel("ps3_eye parameter");
    gui->addSpacer();
    gui->addCustomDrawWidget(&ps3_ui_texture, 200, 150, "PS3CAM");
    gui->addIntSlider("ps3_gain", 0, 255, &ps3_gain);
    gui->addIntSlider("ps3_exposure", 0, 255, &ps3_exposure);
    gui->addIntSlider("ps3_brightness", 0, 255, &ps3_brightness);
    gui->addIntSlider("ps3_contrast", 0, 255, &ps3_contrast);
    gui->addIntSlider("ps3_redbalance", 0, 255, &ps3_redbalance);
    gui->addIntSlider("ps3_bluebalance", 0, 255, &ps3_bluebalance);
    gui->autoSizeToFitWidgets();
    guihash["1"] = gui;
    guis.push_back(gui);
}

void Calibration::setupGui2()
{

    ofxUiCustomCanvas *gui = new ofxUiCustomCanvas("BLOBTRACKER");

    if(guis.size() > 0)
    {
        ofxUiCustomCanvas *previous = guis[guis.size()-1];
        gui->getRect()->setX(previous->getRect()->getX()+previous->getRect()->getWidth()+1);
    }

    gui->setDrawBack(false);
    gui->setName("blobtracker_gui");

   // gui->addLabel("colortracker parameter");
    gui->addSpacer();
    gui->addCustomDrawWidget(&ps3_ui_processed_img, 200, 150, "PROCESSED");
    gui->addSlider("Hue", 0.0, 1.0, &trackerParam.tHue);
    gui->addSlider("Hue Threshold", 0.0, 1.0, &trackerParam.tHueThresh);
    gui->addSlider("Saturation", 0.0, 1.0, &trackerParam.tSat);
    gui->addSlider("Value", 0.0, 1.0, &trackerParam.tValue);
    gui->autoSizeToFitWidgets();
    guihash["2"] = gui;
    guis.push_back(gui);

}

void Calibration::guiEvent(ofxUIEventArgs &e)
{
    if(e.getName() == "ps3_gain")
    {
        ofxUIIntSlider *slider =  (ofxUIIntSlider *) e.getSlider();
        ps3eye.setGain(slider->getValue());
    }
    else if(e.getName() == "ps3_brightness")
    {
        ofxUIIntSlider *slider =  (ofxUIIntSlider *) e.getSlider();
        ps3eye.setBrightness(slider->getValue());
    }
    else if(e.getName() == "ps3_contrast")
    {
        ofxUIIntSlider *slider =  (ofxUIIntSlider *) e.getSlider();
        ps3eye.setContrast(slider->getValue());
    }
    else if(e.getName() == "ps3_redbalance")
    {
        ofxUIIntSlider *slider =  (ofxUIIntSlider *) e.getSlider();
        ps3eye.setRedBalance(slider->getValue());
    }
    else if(e.getName() == "ps3_bluebalance")
    {
        ofxUIIntSlider *slider =  (ofxUIIntSlider *) e.getSlider();
        ps3eye.setBlueBalance(slider->getValue());
    }
    else if(e.getName() == "ps3_exposure")
    {
        ofxUIIntSlider *slider =  (ofxUIIntSlider *) e.getSlider();
        ps3eye.setExposure(slider->getValue());
    }


//     else if(e.getName() == "FULLSCREEN")
//    {
//        ofxUIToggle *toggle = e.getToggle();
//        ofSetFullscreen(toggle->getValue());
//    }
}



Calibration::Calibration()
{
    hide_calib = false;
    guiVisible = true;
}

void Calibration::drawGrid(float x, float y)
{
    float w = ofGetWidth();
    float h = ofGetHeight();

    for(int i = 0; i < h; i+=y)
    {
        ofLine(0,i,w,i);
    }

    for(int j = 0; j < w; j+=x)
    {
        ofLine(j,0,j,h);
    }
}



//Blob Callbacks
void Calibration::enableBlobEventCallbacks()
{
    ofAddListener(blobTracker.blobAdded, this, &Calibration::blobAdded);
    ofAddListener(blobTracker.blobMoved, this, &Calibration::blobMoved);
    ofAddListener(blobTracker.blobDeleted, this, &Calibration::blobDeleted);
}

void Calibration::disableBlobEventCallbacks()
{
    ofRemoveListener(blobTracker.blobAdded, this, &Calibration::blobAdded);
    ofRemoveListener(blobTracker.blobMoved, this, &Calibration::blobMoved);
    ofRemoveListener(blobTracker.blobDeleted, this, &Calibration::blobDeleted);
}

void Calibration::enableGuiEventCallbacks()
{
    for(int i = 0; i < guis.size(); i++)
    {
        ofxUiCustomCanvas *gui = guis[i];
        ofAddListener(gui->newGUIEvent, this, &Calibration::guiEvent);
    }
}

void Calibration::disableGuiEventCallbacks()
{
    for(int i = 0; i < guis.size(); i++)
    {
        ofxUiCustomCanvas *gui = guis[i];
        ofRemoveListener(gui->newGUIEvent, this, &Calibration::guiEvent);
    }
}


void Calibration::enableKeyEventCallbacks()
{
    ofAddListener(ofEvents().keyPressed, this, &Calibration::onKeyPressed);
}

void Calibration::disableKeyEventCallbacks()
{
    ofRemoveListener(ofEvents().keyPressed, this, &Calibration::onKeyPressed);
}


//App Callbacks
void Calibration::enableAppEventCallbacks()
{
    ofAddListener(ofEvents().windowResized, this,  &Calibration::onWindowResized);
    ofAddListener(ofEvents().update, this,  &Calibration::onUpdate);
    ofAddListener(ofEvents().draw, this,    &Calibration::onDraw);
    ofAddListener(ofEvents().exit, this,    &Calibration::onExit);
}

//App Callbacks
void Calibration::disableAppEventCallbacks()
{
    ofRemoveListener(ofEvents().windowResized, this,  &Calibration::onWindowResized);
    ofRemoveListener(ofEvents().update, this,   &Calibration::onUpdate);
    ofRemoveListener(ofEvents().draw, this,     &Calibration::onDraw);
    ofRemoveListener(ofEvents().exit, this,     &Calibration::onExit);
}


void Calibration::onWindowResized(ofResizeEventArgs &data)
{
    windowCenter.x = ofGetWidth()/2;
    windowCenter.y = ofGetHeight()/2;
}

void Calibration::onUpdate(ofEventArgs &data)
{

    bool newWebcamFrame = false;

    ////    webcam.update();

    ps3eye.update();

    ////    newWebcamFrame = webcam.isFrameNew();

    newWebcamFrame = ps3eye.isFrameNew();

    if (newWebcamFrame)
        {
            colorTracker.setParam(&trackerParam);
            if (isVisible()) ps3eye_texture.loadData(ps3eye.getPixelsRef());
            colorTracker.processVidGrabber(&ps3eye);

            blobTracker.update(colorTracker.processedImg);
        }


}

void Calibration::onDraw(ofEventArgs &data)
{


    //ps3eye_image.draw(0,0);
    //ps3eye_texture.draw(windowCenter.x-640,windowCenter.y-200);
    //colorTracker.processedImg.draw(windowCenter.x, windowCenter.y - 200);

    if (isVisible())
    {
        ofPushStyle();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    //	if(bdrawGrid)
    //	{
            ofSetColor(255, 255, 255, 25);
            drawGrid(20,20);
    //	}
        ofPopStyle();
        ofDrawBitmapString("Calibration Mode: Press \"g\" to hide GUI, Press W to enter Warp Mode", windowCenter.x-300, ofGetHeight()-100);

    }
}

void Calibration::onKeyPressed(ofKeyEventArgs &data)
{
    switch (data.key)
    {
    case 'g':
        toggleVisible();
        //gui0->toggleVisible();
        break;
    case 's':
        if(isVisible()) saveSettings();
        break;
    case 'l':
        if(isVisible()) loadSettings();
        break;
    default: break;
    }

    //printf("key = %i", data.key);
}

void Calibration::onExit(ofEventArgs &data)
{
    for(int i = 0; i < guis.size(); i++)
    {
        ofxUiCustomCanvas *gui = guis[i];
        delete gui;
    }
    guis.clear();

    disableBlobEventCallbacks();
    disableAppEventCallbacks();
    disableKeyEventCallbacks();


    disableGuiEventCallbacks();

}


bool Calibration::isVisible()
{
    return guiVisible;
}

void Calibration::toggleVisible()
{
    guiVisible = !guiVisible;
    for(int i = 0; i < guis.size(); i++)
    {
        ofxUiCustomCanvas *gui = guis[i];
        gui->setVisible(guiVisible);
        //delete gui;
    }
}

void Calibration::blobAdded(ofxBlob &_blob)
{

    ofPoint pos = ofPoint((ofGetWidth()/2)-480,(ofGetHeight()/2)-120);

    printf("blob added %f %f\n", _blob.centroid.x, _blob.centroid.y);

//    ofVec4f hitpos = warper.fromScreenToWarpCoord(pos.x + _blob.centroid.x*320, pos.y + _blob.centroid.y*240, 1);

//    lastBlobPos.x = hitpos.x;
//    lastBlobPos.y = hitpos.y;

//    if ( gedung1.hitTest(hitpos))
//        {
//            explode.play();
//        }
}

void Calibration::blobMoved(ofxBlob &_blob)
{

}

void Calibration::blobDeleted(ofxBlob &_blob)
{

}


void Calibration::loadSettings()
{
    vector<ofxUiCustomCanvas *>::iterator it;
    for(it = guis.begin(); it != guis.end(); it++)
    {
        (*it)->loadSettings("GUI/"+(*it)->getName()+"Settings.xml");
    }
}

void Calibration::saveSettings()
{
    vector<ofxUiCustomCanvas *>::iterator it;
    for(it = guis.begin(); it != guis.end(); it++)
    {
        (*it)->saveSettings("GUI/"+(*it)->getName()+"Settings.xml");
    }
}
