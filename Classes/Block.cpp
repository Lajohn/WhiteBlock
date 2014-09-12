#include "Block.h"

USING_NS_CC;

Block::Block()
{
}


Block::~Block()
{
}


Vector<Block*>* Block::blocks = new Vector<Block*>();

Vector<Block*>* Block::getBlocks(){
	return Block::blocks;
}
//创建
Block* Block::createWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor){
	auto b = new Block();
	if (b && b->initWithArgs(color, size, label, fontSize, textColor))
	{
		b->autorelease();
		blocks->pushBack(b);
		return b;
	}
	CC_SAFE_DELETE(b);
	return nullptr;
}

//初始化
bool Block::initWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor){

	if (!Sprite::init()){
		return false;
	}

	//设置Block大小
	this->setContentSize(size);
	//设置锚点
	setAnchorPoint(Vec2::ZERO);
	//设置纹理形状大小
	setTextureRect(Rect(0, 0, size.width, size.height));
	//设置颜色
	setColor(color);

	//创建文本
	auto l = Label::create();
	//设置文字
	l->setString(label);
	//设置字体颜色
	l->setTextColor(textColor);
	//设置字体大小
	l->setSystemFontSize(fontSize);
	//设置位置
	l->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(l);




	return true;
}

//删除
void Block::removeBlock(){
	this->removeFromParent();
	blocks->eraseObject(this);
}

int Block::getLineIndex(){
	return this->lineIndex;
}


void Block::setLineIndex(int index){
	this->lineIndex = index;
}

void Block::moveDown(){
	this->lineIndex--;
	runAction(Sequence::create(
		MoveTo::create(0.1f, Vec2(getPositionX(), lineIndex*(getContentSize().height+1))), 
		CallFunc::create([&](){
		if (this->getLineIndex()<0){
			this->removeBlock();
		}
		}), NULL));
}

