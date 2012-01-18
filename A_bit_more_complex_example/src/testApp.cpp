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
	for(int i = 0; i < 80; i++){
		balls[i].setup(ofRandom(10, ofGetWidth() - 10), ofRandom(10, ofGetHeight()-10), ofRandom(5, 25));
		balls[i].vel.x = ofRandom(1.5, 2.8);
		balls[i].vel.y = ofRandom(1.5, 2.8);
	}	
	
}

//--------------------------------------------------------------
void testApp::update(){	

	ofBackground(20, 20, 20);
	ofSetWindowShape(800, 600);
	
	for(int i = 0; i < 80; i++){
		balls[i].update(ofGetWidth(), ofGetHeight());
	}
	
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
