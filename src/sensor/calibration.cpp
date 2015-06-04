#include "calibration.h"

Calibration::Calibration()
{
    calibDot.set(0,0);
    hide_calib = false;
    bDrawWhiteBg = false;
    guiVisible = true;
    bDebugContour = false;
    bCalibDot = false;
    blobMinArea = 20;
    bBlobTracker = true;
    guiColor.setBrightness(90);
    warperActiveCorner = 0;
}


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
    ps3_hue = ps3eye.getHue();
    ps3_sharpness = ps3eye.getSharpness();

    ps3_ui_processed_img.setup(&colorTracker.processedImg, &blobTracker);
    ps3_ui_texture.setTexture(&ps3eye_texture);

    setupGui1();
    setupGui2();
    setupGui3();


    enableGuiEventCallbacks();

    warper.setup(0,0,320,240);

    windowCenter.x = ofGetWidth()/2;
    windowCenter.y = ofGetHeight()/2;

    receiver.setup(9090);
    //sender.setup("127.0.0.1", 9091);
}


void Calibration::setupGui1()
{
    ofxUiCustomCanvas *gui = new ofxUiCustomCanvas("PS3EYECAM");


    gui->setColorFill(guiColor);
    //gui->setDrawBack(false);
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
    gui->addIntSlider("ps3_hue", 0, 255, &ps3_hue);
    gui->addIntSlider("ps3_sharpness", 0, 255, &ps3_sharpness);

    gui->autoSizeToFitWidgets();
    guihash["1"] = gui;
    guis.push_back(gui);
}

void Calibration::setupGui2()
{

    ofxUiCustomCanvas *gui = new ofxUiCustomCanvas("BLOBTRACKER");
    gui->setColorFill(guiColor);

    if(guis.size() > 0)
        {
            ofxUiCustomCanvas *previous = guis[guis.size()-1];
            gui->getRect()->setX(previous->getRect()->getX()+previous->getRect()->getWidth()+1);
        }

    //gui->setDrawBack(false);
    gui->setName("blobtracker_gui");

    // gui->addLabel("colortracker parameter");
    gui->addSpacer();
    gui->addCustomDrawWidget(&ps3_ui_processed_img, 200, 150, "PROCESSED");
    gui->addSlider("Hue", 0.0, 1.0, &trackerParam.tHue);
    gui->addSlider("Hue Threshold", 0.0, 1.0, &trackerParam.tHueThresh);
    gui->addSlider("Saturation", 0.0, 1.0, &trackerParam.tSat);
    gui->addSlider("Value", 0.0, 1.0, &trackerParam.tValue);
    gui->addSpacer();
    gui->addIntSlider("blobMinArea", 0, 255, &blobMinArea);

    //gui->add2DPad("calib_dot", ofGetWidth())
    gui->autoSizeToFitWidgets();
    guihash["2"] = gui;
    guis.push_back(gui);

}



