#pragma once

#include "ofMain.h"
#include "musicSystem.hpp"
#include "ParticleSystem.hpp"
#include "Particle.hpp"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    //-------music system-------
    ofSoundPlayer mPlayer;
    musicSystem musicSystem;
    ofSoundPlayer music;
    
    ofVec3f systemOffset;
    
    //-------point particle effect-------
    vector<ParticleSystem>  mSystem;
    ofPolyline line;
    
    ofVec3f mGravity;
    
    void trackPoint(ofVec3f pointPos);
    //-----scene-----
    ofEasyCam cam;
};
