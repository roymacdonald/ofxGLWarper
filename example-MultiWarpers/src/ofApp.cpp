#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	 
	img.load("image.jpg");
    for (unsigned int i =0; i<NUM_WARPERS; i++){
        warpers.push_back(ofxGLWarper());
        warpers.back().setup((i%2)*img.getWidth(),floor(float(i)/2)*img.getHeight(),img.getWidth(), img.getHeight());
		warpers.back().drawSettings.bDrawRectangle = true; // default: true. Check drawSettings options for customization.
    }
    //ofSetVerticalSync(true); // is enabled by default since OF 0.8
	
	activeWarper =-1;

    ofBackground(20, 20, 20);
}

//--------------------------------------------------------------
void ofApp::update(){	

	
}
//--------------------------------------------------------------
void ofApp::draw(){
    for (unsigned int i =0; i<NUM_WARPERS; i++){
        warpers[i].begin();
        img.draw((i%2)*img.getWidth(),floor(float(i)/2)*img.getHeight());
        warpers[i].end();
	}
    ofDrawBitmapString("Press keys 1 to 4 to toggle each warper", 20, 50);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  bool bDeactivateOthers = false;
    switch (key) {
        case '1':
            activeWarper=0;
            warpers[0].toggleActive();
            bDeactivateOthers =true;
            break;
        case '2':
            activeWarper=1;
            warpers[1].toggleActive();
            bDeactivateOthers =true;
            break;
        case '3':
            activeWarper=2;        
            bDeactivateOthers =true;
            warpers[2].toggleActive();
            break;
        case '4':
            activeWarper=3;        
            bDeactivateOthers =true;
            warpers[3].toggleActive();
            break; 
            //*/
        default:
            //here are two methods of saving:
            //the first one saves multiple warpers in the same file, but you have to manage an ofXml object.
            if (key == 's'){
                for (unsigned int var = 0; var < NUM_WARPERS; ++var) {
                    warpers[var].saveToXml(XML, "warper" + ofToString(var));
                }
                XML.save("saveFile.xml");
            }
            if (key == 'l'){
                XML.load("saveFile.xml");
                for (unsigned int var = 0; var < NUM_WARPERS; ++var) {
                    warpers[var].loadFromXml(XML, "warper" + ofToString(var));
                }
            }
            //the second one is one file per save, but you don't have to manage an ofXml object.
            if (key == 'S'){
                for (unsigned int var = 0; var < NUM_WARPERS; ++var) {
                warpers[var].save("warper" + ofToString(var) + ".xml");
                }
            }
            if (key == 'L'){
                for (unsigned int var = 0; var < NUM_WARPERS; ++var) {
                warpers[var].load("warper" + ofToString(var) + ".xml");
                }
            }
            break;
    }
    
    if (bDeactivateOthers) {
        for (unsigned int i =0; i<NUM_WARPERS; i++){
            if (i!=activeWarper) {
                warpers[i].deactivate();
            }
        }
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
