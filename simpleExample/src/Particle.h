//
//  Particle.h
//  simpleExample
//
//  Created by Jeffrey Crouse on 11/29/12.
//
//

#pragma once


class Particle {
public:
    Particle() {
        radius = ofRandom(10, 40);
        pos.x = ofRandom(radius, ofGetWidth()-radius);
        pos.y = ofRandom(radius, ofGetHeight()-radius);
        vel.x = ofRandom(-8, 8);
        vel.y = ofRandom(-8, 8);
        color.setHsb( ofRandom(0, 255), 255, 200 );
    }
    void update() {
        pos += vel;
        loop();
    }
    void loop() {
        if(pos.x > ofGetWidth()+radius) pos.x = -radius;
        if(pos.x < -radius) pos.x = ofGetWidth() + radius;
        if(pos.y > ofGetHeight()+radius) pos.y = -radius;
        if(pos.y < -radius) pos.y = ofGetHeight()+radius;
    }
    
    void draw() {
        ofSetColor(color);
        ofCircle(pos, radius);
    }
    ofColor color;
    ofPoint pos, vel;
    float radius;
};