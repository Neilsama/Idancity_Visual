//
//  Particle.cpp
//  particle - in class
//
//  Created by Neil on 11/1/16.
//
//

#include "Particle.hpp"

Particle::Particle(ofVec3f position): mPosition(position), mVelocity(ofRandom(-2.f, 2.f), ofRandom(-2.f, 2.f),ofRandom(-2.f, 2.f)),mAcceleration(ofVec3f(0)),mLifeSpan(200.f){

}

//-------------------------------------------------
void Particle::resetForces(){
    mAcceleration *= 0;
};

//-------------------------------------------------
void Particle::applyForce(ofVec3f force){
    mAcceleration += force;
};

//-------------------------------------------------
void Particle::update(float multiplier){
    mVelocity += mAcceleration;
    mPosition += mVelocity * multiplier;
    
    if(mLifeSpan > 0){
        mLifeSpan -= 2.f;
    }
};

//-------------------------------------------------
void Particle:: draw(){
    if(mLifeSpan > 100){
        //new particle is brighter
        ofSetColor(mLifeSpan);
    }
    else if(mLifeSpan <= 100){
        //do some sparkling
        ofSetColor(ofRandom(0,200));
    }
    
    //closer particle is smaller;
    ofDrawCircle(mPosition, 1.f * ofMap(mLifeSpan, 0 ,200.f, 0, 1.f));
};
