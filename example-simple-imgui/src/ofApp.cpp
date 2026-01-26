#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //lets load a test image first
    img.load("image.jpg");

	//we run at 60 fps!
    warper.setup(70, 120, img.getWidth(), img.getHeight()); //initializates ofxGLWarper

    ofBackground(20, 20, 20);
	warper.drawSettings.bDrawRectangle = true; // default: true. Check drawSettings options for customization.
    
    gui.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

	
}
//--------------------------------------------------------------
void ofApp::draw(){

    if(warper.isEnabled()) warper.begin();	///all the things that are drawn AFTER ofxGLWarper's begin method are afected by it.
					///el metodo draw de ofxGLWarper afecta a todos los elementos dibujados despues si.
	// -- NOW LETS DRAW!!!!!!  -----
	
	img.draw(70, 120);

    if(warper.isEnabled()) warper.end();
	
    gui.begin();
    // In a menu
    if(ImGui::BeginMainMenuBar()){
        if(ImGui::BeginMenu("ofxGLWarper")){
            warper.drawImGuiWidget();
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    // In a window
    if(ImGui::Begin("ofxGLWarperWindow")){
        ImGui::TextWrapped("To edit the warping, you can either\n - Use ImGui\n - Use the edit mode\n");
        ImGui::TextDisabled("Note that both don't work well together.");
        ImGui::Separator();
        warper.drawImGuiWidget();
    }
    ImGui::End();
    gui.end();
	
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
switch (key) {
	case ' ':
		if (warper.isActive()) {
			warper.deactivate(); //once you are done with the Wrapping you should call this method, so it realeses the keyboard and mouse and stop processing the transformation matrixes.
								 // this will reduce the amount of precessing needed.
		}else {
			warper.activate();
		}

		break;
	default:
		break;
}
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::mouseReleased(){}
