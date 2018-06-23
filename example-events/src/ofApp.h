#pragma once

#include "ofMain.h"
#include "ofxGLWarper.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void onCornerChange(ofxGLWarper::CornerLocation &cornerLocation);
    
    ofxGLWarper warper;
    ofImage image;
    
    ofPoint TLPosition;
    ofPoint TRPosition;
    ofPoint BLPosition;
    ofPoint BRPosition;
};
