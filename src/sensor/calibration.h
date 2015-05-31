#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "ofMain.h"
#include "ofxPS3EyeGrabber.h"
#include "ofxGLWarper.h"
#include "ofxBlobTracker.h"
#include "ofxUI.h"
#include "ofxUIFBO.h"

#include "colortracker.h"


class ofxUiCustomTextureViewer : public ofxDrawProxy {
private:
    ofTexture* texture;
public:
    void setTexture(ofTexture* _texture)
    {
        texture = _texture;
    }

    void draw(float x, float y, float w , float h){
        if(texture)
        texture->draw(x,y,w,h);
    }
};

class ofxUiCustomCvGrayScale : public ofxDrawProxy {
private:
    ofxCvGrayscaleImage* texture;
    ofxBlobTracker* blobTracker;
public:
    void setup(ofxCvGrayscaleImage* _texture, ofxBlobTracker* _blobTracker)
    {
        texture = _texture;
        blobTracker = _blobTracker;
    }

    void draw(float x, float y, float w , float h){
        texture->draw(x,y,w,h);
        blobTracker->draw(x,y,w,h);
//        blobTracker->dr
    }
};

class ofxUiCustomCanvas : public ofxUISuperCanvas
{
public:
    ofxUiCustomCanvas(string _label, int _size = OFX_UI_FONT_MEDIUM) : ofxUISuperCanvas(_label, _size)
    {

    }

    ofxUIFBO* addCustomDrawWidget(ofxDrawProxy * _drawProxy,int w, int h, const char * title) {
        ofxUIFBO* widget = new ofxUIFBO(w,h, _drawProxy, title );
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
};

class Calibration
{
public:
    Calibration();

    void enableAppEventCallbacks();
    void disableAppEventCallbacks();

    void onUpdate(ofEventArgs &data);
    void onDraw(ofEventArgs &data);
    void onExit(ofEventArgs &data);
    void onWindowResized(ofResizeEventArgs &data);
    void onKeyPressed(ofKeyEventArgs &data);

    void setupGui2();
    void setupGui1();

    void setup();

    //blob tracker addon events
    void blobAdded(ofxBlob &_blob);
    void blobMoved(ofxBlob &_blob);
    void blobDeleted(ofxBlob &_blob);

    void enableBlobEventCallbacks();
    void disableBlobEventCallbacks();
    void drawGrid(float x, float y);
    void guiEvent(ofxUIEventArgs &e);
    void enableGuiEventCallbacks();
    void disableGuiEventCallbacks();
    void enableKeyEventCallbacks();
    void disableKeyEventCallbacks();

    void toggleVisible();
    bool isVisible();
    void saveSettings();
    void loadSettings();
private:

    bool ps3_bAutogain;
    bool ps3_bWhiteBalance;
    int ps3_gain;
    int ps3_brightness;
    int ps3_contrast;
    int ps3_redbalance;
    int ps3_bluebalance;
    int ps3_exposure;


    //gui
    vector<ofxUiCustomCanvas *> guis;
    map<string, ofxUiCustomCanvas *> guihash;
    bool guiVisible;

    ofxUiCustomCanvas *gui0;
    ofxUiCustomTextureViewer ps3_ui_texture;
    ofxUiCustomCvGrayScale ps3_ui_processed_img;

    ofxPS3EyeGrabber ps3eye;
    ofTexture ps3eye_texture;
    ofImage ps3eye_image;

    //color tracker module
    ColorTracker colorTracker;
    TrackerParam trackerParam;

    //built in blob tracker
    ofxCvContourFinder 	contourFinder;

    //blob tracker addon
    ofxBlobTracker blobTracker;

    //warper module
    ofxGLWarper warper;

    ofVec2f lastBlobPos;

    bool hide_calib;

    unsigned int ps3gain;
    unsigned int ps3brightness;

    ofPoint windowCenter;


};

#endif // CALIBRATION_H
