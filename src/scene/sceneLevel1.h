#ifndef SCENELEVEL1_H
#define SCENELEVEL1_H

//
//  oFxSceneManager Scene Template
//
//

#include "ofMain.h"
#include "ofxScene.h"
#include "ofxSpriteSheetRenderer.h"

#include "ofxtiming.h"

#include "Obj2D.h"

#include "joglo.h"
#include "traktor.h"
#include "ufo_boss.h"


#define GM_BAD_ASSET_COUNT 10

#define GM_PABRIK_ID 0
#define GM_HOTEL_ID 1
#define GM_CRANE_ID 2
#define GM_BALIHO_ID 3
#define GM_MART24_ID 4
#define GM_TRAKTOR_ID 5


//create a new animation. This could be done optinally in your code andnot as a static, just by saying animation_t walkAnimation; walkAnimation.index =0, walkAnimation.frame=0 etc. I find this method the easiest though
static animation_t explodeAnim =
{	0,	/* .index			(int) - this is the index of the first animation frame. indicies start at 0 and go left to right, top to bottom by tileWidth on the spriteSheet		*/
    0,	/* .frame			(int) - this is the current frame. It's an internal variable and should always be set to 0 at init													*/
    16,	/* .totalframes		(int) - the animation length in frames																												*/
    1,	/* .width			(int) - the width of each animation frame in tiles																									*/
    1,	/* .height			(int) - the height of each animation frame in tiles																									*/
    100,	/* .frameduration	(unsigned int) - how many milliseconds each frame should be on screen. Less = faster																*/
    0,	/* .nexttick		(unsigned int) - the next time the frame should change. based on frame duration. This is an internal variable and should always be set to 0 at init	*/
    1,	/* .loops			(int) - the number of loops to run. -1 equals infinite. This can be adjusted at runtime to pause animations, etc.									*/
    -1,	/* .finalindex		(int) - the index of the final tile to draw when the animation finishes. -1 is the default so total_frames-1 will be the last frame.				*/
    1	/* .frameskip		(int) - the incrementation of each frame. 1 should be set by default. If you wanted the animation to play backwards you could set this to -1, etc.	*/
};
//a quick and dirty sprite implementation
struct basicSprite {
    animation_t animation;	// a variable to store the animation this sprite uses
    ofPoint pos;			// the position on the screen this sprite will be drawn at
    float speed;			// the speed at which this sprite moves down the screen
};

struct gmAssetDef
{
    string name;
    ofImage * img;
};


class sceneLevel1 : public ofxScene {
public:

    enum gameState{PLAYING, START_SCREEN, END_LEVEL};

    void setup(ofPtr<ofxScene> pPreviousScene);
    void update();
    void draw();


    //void keyPressed(int key) {}
    //void keyReleased(int key) {}
    //void mouseMoved(int x, int y) {}
    //void mouseDragged(int x, int y, int button) {}
    void mousePressed(int x, int y, int button);
    //void mouseReleased(int x, int y, int button) {}
    //void windowResized(int w, int h) {}
    //void dragEvent(ofDragInfo dragInfo) {}
    //void gotMessage(ofMessage msg) {}

//    virtual void willFadeIn() {}
    virtual void willDraw();
//    virtual void willFadeOut() {}
    void willExit();

    static bool checkDead(Obj2D *p);
    void updateSprites();

    void updateBossFire();
    void updateBadBuildings();
    void drawBadBuildings();
    void drawGroundedBuildings();
    void clearAllBuildings();
    void loadBadBuildingAsset(int id, ofImage *_img, string _fileName);
    void loadAssetToImg(ofImage* _img, string _fileName);
private:
    //state
    gameState state;

    //game assets
    ofImage gmImgTopTitle;
    ofImage gmImgBackgroundLandscape;
    ofImage gmImgBackgroundLandscapeFar;
    ofImage gmImgBackgroundAwan;

    //game element
    ofImage gmImgBossUfo;
    ofImage gmImgJoglo;
    ofImage gmImgPohon;
    ofImage gmImgPabrik;
    ofImage gmImgCrane;
    ofImage gmImgHotel;
    ofImage gmImgBaliho;
    ofImage gmImgMart24;
    ofImage gmImgTraktor;

    gmAssetDef gmBadBuildingAssetDef[GM_BAD_ASSET_COUNT];
    ofImage gmBadBuildingImgArr[GM_BAD_ASSET_COUNT];


    gmTraktor traktor1;

    ofxTiming tmrBossFire;
    gmUfoBoss ufo;


    ofSoundPlayer gmSndExplode;
    ofSoundPlayer gmSndLaser[2];
    ofSoundPlayer gmSndMusic[2];

    ofxSpriteSheetRenderer * gmSpriteRenderer;
    vector <basicSprite *>  gmSprites;

    //landscape target for boss
    vector <Obj2D *> gmVectorBadBuildings;
    vector <Obj2D *> gmVectorGroundBuildings;

    vector <ofPoint> landscape_border;
    ofPolyline landscape_line;


    void addBadBuilding()
    {

    }
};

#endif // SCENELEVEL1_H
