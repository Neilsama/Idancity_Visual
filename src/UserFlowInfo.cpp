//
//  UserFlowInfo.cpp
//  Idancity_Visual
//
//  Created by Neil on 11/29/16.
//
//

#include "UserFlowInfo.hpp"


void UserFlowInfo::init(){
    fontSize = 52;
    font.load("Chalkduster.ttf", fontSize);
    cout << "font loaded" <<endl;
}

//-----------------------------------------------------
void UserFlowInfo::showInfo(string str, float x, float y){
    ofSetColor(255);
    font.drawString(str, x, y);
}
