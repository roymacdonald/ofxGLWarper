#ifndef _GL_WARPER
#define _GL_WARPER
#include "stdio.h"
#include "cv.h"
#include "ofMain.h"
// ofxGLWarper by Roy Macdonald
// ... / ... 
//
// -- little changes made by Eloi Maduell - 12/2011
// -- thanks to Arturo and hv_francesco 
// added resolution of the quad in setup()
// changed draw() to begin() end() model
// added fromScreenToWarpCoord() and fromWarpToScreenCoord()

class ofxGLWarper{
	
public:
		
<<<<<<< HEAD
	void setup(int _resX, int _resY); //changed to have resolution as parameter for the quad
	void begin();	//changed name from draw to begin
	void end();		//added to make it easier to use, similar to ofFbo (begin,end)
		
=======
	void setup();
	void update();
	void draw();
	void end();
	void keyReleased(ofKeyEventArgs &args);
	void keyPressed(ofKeyEventArgs &args);
>>>>>>> nose
	void mouseDragged(ofMouseEventArgs &args);
	void mousePressed(ofMouseEventArgs &args);
	void mouseReleased(ofMouseEventArgs &args);
	void mouseMoved(ofMouseEventArgs &args);
	void processMatrices();
	
	void activate();
	void deactivate();
	bool isActive();
	bool setSourceMatrix(CvPoint2D32f *src, int length);
	
	ofVec4f		fromScreenToWarpCoord(float x,float y,float z);
	ofVec4f		fromWarpToScreenCoord(float x,float y,float z);

private:
	int  width; //width of the quad to work with
	int	 height; // height of the quad to work with
	bool active;
	ofPoint corners[4];
	int whichCorner, lastCorner;
	GLfloat myMatrix[16];
	CvPoint2D32f cvsrc[4];
	bool overCorner;
	ofVec2f normPix;
	bool isKeyShift;
	bool doProcess;
	ofVec2f inc;
};

#endif	

