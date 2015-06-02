#include "colortracker.h"

void ColorTracker::setParam(const TrackerParam *param)
{
    imgParam.tHue = param->tHue;
    imgParam.tHueThresh = param->tHueThresh;
    imgParam.tSat = param->tSat;
    imgParam.tValue = param->tValue;
}

void ColorTracker::setParam(float hue, float hueThresh, float sat, float value)
{
    imgParam.tHue = hue;
    imgParam.tHueThresh = hueThresh;
    imgParam.tSat = sat;
    imgParam.tValue = value;
}

void ColorTracker::processHSV(ofxCvColorImage *source, float hue, float hueThresh, float sat, float value)
{
    //http://forum.openframeworks.cc/t/coloured-blob-detection/151/11
    int sourceWidth = source->width, sourceHeight = source->height;

    ofxCvColorImage hsvFrame;
    ofxCvGrayscaleImage hsvBlob;

    hsvBlob.allocate(source->width, source->height);
    hsvFrame.allocate(source->width, source->height);

    hsvFrame = *source;
    hsvFrame.convertRgbToHsv();

    int totalPixels = sourceWidth*sourceHeight*3;

    unsigned char * pix = hsvFrame.getPixels();
    unsigned char * pre = new unsigned char[sourceWidth*sourceHeight*3];

    //set these values your self
    float h       = hue     * 255;
    float ht      = hueThresh * 255;
    float s       = sat       * 255;
    float v       = value    * 255;

    //here we figure out what is the max allowed hue
    //and the minimum allowed hue. because hue is
    //continious we have to make sure we handle what happens
    //if hueMax goes over 255
    //or hueMin goes less than 0

    float hueMax   = h + ht*0.5;
    float hueMin   = h - ht*0.5;

    int k = 0;

    for(int i = 0; i < totalPixels-3; i+=3)
    {

        float pixHue = pix[i];

        if( pix[i+1] >= s  && pix[i+2] >= v)
        {

            //we do this to check the cases when the
            //hue min could have wrapped
            //or the hue max could have wrapped
            //also if saturation is zero
            //then hue doesn't matter hence (s == 0)
            if( (s == 0) || (pixHue >= hueMin && pixHue <= hueMax) ||
                    (pixHue -255 >= hueMin && pixHue -255 <= hueMax) ||
                    (pixHue +255 >= hueMin && pixHue +255 <= hueMax) )
            {

                //we have a white pixel
                pre[k] = 255;
            }
            else pre[k] = 0;
        }
        else pre[k] = 0;
        k++;
    }

    hsvBlob.setFromPixels(pre, sourceWidth, sourceHeight);

    free(pre);

    //processedImg.allocate(source->width, source->height);

    processedImg = hsvBlob;
}

void ColorTracker::processVidGrabber(ofVideoGrabber *webcam)
{
    ofxCvColorImage sourceImg;
    sourceImg.allocate(webcam->width, webcam->height);
    sourceImg.setFromPixels(webcam->getPixels(), webcam->width, webcam->height);
    processHSV(&sourceImg, imgParam.tHue, imgParam.tHueThresh, imgParam.tSat, imgParam.tValue);
}


void ColorTracker::processVidGrabber(ofPixels &_pix)
{
    ofxCvColorImage sourceImg;

    int imgWidth =  _pix.getWidth(); //webcam->getWidth();
    int imgHeight = _pix.getHeight();// webcam->getHeight();

    sourceImg.allocate(imgWidth, imgHeight);

    int channel_dst  = sourceImg.getPixelsRef().getBytesPerPixel();
    int channel_src  = _pix.getBytesPerPixel();


    unsigned char * pix =  _pix.getPixels();


//    //source image
    unsigned char * pix_dst = sourceImg.getPixelsRef().getPixels();

    for (int x = 0 ; x < imgWidth; x++)
    {
        for (int y = 0 ; y < imgHeight; y++)
        {
            int arrpos_src = (y*channel_src*imgWidth) + x*channel_src;
            int arrpos_dst = (y*channel_dst*imgWidth) + x*channel_dst;

            pix_dst[arrpos_dst]   =  pix[arrpos_src+0];
            pix_dst[arrpos_dst+1] =  pix[arrpos_src+1];
            pix_dst[arrpos_dst+2] =  pix[arrpos_src+2];
        }
    }

    //sourceImg.allocate(webcam->getWidth(), webcam->getHeight());
    //sourceImg.setFromPixels(webcam->getPixels(), webcam->getWidth(), webcam->getHeight());



    processHSV(&sourceImg, imgParam.tHue, imgParam.tHueThresh, imgParam.tSat, imgParam.tValue);
}


void ColorTracker::processVidGrabber(ofxPS3EyeGrabber *webcam)
{
    ofxCvColorImage sourceImg;

    int imgWidth = webcam->getWidth();
    int imgHeight = webcam->getHeight();

    sourceImg.allocate(imgWidth, imgHeight);

    int channel_dst  = sourceImg.getPixelsRef().getBytesPerPixel();
    int channel_src  = webcam->getPixelsRef().getBytesPerPixel();


    unsigned char * pix = webcam->getPixelsRef().getPixels();


//    //source image
    unsigned char * pix_dst = sourceImg.getPixelsRef().getPixels();

    for (int x = 0 ; x < imgWidth; x++)
    {
        for (int y = 0 ; y < imgHeight; y++)
        {
            int arrpos_src = (y*channel_src*imgWidth) + x*channel_src;
            int arrpos_dst = (y*channel_dst*imgWidth) + x*channel_dst;

            pix_dst[arrpos_dst]   =  pix[arrpos_src+0];
            pix_dst[arrpos_dst+1] =  pix[arrpos_src+1];
            pix_dst[arrpos_dst+2] =  pix[arrpos_src+2];
        }
    }

    //sourceImg.allocate(webcam->getWidth(), webcam->getHeight());
    //sourceImg.setFromPixels(webcam->getPixels(), webcam->getWidth(), webcam->getHeight());



    processHSV(&sourceImg, imgParam.tHue, imgParam.tHueThresh, imgParam.tSat, imgParam.tValue);
}