void Calibration::setupGui3()
{

    ofxUiCustomCanvas *gui = new ofxUiCustomCanvas("SETTINGS");
    gui->setColorFill(guiColor);

    if(guis.size() > 0)
        {
            ofxUiCustomCanvas *previous = guis[guis.size()-1];
            gui->getRect()->setX(previous->getRect()->getX()+previous->getRect()->getWidth()+1);
        }

    //gui->setDrawBack(false);
    gui->setName("settings");


    gui->addLabel("save/load param", OFX_UI_FONT_SMALL);
    // gui->addLabel("colortracker parameter");
    gui->addSpacer();

    gui->addButton("warper1_to_blob", true);
    gui->addButton("warper2_to_blob", true);
    gui->addButton("warper3_to_blob", true);
    gui->addButton("warper4_to_blob", true);

    gui->addSpacer();
    gui->addToggle("debug_contour", &bDebugContour);
    gui->addToggle("blob_tracker", &bBlobTracker);

    gui->addToggle("calib_cam",  &bDrawWhiteBg);
    gui->addToggle("calib_dot", &bCalibDot);
    gui->addToggle("warper_mode", false);



    gui->addSpacer();

    gui->addButton("save_camera", true);
    gui->addButton("load_camera", true);
    gui->addSpacer();

    gui->addButton("save_blobtracker", true);
    gui->addButton("load_blobtracker", true);
    gui->addSpacer();

    gui->addButton("save_warper", true);
    gui->addButton("load_warper", true);

    //gui->add2DPad("calib_dot", ofGetWidth())
    gui->autoSizeToFitWidgets();
    guihash["3"] = gui;
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
    else if(e.getName() == "ps3_hue")
        {
            ofxUIIntSlider *slider =  (ofxUIIntSlider *) e.getSlider();
            ps3eye.setHue(slider->getValue());
        }
    else if(e.getName() == "ps3_sharpness")
        {
            ofxUIIntSlider *slider =  (ofxUIIntSlider *) e.getSlider();
            ps3eye.setSharpness(slider->getValue());
        }

    else if(e.getName() == "save_camera")
        {
            ofxUIButton *btn =  (ofxUIButton *) e.getButton();
            if (btn->getValue())
                guihash["1"]->saveSettings("settings/"+guihash["1"]->getName()+"Settings.xml");
        }

    else if(e.getName() == "load_camera")
        {
            ofxUIButton *btn =  (ofxUIButton *) e.getButton();
            if (btn->getValue())
                guihash["1"]->loadSettings("settings/"+guihash["1"]->getName()+"Settings.xml");
        }


    else if(e.getName() == "save_blobtracker")
        {
            ofxUIButton *btn =  (ofxUIButton *) e.getButton();
            if (btn->getValue())
                guihash["1"]->saveSettings("settings/"+guihash["1"]->getName()+"Settings.xml");
        }

    else if(e.getName() == "load_blobtracker")
        {
            ofxUIButton *btn =  (ofxUIButton *) e.getButton();
            if (btn->getValue())
                guihash["2"]->loadSettings("settings/"+guihash["2"]->getName()+"Settings.xml");
        }


    else if(e.getName() == "save_warper")
        {
            ofxUIButton *btn =  (ofxUIButton *) e.getButton();
            if (btn->getValue())
                warper.save("settings/warper.xml");
        }

    else if(e.getName() == "load_warper")
        {
            ofxUIButton *btn =  (ofxUIButton *) e.getButton();
            if (btn->getValue())
                warper.load("settings/warper.xml");
        }

    else if(e.getName() == "warper_mode")
        {
            ofxUIToggle *tgl =  (ofxUIToggle *) e.getToggle();

            if (tgl->getValue())
                warper.activate();
            else
                warper.deactivate();

        }

//     else if(e.getName() == "FULLSCREEN")
//    {
//        ofxUIToggle *toggle = e.getToggle();
//        ofSetFullscreen(toggle->getValue());
//    }
}


void Calibration::drawDotCalibration()
{
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//	if(bdrawGrid)
//	{
    ofSetColor(255, 0, 0, 255);
    ofRect(0,0,20,20);
    ofRect(ofGetWidth()-20,0,20,20);
    ofRect(ofGetWidth()-20,ofGetHeight()-20,20,20);
    ofRect(0,ofGetHeight()-20,20,20);
//	}
    ofPopStyle();

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
//    ofAddListener(ofEvents().mousePressed, this,  &Calibration::onMousePressed);

    ofAddListener(ofEvents().windowResized, this,  &Calibration::onWindowResized);
    ofAddListener(ofEvents().update, this,  &Calibration::onUpdate);
    ofAddListener(ofEvents().draw, this,    &Calibration::onDraw);
    ofAddListener(ofEvents().exit, this,    &Calibration::onExit);
}

//App Callbacks
void Calibration::disableAppEventCallbacks()
{
//    ofRemoveListener(ofEvents().mousePressed, this,  &Calibration::onMousePressed);

    ofRemoveListener(ofEvents().windowResized, this,  &Calibration::onWindowResized);
    ofRemoveListener(ofEvents().update, this,   &Calibration::onUpdate);
    ofRemoveListener(ofEvents().draw, this,     &Calibration::onDraw);
    ofRemoveListener(ofEvents().exit, this,     &Calibration::onExit);
}

void Calibration::onMousePressed(ofMouseEventArgs &data)
{


}

void Calibration::onWindowResized(ofResizeEventArgs &data)
{
    windowCenter.x = ofGetWidth()/2;
    windowCenter.y = ofGetHeight()/2;
}

