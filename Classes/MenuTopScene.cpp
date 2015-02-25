//
//  MenuTopScene.cpp
//  TableView03
//
//  Created by MAEDAHAJIME on 2015/02/21.
//
//

#include "MenuTopScene.h"
#include "TopTableView.h"
//音をならすためにinclude
#include "SimpleAudioEngine.h"

// 名前空間 #define USING_NS_CC using namespace cocos2d
USING_NS_CC;

using namespace std; // String*

Scene* MenuTopScene::createScene()
{
    // 「シーン」は自動解放オブジェクトです
    auto scene = Scene::create();
    
    // 「レイアウト」は自動解放オブジェクトです
    auto layer = MenuTopScene::create();
    
    // シーンに子としてレイヤーを追加
    scene->addChild(layer);
    
    // シーンを返す
    return scene;
}

MenuTopScene::MenuTopScene()
{
    
}

MenuTopScene::~MenuTopScene()
{
    
}

// 「INIT」初期化
bool MenuTopScene::init()
{
    if ( !Layer::init() )
    {
        
        return false;
    }
    
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    // バックキー処理
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MenuTopScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    
    auto director = Director::getInstance();
    auto winSize = director->getWinSize();
    
    // 背景の追加
    auto background = Sprite::create("fire1-1@2x.png");
    background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(background);
    
    // ミーラーレス一眼&ラベルを生成
    auto label1 = Label::createWithSystemFont("ミーラーレス一眼&", "Arial", 30);
    label1->setColor(Color3B::GREEN);
    // ラベルの設置
    label1->setPosition(Vec2(winSize.width / 2 - 170, winSize.height - 50));
    // ラベルタイトルを呼び込み追加
    this->addChild(label1,1);
    
    // デジタル一眼レフラベルを生成
    auto label2 = Label::createWithSystemFont("デジタル一眼レフ", "Arial", 30);
    label2->setColor(Color3B::GREEN);
    // ラベルの設置
    label2->setPosition(Vec2(winSize.width / 2 - 180, winSize.height - 85));
    // ラベルタイトルを呼び込み追加
    this->addChild(label2,1);
    
    // iSceneラベルを生成
    auto label3 = Label::createWithSystemFont("iScene", "Didot", 50);
    label3->setColor(Color3B::GREEN);
    // ラベルの設置
    label3->setPosition(Vec2(winSize.width / 2 + 110, winSize.height - 730));
    // ラベルタイトルを呼び込み追加
    this->addChild(label3,1);
    
    // notepadラベルを生成
    auto label4 = Label::createWithSystemFont("notepad", "Didot", 55);
    label4->setColor(Color3B::WHITE);
    // ラベルの設置
    label4->setPosition(Vec2(winSize.width / 2 + 190, winSize.height - 835));
    // ラベルタイトルを呼び込み追加
    this->addChild(label4,2);
    
    // 2015ラベルを生成
    auto label5 = Label::createWithSystemFont("2015", "Arial", 30);
    label5->setColor(Color3B::GREEN);
    // ラベルの設置
    label5->setPosition(Vec2(winSize.width / 2 + 200, winSize.height - 890));
    // ラベルタイトルを呼び込み追加
    this->addChild(label5,2);
    
    // フイルム画像の追加
    auto logo = Sprite::create("Film@2x.png");
    logo->setPosition(Vec2(winSize.width / 2.0 + 140, winSize.height - 790));
    logo->setScaleX(0.8); // 0.8倍縮小
    logo->setScaleY(0.8); // 0.8倍縮小
    this->addChild(logo);
    
    // 花火撮影ラベル Touch to Sutartの追加
    auto touchToStart = Label::createWithSystemFont("花火撮影", "Arial", 60);
    touchToStart->setPosition(Vec2(winSize.width / 2.0 + 160, 350));
    
    // 点滅させるアクションの定義
    auto blink = Sequence::create(FadeTo::create(0.5, 127),
                                  FadeTo::create(0.5, 225),
                                  NULL);
    
    // RepeatForever blink：無限に点滅
    touchToStart->runAction(RepeatForever::create(blink));
    this->addChild(touchToStart);
    
    // 画面をタッチしたときにテーブル画面へ遷移
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* touch, Event* event){
        // 効果音
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("onepoint26.mp3");
        // 何度も押せないように一度押したらアクションを無効化する
        this->getEventDispatcher()->removeAllEventListeners();
        // 0.5秒待ってからCallFuncを呼ぶ
        auto delay = DelayTime::create(0.5);
        // テーブル画面に遷移を始めるアクション
        auto starGame = CallFunc::create([]{
            // テーブル画面
            auto scene = TopTableView::createScene();
            // シーンを移動する
            auto transition = TransitionProgressInOut::create(1.5, scene);
            // (replaceScene)直前のsceneはもう使わないから捨ててしまう方法
            Director::getInstance()->replaceScene(transition);
            
            //下からシーンが移動。
            //Director::getInstance()->replaceScene(TransitionMoveInB::create(1.0f,TopTableView::createScene()));
        });
        this->runAction(Sequence::create(delay, starGame, NULL));
        
        return true;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

// BGMの再生
void MenuTopScene::onEnterTransitionDidFinish()
{
    // BGMの再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("o12.mp3", true);
}

// バックキー処理 onKeyReleased()でバックキーのイベントを取得
void MenuTopScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        Director::getInstance()->end(); // アプリを終了させる
    }
}

/*
 (runWithScene) プログラム起動後、最初のsceneを起動する処理。
 (replaceScene) 直前のsceneはもう使わないから捨ててしまう方法。基本はこれになります。
 (pushScene)    直前のsceneに戻る予定があるので、メモリに取っておく方法です。
 (popScene)     pushしたsceneを消して、元のsceneに戻る処理。

 pushとpopは、ゲーム中にオプション画面を開いてまた戻ってくる時などに使用します。

 cocos2dその7。シーン遷移 【pushScene、runWithScene】
 http://ameblo.jp/hash-r-1234/entry-10967942550.html
 
 */
