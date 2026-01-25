#ifdef ofxAddons_ENABLE_IMGUI
#ifndef _GL_WARPERIMGUI
#define _GL_WARPERIMGUI
#include "ofxGLWarper.h"
#include "ofMain.h"

// ofxGLWarperImGui by Daan de Lange

class ofxGLWarperImGui : public ofxGLWarper {
	
public:
    
    ~ofxGLWarperImGui();

	bool isEnabled() const;
	void drawImGuiWidget(ofRectangle resetDimension = ofGetWindowRect());
	bool bEnableQuadWarper = false;
};

#endif // _GL_WARPERIMGUI
#endif // ofxAddons_ENABLE_IMGUI
