#include "testApp.h"
#include "stdio.h"

//--------------------------------------------------------------
void testApp::setup(){	 
	//we run at 60 fps!
	warper.setup(); //initializates ofxGLWarper
	warper.activate();// this allows ofxGLWarper to automatically listen to the mouse and keyboard input and updates automatically it's matrixes.
	ofSetVerticalSync(true);
	
	//loads load in some truetype fonts
	ttf.loadFont("type/frabk.ttf", 22);
	ttf2.loadFont("type/frabk.ttf", 14);

	
	//lets load a test image too
	img.loadImage("ofTheo.jpg");
	
	//lets setup some stupid particles
		
	
}

//--------------------------------------------------------------
void testApp::update(){	

	ofBackground(20, 20, 20);
	ofSetWindowShape(800, 600);	
}
//--------------------------------------------------------------
void testApp::draw(){

	warper.draw();	///all the things that are drawn AFTER ofxGLWarper's draw method are afected by it.
					///el metodo draw de ofxGLWarper afecta a todos los elementos dibujados despues si.
	
	// -- NOW LETS DRAW!!!!!!  -----
	
	//test an image
	ofSetHexColor(0xAAAAAA);
	img.draw(70, 120);

	//lets draw a bounding box
	ofNoFill();
	ofSetHexColor(0xFF00FF);
	ofRect(1, 1, ofGetWidth()-2, ofGetHeight()-2);
  

	
	//some text
	ofSetHexColor(0x000000);
	ttf.drawString("grab corners to warp openGL graphics", 28, 33);

	ofSetHexColor(0xFF00FF);
	ttf.drawString("grab corners to warp openGL graphics", 30, 30);
	
	ofSetHexColor(0x000000);
	ttf2.drawString("warps images nicely too!", 78, 433);

	ofSetHexColor(0xFF00FF);
	ttf2.drawString("warps images nicely too!", 80, 430);
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
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
void testApp::keyReleased(int key){}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){}
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){}
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){}
//--------------------------------------------------------------
void testApp::mouseReleased(){}
