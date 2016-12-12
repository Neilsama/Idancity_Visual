#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    radius = 350;
    moveArea_height  = 350;  //circle radius
    moveArea_width = 350;   //kinectRatio;
    
    //-----------------setup music-----------------
    
        systemOffset = ofVec3f(ofGetWidth()/2, ofGetHeight()/2 + 10.0, 0.0); // system offset relative to center point of window
        nMusic = 9;
        nBandsToGet = 128;
    
        //------------load music randomly------------
    
        int i = int(ofRandom(nMusic));
        mPlayer.load("music_"+ofToString(i)+".mp3");
        musicSystem.initialize(ofVec3f(0,0,0), moveArea_height, mPlayer);
        musicSystem.setStroke(15);
    
        mGravity = ofVec3f(0.f, 0.02f, 0.02f); // set particle system gravity
    
    //------------setup kinect-------------
    
        ofSetLogLevel(OF_LOG_VERBOSE);
        kinect.setRegistration();
        kinect.init(false,true,false);
        kinect.open();
        kinect.setDepthClipping(500,3000);
        kinect.setCameraTiltAngle(0);
        colorImg.allocate(kinect.width, kinect.height);
        grayImg.allocate(kinect.width, kinect.height);
        grayBg.allocate(kinect.width, kinect.height);
        grayDiff.allocate(kinect.width, kinect.height);
    
        bLearnBackground = true;
        threshold = 50;
    
        nMaxPoints = 6;
    
        kinectOffset = ofVec3f(-kinect.width/2, -kinect.height/2, 0);

    
    //--------------setup Mesh----------------
    
        ofSetVerticalSync(true);
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
        glEnable(GL_POINT_SMOOTH);
        glPointSize(2);
        bDrawMesh = false;
        bHasPoint = false;
        bBegin = false;
        bAddpoint = false;
        bRotate = false;
        degree = 0;
    
        info.init();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //--------music fft update if sounds play------------
    
    if(mPlayer.isPlaying()){
        valFFT = ofSoundGetSpectrum(nBandsToGet);
        float temp;
    
        for(int i = 0; i < nBandsToGet; i++){
            temp += valFFT[i];
        }
        avgFFT = temp/nBandsToGet*10;
        
    
        //-------particle system------------
    
        for (int i = 0; i < mSystem.size(); i++){
            mSystem[i].update(mGravity, avgFFT); //apply gravity all particles
        }
    }
    
    musicSystem.updateCircleStrock( avgFFT);
    
    //--------update kinect if begin----------
    
    if(bBegin){
        kinect.update();
    
        if(kinect.isFrameNew()){
            colorImg.setFromPixels(kinect.getPixels());
            colorImg.mirror(false, true);
            grayImg = colorImg;
            if(bLearnBackground){
                grayBg = grayImg;
                bLearnBackground = false;
            }
            grayDiff.absDiff(grayBg,grayImg);
            grayDiff.threshold(threshold);
        }
 
        contourFinder.findContours(grayDiff, 0, kinect.width*kinect.height, nMaxPoints, true);
    
    
    //---------calculate blobs center position, push that point
    
        if(contourFinder.nBlobs != 0){
            bHasPoint = true;
            for(int i = 0; i < contourFinder.nBlobs; i++){
                ofVec2f tempVec2f = contourFinder.blobs[i].boundingRect.getCenter();
                float tempZ = kinect.getDistanceAt(tempVec2f); //get depth value of specific point
                cout << tempZ << endl;
                tempVec2f.y = 480-tempVec2f.y;
        
                float z;
                if(tempZ>1000 && tempZ<3000)
                    z = ofMap(tempZ, 1000, 3000, -200,0);
                if(tempZ >4000 && z <8000)
                    z = ofMap(tempZ, 4000, 8000, 0,200);

                brightestPoint[i] = ofVec3f(tempVec2f.x,tempVec2f.y,z)+kinectOffset;
            
            }
            
            if(brightestPoint[0] != ofVec3f(0)){
                line.addVertex(brightestPoint[0]);
                pts.push_back(brightestPoint[0]);
                line.begin();
            }
            
        }
        if(contourFinder.nBlobs == 0){
            bHasPoint = false;
            for(int i = 0; i<4;i++)
                brightestPoint[i] = ofVec3f(0);
        }
    }
    
    if(bAddpoint){
        if(it != pts.end()){
            mesh.addVertex(*it);
            it++;
        }
    }
    if(bRotate){
        degree += 1;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //information on screen-------------
    
    
        ofBackgroundGradient(ofColor(50), ofColor(0));
        ofSetColor(255);

        //---------information about UI-----------
        if(!mPlayer.isPlaying() && !bBegin){
            cout << "bug point bdrawmesh: " << bDrawMesh <<endl;
            info.showInfo("WELCOME!!!!", 760, 300);
           info.showInfo("PLEASE SAY",770,400);
            info.showInfo("'I LOVE NEIL'",750,500);
            info.showInfo("TO BEGIN",780,600);
        }
        if(bFinished){
            cout << "draw info - bFinished is: " << bFinished <<endl;
            info.showInfo("THANKS BABY~", 700, 200);
        }
    
    //--------draw kinect image for test-----
       // contourFinder.draw();
    
    
    
    //the following part are translate the coordinations with systemOffset
    //*******************************************************************
    //--------------draw the ground plane------------
        cam.begin();
        cam.disableMouseInput();
        musicSystem.drawSpace();
        cam.end();
    
    //-----------translate coordination---------------------
    
        ofPushMatrix();
        ofTranslate(systemOffset);
      
        //------tracking point and light cooresponding arc of the circle in 3d space---------------------

        if(bHasPoint && mPlayer.isPlaying() && !bDrawMesh){
            for(int i = 0; i < contourFinder.nBlobs;i++){
                trackPoint(brightestPoint[i]);
            }
        }
    
        camGraphic.begin();
    
        //-----draw mouse particle system in 2d ------------------
    
        if(bBegin){
            for (int i = 0; i < mSystem.size(); i++){
                mSystem[i].draw();
            }
        }
    
        ofSetColor(200, 200, 200);
    
        //------draw line---------------------
    
        if(bRotate)
            ofRotateY(degree);
    
        if(!bDrawMesh && bBegin)
    
            line.draw();
    
        if(bDrawMesh){
            mesh.drawWireframe();
            mesh.drawVertices();
            ofSetColor(200, 200, 200, 50);
            mesh.drawFaces();
        }
    
        camGraphic.end();
   
   
    
    ofPopMatrix();
    

    
}


