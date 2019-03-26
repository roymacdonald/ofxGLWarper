#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    img.load("image.jpg");

    warper.setup(100, 120, img.getWidth(), img.getHeight()); //initializates ofxGLWarper
    warper.setCornerSensibility(0.1f);
    warper.activate();// this allows ofxGLWarper to automatically listen to the mouse and keyboard input and updates automatically it's matrixes.

    //here are some example options:
    //warper.enableKeys(false);
    //warper.drawSettings.bDrawCorners = warper.drawSettings.bDrawRectangle = false;
    //warper.drawSettings.cornersColor = ofColor(0, 220, 35);
}

//--------------------------------------------------------------
void ofApp::update(){

}
//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(0,0,0), ofColor(20,200,0), OF_GRADIENT_BAR);
    warper.begin();
	
    img.draw(100, 120);

    warper.end();

    glm::vec4 A_pos = warper.fromScreenToWarpCoord(Rclick_pos);
    glm::vec4 B_pos = warper.fromWarpToScreenCoord(A_pos);



    // below is just texts and graphical helpers

    ofPushStyle();

    ofSetColor(80,250,250);
    ofDrawRectangle(A_pos.x, A_pos.y, 10, 10);
    ofDrawBitmapStringHighlight("A:fromScreenToWarpCoord(Right-click position)",A_pos.x + 15, A_pos.y);

    ofSetColor(250,250,250);
    ofDrawRectangle(B_pos.x, B_pos.y, 10, 10);
    ofDrawBitmapStringHighlight("B:fromWarpToScreenCoord(A)",B_pos.x + 15, B_pos.y + 15);

    ofPopStyle();

    std::string math_text = "A_pos = (" + ofToString(A_pos.x, 0) + "," + ofToString(A_pos.y, 0) + ") = warper.fromScreenToWarpCoord(Rclick_pos)";
    ofDrawBitmapStringHighlight(math_text,10, 20);
    math_text = "B_pos = (" + ofToString(B_pos.x, 0) + "," + ofToString(B_pos.y, 0) + ") = warper.fromWarpToScreenCoord( A_pos(" + ofToString(A_pos.x, 0) + "," + ofToString(A_pos.y, 0) + ") )";
    ofDrawBitmapStringHighlight(math_text,10, 45);
	
    ofDrawBitmapString("Hello, this example app is demonstrating the coordinates conversion functions.", 10, 65);
    ofDrawBitmapString("Drag the warper's corners to transform the image in space, and use your", 10, 80);
    ofDrawBitmapString("RIGHT-CLICK to select a new point, have fun and I wish you to understand those ;)", 10, 95);

    if (mouseXpoint > 65){
        ofDrawBitmapStringHighlight(ofToString(mouseXpoint) + "," + ofToString(mouseYpoint),mouseXpoint-60, mouseYpoint+10);
    } else {
        ofDrawBitmapStringHighlight(ofToString(mouseXpoint) + "," + ofToString(mouseYpoint),mouseXpoint, mouseYpoint);
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' '){warper.toggleActive();}
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){ mouseXpoint = x; mouseYpoint = y;}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){mouseXpoint = x; mouseYpoint = y;}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (button == 2){
        Rclick_pos.x = x;
        Rclick_pos.y = y;
    }
}
//--------------------------------------------------------------
void ofApp::mouseReleased(){}
