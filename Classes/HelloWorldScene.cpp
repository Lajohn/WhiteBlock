#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	srand(time(NULL));
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加游戏层
	gameLayer = Layer::create();
	addChild(gameLayer);

	score = 0;

	//添加计时
	timerLabel = Label::create();
	timerLabel->setColor(Color3B::RED);
	timerLabel->setSystemFontSize(20);
	timerLabel->setString("Timer:");
	timerLabel->setPosition(Vec2(visibleSize.width *0.3, visibleSize.height - 100));
	this->addChild(timerLabel, 10);

	scoreLabel = Label::create();
	scoreLabel->setColor(Color3B::RED);
	scoreLabel->setSystemFontSize(20);
	scoreLabel->setString("Socre:");
	scoreLabel->setPosition(Vec2(visibleSize.width *0.6, visibleSize.height - 100));
	this->addChild(scoreLabel, 10);

	startGame();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch *t,Event *e){
		log("onTouchBegan");
		if (isGameOver){
			log("isGameOver");
			reStartGame();
			return false;
		}


		auto bs = Block::getBlocks();
		Block* b;

		for (auto it = bs->begin(); it!=bs->end(); it++)
		{
			b = *it;
			if (b->getLineIndex()==0&&b->getBoundingBox().containsPoint(t->getLocation())){
				if (b->getColor()==Color3B::BLACK||b->getColor()==Color3B::YELLOW){
					if (b->getColor() == Color3B::BLACK){
						score++;
						scoreLabel->setString(StringUtils::format("Score:%i", score));
					}
					startTimer();
					this->moveDown();
				}
				else if (b->getColor() == Color3B::WHITE){
					this->addEndLine();
					this->isGameOver = true;
					endTimer();
				}
				break;
			}
		}

		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, gameLayer);
    
    return true;
}

void HelloWorld::addStartLine(){
	auto b = Block::createWithArgs(Color3B::YELLOW, Size(visibleSize.width, visibleSize.height / 4), "", 20, Color4B::WHITE);
	b->setLineIndex(0);
	gameLayer->addChild(b);
	linesCount = 0;
}

void HelloWorld::addEndLine(){
	auto b = Block::createWithArgs(Color3B::GREEN, Size(visibleSize.width, visibleSize.height), "Game Over", visibleSize.width/10, Color4B::BLACK);
	b->setLineIndex(0);
	gameLayer->addChild(b);
	linesCount = 0;
}

void HelloWorld::addNormalLine(int lineIndex){
	Block* b;
	int index = rand() % 4;
	for (int i = 0; i < 4;i++){
		b = Block::createWithArgs(index == i ? Color3B::BLACK : Color3B::WHITE, Size(visibleSize.width / 4 - 1, visibleSize.height / 4 - 1), "", 20, Color4B::RED);
		b->setPosition(Vec2(i*visibleSize.width / 4, lineIndex*visibleSize.height / 4));
		b->setLineIndex(lineIndex);
		gameLayer->addChild(b);
	}
	linesCount++;
}

void HelloWorld::startGame(){
	this->isStartTimer = false;
	this->isGameOver = false;

	addStartLine();
	addNormalLine(1);
	addNormalLine(2);
	addNormalLine(3);
}

void HelloWorld::moveDown(){
	addNormalLine(4);
	auto bs = Block::getBlocks();
	for (auto i = bs->begin(); i !=bs->end(); i++)
	{
		(*i)->moveDown();
	}

}

void HelloWorld::reStartGame(){

	score = 0;
	scoreLabel->setString(StringUtils::format("Score:%i", 0));
	timerLabel->setString(StringUtils::format("Timer:%i", 0));


	auto bs = Block::getBlocks();
	for (auto i = bs->begin(); i != bs->end(); i++)
	{
		(*i)->removeFromParent();
	}
	bs->clear();
	log(">>>>>>>%d",bs->size());
	startGame();
}


void HelloWorld::startTimer(){
	if (!isStartTimer){
		startTime = clock();
		scheduleUpdate();
		isStartTimer = true;
	}
}

void HelloWorld::endTimer(){
	if (isStartTimer){
		unscheduleUpdate();
		isStartTimer = false;
	}
}

void HelloWorld::update(float dt){
	int t = (int)(clock() - startTime)/1000;
	timerLabel->setString(StringUtils::format("Timer:%i", 10-t));
	if (t>=10){
		this->addEndLine();
		this->isGameOver = true;
		endTimer();
	}
}




void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
