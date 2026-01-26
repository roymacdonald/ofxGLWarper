#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxGLWarperImGui.h"

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

        // Note: If your compiiler can't find the `ofxGLWarperImGui` type :
        // You need to add `ofxAddons_ENABLE_IMGUI` to your project settings !
        // (of0.12.0's PG doesn't add them correctly. of0.12.1 should be ok)
        ofxGLWarperImGui warper;
    
        ofxImGui::Gui gui;
        ofImage img;
};


