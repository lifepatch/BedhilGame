//
//  sceneLevel1.cpp
//
//

#include "sceneLevel1.h"
//#include "FirstScene.h"

void sceneLevel1::setup(ofPtr<ofxScene> previousScene)
{
    //FirstScene* scene = dynamic_cast<FirstScene *>(previousScene.get());
    //y = scene->y;
    gmImgBossUfo.loadImage("assets/element/boss_ufo.png");
    gmImgBossUfo.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

    gmImgBackgroundLandscape.loadImage("assets/game/landscape_combined.png");
    gmImgBackgroundLandscape.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

    gmImgBackgroundAwan.loadImage("assets/game/awan.png");
    gmImgBackgroundAwan.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

    gmImgTopTitle.loadImage("assets/game/bedil_title.png");
    gmImgBossUfo.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

    gmImgJoglo.loadImage("assets/element/rumah.png");
    gmImgJoglo.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

    gmImgPohon.loadImage("assets/element/pohon.png");
    gmImgPohon.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

    gmImgPabrik.loadImage("assets/element/pabrik.png");
    gmImgPabrik.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

    gmImgHotel.loadImage("assets/element/hotel.png");
    gmImgHotel.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

    gmImgCrane.loadImage("assets/element/crane.png");
    gmImgCrane.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

    gmImgBaliho.loadImage("assets/element/baliho1.png");
    gmImgBaliho.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

    gmImgMart24.loadImage("assets/element/mart24.png");
    gmImgMart24.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

    gmImgTraktor.loadImage("assets/element/traktor.png");
    gmImgTraktor.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);


    gmSndExplode.loadSound("explode1.wav");
    gmSndLaser[0].loadSound("laser1.wav");
    gmSndLaser[1].loadSound("laser2.aiff");

    gmSndMusic[0].loadSound("bgmusic1.mp3");
    gmSndMusic[0].setLoop(true);

    gmSndMusic[1].loadSound("bgmusic2.mp3");
    gmSndMusic[1].setLoop(true);

    gmSndMusic[0].play();

    tmrBossFire.setup(0.8);


    landscape_border.push_back(ofPoint(0,18));
    landscape_border.push_back(ofPoint(39,4));
    landscape_border.push_back(ofPoint(106,6));
    landscape_border.push_back(ofPoint(222,26));
    landscape_border.push_back(ofPoint(359,27));
    landscape_border.push_back(ofPoint(419,2));
    landscape_border.push_back(ofPoint(487,1));
    landscape_border.push_back(ofPoint(585,18));
    landscape_border.push_back(ofPoint(804,12));
    landscape_border.push_back(ofPoint(843,21));
    landscape_border.push_back(ofPoint(977,23));
    landscape_border.push_back(ofPoint(1023,7));

    for(int i = 0; i < landscape_border.size(); i++)
        {
            landscape_border.at(i).y = landscape_border.at(i).y + ofGetHeight() - 41;
            landscape_line.addVertex(landscape_border.at(i));
        }


}

void sceneLevel1::update()
{

    if (state == PLAYING)
        {

            ufo.update();

            //UFO FIRE : TRUE when ready to fire
            if (tmrBossFire.tick())
                {

                    float rnd = ofRandom(0.6);
                    // printf("rnd %f\n", rnd);
                    gmJoglo new_joglo;

                    if (rnd > 0.55)
                        {
                            new_joglo.setup(&gmImgCrane);
                        }
                    else if (rnd > 0.4)
                        {
                            new_joglo.setup(&gmImgPabrik);
                        }
                    else if (rnd > 0.3)
                        {
                            new_joglo.setup(&gmImgTraktor);

                        }
                    else if (rnd > 0.2)
                        {
                            new_joglo.setup(&gmImgHotel);

                        }
                    else if (rnd > 0.1)
                        {
                            new_joglo.setup(&gmImgMart24);
                        }
                    else
                        {
                            new_joglo.setup(&gmImgBaliho);
                        }


                    ofPoint ufo_center = ufo.getCenter();

                    float dest_y =  landscape_line.getPointAtLength(ufo_center.x).y  - (new_joglo.height/2);

                    //new_joglo.setFromCenter(ufo_center_x, dest_y, new_joglo.width, new_joglo.height);

                    new_joglo.setFromCenter(ufo_center.x, ufo_center.y+70, new_joglo.width, new_joglo.height);
                    new_joglo.setDestination(dest_y + new_joglo.height/2 + (ofRandom(2)));

                    new_joglo.speed.y = ofRandom(100.0, 200.0);
                    new_joglo.speed.x = ufo.getSpeed() * 5;


                    new_joglo.speed.y = new_joglo.speed.y - 500;


                    gmVectorBuildings.push_back(new_joglo);

                    tmrBossFire.setInterval(ofRandom(0.2,1.5));

                    if (ofRandom(0,2) > 1)
                        gmSndLaser[0].play();
                    else
                        gmSndLaser[1].play();
                }


            for(int i = 0; i < gmVectorBuildings.size(); i++)
                {
                    gmVectorBuildings.at(i).addGravity(40);
                    gmVectorBuildings.at(i).update(0.033333);
                }
        }



}

void sceneLevel1::draw()
{

    ofBackground(0,0,0);


    if (state == PLAYING)
        {

            gmImgTopTitle.draw(0,10+40);
            gmImgBackgroundLandscape.draw(0,ofGetHeight()-gmImgBackgroundLandscape.height);

            gmImgBackgroundAwan.draw(689,387);
            gmImgBackgroundAwan.draw(-134,447);


            ufo.draw();


            for(int i = 0; i < gmVectorBuildings.size(); i++)
                {
                    gmVectorBuildings.at(i).draw();
                }


            ofCircle( ufo.getCenter().x,  landscape_line.getPointAtLength( ufo.getCenter().x).y  + 4     ,10.0);


        }

}

void sceneLevel1::mousePressed(int x, int y, int button)
{
    printf("wew\n");
    for(int i = 0; i < gmVectorBuildings.size(); i++)
        {
            if (gmVectorBuildings.at(i).inside(x,y))
            {
                 printf("inside\n");
                gmSndExplode.play();
            }
        }
}

void sceneLevel1::willDraw()
{
    state = PLAYING;

    ofSeedRandom();

}

void sceneLevel1::willExit()
{
    printf("exit\n");
    gmVectorBuildings.clear();
    gmSndMusic[0].stop();
    gmSndMusic[1].stop();

}
