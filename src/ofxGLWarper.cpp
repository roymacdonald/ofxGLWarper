#include "ofxGLWarper.h"
#include "ofxHomography.h"

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
    ofLogVerbose() << "ofxGLWarper setup: " <<_x << " " <<_y << " " <<_w << " " <<_h << endl;
    ofUnregisterMouseEvents(this);

    corners[0].x = _x;
    corners[0].y = _y;

    corners[1].x = _x + _w;
    corners[1].y = _y;

    corners[2].x = _x + _w;
    corners[2].y = _y + _h;

    corners[3].x = _x;
    corners[3].y = _y + _h;

    active=false;

    myMatrix = ofMatrix4x4(); // identity

    x=_x;
    y=_y;
    width=_w;
    height=_h;
    whichCorner = -1;
    cornerSelected = false;
    cornerSensibility = 0.5;
    bUseKeys = true;

    processMatrices();
}
//--------------------------------------------------------------
bool ofxGLWarper::isActive(){
    return active;
}
//--------------------------------------------------------------
void ofxGLWarper::activate(){
    ofRegisterMouseEvents(this);
    active=true;
    if (bUseKeys) {
        ofRegisterKeyEvents(this);
    }
}
//--------------------------------------------------------------
void ofxGLWarper::deactivate(){
    ofUnregisterMouseEvents(this);
    active=false;
    if (bUseKeys) {
        ofUnregisterKeyEvents(this);
    }
}
//--------------------------------------------------------------
void ofxGLWarper::toggleActive(){
    if(!active){
        activate();
        ofLogVerbose() << "activate"<<endl;
    }else{
        deactivate();
        ofLogVerbose() << "desactivate"<<endl;
    }
}
//--------------------------------------------------------------
void ofxGLWarper::enableKeys(bool k){
    if (k) {
        ofRegisterKeyEvents(this);
    }else{
        ofUnregisterKeyEvents(this);
    }
}
//--------------------------------------------------------------
void ofxGLWarper::toggleKeys(){
    enableKeys(!bUseKeys);
}
//--------------------------------------------------------------
bool ofxGLWarper::getUseKeys(){
    return bUseKeys;
}
//--------------------------------------------------------------
void ofxGLWarper::setUseKeys(bool use){
    bUseKeys = use;
}
//--------------------------------------------------------------
void ofxGLWarper::processMatrices(){
    //we set it to the default - 0 translation
    //and 1.0 scale for x y z and w
    myMatrix = ofMatrix4x4(); // default constructor generates identity

    //ofPoints instead of openCV points
    ofPoint cvsrc[4];
    ofPoint cvdst[4];

    //we set the warp coordinates
    //source coordinates as the dimensions of our window
    cvsrc[0].set(0,0);
    cvsrc[1].set(width,0);
    cvsrc[2].set(width,height);
    cvsrc[3].set(0,height);

    //corners are in 0.0 - 1.0 range
    //so we scale up so that they are at the window's scale
    for(int i = 0; i < 4; i++){
        cvdst[i].set(corners[i].x,corners[i].y);
    }


    //figure out the warping!

    myMatrix = ofxHomography::findHomography(cvsrc, cvdst);

}
//--------------------------------------------------------------
void ofxGLWarper::draw(){
    if (active) {
        ofPushStyle();
        ofSetColor(255, 255, 255);
        ofNoFill();
        ofDrawRectangle(x, y, width, height);
        ofPopStyle();
    }
}
//--------------------------------------------------------------
void ofxGLWarper::begin(){
    if (active) {
        processMatrices();
    }
    ofPushMatrix();
    ofMultMatrix(myMatrix);

    ofTranslate(-1*x,-1*y); //if not, you have to draw from warper's origin. As you wish.
}
//--------------------------------------------------------------
void ofxGLWarper::end(){
    ofPopMatrix();
    if (active) {// this draws colored squares over the corners as a visual aid.
        ofPushStyle();
        ofSetRectMode(OF_RECTMODE_CENTER);
        for (int i = 0; i < 4; i++) {
            if(i==whichCorner){
                ofSetColor(255, 0, 0);
            }else{
                ofSetColor(255, 255, 0);
            }
            ofDrawRectangle(corners[i], 10, 10);
        }
        ofPopStyle();
    }
}
//--------------------------------------------------------------
void ofxGLWarper::save(const string &saveFile){
    ofXml XML;
    saveToXml(XML);
    XML.save(saveFile);
}
//--------------------------------------------------------------
void ofxGLWarper::saveToXml(ofXml &XML, const string& warperID){
    
    XML.removeChild(warperID);//if child doesn't exist yet, it's ok.
    auto c = XML.appendChild(warperID);
    for(int i =0; i<4; i++){
		auto nc = c.appendChild("corner");
		nc.appendChild("x").set(corners[i].x);
        nc.appendChild("y").set(corners[i].y);
    }
    c.appendChild("active").set(active);
}
//--------------------------------------------------------------
void ofxGLWarper::load(const string &loadFile){
    ofXml XML;
    if( !XML.load(loadFile) ){
        ofLog(OF_LOG_ERROR, "ofxGLWarper : xml file not loaded. Check file path.");
        return;
    }
    loadFromXml(XML);
}

