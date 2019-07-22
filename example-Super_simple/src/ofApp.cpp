#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //lets load a test image first
    img.load("image.jpg");

	//we run at 60 fps!
    warper.setup(70, 120, img.getWidth(), img.getHeight()); //initializates ofxGLWarper
	warper.activate();// this allows ofxGLWarper to automatically listen to the mouse and keyboard input and updates automatically it's matrixes.

    ofBackground(20, 20, 20);
	warper.drawSettings.bDrawRectangle = true; // default: true. Check drawSettings options for customization.
}

//--------------------------------------------------------------
void ofApp::update(){

	
}
//--------------------------------------------------------------
void ofApp::draw(){

    warper.begin();	///all the things that are drawn AFTER ofxGLWarper's begin method are afected by it.
					///el metodo draw de ofxGLWarper afecta a todos los elementos dibujados despues si.
	// -- NOW LETS DRAW!!!!!!  -----
	
	img.draw(70, 120);

	warper.end();
	
	stringstream ss;
	ss <<"Just drag the corners of the image for it to warp." << endl;
	ss << "Press and hold the shift key, then clic and drag over the image to move it.";
	ofDrawBitmapString(ss.str(), 20, 100);
	
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
