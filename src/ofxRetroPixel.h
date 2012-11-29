//
//  ofxRetroPixel.h
//  emptyExample
//
//  Created by Akira Hayasaka on 6/29/12.
//  Copyright (c) 2012 ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆. All rights reserved.
//

#pragma once
#include "ofMain.h"
#define STRINGIFY(A) #A


class ofxRetroPixel
{
public:
    
    void setup(int winW, int winH);
    void draw(ofTexture& screenTex, 
              int _texelSize = 26, bool bUseShader = true,
              bool bNeedGrid = true, int gridLineWidth = 10);
    ofFbo getFBO();
    
private:
    
    void loadShader();
    void drawGrid(bool bUseShader, int gridLineWidth);
    
    ofFbo fbo;
    ofShader retroShader;
    ofImage lowres;
    
    int texelSize;
};

