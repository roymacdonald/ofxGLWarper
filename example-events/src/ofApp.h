#pragma once

#include "ofMain.h"
#include "ofxGLWarper.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    void onCornerChange(const void * sender, glm::vec2 &v);
    
    ofxGLWarper warper;
    ofImage image;
    
    glm::vec2 TLPosition, TRPosition, BLPosition, BRPosition;

    float sw, sh, iw, ih;
};
