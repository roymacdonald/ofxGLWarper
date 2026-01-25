#pragma once

#include "ofMain.h"
#include "ofxGLWarperImGui.h"
#include "ofxImGui.h"

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

        ofxGLWarperImGui warper;
        ofxImGui::Gui gui;
        ofImage img;
};


