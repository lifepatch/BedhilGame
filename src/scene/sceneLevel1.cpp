//
//  sceneLevel1.cpp
//
//

#include "sceneLevel1.h"
//#include "FirstScene.h"

void sceneLevel1::setup(ofPtr<ofxScene> previousScene)
{
//    fbo.allocate(ofGetWidth(), ofGetHeight());
//    glitch.setup(&fbo);

    loadAssetToImg(&gmImgBossUfo,               "assets/element/boss_ufo.png");
    loadAssetToImg(&gmImgBackgroundLandscape,   "assets/game/landscape_combined.png");
    loadAssetToImg(&gmImgBackgroundAwan,        "assets/game/awan.png");
    loadAssetToImg(&gmImgTopTitle,              "assets/game/bedil_title.png");
    loadAssetToImg(&gmImgTugu,                   "assets/element/tugu.png");

    //loadBadBuildingAsset(0,     &gmImgJoglo,                 "assets/element/rumah.png");
    //loadBadBuildingAsset(1,     &gmImgPohon,                 "assets/element/pohon.png");

    loadBadBuildingAsset(0,     gmBadBuildingImgArr,       "assets/element/pabrik.png");
    loadBadBuildingAsset(1,     gmBadBuildingImgArr,       "assets/element/hotel.png");
    loadBadBuildingAsset(2,     gmBadBuildingImgArr,       "assets/element/crane.png");
    loadBadBuildingAsset(3,     gmBadBuildingImgArr,       "assets/element/baliho1.png");
    loadBadBuildingAsset(4,     gmBadBuildingImgArr,       "assets/element/mart24.png");
    loadBadBuildingAsset(5,     gmBadBuildingImgArr,       "assets/element/traktor.png");

    loadBadBuildingAsset(6,     gmBadBuildingImgArr,       "assets/element/hotel2.png");
    loadBadBuildingAsset(7,     gmBadBuildingImgArr,       "assets/element/hotel3.png");
    loadBadBuildingAsset(8,     gmBadBuildingImgArr,       "assets/element/hotel4.png");
    loadBadBuildingAsset(9,     gmBadBuildingImgArr,       "assets/element/traktor.png");



    loadGoodBuildingAsset(0, gmGoodBuildingImgArr,  "assets/element/rumah.png");
    loadGoodBuildingAsset(1, gmGoodBuildingImgArr,  "assets/element/pohon.png");


    gmSndExplode.loadSound("explode1.wav");
    gmSndLaser[0].loadSound("laser1.wav");
    gmSndLaser[1].loadSound("laser2.aiff");

    gmSndMusic[0].loadSound("bgmusic1.mp3");
    gmSndMusic[0].setLoop(true);

    gmSndMusic[1].loadSound("bgmusic2.mp3");
    gmSndMusic[1].setLoop(true);

    gmSndMusic[2].loadSound("bgmusic_mutant.mp3");
    gmSndMusic[2].setLoop(true);

    soundMutant = false;
    gmSndMusic[0].play();

    tmrBossFire.setup(0.8);
    tmrMutantMode.setup(120);
    tmrCutScene.setup(5);
    tmrMutantScene.setup(60);


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

    //gmSpriteRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 32);
    gmSpriteRenderer = new ofxSpriteSheetRenderer(100, 100,0, 128);

    gmSpriteRenderer->loadTexture("assets/game/explode.png", 256, GL_NEAREST);
    ofEnableAlphaBlending();


    preloadGoodBuilding();


    state = PLAYING;

}

void sceneLevel1::loadAssetToImg(ofImage* _img, string _fileName)
{
    _img->loadImage(_fileName);
    _img->getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
}

void sceneLevel1::loadBadBuildingAsset(int id, ofImage * _img, string _fileName )
{
    loadAssetToImg(&_img[id], _fileName);
    gmBadBuildingAssetDef[id].img = &_img[id];
    gmBadBuildingAssetDef[id].name = "";
}


