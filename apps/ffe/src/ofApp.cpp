#include "ofApp.h"
#include <stdlib.h>

namespace {

    static const int numDivs = 4;

} // anonymous

ofApp::ofApp() : amp_(200.f, 450.f, 0.01, 50),
                 rot_(-45.f, 45.f, 0.09, 10),
                 zom_(150.f, 500.f, 0.03, 30) {}

void ofApp::setup() {
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    // srand(0x420);
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0x00, 0x00, 0x00);
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // player.loadMovie("kikis.delivery.service.1989.720p.bluray.x264-en.m4v");
    // player.loadMovie("Citizenfour-HD.mp4");
    // player.loadMovie("6022_Riders_of_the_California_Surf_01_16_36_00_3mb.m4v");
    // player.loadMovie("tbt.mp4");
    player.loadMovie("deadmau5.0.mp4");
    player.setPosition(rand() / (float)RAND_MAX);
    player.play();
    // player.setSpeed(2.f);
    // player.setVolume(0.f);

    
    int w = ofGetWidth()/numDivs;
    int h = ofGetHeight()/numDivs;
   
    mesh.setMode(OF_PRIMITIVE_LINES);
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            mesh.addVertex(ofPoint(numDivs*i, numDivs*j, 0));
            mesh.addColor(ofFloatColor(0, 0, 0));
        }
    }
    
    for (int j = 0; j < h-1; j++) {
        for (int i = 0; i < w-1; i++) {
            mesh.addIndex(i + j*w);
            mesh.addIndex((i+1) + j*w);
            mesh.addIndex(i + (j+1)*w);
            
            mesh.addIndex((i+1) + j*w);
            mesh.addIndex((i+1) + (j+1)*w);
            mesh.addIndex(i + (j+1)*w);
        }
    }
    
    cam.setScale(1, -1, 1);
}

//--------------------------------------------------------------
void ofApp::update() {
    if (!player.isLoaded()) {
        return;
    }
    
    player.update();
    
    if (!player.isFrameNew()) {
        return;
    }
    
    // the mesh size
    int mw = ofGetWidth()/numDivs;
    int mh = ofGetHeight()/numDivs;

    // the player size
    int pw = player.getWidth();
    int ph = player.getHeight();
    
    int pgw = player.getWidth()/mw;
    int pgh = player.getHeight()/mh;
    
    unsigned char* pixels = player.getPixels();
    
    float z = amp_.next();
    
    for (int j = 0; j < mh; j++) {
        for (int i = 0; i < mw; i++) {
            int idx = (int)(i + j*mw);
            int pdx = 3*(i*pgw + j*pgh*pw);
            ofFloatColor sample(pixels[pdx]/255.f,
                                pixels[pdx + 1]/255.f,
                                pixels[pdx + 2]/255.f);
            
            ofVec3f vec = mesh.getVertex(idx);
            vec.z = sample.getBrightness() * z;
            mesh.setVertex(idx, vec);
            mesh.setColor(idx, sample);
        }
    }
    
    //let's move the camera when you move the mouse
    //float rotateAmount = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, 360);
    float rotateAmount = rot_.next();
    
    //move the camera around the mesh
    ofVec3f camDirection(0,0,1);
     ofVec3f center(player.getWidth()/2.f, player.getHeight()/2.f, zom_.next());
    ofVec3f camDirectionRotated = camDirection.rotated(rotateAmount, ofVec3f(1,0,0));
    ofVec3f camPosition = center + camDirectionRotated * 300.f;
    
    cam.setPosition(camPosition);
    cam.lookAt(center);

}

//--------------------------------------------------------------
void ofApp::draw(){
    if (!player.isLoaded()) {
        return;
    }
    
    ofEnableDepthTest();
    cam.begin();
    mesh.drawFaces();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}