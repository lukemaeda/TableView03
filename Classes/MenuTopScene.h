//
//  MenuTopScene.h
//  TableView03
//
//  Created by MAEDAHAJIME on 2015/02/21.
//
//

#ifndef __TableView03__MenuTopScene__
#define __TableView03__MenuTopScene__

#include "cocos2d.h"

class MenuTopScene : public cocos2d::Layer
{
protected:
    MenuTopScene();
    virtual ~MenuTopScene();
    //初期化のメソッド
    bool init() override;
    
public:
    static cocos2d::Scene* createScene();
    // BGMの再生
    void onEnterTransitionDidFinish() override;
    // create()を使えるようにしている。
    CREATE_FUNC(MenuTopScene);
    
    // バッククリックキー
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    
};

#endif /* defined(__TableView03__MenuTopScene__) */
