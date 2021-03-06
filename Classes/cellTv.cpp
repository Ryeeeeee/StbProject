#include "cellTv.h"

#define COVER_TAG 1111
#define CELL_TAG 1112
//#define FRAME_TAG 1113
#define TOP_GLOBEL_ZORER 1000

cellTv::cellTv(void)
{
}

cellTv::~cellTv(void)
{
}

cellTv * cellTv::create(void)
{
	cellTv * ret = new cellTv();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
	return ret;
}

cellTv* cellTv::createNode(const std::string& filename, float globalZorder, bool withCover)
{
    auto node = cellTv::create();
    node->setGlobalZOrder(globalZorder);
    node->saveGlobelZorder(globalZorder);
    
    auto* pcellTv = Sprite::createWithSpriteFrameName(filename);
    pcellTv->setGlobalZOrder(globalZorder+0.01);
    pcellTv->setTag(CELL_TAG);
    
    node->addChild(pcellTv, 0);
    
//    auto* pcellFrame = Sprite::createWithSpriteFrameName("cellframe.png");
//    pcellFrame->setGlobalZOrder(globalZorder+0.02);
//    pcellFrame->setTag(FRAME_TAG);
//    node->addChild(pcellFrame, 1);

    if (withCover) {
        auto* pCover = Sprite::createWithSpriteFrameName("cellbackground.png");
        pCover->setTag(COVER_TAG);
        pCover->setOpacity(255*3/4);
        pCover->setGlobalZOrder(globalZorder+0.03);
        node->addChild(pCover, 2);
    }
    
    return node;
}

void cellTv::runRotateAction()
{
    ActionInterval* action1 = EaseSineOut::create(OrbitCamera::create(2, 1, 0, 0, 360, 0, 0));
    
    float time = CCRANDOM_0_1() * 10 + _time;
    
    runAction(EaseElasticOut::create(Sequence::create(DelayTime::create(time), ReverseTime::create(action1), NULL)));
}

void cellTv::rotateDelay(int delayTime)
{
    auto delayAction = DelayTime::create(0.25*delayTime + CCRANDOM_0_1());
    ActionInterval* action1 = EaseSineOut::create(OrbitCamera::create(0.5, 1, 0, 0, 360, 0, 0));
    runAction(EaseSineOut::create(Sequence::create(delayAction,
                               action1,
                               CallFunc::create( CC_CALLBACK_0(cellTv::setCoverVisible,this)),
                               NULL)));
}

void cellTv::moveToDestination()
{
    runAction(EaseSineOut::create(Sequence::create(
                               DelayTime::create(_time),
                               Show::create(),
                               EaseSineOut::create(MoveTo::create(0.5, _destination)),
                               NULL)));
}

void cellTv::moveToSource()
{
    runAction(EaseSineOut::create(Sequence::create(
                               DelayTime::create(_time),
                               EaseSineOut::create(MoveTo::create(0.5, _source)),
                               Hide::create(),
                               NULL)));
}

void cellTv::setCoverVisible()
{
    auto node = this->getChildByTag(COVER_TAG);
    if(node == NULL) return;
    
    node->runAction(EaseSineIn::create(Sequence::create(FadeOut::create(0.2), RemoveSelf::create(), NULL) ));
}

void cellTv::resetGlobelZorder()
{
    getChildByTag(CELL_TAG)->setGlobalZOrder(_globelZorder+0.01);
//    getChildByTag(FRAME_TAG)->setGlobalZOrder(_globelZorder+0.02);
}

void cellTv::bringNodeToTop()
{
    getChildByTag(CELL_TAG)->setGlobalZOrder(TOP_GLOBEL_ZORER);
//    getChildByTag(FRAME_TAG)->setGlobalZOrder(TOP_GLOBEL_ZORER);
}


void cellTv::onEnter()
{
    Node::onEnter();

}

void cellTv::onExit()
{
    Node::onExit();
}    
