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
//����
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

//��ʼ��
bool Block::initWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor){

	if (!Sprite::init()){
		return false;
	}

	//����Block��С
	this->setContentSize(size);
	//����ê��
	setAnchorPoint(Vec2::ZERO);
	//����������״��С
	setTextureRect(Rect(0, 0, size.width, size.height));
	//������ɫ
	setColor(color);

	//�����ı�
	auto l = Label::create();
	//��������
	l->setString(label);
	//����������ɫ
	l->setTextColor(textColor);
	//���������С
	l->setSystemFontSize(fontSize);
	//����λ��
	l->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(l);




	return true;
}

//ɾ��
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

