#include "ofxGLWarper.h"
#include "stdio.h"
#include "cv.h"


//--------------------------------------------------------------
void ofxGLWarper::setup(){
	setup(ofGetWidth(), ofGetHeight());
}
//--------------------------------------------------------------
void ofxGLWarper::setup(int _resX, int _resY){	 
	setup(0,0,_resX,_resY);	
}
//--------------------------------------------------------------
void ofxGLWarper::setup(int _x, int _y, int _w, int _h){
	ofUnregisterMouseEvents(this);
	
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
	x=_x;
	y=_y;
	width=_w;
	height=_h;
	whichCorner = -1;
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
	cvsrc[0].x = x;
	cvsrc[0].y = y;
	cvsrc[1].x = x+width;
	cvsrc[1].y = y;
	cvsrc[2].x = x+width;
	cvsrc[2].y = y+height;
	cvsrc[3].x = x;
	cvsrc[3].y = y+height;			
	
	//corners are in 0.0 - 1.0 range
	//so we scale up so that they are at the window's scale
	for(int i = 0; i < 4; i++){
		cvdst[i].x = corners[i].x  * (float)width;
		cvdst[i].y = corners[i].y * (float)height;
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
		ofPushStyle();
		ofSetColor(255, 255, 255);
		ofNoFill();
		ofRect(x, y, width, height);
		ofPopStyle();
	}
}

//--------------------------------------------------------------
void ofxGLWarper::begin(){
	if (active) {
		processMatrices();
	}
	glPushMatrix();
	glMultMatrixf(myMatrix);
}


//--------------------------------------------------------------
void ofxGLWarper::end(){
	glPopMatrix();
}
//--------------------------------------------------------------
void ofxGLWarper::save(string saveFile){
	ofxXmlSettings XML;
	XML.clear();
	XML.addTag("corners");
	XML.pushTag("corners");
	
	
	for(int i =0; i<4; i++){
		int t = XML.addTag("corner");
		XML.setValue("corner:x",corners[i].x, t);
		XML.setValue("corner:y",corners[i].y, t);
	}
	XML.saveFile(saveFile);
}
//--------------------------------------------------------------
void ofxGLWarper::load(string loadFile){
	ofxXmlSettings XML;
	if( !XML.loadFile(loadFile) ){
		ofLog(OF_LOG_ERROR, "ofxGLWarper : xml file not loaded. Check file path.");
	}
	
	if(!XML.tagExists("corners")){
		ofLog(OF_LOG_ERROR, "ofxGLWarper : incorrrect xml formating. No \"corners\" tag found");
		return;
	}
	XML.pushTag("corners");
	if (XML.getNumTags("corner")<4 ) {
		ofLog(OF_LOG_ERROR, "ofxGLWarper : incorrrect xml formating. less than 4 \"corner\" tags found");
		return;	
	}
	for(int i =0; i<4; i++){
		int t = XML.addTag("corner");
		XML.pushTag("corner", i);
		if (XML.tagExists("x") && XML.tagExists("y")){
			corners[i].x = XML.getValue("x", double(1.0));
			corners[i].y = XML.getValue("y", double(1.0));
		}
		XML.popTag();
	}
	
	processMatrices();
	ofLog(OF_LOG_ERROR, "ofxGLWarper : xml file loaded OK!.");
	
}
//--------------------------------------------------------------
void ofxGLWarper::mouseDragged(ofMouseEventArgs &args){

	float scaleX = (float)args.x / width;
	float scaleY = (float)args.y / height;
	
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
		float distx = corners[i].x - (float)args.x/width;
		float disty = corners[i].y - (float)args.y/height;
		float dist  = sqrt( distx * distx + disty * disty);
		
		if(dist < smallestDist && dist < 0.5){
			whichCorner = i;
			smallestDist = dist;
		}
	}
	
}
//--------------------------------------------------------------
void ofxGLWarper::mouseReleased(ofMouseEventArgs &args){
	whichCorner = -1;
}
//--------------------------------------------------------------
void ofxGLWarper::mouseMoved(ofMouseEventArgs &args){}
//--------------------------------------------------------------
ofVec4f ofxGLWarper::fromScreenToWarpCoord(float x, float y, float z)
{
	ofVec4f mousePoint;
	ofVec4f warpedPoint;
	
	// this is the point on the image which i want to know the coordinates inside the warped system ... 
	mousePoint.x = x;
	mousePoint.y = y;
	mousePoint.z = 0.0;
	mousePoint.w = 1.0;
	
	// i create a ofMatrix4x4 with the ofxGLWarper myMatrixData in column order
	ofMatrix4x4 myOFmatrix = ofMatrix4x4(myMatrix[0], myMatrix[4],myMatrix[8],myMatrix[12],
										 myMatrix[1], myMatrix[5],myMatrix[9], myMatrix[13],
										 myMatrix[2], myMatrix[6],myMatrix[10],myMatrix[14],
										 myMatrix[3],myMatrix[7],myMatrix[11],myMatrix[15]);
	// do not invert the matrix 
	ofMatrix4x4 invertedMyMatrix = myOFmatrix.getInverse();	
	//ofMatrix4x4 invertedMyMatrix = myOFmatrix;
	
	// multiply both to get the point transformed by the matrix
	warpedPoint = invertedMyMatrix * mousePoint ;
	
	// we need to normalize the value as described here : http://tech.groups.yahoo.com/group/OpenCV/message/80121
	warpedPoint.x = warpedPoint.x / warpedPoint.w;
	warpedPoint.y = warpedPoint.y / warpedPoint.w;
	warpedPoint.z = warpedPoint.z / warpedPoint.w;
	
	return warpedPoint;
}

//--------------------------------------------------------------
ofVec4f ofxGLWarper::fromWarpToScreenCoord(float x, float y, float z)
{
	ofVec4f mousePoint;
	ofVec4f warpedPoint;
	
	// this is the point inside the warped system which i want to know the coordinates on the image  ... 
	mousePoint.x = x;
	mousePoint.y = y;
	mousePoint.z = 0.0;
	mousePoint.w = 1.0;
	
	// i create a ofMatrix4x4 with the ofxGLWarper myMatrixData in column order
	ofMatrix4x4 myOFmatrix = ofMatrix4x4(myMatrix[0], myMatrix[4],myMatrix[8],myMatrix[12],
										 myMatrix[1], myMatrix[5],myMatrix[9], myMatrix[13],
										 myMatrix[2], myMatrix[6],myMatrix[10],myMatrix[14],
										 myMatrix[3],myMatrix[7],myMatrix[11],myMatrix[15]);
	// invert the matrix 
	//ofMatrix4x4 invertedMyMatrix = myOFmatrix.getInverse();	
	ofMatrix4x4 invertedMyMatrix = myOFmatrix;
	
	// multiply both to get the point transformed by the matrix
	warpedPoint = invertedMyMatrix * mousePoint ;
	
	warpedPoint.x = warpedPoint.x / warpedPoint.w;
	warpedPoint.y = warpedPoint.y / warpedPoint.w;
	warpedPoint.z = warpedPoint.z / warpedPoint.w;
	
	return warpedPoint;
}