void sceneLevel1::loadGoodBuildingAsset(int id, ofImage * _img, string _fileName )
{
    loadAssetToImg(&_img[id], _fileName);
    gmGoodBuildingAssetDef[id].img = &_img[id];
    gmGoodBuildingAssetDef[id].name = "";
}



void sceneLevel1::updateSprites()
{
    gmSpriteRenderer->clear();
    gmSpriteRenderer->update(ofGetElapsedTimeMillis());
    if(gmSprites.size()>0) // if we have sprites
        {
            for(int i=gmSprites.size()-1; i>=0; i--) //go through them
                {
                    if(gmSprites[i]->animation.frame >= 15) //if they are past the bottom of the screen
                        {
                            delete gmSprites[i]; //delete them
                            gmSprites.erase(gmSprites.begin()+i); // remove them from the vector
                        }
                    else
                        {
                            gmSpriteRenderer->addCenteredTile(&gmSprites[i]->animation, gmSprites[i]->pos.x, gmSprites[i]->pos.y); // add them to the sprite renderer (add their animation at their position, there are a lot more options for what could happen here, scale, tint, rotation, etc, but the animation, x and y are the only variables that are required)
                        }
                }
        }
}


void sceneLevel1::preloadGoodBuilding()
{



    int max = 100;

    for (int i = 0; i < ofGetWidth(); i+=100)
        {
            //printf("%i", i);
            if (ofRandom(10) > 2)
                {
                    int id = (int) ofRandom(0, GM_GOOD_ASSET_COUNT);

                    Obj2D * new_good_building  = new Obj2D();

                    new_good_building->setup(gmGoodBuildingAssetDef[id].img);
                    float dest_y =  landscape_line.getPointAtLength(i).y  - (new_good_building->height/1);
                    new_good_building->setPosition(i, dest_y);
                    gmVectorGoodBuildings.push_back(new_good_building);
                }

        }





}


void sceneLevel1::updateBossFire()
{
    if (tmrBossFire.tick())
        {

            float rnd = ofRandom(0.6);
            // printf("rnd %f\n", rnd);
            Obj2D * new_bad_building  = new Obj2D();

            int id = (int) ofRandom(0, GM_BAD_ASSET_COUNT);


            new_bad_building->setup(gmBadBuildingAssetDef[id].img);

            ofPoint ufo_center = ufo.getCenter();

            float dest_y =  landscape_line.getPointAtLength(ufo_center.x).y  - (new_bad_building->height/2);

            //new_joglo->setFromCenter(ufo_center_x, dest_y, new_joglo->width, new_joglo->height);

            new_bad_building->setFromCenter(ufo_center.x, ufo_center.y+70, new_bad_building->width, new_bad_building->height);
            new_bad_building->setDestination(dest_y + new_bad_building->height/2 + (ofRandom(0.5)));

            new_bad_building->speed.y = ofRandom(100.0, 200.0);
            new_bad_building->speed.x = ufo.getSpeed() * 5;


            new_bad_building->speed.y = new_bad_building->speed.y - 500;


            gmVectorBadBuildings.push_back(new_bad_building);

            tmrBossFire.setInterval(ofRandom(0.2,1.5));

            if (ofRandom(0,2) > 1)
                gmSndLaser[0].play();
            else
                gmSndLaser[1].play();
        }
}



