//
//  Particle.hpp
//  particle - in class
//
//  Created by Neil on 11/1/16.
//
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>
#include "ofMain.h"

class Particle{
public:
    Particle(ofVec3f position);
    
    void resetForces();
    void applyForce(ofVec3f force);
    void update(float multiplier);
    void draw();
    
    ofVec3f mPosition, mVelocity, mAcceleration;
    float mLifeSpan;
};


#endif /* Particle_hpp */
