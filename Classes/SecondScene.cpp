//
//  SecondScene.cpp
//  TableView02
//
//  Created by MAEDAHAJIME on 2015/02/19.
//
//

#include "SecondScene.h"
#include "TopTableView.h"
//音をならすためにinclude
#include "SimpleAudioEngine.h"

// 名前空間 #define USING_NS_CC using namespace cocos2d
USING_NS_CC;

using namespace std; // String*

Scene* SecondScene::createScene()
{
    // 「シーン」は自動解放オブジェクトです
    auto scene = Scene::create();
    
    // 「レイアウト」は自動解放オブジェクトです
    auto layer = SecondScene::create();
    
    // シーンに子としてレイヤーを追加
    scene->addChild(layer);
    
    // シーンを返す
    return scene;
}

// 「INIT」初期化
bool SecondScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    // バックキー処理
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(SecondScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    
    //画面の座標関係の詳しい説明はここ http://www.cocos2d-x.org/wiki/Coordinate_System
    //画面サイズを取得
    Size winSize = Director::getInstance()->getVisibleSize();
    // 原点を取得
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // バックグランドカラー
    auto background = LayerColor::create(Color4B::BLUE,
                                         winSize.width,
                                         winSize.height);
    //バックグランドカラー追加 第2引数は表示順
    this->addChild(background, 0);
    
    
    // UserDefault 読込　LOG表示
    auto userRead = cocos2d::UserDefault::getInstance();
    log("row 行番号: %d", userRead->getIntegerForKey("row"));
    
    // int型 UserDefaultのrowを呼び込む
    auto row = userRead->getIntegerForKey("row");
    
    //////////////////////////////////////////////
    
    // Plist ValueVector
    ValueVector vec = FileUtils::getInstance()->getValueVectorFromFile("data.plist");
    
    // 最初の0行目を選択した時
    if (row == 0) {
        idx0 = row;     // 最初のCellの1行目
    } else {
        idx0 = row * 4; // 次のCellの2行目 Plist行数 x 4
    }

    // Plist 1行目は、idx0 = row 連番
    long idx1 = idx0 + 1; // Plist 2行目 花火の種類
    long idx2 = idx1 + 1; // Plist 3行目 花火の写真
    long idx3 = idx2 + 1; // Plist 4行目 花火の小写真
    
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    
    // Plist 花火の写真画像CCSpriteクラスを初期化しています。
    std::string vec_3 = vec.at(idx2).asString();
    auto sprite1 = Sprite::create(vec_3);
    //位置を設定
    sprite1->setPosition(Vec2(winSize.width/2, winSize.height/2));
    //画面に追加をしています。
    this->addChild(sprite1);
    
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    
    // Plist 花火の種類タイトルを設置
    std::string vec_1 = vec.at(idx1).asString();
    auto lbl_title = Label::createWithSystemFont(vec_1, "Arial", 40);
    lbl_title->setPosition(Point(origin.x + winSize.width/2,
                                 origin.y + winSize.height - 19
                                 -lbl_title->getContentSize().height));
    lbl_title->setColor(Color3B::GREEN);
    this->addChild(lbl_title,1);
    
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    //戻るボタンを設置
    auto backButton = MenuItemImage::create(
                                            "Back.png",  //表示
                                            "BackSelected.png",  //タップ時の画像
                                            CC_CALLBACK_1(SecondScene::pushBack, this));
    
    backButton->setPosition(Point(winSize.width /2 - 260 ,winSize.height/2 + 510));
    
    //create menu, it's an autorelease object
    auto menu = Menu::create(backButton, NULL);
    
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu, 1);
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    
    return true;
}

// pushBackボタン
void SecondScene::pushBack(Ref *pSender)
{
    // 効果音を鳴らす
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("onepoint26.mp3");
    
    // 遷移先の画面のインスタンス
    Scene *pScene = TopTableView::createScene();
    
    // 0.5秒かけてフェードアウトしながら次の画面に遷移します
    //    引数１:フィードの時間
    //    引数２：移動先のシーン
    //    引数３：フィードの色（オプション）
    TransitionFade* transition = TransitionFade::create(0.5f, pScene);
    
    //遷移実行  遷移時のアニメーション　http://study-cocos2d-x.info/scenelayer/55/
    Director::getInstance()->replaceScene(transition);
}

// バックキー処理 onKeyReleased()でバックキーのイベントを取得
void SecondScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        // 遷移先の画面のインスタンス
        Scene *pScene = TopTableView::createScene();
        
        // 0.5秒かけてフェードアウトしながら次の画面に遷移します
        //    引数１:フィードの時間
        //    引数２：移動先のシーン
        //    引数３：フィードの色（オプション）
        TransitionFade* transition = TransitionFade::create(0.5f, pScene);
        
        //遷移実行  遷移時のアニメーション　http://study-cocos2d-x.info/scenelayer/55/
        // (replaceScene)直前のsceneはもう使わないから捨ててしまう方法
        Director::getInstance()->replaceScene(transition);
    }
}