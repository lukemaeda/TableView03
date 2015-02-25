//
//  SecondScene.h
//  TableView02
//
//  Created by MAEDAHAJIME on 2015/02/19.
//
//

#ifndef __TableView02__SecondScene__
#define __TableView02__SecondScene__

#include "cocos2d.h"

class SecondScene : public cocos2d::Layer
{
public:
    
    //初期化のメソッド
    virtual bool init();
    
    static cocos2d::Scene* createScene();
    
    // 戻るボタン押下時の処理宣言 戻る Object →　Ref に変更
    void pushBack(cocos2d::Ref *pSender);
    
    // row行数グローバル変数
    long idx0 = 0;
    
    // バッククリックキー
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

    // create()を使えるようにしている。
    CREATE_FUNC(SecondScene);
    
};

#endif /* defined(__TableView02__SecondScene__) */
