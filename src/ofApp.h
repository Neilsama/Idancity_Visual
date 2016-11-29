#pragma once

#include "ofMain.h"
#include "musicSystem.hpp"
#include "ParticleSystem.hpp"
#include "Particle.hpp"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

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
        int nMusic;
        int radius; //the radius of blue circle
    
        ofVec3f systemOffset; // the circle is not be draw 
    
    //-------point particle effect-------
        vector<ParticleSystem>  mSystem;
        int nPoints;
    
        ofVec3f mGravity;
    
        void trackPoint(ofVec3f pointPos);
    
    //-----3d scene-----
        ofEasyCam cam;
        ofEasyCam camGraphic;
    
    //-----kinect -------
        ofxKinect kinect;
        ofVec3f kinectOffset;
        float kinectRatio = 0.75;
        ofxCvColorImage colorImg;
        ofxCvGrayscaleImage grayImg,grayBg,grayDiff;
        ofxCvGrayscaleImage temp;
    
        bool bLearnBackground;
        float brightness;
        int threshold;
    
        int moveArea_width, moveArea_height;
    
        ofxCvContourFinder contourFinder;
        vector<ofVec3f> brightestPoint;
            
    //------movement lines-----------
    
        ofPolyline line1;
        ofMesh mesh;
        
    
        bool bDrawMesh;
    
    
};
