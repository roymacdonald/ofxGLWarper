#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    image.load("image.jpg");
    warper.setup(0,0,image.getWidth(),image.getHeight());
    warper.activate();
    
    // position the image in the center of the screen
    // screen size
    sw = ofGetWidth();
    sh = ofGetHeight();
    // image size
    iw = image.getWidth();
    ih = image.getHeight();
    
    TLPosition = glm::vec2(sw/2 - iw/2, sh/2 - ih/2);
    TRPosition = glm::vec2(sw/2 + iw/2, sh/2 - ih/2);
    BLPosition = glm::vec2(sw/2 - iw/2, sh/2 + ih/2);
    BRPosition = glm::vec2(sw/2 + iw/2, sh/2 + ih/2);
    
    warper.setCorner(ofxGLWarper::TOP_LEFT, TLPosition);
    warper.setCorner(ofxGLWarper::TOP_RIGHT, TRPosition);
    warper.setCorner(ofxGLWarper::BOTTOM_LEFT, BLPosition);
    warper.setCorner(ofxGLWarper::BOTTOM_RIGHT, BRPosition);
    //alternatively, this works the same:
    // warper.setAllCorners(TLPosition, TRPosition, BLPosition, BRPosition);
    
    // start listening to corner events, the function is only called if the value changed.
    warper.corners[0].addListener(this, &ofApp::onCornerChange);
    warper.corners[1].addListener(this, &ofApp::onCornerChange);
    warper.corners[2].addListener(this, &ofApp::onCornerChange);
    warper.corners[3].addListener(this, &ofApp::onCornerChange);
	
	warper.drawSettings.bDrawRectangle = false; // default: true. Check drawSettings options for customization.

}

//--------------------------------------------------------------
void ofApp::update(){
    // move the TOP_LEFT corner via code
    glm::vec2 newPosition = glm::vec2(sw/2 - iw/2, sh/2 - ih/2);
    newPosition += glm::vec2(50,50) * sin(ofGetElapsedTimef());
    warper.setCorner(ofxGLWarper::TOP_LEFT, newPosition);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(120,120,120), ofColor(60,60,60));
    
    ofDrawBitmapString("The 'top left' corner is controlled by code.\nAll the other corners are controlled by the mouse.", 50,50);
    warper.begin();
    image.draw(0, 0);
    warper.end();
    
    ofDrawBitmapString("The circles have their position updated everytime\nthe warper triggers a change event.", 50,100);    
    ofDrawCircle(TLPosition, 15);
    ofDrawCircle(TRPosition, 15);
    ofDrawCircle(BLPosition, 15);
    ofDrawCircle(BRPosition, 15);

}

//--------------------------------------------------------------
void ofApp::onCornerChange(const void * sender, glm::vec2 &v){
    if (sender == &warper.corners[ofxGLWarper::TOP_LEFT]){
        TLPosition = v;
    }else if (sender == &warper.corners[ofxGLWarper::TOP_RIGHT]){
        TRPosition = v;
    }else if (sender == &warper.corners[ofxGLWarper::BOTTOM_LEFT]){
        BLPosition = v;
    }else if (sender == &warper.corners[ofxGLWarper::BOTTOM_RIGHT]){
        BRPosition = v;
    }
}

void ofApp::keyPressed(int key){

}
