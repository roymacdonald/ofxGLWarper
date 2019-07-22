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
    enum CornerLocation{
        TOP_LEFT,
        TOP_RIGHT,
        BOTTOM_RIGHT,
        BOTTOM_LEFT
    };
    
    ~ofxGLWarper();
	void setup();		
	void setup(int _resX, int _resY); //changed to have resolution as parameter for the quad
	void setup(int _x, int _y, int _w, int _h);

    void reSetupWarped(int _x, int _y, int _w, int _h); // allows you to redefine base rectangle without losing the current warping.

    void draw();	// This is deprecated (included in end()). Please check the drawSettings structure below.
	void begin();	//changed name from draw to begin
	void end();		//added to make it easier to use, similar to ofFbo (begin,end)
		
	void mouseDragged(ofMouseEventArgs &args);
	void mousePressed(ofMouseEventArgs &args);
	void mouseReleased(ofMouseEventArgs &args);
    void mouseMoved(ofMouseEventArgs &args){}
    void mouseScrolled(ofMouseEventArgs &args){}
    void mouseEntered(ofMouseEventArgs &args){}
    void mouseExited(ofMouseEventArgs &args){}
    void keyPressed(ofKeyEventArgs &args);
	void keyReleased(ofKeyEventArgs &args);
	
    void processMatrices();

    void save(const string& saveFile = "warpConfig.xml");
    void load(const string& loadFile = "warpConfig.xml");

    void saveToXml(ofXml& XML, const string& warperID = "corners");
    void loadFromXml(ofXml& XML, const string& warperID = "corners");

    void toggleActive();
    void activate(bool bActivate = true);
    void deactivate();
    bool isActive();

    void enableKeys(bool k = true);
    void toggleKeys();
    void enableMouse(bool m = true);
    void toggleMouse();

    glm::vec4 fromScreenToWarpCoord(float x,float y,float z = 0);
    glm::vec4 fromScreenToWarpCoord(const glm::vec4 &position);
    glm::vec4 fromWarpToScreenCoord(float x,float y,float z = 0);
    glm::vec4 fromWarpToScreenCoord(const glm::vec4 &position);

    void selectCorner(CornerLocation cornerLocation);
    void setCorner(CornerLocation cornerLocation, const glm::vec2 &onScreenLocation);
    void setCorner(CornerLocation cornerLocation, float onScreenLocationX, float onScreenLocationY);
    void moveCorner(CornerLocation cornerLocation, const glm::vec2 &moveBy);
    void moveCorner(CornerLocation cornerLocation, float byX, float byY);
    glm::vec2 getCorner(CornerLocation cornerLocation);

    void setAllCorners(const glm::vec2 &top_left, const glm::vec2 &top_right, const glm::vec2 &bot_left, const glm::vec2 &bot_right);
    void moveAllCorners(const glm::vec2 &moveBy);
    void moveAllCorners(float byX, float byY);

	ofRectangle getBaseRectangle(); // gets you the rect used to setup
	bool getCornerIsSelected();
	CornerLocation getSelectedCornerLocation();

    void setCornerSensibility(float sensibility);
    float getCornerSensibility();

    ofParameter<glm::vec2> corners[4];

    struct drawSettings{
        bool bDrawCorners = true;
        bool bDrawRectangle = true;
        bool bForceDrawing = false; // Draws warper even if not active.
        ofColor selectedCornerColor = ofColor(255, 0, 0);
        ofColor cornersColor = ofColor(255, 255, 0);
        ofColor rectangleColor = ofColor(255, 255, 255);
    };
    drawSettings drawSettings;

private:
	ofPolyline cornersPoly;
	int x, y;
	int  width; //width of the quad to work with
	int	 height; // height of the quad to work with
    bool active = false;
    int selectedCorner;
	bool bMoveAll = false;
	glm::vec2 mousePressPos;
	
    glm::mat4 myMatrix;
    float cornerSensibility;
    bool cornerIsSelected;
    bool bUseKeys = false; // false before a setup
    bool bUseMouse = false; // false before a setup
};

#endif