//--------------------------------------------------------------
void ofxGLWarper::loadFromXml(ofXml &XML, const string& warperID){
    auto c = XML.getChild(warperID);
    if(!c){
        ofLog(OF_LOG_ERROR, "ofxGLWarper : incorrrect xml formating. No \"" + warperID + "\" tag found");
        return;
    }
	
    if (c.find("corner").size()<4 ) {
        ofLog(OF_LOG_ERROR, "ofxGLWarper : incorrrect xml formating. less than 4 \"corner\" tags found");
        return;
    }
	auto cor = c.getChildren("corner");
	int i = 0;
	for(auto& ch: cor){
		corners[i].x = ch.getChild("x").getFloatValue();
		corners[i].y = ch.getChild("y").getFloatValue();
		i++;
    }

    (c.getChild("active").getBoolValue()) ? this->activate() : this->deactivate() ;

    processMatrices();
    //ofLog(OF_LOG_WARNING, "ofxGLWarper : xml object loaded OK!."); // Since the method works, this can be quiet...

}
//--------------------------------------------------------------
void ofxGLWarper::mouseDragged(ofMouseEventArgs &args){
    if(whichCorner >= 0 && cornerSelected){
        corners[whichCorner].x = args.x;
        corners[whichCorner].y = args.y;

        CornerLocation location = (CornerLocation)whichCorner;
        ofNotifyEvent(changeEvent, location, this);
    }
}
//--------------------------------------------------------------
void ofxGLWarper::mousePressed(ofMouseEventArgs &args){

    float smallestDist = sqrt(ofGetWidth() * ofGetWidth() + ofGetHeight() * ofGetHeight());
    //whichCorner = -1;
    float sensFactor = cornerSensibility * sqrt( width  * width  + height  * height );

    cornerSelected = false;
    for(int i = 0; i < 4; i++){
        float distx = corners[i].x - args.x;
        float disty = corners[i].y - args.y;
        float dist  = sqrt( distx * distx + disty * disty);
        ofLogVerbose() << "mouse to corner dist: " << dist << endl;
        if(dist < smallestDist && dist < sensFactor ){
            whichCorner = i;
            smallestDist = dist;
            cornerSelected=true;
        }
    }
}

//--------------------------------------------------------------
void ofxGLWarper::keyPressed(ofKeyEventArgs &args){
	if (whichCorner >= 0 && cornerSelected) {
        switch (args.key) {
            case OF_KEY_DOWN:
                corners[whichCorner].y++;
                break;
            case OF_KEY_UP:
                corners[whichCorner].y--;
                break;
            case OF_KEY_LEFT:
                corners[whichCorner].x--;
                break;
            case OF_KEY_RIGHT:
                corners[whichCorner].x++;
                break;
            default:
			break;
		}
	}
}
//--------------------------------------------------------------
ofVec4f ofxGLWarper::fromScreenToWarpCoord(float x, float y, float z){
    ofVec4f mousePoint;
    ofVec4f warpedPoint;

    // this is the point on the image which i want to know the coordinates inside the warped system ...
    mousePoint.x = x;
    mousePoint.y = y;
    mousePoint.z = 0.0;
    mousePoint.w = 1.0;

    // i create a ofMatrix4x4 with the ofxGLWarper myMatrixData in column order
    ofMatrix4x4 myOFmatrix = ofMatrix4x4::getTransposedOf(myMatrix);

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
ofVec4f ofxGLWarper::fromWarpToScreenCoord(float x, float y, float z){
    ofVec4f mousePoint;
    ofVec4f warpedPoint;

    // this is the point inside the warped system which i want to know the coordinates on the image  ...
    mousePoint.x = x;
    mousePoint.y = y;
    mousePoint.z = 0.0;
    mousePoint.w = 1.0;

    // i create a ofMatrix4x4 with the ofxGLWarper myMatrixData in column order
    ofMatrix4x4 myOFmatrix = ofMatrix4x4::getTransposedOf(myMatrix);

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
//--------------------------------------------------------------
void ofxGLWarper::setCorner(CornerLocation cornerLocation, ofPoint screenLocation){
    corners[cornerLocation] = screenLocation;// / ofPoint(width, height, 1);
    processMatrices();

    CornerLocation location = cornerLocation;
    ofNotifyEvent(changeEvent, location, this);
}
//--------------------------------------------------------------
void ofxGLWarper::setAllCorners(ofPoint& top_left, ofPoint &top_right, ofPoint &bot_left, ofPoint &bot_right){
    //if you want to set all corners and avoid 3 useless processMatrices()
    corners[TOP_LEFT] = top_left;
    corners[TOP_RIGHT] = top_right;
    corners[BOTTOM_LEFT] = bot_left;
    corners[BOTTOM_RIGHT] = bot_right;

    processMatrices();

    CornerLocation location = TOP_LEFT;
    ofNotifyEvent(changeEvent, location, this);
    location = TOP_RIGHT;
    ofNotifyEvent(changeEvent, location, this);
    location = BOTTOM_RIGHT;
    ofNotifyEvent(changeEvent, location, this);
    location = BOTTOM_LEFT;
    ofNotifyEvent(changeEvent, location, this);
}
//--------------------------------------------------------------
ofPoint ofxGLWarper::getCorner(CornerLocation cornerLocation){
    return corners[cornerLocation];// * ofPoint(width, height, 1);
}
//--------------------------------------------------------------
void ofxGLWarper::setCornerSensibility(float sensibility){
    cornerSensibility = sensibility;
}
//--------------------------------------------------------------
float ofxGLWarper::getCornerSensibility(){
    return cornerSensibility;
}
