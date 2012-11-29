//
//  ofxRetroPixel.cpp
//  simpleExample
//
//  Created by Jeffrey Crouse on 11/29/12.
//
//

#include "ofxRetroPixel.h"


void ofxRetroPixel::setup(int winW, int winH)
{
    fbo.allocate(winW, winH);
    loadShader();
}

// Shader is faster than GL.
// But GL has nicer edge than shader.
// I love shader, so the default is "shader on".
void ofxRetroPixel::draw(ofTexture& screenTex, int _texelSize, bool bUseShader, bool bNeedGrid, int gridLineWidth)
{
    texelSize = _texelSize;
    fbo.begin();
    ofClear(0);
    if (bUseShader)
    {
        retroShader.begin();
        retroShader.setUniform1f("pixel_w", texelSize);
        retroShader.setUniform1f("pixel_h", texelSize);
    }
    
    screenTex.draw(0, 0);
    
    if (bUseShader)
    {
        retroShader.end();
        if (bNeedGrid)
            drawGrid(bUseShader, gridLineWidth);
        fbo.end();
        fbo.draw(0, 0);
    }
    else
    {
        fbo.end();
        ofPixels px;
        fbo.readToPixels(px);
        px.resize(fbo.getWidth()/texelSize,
                  fbo.getHeight()/texelSize);
        lowres.setFromPixels(px);
        lowres.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        lowres.draw(ofPoint(0,0), fbo.getWidth(), fbo.getHeight());
        if (bNeedGrid)
            drawGrid(bUseShader, gridLineWidth);
    }
}

ofFbo ofxRetroPixel::getFBO()
{
    return fbo;
}




void ofxRetroPixel::loadShader()
{
    string retroFragShader = "#version 120\n \ 
    #extension GL_ARB_texture_rectangle : enable\n \
    \
    uniform sampler2DRect sceneTex;\
    uniform float pixel_w;\
    uniform float pixel_h;\
    \
    void main (void)\
    {\
        vec2 uv = gl_TexCoord[0].xy;\
        float dx = pixel_w;\
        float dy = pixel_h;\
        vec2 coord = vec2(dx*floor(uv.x/dx),dy*floor(uv.y/dy));\
        vec3 tc = texture2DRect(sceneTex, coord).rgb;\
        gl_FragColor = vec4(tc, 1.0);\
    }\
    ";
    retroShader.setupShaderFromSource(GL_FRAGMENT_SHADER, retroFragShader);
    retroShader.linkProgram();
}

void ofxRetroPixel::drawGrid(bool bUseShader, int gridLineWidth)
{
    ofPushStyle();
    ofSetColor(ofColor::black);
    ofSetLineWidth(gridLineWidth);
    
    int xstep = fbo.getWidth()/texelSize;
    for (int i = 0; i < xstep; i++)
    {
        int xadjust = 0;
        if (!bUseShader)
            xadjust = i/2;
        
        ofLine(i*texelSize + xadjust, 0,
               i*texelSize + xadjust, ofGetHeight());
    }
    
    int ystep = fbo.getHeight()/texelSize;
    for (int i = 0; i < ystep; i++)
    {
        ofLine(0, i*texelSize,
               ofGetWidth(), i*texelSize);
    }
    
    ofPopStyle();
}