void sceneLevel1::updateBossFireMutant()
{
    if (tmrBossFire.tick())
        {

            float rnd = ofRandom(0.6);
            // printf("rnd %f\n", rnd);
            Obj2D * new_bad_building  = new Obj2D();

            int id = (int) ofRandom(0, GM_BAD_ASSET_COUNT);


            new_bad_building->setup(gmBadBuildingAssetDef[id].img);

            ofPoint ufo_center = ufo.getCenter();

            float dest_y =  landscape_line.getPointAtLength(ufo_center.x).y  - (new_bad_building->height/2);

            //new_joglo->setFromCenter(ufo_center_x, dest_y, new_joglo->width, new_joglo->height);

            new_bad_building->setFromCenter(ufo_center.x, ufo_center.y+70, new_bad_building->width, new_bad_building->height);
            new_bad_building->setDestination(dest_y + new_bad_building->height/2 + (ofRandom(0.5)));

            new_bad_building->speed.y = ofRandom(100.0, 200.0);
            new_bad_building->speed.x = ufo.getSpeed() * 5;


            new_bad_building->speed.y = new_bad_building->speed.y - 10;


            gmVectorBadBuildings.push_back(new_bad_building);

            tmrBossFire.setInterval(ofRandom(0.1,0.3));

            if (ofRandom(0,2) > 1)
                gmSndLaser[0].play();
            else
                gmSndLaser[1].play();
        }
}

void sceneLevel1::updateBadBuildings()
{

    // delete and erase with a loop
    vector<Obj2D *>::iterator it = gmVectorBadBuildings.begin();
    for(; it != gmVectorBadBuildings.end();)
        {
            if( (*it)->isDead() )
                {
                    delete *it;
                    it = gmVectorBadBuildings.erase(it);
                }
            else if ( (*it)->isGrounded() )
                {
                    gmVectorGroundBuildings.push_back(*it);
                    it = gmVectorBadBuildings.erase(it);
                }
            else
                ++it;
        }


    for(int i = 0; i < gmVectorBadBuildings.size(); i++)
        {
            gmVectorBadBuildings.at(i)->addGravity(40);
            gmVectorBadBuildings.at(i)->update(0.033333);
        }

    //ofRemove(gmVectorBadBuildings, checkDead);
}

void sceneLevel1::update()
{


    switch (state)
        {
        case PLAYING:
                if (tmrMutantMode.tick())
                {
                    state = CUTSCENE;            //update sprites
                    tmrCutScene.resync();
                }
                updateSprites();
                //update boss position
                ufo.update();
                //UFO FIRE : TRUE when ready to fire
                updateBossFire();
                //bad building drops from skies
                updateBadBuildings();
            break;
        case CUTSCENE:
                if (tmrCutScene.tick())
                {
                    state = MUTANT;
                    tmrMutantScene.resync();
                }
            break;
        case MUTANT:


                if (soundMutant == false)
                {
                    gmSndMusic[0].stop();
                    gmSndMusic[2].play();
                    soundMutant = true;
                }

                if (tmrMutantScene.tick()) this->exitScene();
                //update sprites
                updateSprites();
                //update boss position
                ufo.updateMutant();
                //UFO FIRE : TRUE when ready to fire
                updateBossFireMutant();
                //bad building drops from skies
                updateBadBuildings();
            break;
         default:
            break;
        }




}


bool sceneLevel1::checkDead(Obj2D *p )
{
    return p->isDead();
}


void sceneLevel1::drawBadBuildings()
{
    for(int i = 0; i < gmVectorBadBuildings.size(); i++)
        {
            gmVectorBadBuildings.at(i)->draw();
        }
}

void sceneLevel1::drawGroundedBuildings()
{
    for(int i = 0; i < gmVectorGroundBuildings.size(); i++)
        {
            gmVectorGroundBuildings.at(i)->draw();
        }
}

void sceneLevel1::drawGoodBuildings()
{
    for(int i = 0; i < gmVectorGoodBuildings.size(); i++)
        {
            gmVectorGoodBuildings.at(i)->draw();
        }
}

