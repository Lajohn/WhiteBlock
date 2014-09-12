#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Block.h"

class HelloWorld : public cocos2d::Layer
{
private:
	cocos2d::Size visibleSize;
	cocos2d::Layer *gameLayer;
	bool isStartTimer;
public:

	bool isGameOver;
	int linesCount;
	int score;
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void addStartLine();
	void addEndLine();
	void addNormalLine(int lineIndex);
	void startGame();
	void moveDown();
	void reStartGame();

	double startTime;
	cocos2d::Label* timerLabel;
	cocos2d::Label* scoreLabel;
	void startTimer();
	void endTimer();
	virtual void update(float dt);
};

#endif // __HELLOWORLD_SCENE_H__
