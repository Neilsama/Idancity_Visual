//
//  ParticleSystem.hpp
//  particle - in class
//
//  Created by Neil on 11/1/16.
//
//

#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Particle.hpp"

class ParticleSystem{

public:
    ParticleSystem(ofVec3f position, float fft);
    void update(ofVec3f force,float fft);
    void draw();
    
    vector<Particle>    mParticleList;
    ofVec3f             mPosition;
    int                 mEmitRate;
    float               mfft;
    bool                mIsAddingParticles;
};



#endif /* ParticleSystem_hpp */
