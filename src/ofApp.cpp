#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    radius = 350;
    moveArea_height  = 350;  //circle radius
    moveArea_width = 350;   //kinectRatio;
    
   // ofSetOrientation(OF_ORIENTATION_DEFAULT,false); // adjust openGL coordinate
    
    //-----------------setup music-----------------
    
        systemOffset = ofVec3f(ofGetWidth()/2, ofGetHeight()/2 + 10.0, 0.0); // system offset relative to center point of window
        nMusic = 9;
    
        //------------load music randomly------------
    
        int i = int(ofRandom(nMusic));
        mPlayer.load("music_"+ofToString(i)+".mp3");
        musicSystem.initialize(ofVec3f(0,0,0), moveArea_height, mPlayer);
        musicSystem.setStroke(5);
    
        mGravity = ofVec3f(0.f, 0.02f, 0.02f); // set particle system gravity
    
    //------------setup kinect-------------
    
        ofSetLogLevel(OF_LOG_VERBOSE);
        kinect.setRegistration();
        kinect.init(false,true,false);
        kinect.open();
        kinect.setDepthClipping(500,3000);
        kinect.setCameraTiltAngle(-5);
        colorImg.allocate(kinect.width, kinect.height);
        grayImg.allocate(kinect.width, kinect.height);
        grayBg.allocate(kinect.width, kinect.height);
        grayDiff.allocate(kinect.width, kinect.height);
    
        bLearnBackground = true;
        threshold = 50;

        kinectOffset = ofVec3f(-kinect.width/2, -kinect.height/2, 0);
    
    //--------------setup Mesh----------------
    
        ofSetVerticalSync(true);
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
        glEnable(GL_POINT_SMOOTH);
        glPointSize(2);
        bDrawMesh = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //-------particle system------------
    
        for (int i = 0; i < mSystem.size(); i++){
            mSystem[i].update(mGravity); //apply gravity all particles
        }
    
    //--------update kinect----------
    
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
 
        contourFinder.findContours(grayDiff, 0, kinect.width*kinect.height, 4, true);
        cout <<contourFinder.nBlobs <<endl;
    
        //---------calculate blobs center position, push that point
    
        for(int i = 0; i < contourFinder.nBlobs; i++){
            ofVec2f tempVec2f = contourFinder.blobs[i].boundingRect.getCenter();
            float tempZ = kinect.getDistanceAt(tempVec2f); //get depth value of specific point
            tempVec2f.y = 480-tempVec2f.y;
        
            
            float z;
            if(tempZ>1000 && tempZ<3000)
                z = ofMap(tempZ, 1000, 3000, -200,0);
            if(tempZ >5000 && z <9000)
                z = ofMap(tempZ, 5000, 9000, 0,200);

            if(brightestPoint.size()<contourFinder.nBlobs)
                brightestPoint.push_back(ofVec3f(tempVec2f.x,tempVec2f.y,z)+kinectOffset);
            else
                brightestPoint.clear();

        }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //information on screen-------------
    
    
        ofBackgroundGradient(ofColor(50), ofColor(0));
        ofSetColor(255);

        ofDrawBitmapString("find "+ofToString(contourFinder.nBlobs)+" blobs", 30, 40);
    
        //--------information about blobs---------
        for (int i = 0; i < brightestPoint.size(); i++) {
                    ofDrawBitmapString("brightnestPoin["+ofToString(i)+"]: "+ofToString(brightestPoint[i].x)+", "+ofToString(brightestPoint[i].y)+", "+ofToString(brightestPoint[i].z)+"), distance is: "+ofToString(kinect.getDistanceAt(brightestPoint[i].x,brightestPoint[i].y))+" [point.z]: "+ofToString(brightestPoint[i].z),30, 100+i*15);
                }
    
    
    //--------draw kinect image for test-----
        contourFinder.draw();
    
    
    
    //the following part are translate the coordinations with systemOffset
    //-----------translate coordination---------------------
        ofPushMatrix();
        ofTranslate(systemOffset);
      
        //------tracking point and light cooresponding arc of the circle in 3d space---------------------

        if(brightestPoint.size()>0){
            for(int i = 0; i<brightestPoint.size();i++){
                trackPoint(brightestPoint[i]);
            }
        }
    
        camGraphic.begin();
        //-----draw mouse particle system in 2d ------------------
    
        for (int i = 0; i < mSystem.size(); i++){
            mSystem[i].draw();
        }
        ofSetColor(200, 200, 200);
    
    

        //------draw line---------------------
    
        nPoints = brightestPoint.size();
    
    
            if(nPoints == 1){
            line1.begin();
            line1.addVertex(brightestPoint[0]);
//            ofDrawBitmapString("brightnestPoin[0]: "+ofToString(brightestPoint[0].x)+", "+ofToString(brightestPoint[0].y)+", "+ofToString(brightestPoint[0].z),brightestPoint[0].x, brightestPoint[0].y);
        }

        if(!bDrawMesh)
            line1.draw();
    
        if(bDrawMesh){
            
            mesh.drawWireframe();
            mesh.drawVertices();
            ofSetColor(200, 200, 200, 70);
            mesh.drawFaces();
        }
    
        camGraphic.end();
   
   
    
    ofPopMatrix();
    
    
    //--------------draw the ground plane------------
    cam.begin();
    cam.disableMouseInput();
    musicSystem.drawSpace();
    cam.end();

    
}


//--------------------------------------------------------------
void ofApp::trackPoint(ofVec3f pointPos){
      ofFill();
    if(mPlayer.isPlaying()){
//              ofDrawBitmapString("track point: "+ofToString(pointPos.x)+", "+ofToString(pointPos.y)+", "+ofToString(pointPos.z),pointPos.x, pointPos.y);
    
        
        //create a new particle system after click
            ParticleSystem system = ParticleSystem(ofVec3f (pointPos.x, pointPos.y, pointPos.z));
            mSystem.push_back(system);

        
        
    //check mouse position to trigger flash strock-------------
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
        case OF_KEY_RETURN:
            mPlayer.play();
            break;
        case OF_KEY_UP:{
            int i = int(ofRandom(nMusic));
            mPlayer.load("music_"+ofToString(i)+".mp3");
            mPlayer.play();
        }
        case 's':{
            mesh.addVertices(line1.getVertices());
            mesh.save("userMovement");
            mesh.save("userMovement.ply");
            line1.clear();
            bDrawMesh = true;
        
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
