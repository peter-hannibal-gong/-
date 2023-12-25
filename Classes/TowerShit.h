
#ifndef __CarrotFantasy__TowerShit__
#define __CarrotFantasy__TowerShit__

#include "cocos2d.h"

class TowerShit : public cocos2d::Sprite
{


public:
    static Sprite* createSprite();
	
	virtual bool init();

	CREATE_FUNC(TowerShit);


};
#endif /* defined(__CarrotFantasy__TowerShit__) */