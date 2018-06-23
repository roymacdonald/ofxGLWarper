#pragma once

#include "ofMain.h"
#include "ofxGLWarper.h"

//stupid ball class 
class ball{
	
public:
	ball(){
		
	}
	
	void setup(float x, float y, float r){
		pos.x = x;
		pos.y = y;
		pos.z = r;
		
		vel.x = 2.0;
		vel.y = 1.6;
	}	
	
	void update(int width, int height){
		if( pos.x + pos.z >= width){
			pos.x = width - pos.z;
			vel.x *= -1;
		}else if( pos.x - pos.z <= 0){
			pos.x = pos.z;
			vel.x *= -1;
		}
		
		if( pos.y + pos.z >= height){
			pos.y = height - pos.z;
			vel.y *= -1;
		}else if( pos.y - pos.z <= 0){
			pos.y = pos.z;
			vel.y *= -1;
		}
		
		pos.x += vel.x;
		pos.y += vel.y;
	}
	
	void draw(){	
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofDrawCircle(pos.x, pos.y,  pos.z);
		ofSetRectMode(OF_RECTMODE_CORNER);			
	}
	
	ofPoint pos;
	ofPoint vel;
	
};

class ofApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
		
		ofTrueTypeFont ttf;
		ofTrueTypeFont ttf2;
		
		ofxGLWarper warper;
	
		ofImage img;
	
	ball balls[80];
		
};


