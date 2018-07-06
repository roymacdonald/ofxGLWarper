#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	 
	//we run at 60 fps!
    warper.setup(); //initializates ofxGLWarper
	warper.activate();// this allows ofxGLWarper to automatically listen to the mouse and keyboard input and updates automatically it's matrixes.
	ofSetVerticalSync(true);
	
	//loads load in some truetype fonts
	ttf.load("type/mono.ttf", 22);
	ttf2.load("type/mono.ttf", 14);

	
	//lets load a test image too
	img.load("image.jpg");
	
	
	//lets setup some stupid particles
	for(int i = 0; i < 80; i++){
		balls[i].setup(ofRandom(10, ofGetWidth() - 10), ofRandom(10, ofGetHeight()-10), ofRandom(5, 25));
		balls[i].vel.x = ofRandom(1.5, 2.8);
		balls[i].vel.y = ofRandom(1.5, 2.8);
    }

    ofBackground(20, 20, 20);
	
}

//--------------------------------------------------------------
void ofApp::update(){	
	
	for(int i = 0; i < 80; i++){
		balls[i].update(ofGetWidth(), ofGetHeight());
	}
	
}
//--------------------------------------------------------------
void ofApp::draw(){
	
	warper.begin();	///all the things that are drawn AFTER begin and BEFORE end ofxGLWarper's methods are afected by ofxGLWarper.
					/// Todos los elementos dibujados DESPUES de el metodo begin y ANTES de el metodo end de ofxGLWarper estar‡n afectados por ofxGLWarper.
	
	// -- NOW LETS DRAW!!!!!!  -----
	
	//test an image
	
	ofSetHexColor(0xAAAAAA);
	img.draw(70, 120);

	//lets draw a bounding box
	ofNoFill();
	ofSetHexColor(0xFF00FF);
	ofDrawRectangle(1, 1, ofGetWidth()-2, ofGetHeight()-2);
  
	
	//our particles
 	ofEnableAlphaBlending();
	ofSetColor(255, 0, 255, 130);
	ofFill();
	for(int i = 0; i < 40; i++)balls[i].draw();
 	ofDisableAlphaBlending();
	
	//some text
	ofSetHexColor(0x000000);
	ttf.drawString("grab corners to warp openGL graphics", 28, 33);

	ofSetHexColor(0xFF00FF);
	ttf.drawString("grab corners to warp openGL graphics", 30, 30);
	
	ofSetHexColor(0x000000);
	ttf2.drawString("warps images nicely too!", 78, 433);

	ofSetHexColor(0xFF00FF);
	ttf2.drawString("warps images nicely too!", 80, 430);
	warper.end();// feel free to move this to another position within de draw chain to see how this affects the drawing.
	
	ofSetColor(255);
	ofDrawBitmapString("Press the space bar to activate/deactivate the warpers\nPress 's' to save to XML file\nPress 'l' to load from a XML file.", 50, ofGetHeight() -70);
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
	case 's': // press 's' to save the warp coordinates to an XML file.
		warper.save("warpConfig.xml");
		break;
	case 'l':// press 'l' to load the warp coordinates from an XML file.
		warper.load("warpConfig.xml");	
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