void Calibration::onUpdate(ofEventArgs &data)
{

    bool newWebcamFrame = false;

    ps3eye.update();

    newWebcamFrame = ps3eye.isFrameNew();

    if (newWebcamFrame)
        {
            colorTracker.setParam(&trackerParam);
            colorTracker.processVidGrabber(&ps3eye);

            if (isVisible())
                ps3eye_texture.loadData(ps3eye.getPixelsRef());
            if (bDebugContour)
                contourFinder.findContours(colorTracker.processedImg, blobMinArea, (340*240)/3, 10, false);	// find holes
            if (bBlobTracker)
                blobTracker.update(colorTracker.processedImg, -1, blobMinArea);
        }


    if(isVisible())
        processOSCMessage();

}



void Calibration::onDraw(ofEventArgs &data)
{


    if (isVisible())
        {

//            ofPushStyle();
//            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//            //	if(bdrawGrid)
//            //	{
//            ofSetColor(255, 255, 255, 5);
//            drawGrid(20,20);
//            drawDotCalibration();
//            //	}
//            ofPopStyle();

            if(bDrawWhiteBg) ofRect(0,0,ofGetWidth(), ofGetHeight());

            //ps3 image position for calibration
            float pos_cam_calib_x = windowCenter.x - (ps3eye_texture.getWidth()/2);
            float pos_cam_calib_y = windowCenter.y - (ps3eye_texture.getHeight()/2) ;

            if(bDrawWhiteBg) ps3eye_texture.draw(  pos_cam_calib_x , pos_cam_calib_y );

            warper.begin();
            warper.draw();
            warper.end();

            //ofDrawBitmapString("Calibration Mode: Press \"g\" to hide GUI, Press W to enter Warp Mode", windowCenter.x-300, ofGetHeight()-100);

            if(bCalibDot)
                {
                    ofPushStyle();
                    ofSetColor(255, 0, 0, 255);
                    ofCircle( calibDot.x, calibDot.y, 40);
                    ofPopStyle();
                }


            if (bDebugContour)
                {
                    for(int i = 0; i < contourFinder.nBlobs; i++)
                        {
                            ofRectangle r = contourFinder.blobs.at(i).boundingRect;

                            ofVec4f pos_w = warper.fromScreenToWarpCoord(pos_cam_calib_x + r.x, pos_cam_calib_y + r.y, 1);

                            float calib_pos_x = (pos_w.x/ps3eye.getWidth()) * ofGetWidth();
                            float calib_pos_y = (pos_w.y/ps3eye.getHeight()) * ofGetHeight();

                            //ofCircle(calib_pos_x, calib_pos_y, 2);
                            ofLine(calib_pos_x, 0.0, calib_pos_x, ofGetHeight());
                            ofLine(0.0, calib_pos_y, ofGetWidth(), calib_pos_y);

                        }
                }


        }
}

