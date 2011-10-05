#ifndef _GL_WARPER
#define _GL_WARPER

#define OF_ADDON_USING_OFOPENCV

#include "ofMain.h"


/****
 Base on warping example by Theo Watson.
 modified and extended by Roy Macdonald.
 
 ***//

class ofxGLWarper{
	
public:
		
	void setup();
	void draw();
		
	void mouseDragged(ofMouseEventArgs &args);
	void mousePressed(ofMouseEventArgs &args);
	void mouseReleased(ofMouseEventArgs &args);
	void mouseMoved(ofMouseEventArgs &args);
	void processMatrices();
	
	void activate();
	void deactivate();
	bool isActive();
	
private:
	bool active;
	ofPoint corners[4];
	int whichCorner;
	GLfloat myMatrix[16];
};

#endif	

