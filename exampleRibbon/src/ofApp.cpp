#include "ofApp.h"

void ofApp::setup()
{
    //just set up the openFrameworks stuff
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(255);
    
	//initialize the variable so it's off at the beginning
    usecamera = false;
    
    
    idx = 0;
    
    retro.setup(ofGetWidth(), ofGetHeight());
    screen.allocate(ofGetWidth(), ofGetHeight());
}

void ofApp::update()
{
    //don't move the points if we are using the camera
    if(!usecamera){
        ofVec3f sumOfAllPoints(0,0,0);
        for(int i = 0; i < points.size(); i++){
            points[i].z -= 4;
            sumOfAllPoints += points[i];
        }
        center = sumOfAllPoints / points.size();
    }
    
    screen.begin();
    ofClear(0);
    
    ofPushStyle();
    ofSetColor(ofColor::black);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
    
	//if we're using the camera, start it.
	//everything that you draw between begin()/end() shows up from the view of the camera
    if(usecamera){
        camera.begin();
    }
    
    ofPushStyle();
	ofSetColor(ofColor::white);
	//do the same thing from the first example...
    ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	for(int i = 1; i < points.size(); i++){
		
		//find this point and the next point
		ofVec3f thisPoint = points[i-1];
		ofVec3f nextPoint = points[i];
		
		//get the direction from one to the next.
		//the ribbon should fan out from this direction
		ofVec3f direction = (nextPoint - thisPoint);
		
		//get the distance from one point to the next
		float distance = direction.length();
		
		//get the normalized direction. normalized vectors always have a length of one
		//and are really useful for representing directions as opposed to something with length
		ofVec3f unitDirection = direction.normalized();
		
		//find both directions to the left and to the right
		ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
		ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));
		
		//use the map function to determine the distance.
		//the longer the distance, the narrower the line.
		//this makes it look a bit like brush strokes
		float thickness = ofMap(distance, 0, 60, 100, 2, true);
		
		//calculate the points to the left and to the right
		//by extending the current point in the direction of left/right by the length
		ofVec3f leftPoint = thisPoint+toTheLeft*thickness;
		ofVec3f rightPoint = thisPoint+toTheRight*thickness;
		
		//add these points to the triangle strip
		mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
		mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
	}
    
	//end the shape
	mesh.draw();
    ofPopStyle();
    
    
	//if we're using the camera, take it away
    if(usecamera){
    	camera.end();
    }
    
    screen.end();
}

void ofApp::draw()
{
    retro.draw(screen.getTextureReference(), 26, true, true);
}

void ofApp::keyPressed(int key)
{
    if (key == 's')
    {
        idx++;
        ofFbo fbo = retro.getFBO();
        ofPixels px;
        fbo.readToPixels(px);
        ofSaveImage(px, ofToString(idx) + ".png");
        idx++;
        px.clear();
        screen.readToPixels(px);
        ofSaveImage(px, ofToString(idx) + ".png");
    }
}

void ofApp::keyReleased(int key)
{
	//hitting any key swaps the camera view
    if (key != 's')
        usecamera = !usecamera;
}

void ofApp::mouseMoved(int x, int y)
{
	//if we are using the camera, the mouse moving should rotate it around the whole sculpture
    if(usecamera){
        float rotateAmount = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 360);
		ofVec3f furthestPoint = points[0];
        ofVec3f directionToFurthestPoint = (furthestPoint - center);
        ofVec3f directionToFurthestPointRotated = directionToFurthestPoint.rotated(rotateAmount, ofVec3f(0,1,0));
        camera.setPosition(center + directionToFurthestPointRotated);
        camera.lookAt(center);
    }
	//otherwise add points like before
    else{
        ofVec3f mousePoint(x,y,0);
        points.push_back(mousePoint);
    }
}

void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}