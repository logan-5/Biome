#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SceneryLayer.hpp"
#include "TerrainLayer.hpp"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    /**  you can create scene with following comment code instead of using csb file.
     // 1. super init first
     if ( !Layer::init() )
     {
     return false;
     }
     
     Size visibleSize = Director::getInstance()->getVisibleSize();
     Vec2 origin = Director::getInstance()->getVisibleOrigin();
     
     /////////////////////////////
     // 2. add a menu item with "X" image, which is clicked to quit the program
     //    you may modify it.
     
     // add a "close" icon to exit the progress. it's an autorelease object
     auto closeItem = MenuItemImage::create(
     "CloseNormal.png",
     "CloseSelected.png",
     CC_CALLBACK_1(MainScene::menuCloseCallback, this));
     
     closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
     origin.y + closeItem->getContentSize().height/2));
     
     // create menu, it's an autorelease object
     auto menu = Menu::create(closeItem, NULL);
     menu->setPosition(Vec2::ZERO);
     this->addChild(menu, 1);
     
     /////////////////////////////
     // 3. add your codes below...
     
     // add a label shows "Hello World"
     // create and initialize a label
     
     auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
     
     // position the label on the center of the screen
     label->setPosition(Vec2(origin.x + visibleSize.width/2,
     origin.y + visibleSize.height - label->getContentSize().height));
     
     // add the label as a child to this layer
     this->addChild(label, 1);
     
     // add "MainScene" splash screen"
     auto sprite = Sprite::create("MainScene.png");
     
     // position the sprite on the center of the screen
     sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
     
     // add the sprite as a child to this layer
     this->addChild(sprite, 0);
     **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    cocos2d::Size screenSize = Director::getInstance()->getVisibleSize();
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    
    TerrainLayer* t = TerrainLayer::create();
    t->setContentSize( cocos2d::Size( screenSize.width, screenSize.height/2.f ) );
    rootNode->addChild(t);
    this->terrainLayers.pushBack( t );
    
    SceneryLayer* test = SceneryLayer::create();
    test->initTerrainLayer( t );
    this->sceneryLayers.pushBack( test );
    test->setScene( this );
    test->initSizeX( screenSize.width );
    test->initNumberOfNodes( 5 );
    test->setDensity( 1);//0.6 );
    test->setSpriteScaleVar( 0.1f );
    rootNode->addChild( test );
    
    t = TerrainLayer::create();
    rootNode->addChild(t);
    this->terrainLayers.pushBack( t );
    SceneryLayer* test2 = SceneryLayer::create();
    test2->initTerrainLayer( t );
    this->sceneryLayers.pushBack( test2 );
    test2->setScene( this );
    test2->initSizeX( screenSize.width );
    test2->initNumberOfNodes( 6 );
    test2->initDistanceFactor( .4f );
    test2->setSpriteScale( 0.75f );
    test2->setSpriteScaleVar( 0.1f );
    test2->setDensity( 1);//0.75 );
    rootNode->addChild( test2 );
    
    this->setUpSceneryZOrders();
    
    addChild(rootNode);
    
    this->scheduleUpdate();
    
    biomeManager = std::unique_ptr<BiomeManager>( new BiomeManager );
    
    background = LayerColor::create( Color4B(biomeManager->getCurrentFogInfo().color), screenSize.width, screenSize.height );
    this->addChild( background );
    background->setLocalZOrder( std::numeric_limits<int>::min() );
    
    return true;
}

bool sortScenery(SceneryLayer* one, SceneryLayer* two) {
    return one->getDistanceFactor() > two->getDistanceFactor();
}

void MainScene::setUpSceneryZOrders() {
    std::sort( this->sceneryLayers.begin(), this->sceneryLayers.end(), sortScenery);
    int zs = (int) -(this->sceneryLayers.size() / 2);
    for ( int i = 0; i < this->sceneryLayers.size(); ++i ) {
        if ( zs == 0 ) ++zs;
        this->sceneryLayers.at( i )->setLocalZOrder( zs );
    }
}

void MainScene::update(float dt) {
    //this->biomeManager->step( dt );
    
    // NOTE: terrain layers MUST be stepped first
    // so scenery layers have the terrain they need
    // to determine their Y positions
    for ( auto& tl : this->terrainLayers ) {
        tl->step( -4.f );
    }
    for ( auto& sl : this->sceneryLayers ) {
        sl->step( -4.f );
    }
    
    background->setColor( Color3B( this->biomeManager->getCurrentFogInfo().color ) );
}
