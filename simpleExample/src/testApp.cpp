#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(255);
    
    for(int i=0; i<30; i++) {
        Particle p;
        particles.push_back(p);
    }
    
    retro.setup(ofGetWidth(), ofGetHeight());
    screen.allocate(ofGetWidth(), ofGetHeight());
    
    pixelSize = 8;
    bUseShader = true;
    bAddGrid = true;
    gridLineWidth = 2;
}

//--------------------------------------------------------------
void testApp::update(){
    for(int i=0; i<particles.size(); i++) {
        particles[i].update();
    }
}

//--------------------------------------------------------------
void testApp::draw(){

    screen.begin();
    ofClear(0);
    
    for(int i=0; i<particles.size(); i++) {
        particles[i].draw();
    }
    screen.end();
    
    screen.draw(0, 0);
    

    retro.draw(screen.getTextureReference(), pixelSize, bUseShader, bAddGrid, gridLineWidth);
    
    
    // Draw instructions
    stringstream message;
    message << "FPS: " << ofGetFrameRate() << endl;
    message << "up/down to adjust pixel size: " << pixelSize << endl;
    message << "'b' to toggle shader method vs openGL method: " << (bUseShader ? "shader" : "openGL") << endl;
    message << "'g' to toggle grid lines: " << (bAddGrid ? "on" : "off") << endl;
    message << "[left/right] to adjust grid line width: " << gridLineWidth << endl;
    ofSetColor(255);
    ofDrawBitmapString(message.str(), 10, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    switch(key) {
        case OF_KEY_UP:
            if(pixelSize < 100) pixelSize+=2;
            break;
        case OF_KEY_DOWN:
            if(pixelSize > 2) pixelSize -= 2;
            break;
        case 'b': case 'B':
            bUseShader = !bUseShader;
            break;
        case 'g': case 'G':
            bAddGrid = !bAddGrid;
            break;
        case OF_KEY_LEFT:
            if(gridLineWidth>0) gridLineWidth--;
            break;
        case OF_KEY_RIGHT:
            gridLineWidth++;
            break;
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}