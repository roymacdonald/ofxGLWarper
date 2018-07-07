#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    image.load("image.jpg");
    warper.setup(0,0,image.getWidth(),image.getHeight());
    warper.activate();
    
    // position the image in the center of the screen
    // screen size
    float sw = ofGetWidth();
    float sh = ofGetHeight();
    // image size
    float iw = image.getWidth();
    float ih = image.getHeight();
    
    TLPosition = ofPoint(sw/2 - iw/2, sh/2 - ih/2);
    TRPosition = ofPoint(sw/2 + iw/2, sh/2 - ih/2);
    BLPosition = ofPoint(sw/2 - iw/2, sh/2 + ih/2);
    BRPosition = ofPoint(sw/2 + iw/2, sh/2 + ih/2);
    
    warper.setCorner(ofxGLWarper::TOP_LEFT, TLPosition);
    warper.setCorner(ofxGLWarper::TOP_RIGHT, TRPosition);
    warper.setCorner(ofxGLWarper::BOTTOM_LEFT, BLPosition);
    warper.setCorner(ofxGLWarper::BOTTOM_RIGHT, BRPosition);

    //alternatively, this works the same:
    // warper.setAllCorners(TLPosition, TRPosition, BLPosition, BRPosition);
    
    // start listening to events
    ofAddListener(warper.changeEvent, this, &ofApp::onCornerChange);

}

//--------------------------------------------------------------
void ofApp::update(){
    // move the TOP_LEFT corner via code
    ofPoint newPosition = ofPoint(ofGetWidth()/2 - image.getWidth()/2, ofGetHeight()/2 - image.getHeight()/2);
    newPosition += ofPoint(50,50) * sin(ofGetElapsedTimef());    
    warper.setCorner(ofxGLWarper::TOP_LEFT, newPosition);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(120,120,120), ofColor(80,80,80));
    
    ofDrawBitmapString("The 'top left' corner is controlled by code.\nAll the other corners are controlled by the mouse.", 50,50);
    warper.begin();
    image.draw(0, 0);
    warper.end();
    
    ofDrawBitmapString("The circles have their position updated everytime\nthe warper triggers a change event.", 50,100);    
    ofDrawCircle(TLPosition, 15);
    ofDrawCircle(TRPosition, 15);
    ofDrawCircle(BLPosition, 15);
    ofDrawCircle(BRPosition, 15);

    //this is an alternative if you don't want to put a listener
//    ofDrawCircle(warper.getCorner(ofxGLWarper::TOP_LEFT), 15);
//    ofDrawCircle(warper.getCorner(ofxGLWarper::TOP_RIGHT), 15);
//    ofDrawCircle(warper.getCorner(ofxGLWarper::BOTTOM_LEFT), 15);
//    ofDrawCircle(warper.getCorner(ofxGLWarper::BOTTOM_RIGHT), 15);
}

//--------------------------------------------------------------
void ofApp::onCornerChange(ofxGLWarper::CornerLocation & cornerLocation){
    switch (cornerLocation) {
        case ofxGLWarper::TOP_LEFT:
            TLPosition = warper.getCorner(cornerLocation);
            break;
        case ofxGLWarper::TOP_RIGHT:
            TRPosition = warper.getCorner(cornerLocation);
            break;
        case ofxGLWarper::BOTTOM_LEFT:
            BLPosition = warper.getCorner(cornerLocation);
            break;
        case ofxGLWarper::BOTTOM_RIGHT:
            BRPosition = warper.getCorner(cornerLocation);
            break;

    }
}
