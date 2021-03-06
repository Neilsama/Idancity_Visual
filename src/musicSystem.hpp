//
//  musicSystem.hpp
//  Idancity_Visual
//
//  Created by Neil on 11/13/16.
//
//

#ifndef musicSystem_hpp
#define musicSystem_hpp
//---------------------------


#include <stdio.h>
#include <ofMain.h>

class musicSystem{

    public:
    
    //-----------basic circle parameters-------
    ofVec2f center;
    float radius; //whole circle radius
    float strockSize; //the whole circle stroke
    float dynamicStrockSize;
    float alpha;

    //-----------sound parameters--------

    float avgFFT;
    
    void initialize(ofVec3f _center, float _radius,ofSoundPlayer _music);
    void setStroke(float _strockSize);

    void drawCircle(int id);
    void updateCircleStrock(float fft);
    
    void drawSpace();

    
};

#endif /* musicSystem_hpp */
