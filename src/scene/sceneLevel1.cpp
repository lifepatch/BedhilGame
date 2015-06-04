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

    ufo.update();

    //printf("scene1 uodate\n");
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

        ofSeedRandom();

        float ufo_center_x = ufo.getCenter().x;
        float ufo_center_y = ufo.getCenter().y;

        float dest_y =  landscape_line.getPointAtLength(ufo_center_x).y  - (new_joglo.height/2);

        //new_joglo.setFromCenter(ufo_center_x, dest_y, new_joglo.width, new_joglo.height);

        new_joglo.setFromCenter(ufo_center_x, ufo_center_y+40, new_joglo.width, new_joglo.height);
        new_joglo.setDestination(dest_y + new_joglo.height/2 + (ofRandom(2)));

        new_joglo.speed.y = ofRandom(100.0, 200.0);

        gmVectorBuildings.push_back(new_joglo);

        tmrBossFire.setInterval(ofRandom(0.2,1.5));
    }


    for(int i = 0; i < gmVectorBuildings.size(); i++)
        {
            gmVectorBuildings.at(i).update(0.033333);
        }


}

void sceneLevel1::draw()
{

    ofBackground(0,0,0);

    gmImgTopTitle.draw(0,10);
    gmImgBackgroundLandscape.draw(0,ofGetHeight()-gmImgBackgroundLandscape.height);


    ufo.draw();


    for(int i = 0; i < gmVectorBuildings.size(); i++)
        {
            gmVectorBuildings.at(i).draw();
        }


    ofCircle( ufo.getCenter().x,  landscape_line.getPointAtLength( ufo.getCenter().x).y  + 4     ,10.0);


}

void sceneLevel1::mousePressed(int x, int y, int button)
{


}

void sceneLevel1::willExit()
{
    printf("exit\n");
    gmVectorBuildings.clear();
}
