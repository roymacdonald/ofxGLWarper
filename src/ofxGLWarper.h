#ifndef _GL_WARPER
#define _GL_WARPER

#define OF_ADDON_USING_OFOPENCV

#include "ofMain.h"
#include "ofxXmlSettings.h"
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
    enum CornerLocation{
        TOP_LEFT = 0,
        TOP_RIGHT,
        BOTTOM_RIGHT,
        BOTTOM_LEFT
    };
    
    
	void setup();		
	void setup(int _resX, int _resY); //changed to have resolution as parameter for the quad
	void setup(int _x, int _y, int _w, int _h);
	void draw();	// nowthis method draw the bounding box for the warped elements. intended to be a visual aid.
	void begin();	//changed name from draw to begin
	void end();		//added to make it easier to use, similar to ofFbo (begin,end)
		
	void mouseDragged(ofMouseEventArgs &args);
	void mousePressed(ofMouseEventArgs &args);
	void mouseReleased(ofMouseEventArgs &args);
	void mouseMoved(ofMouseEventArgs &args);
    void keyPressed(ofKeyEventArgs &args);
    void keyReleased(ofKeyEventArgs &args);
	void processMatrices();
	
	void save(string saveFile = "warpConfig.xml");
	void load(string loadFile = "warpConfig.xml");
	
	void saveToXml(ofxXmlSettings& XML);
	void loadFromXml(ofxXmlSettings& XML);
	
    void toogleActive();
	void activate();
	void deactivate();
	bool isActive();
    
	void enableKeys(bool k = true);
    void toogleKeys();
    bool getUseKeys();
    void setUseKeys(bool use = true);
    
	ofVec4f	fromScreenToWarpCoord(float x,float y,float z);
	ofVec4f	fromWarpToScreenCoord(float x,float y,float z);
    
    void setCorner(CornerLocation cornerLocation, ofPoint screenLocation);
    ofPoint getCorner(CornerLocation cornerLocation);
        
    void setCornerSensibility(float sensibility);
    float getCornerSensibility();
    
    ofEvent<CornerLocation> changeEvent;

private:
	int x, y;
	int  width; //width of the quad to work with
	int	 height; // height of the quad to work with
	bool active;
	ofPoint corners[4];
	int whichCorner;
	GLfloat myMatrix[16];
    float cornerSensibility;
    bool cornerSelected;
    bool bUseKeys;
};

#endif	

