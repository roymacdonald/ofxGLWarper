#include "ofApp.h"
#include "stdio.h"

//--------------------------------------------------------------
void ofApp::setup(){	 
	img.load("image.jpg");
	for (int i =0; i<NUM_WARPERS; i++){
        warpers.push_back(ofxGLWarper());
        warpers.back().setup((i%2)*img.getWidth(),floor(float(i)/2)*img.getHeight(),img.getWidth(), img.getHeight());
       //warpers.back().activate();
    }
    //ofSetVerticalSync(true); // is enabled by default since OF 0.8
	
	activeWarper =-1;

    ofBackground(20, 20, 20);
}

//--------------------------------------------------------------
void ofApp::update(){	

	
}
//--------------------------------------------------------------
void ofApp::draw(){
    for (int i =0; i<NUM_WARPERS; i++){
        warpers[i].begin();	
        warpers[i].draw(); 
        img.draw((i%2)*img.getWidth(),floor(float(i)/2)*img.getHeight());
        warpers[i].end();
	}
    ofDrawBitmapString("Press keys 1 to 4 to toggle each warper", 20, 50);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  bool bDeactivateOthers = false;
    switch (key) {
        case '1':
            activeWarper=0;
            warpers[0].toggleActive();
            bDeactivateOthers =true;
            break;
            //*
        case '2':
            activeWarper=1;
            warpers[1].toggleActive();
            bDeactivateOthers =true;
            break;
        case '3':
            activeWarper=2;        
            bDeactivateOthers =true;
            warpers[2].toggleActive();
            break;
        case '4':
            activeWarper=3;        
            bDeactivateOthers =true;
            warpers[3].toggleActive();
            break; 
            //*/
            default:
            break;
    }
    
    if (bDeactivateOthers) {
        for (int i =0; i<NUM_WARPERS; i++){
            if (i!=activeWarper) {
                warpers[i].deactivate();
            }
        }
    }
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::mouseReleased(){}
