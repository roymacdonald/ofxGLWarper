#pragma once

#include "ofMain.h"
#include "ofxGlWarper.h"

class testApp : public ofBaseApp{
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
