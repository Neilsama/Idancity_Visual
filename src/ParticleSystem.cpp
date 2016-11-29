//
//  ParticleSystem.cpp
//  particle - in class
//
//  Created by Neil on 11/1/16.
//
//

#include "ParticleSystem.hpp"

ParticleSystem:: ParticleSystem(ofVec3f position): mPosition(position), mEmitRate(2.5), mIsAddingParticles(true){

}
//--------------------------------------------------------
void ParticleSystem::update(ofVec3f force){
    
    if (mIsAddingParticles){
        //pushing particles into the array
        for(int i = 0; i < mEmitRate ; i++){
            Particle particle(mPosition);
            mParticleList.push_back(particle);
        }
    }
    
    for( int i = 0; i < mParticleList.size(); i++){
        ofVec2f diff = ofVec3f(abs(mParticleList[i].mPosition.x - mPosition.x),abs(mParticleList[i].mPosition.y - mPosition.y),abs(mParticleList[i].mPosition.z - mPosition.z));
        
        mParticleList[i].resetForces();
        
        mParticleList[i].applyForce(force);
        //apply to the random velocity to the particle
        mParticleList[i].update(ofMap(diff.length(), 40, 50, 1, 0.5));
    
        if(diff.length() >= ofRandom(40, 60)){
            //stop adding particle if the particle's diff is higher than a certain munber
            mIsAddingParticles = false;
            //erase the particle if it's too far from the center
            if(mParticleList.size() > 0){
                mParticleList.erase(mParticleList.begin()+i);
            }
        }
    }
    
};

void ParticleSystem::draw(){
    for(int i = 0; i < mParticleList.size(); i++){
        for(int j = i + 1; j < mParticleList.size(); j++){
            float dist = ofDist(mParticleList[i].mPosition.x, mParticleList[i].mPosition.y,mParticleList[i].mPosition.z, mParticleList[j].mPosition.x, mParticleList[j].mPosition.y,mParticleList[j].mPosition.z);
            if(dist < 40){
                ofSetColor(255, 255, 255, ofMap(dist,0,100,0,90));
                ofDrawLine(mParticleList[i].mPosition.x, mParticleList[i].mPosition.y, mParticleList[j].mPosition.x, mParticleList[j].mPosition.y);
            }
          
        }
          mParticleList[i].draw();
    }
};
