#pragma once

#include "ofMain.h"
#include "musicSystem.hpp"
#include "ParticleSystem.hpp"
#include "Particle.hpp"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "UserFlowInfo.hpp"
#include "ofxDxfExport.h"

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
        float * valFFT;
        int nBandsToGet;
        float avgFFT;

        ofSoundPlayer mPlayer;
        musicSystem musicSystem;
        int nMusic; // the number of music
        int radius; //the radius of blue circle
    
        ofVec3f systemOffset; // the circle offset;
    
    //-------point particle effect-------
        vector<ParticleSystem>  mSystem;
        int nMaxPoints; //the number of joint points
    
        ofVec3f mGravity;
    
        void trackPoint(ofVec3f pointPos);
    
    //-----3d scene-----
        ofEasyCam cam;
        ofEasyCam camGraphic;
    
    //-----kinect -------
        ofxKinect kinect;
        ofVec3f kinectOffset; //kinect offset to
        float kinectRatio = 0.75;
        ofxCvColorImage colorImg;
        ofxCvGrayscaleImage grayImg,grayBg,grayDiff;
        ofxCvGrayscaleImage temp;
    
        bool bLearnBackground;
        float brightness;
        int threshold;
    
        int moveArea_width, moveArea_height;
    
        ofxCvContourFinder contourFinder;
        array<ofVec3f,6> brightestPoint;
        ofImage savingImg;
    
        bool bHasPoint; //true: find a light spot; false: no light spot
    
    //------movement lines-----------
    
        ofPolyline line;
        ofMesh mesh;
    
        bool bDrawMesh;
        bool bFinished;
        bool bBegin; // whole system begin, true: kinect begin tracking,music playing
    
        bool bAddpoint; // in play back add pts to mesh;
        bool bRotate;
        float degree;
    
        vector <ofVec3f>::iterator it;
    
    
    //-------userflow info-----
        UserFlowInfo info;
    
        ofxDxfExport dxf;
        vector <ofVec3f> pts;
    

    
    
};
