#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetSmoothLighting(true);
    systemOffset = ofVec3f(0.0, 10.0, 0.0);
    mPlayer.load("music2.mp3");
    
    musicSystem.initialize(ofVec3f(0,0,0), 400, mPlayer);
    musicSystem.setStroke(5);
    
    mGravity = ofVec3f(0.f, 0.02f, 0.02f); // set particle system gravity
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //-------particle system------------
    
    for (int i = 0; i < mSystem.size(); i++){
        mSystem[i].update(mGravity); //apply gravity all particles
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //information on screen-------------
    
    ofBackgroundGradient(ofColor(50), ofColor(0));
    ofSetColor(255);
    if(!mPlayer.isPlaying()){
        ofDrawBitmapString("wait user...", 30, 30);
    }
    else{
        ofDrawBitmapString("detect user...", 30, 30);
        ofDrawBitmapString("FFT is: " + ofToString(musicSystem.avgFFT), 30, 50);
    }
    ofSetColor(255);
    ofDrawBitmapString("mouseX is: "+ofToString(mouseX-ofGetWidth()/2)+"mouseY is: "+ofToString(mouseY-ofGetHeight()/2-systemOffset.y), 30, 80);

    
//draw music system--------------------------
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2+systemOffset.y);
        
        ofFill();
        trackPoint(ofVec3f(mouseX-ofGetWidth()/2, mouseY-ofGetHeight()/2-systemOffset.y, 0));
    
    
    ofPopMatrix();
    
    cam.begin();
    cam.disableMouseInput();
        musicSystem.drawSpace();
    cam.end();
    //mouse particle system----------------------------
    
    for (int i = 0; i < mSystem.size(); i++){
        mSystem[i].draw();
    }
    ofSetColor(200, 200, 200);
    line.draw();
    
}


//--------------------------------------------------------------
void ofApp::trackPoint(ofVec3f pointPos){
    
    
    //check mouse position to trigger flash strock-------------
    if(pointPos.x > 0){
        
        if(pointPos.y <= 0 && pointPos.y > -200){
            musicSystem.drawCircle(11);
        }
        if(pointPos.y < -200 && pointPos.y > -340){
            musicSystem.drawCircle(10);
        }
        if(pointPos.y <= -340 && pointPos.y >= -400){
            musicSystem.drawCircle(9);
        }
        if(pointPos.y <= 200 && pointPos.y > 0){
            musicSystem.drawCircle(0);
        }
        if(pointPos.y <= 340 && pointPos.y > 200){
            musicSystem.drawCircle(1);
        }
        if(pointPos.y <= 400 && pointPos.y > 340){
            musicSystem.drawCircle(2);
        }

    }
    if(pointPos.x < 0){
        if(pointPos.y <= 0 && pointPos.y > -200){
            musicSystem.drawCircle(6);
        }
        if(pointPos.y < -200 && pointPos.y > -340){
            musicSystem.drawCircle(7);
        }
        if(pointPos.y <= -340 && pointPos.y >= -400){
            musicSystem.drawCircle(8);
        }
        if(pointPos.y <= 200 && pointPos.y > 0){
            musicSystem.drawCircle(5);
        }
        if(pointPos.y <= 340 && pointPos.y > 200){
            musicSystem.drawCircle(4);
        }
        if(pointPos.y <= 400 && pointPos.y > 340){
            musicSystem.drawCircle(3);
        }
    }

    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        mPlayer.play();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    }

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    ofPoint pt;
    
    pt.set(x,y);
    line.addVertex(pt);
    
    //create a new particle system after click
    ParticleSystem system = ParticleSystem(ofVec3f (x, y, 0));
    mSystem.push_back(system);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
