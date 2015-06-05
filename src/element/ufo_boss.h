#ifndef UFO_BOSS
#define UFO_BOSS

#include "Obj2D.h"
#include "ofxtiming.h"

class gmUfoBoss : public Obj2D
{
public:

    gmUfoBoss()
    {
        imgBossUfo.loadImage("assets/element/boss_ufo.png");
        imgBossUfo.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

        width = imgBossUfo.width;
        height = imgBossUfo.height;

        halfWidth = width/2;
        halfHeight = height/2;

        ofLoadImage(imgRocket[0], "assets/element/boss_ufo_roket1.png");
        ofLoadImage(imgRocket[1], "assets/element/boss_ufo_roket2.png");

        texRocket[0].loadData(imgRocket[0]);
        texRocket[1].loadData(imgRocket[1]);


        tmrRocket.setup(0.2);
        prevX = 0;



    }

    void update()
    {

        float deaccel = 5;
        float ufo_x = ofMap( sin(TWO_PI * ofGetElapsedTimef() * 1/deaccel ), -1,1,50,ofGetWidth()-50) - halfWidth;
        float tracker_x = ufo_x + halfWidth;

        position.x = ufo_x;
        position.y =  (ofNoise(ofGetElapsedTimef()*1.5) * 200) -80;

        rot  = position.x - prevX;

    }


    void draw()
    {
        ofPushMatrix();
        ofTranslate(position.x + halfWidth, position.y + halfHeight);
            ofPushMatrix();
            if(position.x > prevX)
                {
                    glRotatef(2*rot,0,0,1);
                }
            else
                {
                    glRotatef(2*rot,0,0,1);
                }

            imgBossUfo.draw(- halfWidth, - halfHeight);


            if(tmrRocket.tick())
                {
                    texRocket[0].draw(-53.5, 52);
                }
            else
                {
                    texRocket[1].draw(-53.5, 52);
                }

            ofPopMatrix();
        ofPopMatrix();

        prevX = position.x;



    }


    float getSpeed()
    {
        return rot;
    }


private:
    ofImage imgBossUfo;
    ofPixels imgRocket[2];
    ofTexture texRocket[2];
    ofxTiming tmrRocket;
    float prevX;
    float rot;

    float halfWidth;
    float halfHeight;

};

#endif // UFO_BOSS