void sceneLevel1::draw()
{

//    fbo.begin();
    ofClear(0,0,0,255);
    ofBackground(0,0,0);
    ofSetColor(255);
    if (state == PLAYING)
        {

            gmImgTopTitle.draw(0,30);
            ofRect(76.1,30+32, tmrMutantMode.progress() *152 , 10 );
            gmImgBackgroundLandscape.draw(0,ofGetHeight()-gmImgBackgroundLandscape.height);
            gmImgBackgroundAwan.draw(689,387);
            gmImgBackgroundAwan.draw(-134,447);
            ufo.draw();
            drawGoodBuildings();
            gmImgTugu.draw(447,727-97);
            drawGroundedBuildings();
            drawBadBuildings();
            gmSpriteRenderer->draw();
        }
    else if (state == CUTSCENE)
        {
            //gmImgCutscene.draw(0,0);
           ufo.imgBossUfoMutant.draw(400,314);
           // ofCircle(ofGetWidth()/2, ofGetHeight()/2, 20 - (tmrCutScene.progress()*20));

        }
    else if (state == MUTANT)
        {
            //ofClear(0,0,0,255);
            //ofBackground(0,0,0);
            gmImgTopTitle.draw(0,30);
            gmImgBackgroundLandscape.draw(0,ofGetHeight()-gmImgBackgroundLandscape.height);
            gmImgBackgroundAwan.draw(689,387);
            gmImgBackgroundAwan.draw(-134,447);
            ufo.drawMutant();
            drawGoodBuildings();
            gmImgTugu.draw(447,727-97);
            drawGroundedBuildings();
            drawBadBuildings();
            gmSpriteRenderer->draw();
//            glitch.setFx(OFXPOSTGLITCH_CONVERGENCE, true);
//            glitch.setFx(OFXPOSTGLITCH_SWELL, true);

//            glitch.generateFx();
        }

//    fbo.end();

//    ofSetColor(255);
//    fbo.draw(0,0);

}

void sceneLevel1::mousePressed(int x, int y, int button)
{

    for (std::vector< Obj2D * >::iterator _badBuilding = gmVectorBadBuildings.begin() ; _badBuilding != gmVectorBadBuildings.end(); ++_badBuilding)
        {
            if (  (*_badBuilding)->inside(x,y) )
                {
                    (*_badBuilding)->setDead(true);

                    for(int j = 0; j < 4; j++)
                        {
                            basicSprite * newSprite = new basicSprite(); // create a new sprite
                            newSprite->pos.x = x + ofRandom(-30,30);
                            newSprite->pos.y = y + ofRandom(-70,70);
                            newSprite->speed = ofRandom(1,1); //set its speed
                            newSprite->animation = explodeAnim; //set its animation to the walk animation we declared

                            gmSprites.push_back(newSprite);
                        }


                    printf("inside\n");
                    gmSndExplode.play();

                }
        }



}


void sceneLevel1::willDraw()
{
    state = PLAYING;
    tmrMutantMode.resync();

    ofSeedRandom();
    preloadGoodBuilding();
}

void sceneLevel1::clearAllBuildings()
{
    for (std::vector< Obj2D * >::iterator _badBuilding = gmVectorBadBuildings.begin() ; _badBuilding != gmVectorBadBuildings.end(); ++_badBuilding)
        {
            delete (*_badBuilding);
        }


    for (std::vector< Obj2D * >::iterator _groundedBuilding = gmVectorGroundBuildings.begin() ; _groundedBuilding != gmVectorGroundBuildings.end(); ++_groundedBuilding)
        {
            delete (*_groundedBuilding);
        }


    for (std::vector< Obj2D * >::iterator _goodBuilding = gmVectorGoodBuildings.begin() ; _goodBuilding != gmVectorGoodBuildings.end(); ++_goodBuilding)
        {
            delete (*_goodBuilding);
        }

    gmVectorGroundBuildings.clear();
    gmVectorBadBuildings.clear();
    gmVectorGoodBuildings.clear();

}

void sceneLevel1::willExit()
{

    clearAllBuildings();

    gmSndMusic[0].stop();
    gmSndMusic[1].stop();
    gmSndMusic[2].stop();

}
