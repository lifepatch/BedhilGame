#ifndef SCENEINTRO_H
#define SCENEINTRO_H


//
//  oFxSceneManager Scene Template
//
//

#include "ofxScene.h"
#include "ofxtiming.h"

class sceneGeneric : public ofxScene {
        public:
    sceneGeneric()
    {
        autoEnd = false;
    }

    sceneGeneric(float sec)
    {
        autoEnd = true;
        tmrEnd.setInterval(sec);
    }
        void setup(ofPtr<ofxScene> pPreviousScene)
        {

        }

        void setImg(ofImage *_img)
        {
            gmImg = _img;
        }

void willDraw()
{
    tmrEnd.resync();
}

void update()
{
    if (autoEnd){
        if (tmrEnd.tick()) exitScene();
    }
}

void draw()
{
    gmImg->draw(0,0);

    if(autoEnd)
    {
        ofRect(40,40,100 - (tmrEnd.progress()*100) , 15);
    }
}

void mousePressed(int x, int y, int button)
{
    if (!autoEnd)
    exitScene();
}

bool autoEnd;

ofImage * gmImg;
ofxTiming tmrEnd;

};


#endif // SCENEINTRO_H

