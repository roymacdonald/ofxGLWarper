#pragma once

#include "ofMain.h"
#include "ofxGLWarper.h"

class ofApp : public ofBaseApp{
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();

        ofxGLWarper warper;
        ofImage img;

        int mouseXpoint = 0;
        int mouseYpoint = 0;

        glm::vec4 Rclick_pos = glm::vec4(150, 150, 0, 0); // We have to use vec4 because warping needs 4 dimensions.
};


