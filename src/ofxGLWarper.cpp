#include "ofxGLWarper.h"

//--------------------------------------------------------------
void ofxGLWarper::setup(int _resX, int _resY){	 
	//we run at 60 fps!
	//ofSetVerticalSync(true);
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
	
	overCorner=false;
	
	doProcess=false;
	
	whichCorner =-1;
	
	lastCorner=-1;
	
	isKeyShift=false;
	
	normPix.x=1.0f/ofGetWidth();
	normPix.y=1.0f/ofGetHeight();
	
	inc=normPix;
	
	for(int i = 0; i < 16; i++){
		if(i % 5 != 0) myMatrix[i] = 0.0;
		else myMatrix[i] = 1.0;
	}
	processMatrices();
	
	cout << "myMatrix:"<<endl;
	for(int i=0; i<16; i++){
		if(i%4==0){
			cout << endl;
		}
		cout << ofToString(myMatrix[i])<<"   ";
	
<<<<<<< HEAD
	width=_resX;
	height=_resY;
	whichCorner = -1;
	
	
=======
	}
>>>>>>> nose
}
//--------------------------------------------------------------
bool ofxGLWarper::isActive(){
	return active;
}
//--------------------------------------------------------------
void ofxGLWarper::activate(){
<<<<<<< HEAD
	//ofRegisterMouseEvents(this);
=======
	ofRegisterMouseEvents(this);
	ofRegisterKeyEvents(this);
>>>>>>> nose
	active=true;
}
//--------------------------------------------------------------
void ofxGLWarper::deactivate(){
	ofUnregisterMouseEvents(this);
	ofUnregisterKeyEvents(this);
	active=false;
}
//--------------------------------------------------------------
bool ofxGLWarper::setSourceMatrix(CvPoint2D32f src[], int length){
	if (length!=4) {
		ofLog(OF_LOG_WARNING, "Can't set source matrix. Incorrect size. !=4");
		return false;
	}else {
		for (int i=0; i<4; i++) {
			cvsrc[i]=src[i];	
		}
		processMatrices();
		return true;
	}
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
	//CvPoint2D32f cvsrc[4];
	CvPoint2D32f cvdst[4];	
	
	//we set the warp coordinates
	//source coordinates as the dimensions of our window
	cvsrc[0].x = 0;
	cvsrc[0].y = 0;
	cvsrc[1].x = width;
	cvsrc[1].y = 0;
	cvsrc[2].x = width;
	cvsrc[2].y = height;
	cvsrc[3].x = 0;
	cvsrc[3].y = height;			
	
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
<<<<<<< HEAD
void ofxGLWarper::begin(){
	if (active) {
		processMatrices();
	}
	glPushMatrix();
=======
void ofxGLWarper::update(){}
//--------------------------------------------------------------
void ofxGLWarper::draw(){
	if (active){
		if(overCorner || doProcess) {
			processMatrices();
		}
	}
	ofPushMatrix();
>>>>>>> nose
	glMultMatrixf(myMatrix);
}
//--------------------------------------------------------------
void ofxGLWarper::end(){
	if (whichCorner>=0) {
		ofPushStyle();
		ofEnableAlphaBlending();
		if (overCorner) {
			ofSetColor(255, 100, 0, 180);
		}else {
			ofSetColor(255, 100, 0, 40);
		}
		switch (whichCorner) {
			case 0:
				ofCircle(0, 0, 50);
				break;
			case 1:
				ofCircle(ofGetWidth(), 0, 50);
				break;
			case 2:
				ofCircle(ofGetWidth(),ofGetHeight(),  50);
				break;
			case 3:
				ofCircle(0, ofGetHeight(), 50);
				break;
			default:
				break;
		}
		ofPopStyle();
		
		
	}
	ofPopMatrix();	
}
//--------------------------------------------------------------
void ofxGLWarper::keyPressed(ofKeyEventArgs &key){
	/*
		isKeyShift=true;
		cout << "Shift pressed."<<endl;
	}else {
		isKeyShift=false;
	}

<<<<<<< HEAD

//--------------------------------------------------------------
void ofxGLWarper::end(){
	glPopMatrix();
}

//--------------------------------------------------------------
void ofxGLWarper::mouseDragged(ofMouseEventArgs &args){

	
		float scaleX = (float)args.x / width;
		float scaleY = (float)args.y / height;
		
		if(whichCorner >= 0){
			corners[whichCorner].x = scaleX;
			corners[whichCorner].y = scaleY;			
		}

=======
	*/
	switch (key.key) {
		case '1':
			lastCorner=0;
			break;
		case '2':
			lastCorner=1;
			break;
		case '3':
			lastCorner=2;
			break;
		case '4':
			lastCorner=3;
			break;
			
		if (lastCorner>-1 && active) {
			
			if (isKeyShift) {
				inc*=100;
			}else {
				inc=normPix;
			}
		case OF_KEY_UP:
			corners[lastCorner].y -= inc.y;
			cout << "keyUp: "<< corners[lastCorner].x <<", "<<corners[lastCorner].y<<"  inc: "<< inc.x<<", "<<inc.y<<endl;
			doProcess=true;
			break;
		case OF_KEY_DOWN:
			corners[lastCorner].y += inc.y;
			cout << "keyDown: "<< corners[lastCorner].x <<", "<<corners[lastCorner].y<<"  inc: "<< inc.x<<", "<<inc.y<<endl;
			doProcess=true;
			break;
		case OF_KEY_LEFT:
			corners[lastCorner].x -= inc.x;
			doProcess=true;
			break;
		case OF_KEY_RIGHT:
			corners[lastCorner].x += inc.x;
			doProcess=true;
			break;
		}
		
		default:
			break;
	}

}
//--------------------------------------------------------------
void ofxGLWarper::keyReleased(ofKeyEventArgs &key){
	doProcess=false;
}
//--------------------------------------------------------------
void ofxGLWarper::mouseDragged(ofMouseEventArgs &args){
	if(whichCorner >= 0){
		float scaleX = (float)args.x / ofGetWidth();
		float scaleY = (float)args.y / ofGetHeight();
		corners[whichCorner].x = scaleX;
		corners[whichCorner].y = scaleY;			
	}
>>>>>>> nose
}

//--------------------------------------------------------------
void ofxGLWarper::mousePressed(ofMouseEventArgs &args){
	if (whichCorner>-1) {
		overCorner=true;
	}
}
//--------------------------------------------------------------
void ofxGLWarper::mouseReleased(ofMouseEventArgs &args){
	whichCorner = -1;
	overCorner =false;
}
//--------------------------------------------------------------
void ofxGLWarper::mouseMoved(ofMouseEventArgs &args){
	float smallestDist = 1.0;
	whichCorner = -1;
<<<<<<< HEAD
	activate();

=======
>>>>>>> nose
	
	for(int i = 0; i < 4; i++){
		float distx = corners[i].x - (float)args.x/width;
		float disty = corners[i].y - (float)args.y/height;
		float dist  = sqrt( distx * distx + disty * disty);
		
		if(dist < smallestDist && dist < 0.5){
			whichCorner = i;
			lastCorner = i;
			smallestDist = dist;
			cout << "Which corner: " << whichCorner <<endl;
		}
		cout << "No corner: " << smallestDist << "dist[i] " << dist<<endl<<endl ;
		
	}
<<<<<<< HEAD

}
//--------------------------------------------------------------
void ofxGLWarper::mouseReleased(ofMouseEventArgs &args){
	whichCorner = -1;
	deactivate();
}
//--------------------------------------------------------------
void ofxGLWarper::mouseMoved(ofMouseEventArgs &args){
	whichCorner = -1;
	//deactivate();
}


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
=======
>>>>>>> nose
}