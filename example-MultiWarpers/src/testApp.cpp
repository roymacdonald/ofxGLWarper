#include "testApp.h"
#include "stdio.h"

//--------------------------------------------------------------
void testApp::setup(){	 
	img.loadImage("image.jpg");
	for (int i =0; i<NUM_WARPERS; i++){
        warpers.push_back(ofxGLWarper());
        warpers.back().setup((i%2)*img.width,floor(float(i)/2)*img.height,img.width, img.height); 
       //warpers.back().activate();
    }
    ofSetVerticalSync(true);
	
	activeWarper =-1;
}

//--------------------------------------------------------------
void testApp::update(){	
	ofBackground(20, 20, 20);
	
}
//--------------------------------------------------------------
void testApp::draw(){
    for (int i =0; i<NUM_WARPERS; i++){
        warpers[i].begin();	
        warpers[i].draw(); 
        img.draw((i%2)*img.width,floor(float(i)/2)*img.height);
        warpers[i].draw();
        warpers[i].end();
	}
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
  bool bDeactivateOthers = false;
    switch (key) {
        case '1':
            activeWarper=0;
            warpers[0].toogleActive();
            bDeactivateOthers =true;
            break;
            //*
        case '2':
            activeWarper=1;
            warpers[1].toogleActive();
            bDeactivateOthers =true;
            break;
        case '3':
            activeWarper=2;        
            bDeactivateOthers =true;
            warpers[2].toogleActive();
            break;
        case '4':
            activeWarper=3;        
            bDeactivateOthers =true;
            warpers[3].toogleActive();
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
void testApp::keyReleased(int key){}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){}
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){}
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){}
//--------------------------------------------------------------
void testApp::mouseReleased(){}
