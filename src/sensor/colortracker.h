#ifndef COLORTRACKER_H
#define COLORTRACKER_H

#include "ofMain.h"
#include "ofxOpenCv.h"

#include "ofxPS3EyeGrabber.h"

struct TrackerParam{
    float tHue;
    float tHueThresh;
    float tSat;
    float tValue;
};

class ColorTracker
{
public:

    TrackerParam imgParam;

    ofxCvGrayscaleImage processedImg;

    void setParam(const TrackerParam * param);
    void setParam(float hue, float hueThresh, float sat, float value);
    void processHSV(ofxCvColorImage *source, float hue, float hueThresh, float sat, float value);
    void processVidGrabber(ofVideoGrabber * webcam);
    void processVidGrabber(ofxPS3EyeGrabber * webcam);

    void processVidGrabber(ofPixels &_pix);
};

#endif // COLORTRACKER_H
