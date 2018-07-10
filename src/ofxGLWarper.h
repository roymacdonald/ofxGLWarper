#ifndef _GL_WARPER
#define _GL_WARPER

#include "ofMain.h"
// ofxGLWarper by Roy Macdonald
// ... / ... 
//
// -- little changes made by Eloi Maduell - 12/2011
// -- thanks to Arturo and hv_francesco 
// added resolution of the quad in setup()
// changed draw() to begin() end() model
// added fromScreenToWarpCoord() and fromWarpToScreenCoord()
// OpenCv dependency removed by Cyril Communal - 7/2018


class ofxGLWarper{
	
public:
    enum CornerID{
        TOP_LEFT,
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
    void mouseReleased(ofMouseEventArgs &args){}
    void mouseMoved(ofMouseEventArgs &args){}
    void mouseScrolled(ofMouseEventArgs &args){}
    void mouseEntered(ofMouseEventArgs &args){}
    void mouseExited(ofMouseEventArgs &args){}
    void keyPressed(ofKeyEventArgs &args);
    void keyReleased(ofKeyEventArgs &args){}
    
    void processMatrices();

    void save(const string& saveFile = "warpConfig.xml");
    void load(const string& loadFile = "warpConfig.xml");

    void saveToXml(ofXml& XML, const string& warperID = "corners");
    void loadFromXml(ofXml& XML, const string& warperID = "corners");

    void toggleActive();
    void activate();
    void deactivate();
    bool isActive();

    void enableKeys(bool k = true);
    void toggleKeys();

    glm::vec4 fromScreenToWarpCoord(float x,float y,float z = 0);
    glm::vec4 fromWarpToScreenCoord(float x,float y,float z = 0);

    void selectCorner(CornerID cornerID);
    void setCorner(CornerID cornerID, glm::vec2 &onScreenLocation);
    void setCorner(CornerID cornerID, float onScreenLocationX, float onScreenLocationY);
    void moveCorner(CornerID cornerID, glm::vec2 &moveBy);
    void moveCorner(CornerID cornerID, float byX, float byY);
    glm::vec2 getCorner(CornerID cornerID);

    void setAllCorners(glm::vec2 &top_left, glm::vec2 &top_right, glm::vec2 &bot_left, glm::vec2 &bot_right);
    void moveSurface(glm::vec2 &moveBy);
    void moveSurface(float byX, float byY);

    void setCornerSensibility(float sensibility);
    float getCornerSensibility();

    ofParameter<glm::vec2> corners[4];

private:
	int x, y;
	int  width; //width of the quad to work with
	int	 height; // height of the quad to work with
	bool active;
    int selectedCorner;
    glm::mat4 myMatrix;
    float cornerSensibility;
    bool cornerIsSelected;
    bool bUseKeys;
};

#endif	

