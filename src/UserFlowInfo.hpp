//
//  UserFlowInfo.hpp
//  Idancity_Visual
//
//  Created by Neil on 11/29/16.
//
//

#ifndef UserFlowInfo_hpp
#define UserFlowInfo_hpp

#include <stdio.h>
#include <ofMain.h>

class UserFlowInfo{
public:
    //UserFlowInfo();
    
    ofTrueTypeFont font;
    float fontSize;
    
    void init();
    void showInfo(string str, float x, float y);
};

#endif /* UserFlowInfo_hpp */
