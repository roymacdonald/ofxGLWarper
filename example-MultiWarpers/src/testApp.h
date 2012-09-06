#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxGLWarper.h"

#define NUM_WARPERS 4

class testApp : public ofSimpleApp{
	
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

		vector<ofxGLWarper> warpers;
	
		ofImage img;
    int activeWarper;
};

#endif	

