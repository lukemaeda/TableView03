//
//  TopTableView.cpp
//  TableView02
//
//  Created by MAEDAHAJIME on 2015/02/19.
//
//

#include "TopTableView.h"
#include "MenuTopScene.h"
#include "SecondScene.h"
//音をならすためにinclude
#include "SimpleAudioEngine.h"

/// 行数格納用のキー
const char* ROW_KEY = "row";

Scene* TopTableView::createScene()
{
    auto scene = Scene::create();
    auto layer = TopTableView::create();
    // sceneにlayerを読み込み表示する
    scene->addChild(layer);
    
    return scene;
}

// on "init" you need to initialize your instance
bool TopTableView::init()
{
    // 初期化
    if ( !Layer::init() ) return false;
    
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    // バックキー処理
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(TopTableView::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    
    // 画面サイズサイズを取得
    window_size = Director::getInstance()->getWinSize();
    
    // バックグランドカラー
    auto background = LayerColor::create(Color4B::BLACK,
                                         window_size.width,
                                         window_size.height);
    
    // バックグランドカラー 第2引数は表示順
    this->addChild(background, 0);
    
    // テーブル一覧ラベルを生成
    auto label1 = Label::createWithSystemFont("花火一覧", "Arial", 60);
    
    label1->setColor(Color3B::GREEN);
    
    // ラベルの設置
    label1->setPosition(Vec2(window_size.width / 2 ,window_size.height - 70));
    
    // ラベルタイトルを呼び込み追加
    this->addChild(label1,1);
    
    
    // テーブルのヘッダー空間
    TableView* tableView = TableView::create(this,Size(window_size.width,window_size.height*9/10));
    // テーブル全体表示
    //TableView* tableView = TableView::create(this, window_size);
    
    // 展開方向
    tableView->setDirection(TableView::Direction::VERTICAL);
    // 表示順序上からしたへ
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    
    // 追加
    tableView->setDelegate(this);
    addChild(tableView);
    // tableViewに呼び込む
    tableView->reloadData();
    
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    //戻るボタンを設置
    auto backButton = MenuItemImage::create(
                                            "Back.png",  //表示
                                            "BackSelected.png",  //タップ時の画像
                                            CC_CALLBACK_1(TopTableView::pushBack, this));
    
    backButton->setPosition(Point(window_size.width /2 - 260 ,window_size.height/2 + 500));
    
    //create menu, it's an autorelease object
    auto menu = Menu::create(backButton, NULL);
    
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu, 1);
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    
    return true;
}

// セルの大きさを設定する
Size TopTableView::cellSizeForTable(TableView *table){
    
    return Size(window_size.width, 215);
}

// 1セルに表示させるValueをセット
TableViewCell* TopTableView::tableCellAtIndex(TableView *table, ssize_t idx){
    
    // 行番号
    std::string id = StringUtils::format("%zd", idx);
    
    // セル
    TableViewCell *cell = table->dequeueCell();
    
    cell = new TableViewCell();
    // autoreleaseを呼び出す
    cell->autorelease();
    
    // セルの背景色
    auto background_color = Color3B::GRAY;
    
    // Background
    Sprite* bg = Sprite::create();
    bg->setAnchorPoint(Point(0, 0));
    bg->setTextureRect(Rect(0, 0, window_size.width, 215));
    bg->setColor(background_color);
    bg->setTag(100);
    // Backgroundを呼び出し表示
    cell->addChild(bg);
    
    // ボーダーライン
    Sprite* line = Sprite::create();
    line->setAnchorPoint(Point(0, 0));
    line->setTextureRect(Rect(0, 0, window_size.width, 1));
    line->setColor(Color3B::WHITE);
    cell->addChild(line);
    
    //////////////////////////////////////////////
    
    // Plist ValueVector
    ValueVector vec = FileUtils::getInstance()->getValueVectorFromFile("data.plist");
    
    // 置き換えセル行数変数 
    long idx0 = 0;
    // Cell行idxをidx01に保存
    log("idx:%ld", idx);
    
    // 最初のCellの0行目
    if (idx == 0) {
        idx0 = idx;     // 最初のCellの1行目
    } else {
        idx0 = idx * 4; // 次のCellの2行目 Plist行数 x 4
    }
    
    // Plist 1行目は、idx0
    long idx1 = idx0 + 1; // Plist 2行目
    long idx2 = idx1 + 1; // Plist 3行目 花火小画像
    long idx3 = idx2 + 1; // Plist 4行目 花火大画像
    
    // 花火の種類ラベル表示
    std::string vec_1 = vec.at(idx1).asString();
    auto *label_2 = LabelTTF::create(vec_1.c_str(), "Arial", 52);
    label_2->setAnchorPoint(Point(0, 0));
    label_2->setPosition(Point(140, 70)); // セル幅のセンター
    label_2->setColor(Color3B::GREEN);
    cell->addChild(label_2);
    
    // 花火小画像
    std::string vec_3 = vec.at(idx3).asString();
    Sprite* imge_1 = Sprite::create(vec_3);
    imge_1->setAnchorPoint(Point(0, 0));
    imge_1->setPosition(Point(10, 0));
    imge_1->setScaleX(1.5); // 1.5倍拡大
    imge_1->setScaleY(1.5); // 1.5倍拡大
    cell->addChild(imge_1);
    
    return cell;
}

// セル数
ssize_t TopTableView::numberOfCellsInTableView(TableView *table){
    return 19;
}

// セルがタッチされた時のcallback
void TopTableView::tableCellTouched(TableView* table, TableViewCell* cell){
    
    log("%ziのセルがタッチされました", cell->getIdx());
    // cell 行番号
    float row = cell->getIdx();
    
    ////////////////////////////////////////////////
    // UserDefault 保存
    // 行番号保存
    UserDefault::getInstance()->setIntegerForKey(ROW_KEY, row);
    
    ////////////////////////////////////////////////
    
    // 効果音を鳴らす
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("onepoint26.mp3");
    
    
    // 遷移先の画面のインスタンス
    Scene *pScene = SecondScene::createScene();
    
    // 0.5秒かけてフェードアウトしながら次の画面に遷移します
    //    引数１:フィードの時間
    //    引数２：移動先のシーン
    //    引数３：フィードの色（オプション）
    TransitionFade* transition = TransitionFade::create(0.5f, pScene);
    
    // 遷移実行  遷移時のアニメーション　http://study-cocos2d-x.info/scenelayer/55/
    // 直前のsceneはもう使わないから捨ててしまう方法。基本はこれになります。
    Director::getInstance()->replaceScene(transition);
}

// pushBackボタン
void TopTableView::pushBack(Ref *pSender)
{
    // 効果音を鳴らす
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("onepoint26.mp3");
    
    // 遷移先の画面のインスタンス
    Scene *pScene = MenuTopScene::createScene();
    
    // 0.5秒かけてフェードアウトしながら次の画面に遷移します
    //    引数１:フィードの時間
    //    引数２：移動先のシーン
    //    引数３：フィードの色（オプション）
    TransitionFade* transition = TransitionFade::create(0.5f, pScene);
    
    //遷移実行  遷移時のアニメーション　http://study-cocos2d-x.info/scenelayer/55/
    // (replaceScene)直前のsceneはもう使わないから捨ててしまう方法
    Director::getInstance()->replaceScene(transition);
}

// バックキー処理 onKeyReleased()でバックキーのイベントを取得
void TopTableView::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        // 遷移先の画面のインスタンス
        Scene *pScene = MenuTopScene::createScene();
        
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