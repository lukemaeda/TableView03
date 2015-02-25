//
//  TopTableView.h
//  TableView02
//
//  Created by MAEDAHAJIME on 2015/02/19.
//
//

#ifndef __TableView02__TopTableView__
#define __TableView02__TopTableView__

#include <iostream>
#include "cocos2d.h"
#include <extensions/cocos-ext.h>

USING_NS_CC;
using namespace extension;

class TopTableView : public Layer,
public TableViewDataSource,
public TableViewDelegate
{
    Size window_size;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    //TableViewDataSourceの抽象メソッド
    virtual Size cellSizeForTable(TableView* table);
    virtual TableViewCell* tableCellAtIndex(TableView* table,ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    //TableViewDelegateの抽象メソッド
    virtual void tableCellTouched(TableView* table,TableViewCell* cell);
    
    //TableViewDelegateが継承しているScrollViewの抽象メソッド
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view){};
    
    // 戻るボタン押下時の処理宣言 戻る Object →　Ref に変更
    void pushBack(cocos2d::Ref *pSender);
    
    // バッククリックキー
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

    CREATE_FUNC(TopTableView);
    
};

#endif /* defined(__TableView02__TopTableView__) */
