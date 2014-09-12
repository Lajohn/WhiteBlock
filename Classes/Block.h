#ifndef _BLOCK_H_
#define	_BLOCK_H_

#include "cocos2d.h"

class Block:public cocos2d::Sprite
{
private:
	static cocos2d::Vector<Block*>* blocks;
	int lineIndex;
public:
	Block();
	~Block();
	static cocos2d::Vector<Block*>* getBlocks();
	static Block* createWithArgs(cocos2d::Color3B color, cocos2d::Size size, std::string label, float fontSize, cocos2d::Color4B textColor);
	virtual bool initWithArgs(cocos2d::Color3B color,cocos2d::Size size,std::string label,float fontSize,cocos2d::Color4B textColor);
	void removeBlock();

	int getLineIndex();
	void setLineIndex(int index);
	void moveDown();

};


#endif // !_BLOCK_H_