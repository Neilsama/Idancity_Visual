//
//  musicSystem.cpp
//  Idancity_Visual
//
//  Created by Neil on 11/13/16.
//  this is the animation move with hand
//

#include "musicSystem.hpp"
//

//--------------------------------------------------------------
void musicSystem::initialize(ofVec3f _center, float _radius,ofSoundPlayer _music){
    
    center = _center;
    radius = _radius;
    
    cout << "set up music system..." << endl;

    ofSetPlaneResolution(10, 20);
    
};


//--------------------------------------------------------------
void musicSystem::setStroke(float _strockSize){
    strockSize = _strockSize;
};

//--------------------------------------------------------------
void musicSystem::updateCircleStrock(float fft){
        avgFFT = fft;
        dynamicStrockSize = strockSize * avgFFT;  // Increase for a wider brush
        alpha = ofMap(avgFFT, 0.5, 1.2, 180, 250);  // Increase for a more opaque brush
}

//--------------------------------------------------------------
//here is the flash circle
void musicSystem::drawCircle(int id){
        ofSetColor(0, 229, 221, alpha);
        float angle = 30*id;
        for(angle ; angle <= 30+30*id; angle++){
            ofVec3f point = ofVec3f(radius*cos(ofDegToRad(angle)),radius*sin(ofDegToRad(angle)),0);
            ofDrawCircle(point, dynamicStrockSize);
        }
}

//--------------------------------------------------------------
//Here is the space
void musicSystem::drawSpace(){
        ofRotateX(-90);
        ofNoFill();
        ofSetColor(0, 229, 221);
        ofDrawPlane(0, 0, -10, 80, 100);
}