void Calibration::onKeyPressed(ofKeyEventArgs &data)
{
    switch (data.key)
        {

        case '1':
            guihash["1"]->toggleVisible();
            //bGui1Visible = guihash["1"]->isVisible();
            break;
        case '2':
            guihash["2"]->toggleVisible();
            //bGui2Visible = guihash["2"]->isVisible();
            break;
        case '3':
            guihash["3"]->toggleVisible();
            //bGui2Visible = guihash["2"]->isVisible();
            break;
        case 'c':
            calibDot.set(ofGetMouseX(), ofGetMouseY());
            break;
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
        case 'b':
            bDrawWhiteBg = !bDrawWhiteBg;
            break;
        case 'w':
            warper.toogleActive();
            break;
        default:
            break;
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



void Calibration::processOSCMessage()
{

    while(receiver.hasWaitingMessages())
        {
            // get the next message
            ofxOscMessage m;
            receiver.getNextMessage(&m);

            if(m.getAddress() ==  "/ps3/ps3_gain")
                {
                    ps3_gain = m.getArgAsInt32(0);
                    ps3eye.setGain(ps3_gain);
                }
            else if(m.getAddress() ==  "/ps3/ps3_brightness")
                {
                    ps3_brightness = m.getArgAsInt32(0);
                    ps3eye.setBrightness(ps3_brightness);
                }
            else if(m.getAddress() ==  "/ps3/ps3_contrast")
                {
                    ps3_contrast = m.getArgAsInt32(0);
                    ps3eye.setContrast(ps3_contrast);
                }
            else if(m.getAddress() ==  "/ps3/ps3_redbalance")
                {
                    ps3_redbalance = m.getArgAsInt32(0);
                    ps3eye.setRedBalance(ps3_redbalance);
                }
            else if(m.getAddress() ==  "/ps3/ps3_bluebalance")
                {
                    ps3_bluebalance = m.getArgAsInt32(0);
                    ps3eye.setBlueBalance(ps3_bluebalance);
                }
            else if(m.getAddress() ==  "/ps3/ps3_exposure")
                {
                    ps3_exposure = m.getArgAsInt32(0);
                    ps3eye.setExposure(ps3_exposure);
                }
            else if(m.getAddress() ==  "/ps3/ps3_hue")
                {
                    ps3_hue = m.getArgAsInt32(0);
                    ps3eye.setHue(ps3_hue);
                }
            else if(m.getAddress() ==  "/ps3/ps3_sharpness")
                {
                    ps3_sharpness = m.getArgAsInt32(0);
                    ps3eye.setSharpness(ps3_sharpness);
                }
            else if(m.getAddress() ==  "/blob/hue")
                trackerParam.tHue = m.getArgAsFloat(0);

            else if(m.getAddress() ==  "/blob/hue_threshold")
                trackerParam.tHueThresh = m.getArgAsFloat(0);

            else if(m.getAddress() ==  "/blob/saturation")
                trackerParam.tSat = m.getArgAsFloat(0);

            else if(m.getAddress() ==  "/blob/value")
                trackerParam.tValue = m.getArgAsFloat(0);

            else if(m.getAddress() ==  "/blob/blobMinArea")
                blobMinArea = m.getArgAsFloat(0);

            else if(m.getAddress() ==  "/warper/corner1")
                {
                    warperActiveCorner = 0;

                    sender.setup(m.getRemoteIp(), 9091);
                    ofxOscMessage s;
                    ofPoint loc;
                    loc = warper.getCorner((ofxGLWarper::CornerLocation) warperActiveCorner);
                    s.setAddress("/warper/warperXY");
                    s.addFloatArg(loc.y/ofGetHeight());
                    s.addFloatArg(loc.x/ofGetWidth());
                    sender.sendMessage(s);
                    s.clear();

                }



            else if(m.getAddress() ==  "/warper/corner2")
                {
                    warperActiveCorner = 1;

                    sender.setup(m.getRemoteIp(), 9091);
                    ofxOscMessage s;
                    ofPoint loc;
                    loc = warper.getCorner((ofxGLWarper::CornerLocation) warperActiveCorner);
                    s.setAddress("/warper/warperXY");
                    s.addFloatArg(loc.y/ofGetHeight());
                    s.addFloatArg(loc.x/ofGetWidth());
                    sender.sendMessage(s);
                    s.clear();

                }
            else if(m.getAddress() ==  "/warper/corner3")
                {
                    warperActiveCorner = 2;

                    sender.setup(m.getRemoteIp(), 9091);
                    ofxOscMessage s;
                    ofPoint loc;
                    loc = warper.getCorner((ofxGLWarper::CornerLocation) warperActiveCorner);
                    s.setAddress("/warper/warperXY");
                    s.addFloatArg(loc.y/ofGetHeight());
                    s.addFloatArg(loc.x/ofGetWidth());
                    sender.sendMessage(s);
                    s.clear();

                }
            else if(m.getAddress() ==  "/warper/corner4")
                {
                    warperActiveCorner = 3;

                    sender.setup(m.getRemoteIp(), 9091);
                    ofxOscMessage s;
                    ofPoint loc;
                    loc = warper.getCorner((ofxGLWarper::CornerLocation) warperActiveCorner);
                    s.setAddress("/warper/warperXY");
                    s.addFloatArg(loc.y/ofGetHeight());
                    s.addFloatArg(loc.x/ofGetWidth());
                    sender.sendMessage(s);
                    s.clear();

                }
            else if(m.getAddress() ==  "/warper/warperXY")
                {
                    ofPoint loc;
                    loc.x = m.getArgAsFloat(1) * ofGetWidth();
                    loc.y = m.getArgAsFloat(0) * ofGetHeight();
                    warper.setCorner((ofxGLWarper::CornerLocation) warperActiveCorner, loc);
                }


            else if(m.getAddress() ==  "/key/up")
                {
                    ofPoint loc;

                    loc = warper.getCorner((ofxGLWarper::CornerLocation) warperActiveCorner);
                    loc.y -= 0.5;

                    warper.setCorner((ofxGLWarper::CornerLocation) warperActiveCorner, loc);
                }


            else if(m.getAddress() ==  "/key/down")
                {
                    ofPoint loc;

                    loc = warper.getCorner((ofxGLWarper::CornerLocation) warperActiveCorner);
                    loc.y += 0.5;

                    warper.setCorner((ofxGLWarper::CornerLocation) warperActiveCorner, loc);
                }


            else if(m.getAddress() ==  "/key/left")
                {
                    ofPoint loc;

                    loc = warper.getCorner((ofxGLWarper::CornerLocation) warperActiveCorner);
                    loc.x -= 0.5;

                    warper.setCorner((ofxGLWarper::CornerLocation) warperActiveCorner, loc);
                }

            else if(m.getAddress() ==  "/key/right")
                {
                    ofPoint loc;

                    loc = warper.getCorner((ofxGLWarper::CornerLocation) warperActiveCorner);
                    loc.x += 0.5;

                    warper.setCorner((ofxGLWarper::CornerLocation) warperActiveCorner, loc);
                }

            else if(m.getAddress() ==  "/save_settings")
                saveSettings();
            else if(m.getAddress() ==  "/load_settings")
                loadSettings();
            else if(m.getAddress() ==  "/warp_mode")
                warper.toogleActive();
            else if(m.getAddress() ==  "/white_background")
                bDrawWhiteBg = !bDrawWhiteBg;


            else if(m.getAddress() ==  "/send_me_settings")
                {
                    sender.setup(m.getRemoteIp(), 9091);

                    ofxOscMessage s;


                    s.setAddress("/ps3/ps3_gain");
                    s.addIntArg(ps3_gain);
                    sender.sendMessage(s);
                    s.clear();


                    s.setAddress("/ps3/ps3_brightness");
                    s.addIntArg(ps3_brightness);
                    sender.sendMessage(s);
                    s.clear();

                    s.setAddress("/ps3/ps3_contrast");
                    s.addIntArg(ps3_contrast);
                    sender.sendMessage(s);
                    s.clear();

                    s.setAddress("/ps3/ps3_redbalance");
                    s.addIntArg(ps3_redbalance);
                    sender.sendMessage(s);
                    s.clear();

                    s.setAddress("/ps3/ps3_bluebalance");
                    s.addIntArg(ps3_bluebalance);
                    sender.sendMessage(s);
                    s.clear();

                    s.setAddress("/ps3/ps3_exposure");
                    s.addIntArg(ps3_exposure);
                    sender.sendMessage(s);
                    s.clear();

                    s.setAddress("/ps3/ps3_hue");
                    s.addIntArg(ps3_hue);
                    sender.sendMessage(s);
                    s.clear();

                    s.setAddress("/ps3/ps3_sharpness");
                    s.addIntArg(ps3_sharpness);
                    sender.sendMessage(s);
                    s.clear();


                    s.setAddress("/blob/hue");
                    s.addFloatArg(trackerParam.tHue);
                    sender.sendMessage(s);
                    s.clear();


                    s.setAddress("/blob/hue_threshold");
                    s.addFloatArg(trackerParam.tHueThresh);
                    sender.sendMessage(s);
                    s.clear();

                    s.setAddress("/blob/saturation");
                    s.addFloatArg(trackerParam.tSat);
                    sender.sendMessage(s);
                    s.clear();


                    s.setAddress("/blob/value");
                    s.addFloatArg(trackerParam.tValue);
                    sender.sendMessage(s);
                    s.clear();

                    s.setAddress("/blob/blobMinArea");
                    s.addFloatArg(blobMinArea);
                    sender.sendMessage(s);
                    s.clear();

                }



        }
}

void Calibration::loadSettings()
{
    vector<ofxUiCustomCanvas *>::iterator it;
    for(it = guis.begin(); it != guis.end(); it++)
        {
            (*it)->loadSettings("settings/"+(*it)->getName()+"Settings.xml");
        }

    warper.load("settings/warper.xml");
}

void Calibration::saveSettings()
{
    vector<ofxUiCustomCanvas *>::iterator it;
    for(it = guis.begin(); it != guis.end(); it++)
        {
            (*it)->saveSettings("settings/"+(*it)->getName()+"Settings.xml");
        }

    warper.save("settings/warper.xml");

}