//--------------------------------------------------------------
void ofApp::trackPoint(ofVec3f pointPos){
    
        ofFill();
    
        if(mPlayer.isPlaying()){
        
    //create a new particle system---------------------------
            
        ParticleSystem system = ParticleSystem(ofVec3f (pointPos.x, pointPos.y, pointPos.z),avgFFT);
        mSystem.push_back(system);

    //check points position to trigger flash strock-------------
            
        if(pointPos.x > 0){
            if(pointPos.y <= 0 && pointPos.y > -120){
                musicSystem.drawCircle(0);
            }
            if(pointPos.y < -120 && pointPos.y > -180){
                musicSystem.drawCircle(1);
            }
            if(pointPos.y <= -180 && pointPos.y >= -240){
                musicSystem.drawCircle(2);
            }
            if(pointPos.y <= 120 && pointPos.y > 0){
                musicSystem.drawCircle(11);
            }
            if(pointPos.y <= 180 && pointPos.y > 120){
                musicSystem.drawCircle(10);
            }
            if(pointPos.y <= 240 && pointPos.y > 180){
                musicSystem.drawCircle(9);
            }
        }
            
        if(pointPos.x < 0){
            if(pointPos.y <= 0 && pointPos.y > -120){
                musicSystem.drawCircle(5);
            }
            if(pointPos.y < -120 && pointPos.y > -180){
                musicSystem.drawCircle(4);
            }
            if(pointPos.y <= -180 && pointPos.y >= -240){
                musicSystem.drawCircle(3);
            }
            if(pointPos.y <= 120 && pointPos.y > 0){
                musicSystem.drawCircle(6);
            }
            if(pointPos.y <= 180 && pointPos.y > 120){
                musicSystem.drawCircle(7);
            }
            if(pointPos.y <= 240 && pointPos.y > 180){
                musicSystem.drawCircle(8);
            }
        }
    }
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key) {
        case OF_KEY_RETURN:{
            bDrawMesh = false;
            cout << "press return: bdrawmesh:" << bDrawMesh <<endl;
            if(!mPlayer.isPlaying()){
                mPlayer.play();
                bBegin = true;
                bFinished = false;
                cout << "KeyPressed - bFinished is:  " << bFinished <<endl;
            }
            else{
                mPlayer.stop();
                bBegin = false;
                bFinished = true;
            }
            break;
        }
            
        case OF_KEY_UP:{
            int i = int(ofRandom(nMusic));
            mPlayer.load("music_"+ofToString(i)+".mp3");
            line.clear();
            mesh.clear();
            mPlayer.play();
            break;
        }
        case 's':{
            mesh.addVertices(line.getVertices());
            line.clear();
            bDrawMesh = true;
            bFinished = true;
            bBegin = false;
            break;
        }
        case 'p':{
            bBegin = false;
            bDrawMesh = true;
            it = pts.begin();
            line.clear();
            mesh.clear();
            bAddpoint = true;
            bRotate = true;
            break;
        }
        case'e':{
            savingImg.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
            savingImg.save("screenshot.png");
            break;
        }
            
        
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
