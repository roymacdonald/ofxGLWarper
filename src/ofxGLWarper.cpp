#include "ofxGLWarper.h"
#include "stdio.h"
#include "cv.h"




//--------------------------------------------------------------
void ofxGLWarper::setup(){	 
	//we run at 60 fps!
	//ofSetVerticalSync(true);
	
	corners[0].x = 0.0;
	corners[0].y = 0.0;

	corners[1].x = 1.0;
	corners[1].y = 0.0;

	corners[2].x = 1.0;
	corners[2].y = 1.0;
	
	corners[3].x = 0.0;
	corners[3].y = 1.0;
	
	active=false;
	
	for(int i = 0; i < 16; i++){
		if(i % 5 != 0) myMatrix[i] = 0.0;
		else myMatrix[i] = 1.0;
	}
	
}
//--------------------------------------------------------------
bool ofxGLWarper::isActive(){
	return active;
}
//--------------------------------------------------------------
void ofxGLWarper::activate(){
	ofRegisterMouseEvents(this);
	active=true;
}
//--------------------------------------------------------------
void ofxGLWarper::deactivate(){
	ofUnregisterMouseEvents(this);
	active=false;
}
//--------------------------------------------------------------
void ofxGLWarper::processMatrices(){
	//we set it to the default - 0 translation
	//and 1.0 scale for x y z and w
	for(int i = 0; i < 16; i++){
		if(i % 5 != 0) myMatrix[i] = 0.0;
		else myMatrix[i] = 1.0;
	}
	
	//we need our points as opencv points
	//be nice to do this without opencv?
	CvPoint2D32f cvsrc[4];
	CvPoint2D32f cvdst[4];	
	
	//we set the warp coordinates
	//source coordinates as the dimensions of our window
	cvsrc[0].x = 0;
	cvsrc[0].y = 0;
	cvsrc[1].x = ofGetWidth();
	cvsrc[1].y = 0;
	cvsrc[2].x = ofGetWidth();
	cvsrc[2].y = ofGetHeight();
	cvsrc[3].x = 0;
	cvsrc[3].y = ofGetHeight();			
	
	//corners are in 0.0 - 1.0 range
	//so we scale up so that they are at the window's scale
	for(int i = 0; i < 4; i++){
		cvdst[i].x = corners[i].x  * (float)ofGetWidth();
		cvdst[i].y = corners[i].y * (float) ofGetHeight();
	}
	
	//we create a matrix that will store the results
	//from openCV - this is a 3x3 2D matrix that is
	//row ordered
	CvMat * translate = cvCreateMat(3,3,CV_32FC1);
	
	//this is the slightly easier - but supposidly less
	//accurate warping method 
	//cvWarpPerspectiveQMatrix(cvsrc, cvdst, translate); 
	
	
	//for the more accurate method we need to create
	//a couple of matrixes that just act as containers
	//to store our points  - the nice thing with this 
	//method is you can give it more than four points!
	
	CvMat* src_mat = cvCreateMat( 4, 2, CV_32FC1 );
	CvMat* dst_mat = cvCreateMat( 4, 2, CV_32FC1 );
	
	//copy our points into the matrixes
	cvSetData( src_mat, cvsrc, sizeof(CvPoint2D32f));
	cvSetData( dst_mat, cvdst, sizeof(CvPoint2D32f));
	
	//figure out the warping!
	//warning - older versions of openCV had a bug
	//in this function.
	cvFindHomography(src_mat, dst_mat, translate);
	
	//get the matrix as a list of floats
	float *matrix = translate->data.fl;
	
	
	//we need to copy these values
	//from the 3x3 2D openCV matrix which is row ordered
	//
	// ie:   [0][1][2] x
	//       [3][4][5] y
	//       [6][7][8] w
	
	//to openGL's 4x4 3D column ordered matrix
	//        x  y  z  w   
	// ie:   [0][3][ ][6]
	//       [1][4][ ][7]
	//		 [ ][ ][ ][ ]
	//       [2][5][ ][9]
	//       
	
	myMatrix[0]		= matrix[0];
	myMatrix[4]		= matrix[1];
	myMatrix[12]	= matrix[2];
	
	myMatrix[1]		= matrix[3];
	myMatrix[5]		= matrix[4];
	myMatrix[13]	= matrix[5];	
	
	myMatrix[3]		= matrix[6];
	myMatrix[7]		= matrix[7];
	myMatrix[15]	= matrix[8];	
	

}
//--------------------------------------------------------------
void ofxGLWarper::draw(){
	if (active) {
		processMatrices();
	}
	glMultMatrixf(myMatrix);
}

//--------------------------------------------------------------
void ofxGLWarper::mouseDragged(ofMouseEventArgs &args){

		float scaleX = (float)args.x / ofGetWidth();
		float scaleY = (float)args.y / ofGetHeight();
		
		if(whichCorner >= 0){
			corners[whichCorner].x = scaleX;
			corners[whichCorner].y = scaleY;			
		}
}

//--------------------------------------------------------------
void ofxGLWarper::mousePressed(ofMouseEventArgs &args){
	
	float smallestDist = 1.0;
	whichCorner = -1;

	for(int i = 0; i < 4; i++){
		float distx = corners[i].x - (float)args.x/ofGetWidth();
		float disty = corners[i].y - (float)args.y/ofGetHeight();
		float dist  = sqrt( distx * distx + disty * disty);
		
		if(dist < smallestDist && dist < 0.1){
			whichCorner = i;
			smallestDist = dist;
			cout << "Which corner: " << whichCorner <<endl;
		}
	}
}
//--------------------------------------------------------------
void ofxGLWarper::mouseReleased(ofMouseEventArgs &args){
	whichCorner = -1;
}
//--------------------------------------------------------------
void ofxGLWarper::mouseMoved(ofMouseEventArgs &args){
	whichCorner = -1;
}