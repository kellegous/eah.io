#include "ofApp.h"

namespace {

static const int numDivsX = 80;
static const int numDivsY = 50;
    
static const int padH = 2;
static const int padV = 2;

void SetZ(ofVboMesh& mesh, int index, float z) {
    ofVec3f vec = mesh.getVertex(index);
    vec.z = z;
    mesh.setVertex(index, vec);
}
    
void BoostBrightness(ofFloatColor& c, float f) {
    c.setBrightness(min(c.getBrightness() * f, 1.f));
}
    
} // anonymous


ofApp::ofApp() : amp_(-2*PI, 2*PI, 0.1f, 10),
                 zom_(300.f, 600.f, 0.05f, 50),
                 rotx_(0.f, 1.f, 0.2f, 5),
                 roty_(-1.f, 1.f, 0.2f, 10),
                 rotz_(-1.f, 1.f, 0.2f, 15) {
}

void ofApp::setup() {
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    
    // player.loadMovie("CitizenFour-HD.mp4");
    // player.loadMovie("kikis.delivery.service.1989.720p.bluray.x264-en.m4v");
    player.loadMovie("tbt.mp4");
    // player.loadMovie("deadmau5.0.mp4");
    player.setPosition(rand() / (float)RAND_MAX);
    player.play();
    
    float dx = player.getWidth() / numDivsX;
    float dy = player.getHeight() / numDivsY;
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    for (int j = 0; j < numDivsY; j++) {
        for (int i = 0; i < numDivsX; i++) {
            mesh.addVertex(ofPoint(dx*i + padH, dy*j + padV, 0.f));
            mesh.addColor(ofColor::black);
            
            mesh.addVertex(ofPoint(dx*(i+1) - padH, dy*j + padV, 0.f));
            mesh.addColor(ofColor::black);
            
            mesh.addVertex(ofPoint(dx*(i+1) - padH, dy*(j+1) - padV, 0.f));
            mesh.addColor(ofColor::black);
            
            mesh.addVertex(ofPoint(dx*i + padH, dy*(j+1) - padV, 0.f));
            mesh.addColor(ofColor::black);
        }
    }
    
    for (int j = 0; j < numDivsY; j++) {
        for (int i = 0; i < numDivsX; i++) {
            int ix = 4*(i + j*numDivsX);
            mesh.addIndex(ix);
            mesh.addIndex(ix + 1);
            mesh.addIndex(ix + 3);
            
            mesh.addIndex(ix + 2);
            mesh.addIndex(ix + 3);
            mesh.addIndex(ix + 1);
        }
    }
    
    cam.setScale(1, -1, 1);
}

void ofApp::update() {
    if (!player.isLoaded()) {
        return;
    }
    
    player.update();
    
    if (!player.isFrameNew()) {
        return;
    }
    
    unsigned char* pixels = player.getPixels();
    
    int w = player.getWidth();
    int h = player.getHeight();
    
    int dx = w / numDivsX;
    int dy = h / numDivsY;
    
    float amp = amp_.next();
    
    for (int j = 0; j < numDivsY; j++) {
        for (int i = 0; i < numDivsX; i++) {
            int ai = 3*(i*dx + j*dy*w);
            int bi = 3*((i+1)*dx + j*dy*w);
            int ci = 3*((i+1)*dx + (j+1)*dy*w);
            int di = 3*(i*dx + (j+1)*dy*w);
            
            ofFloatColor a(pixels[ai]/255.f,
                           pixels[ai+1]/255.f,
                           pixels[ai+2]/255.f);
            ofFloatColor b(pixels[bi]/255.f,
                           pixels[bi+1]/255.f,
                           pixels[bi+2]/255.f);
            ofFloatColor c(pixels[ci]/255.f,
                           pixels[ci+1]/255.f,
                           pixels[ci+2]/255.f);
            ofFloatColor d(pixels[di]/255.f,
                           pixels[di+1]/255.f,
                           pixels[di+2]/255.f);
            
            float z = cos(amp + ofGetFrameNum() * (2*PI/240)) * a.getBrightness() * 300.f;

            int ix = 4*(i + j*numDivsX);
            
            SetZ(mesh, ix, z);
            SetZ(mesh, ix+1, z);
            SetZ(mesh, ix+2, z);
            SetZ(mesh, ix+3, z);

            BoostBrightness(a, 1.2f);
            BoostBrightness(b, 1.2f);
            BoostBrightness(c, 1.2f);
            BoostBrightness(d, 1.2f);
            
            mesh.setColor(ix, a);
            mesh.setColor(ix+1, b);
            mesh.setColor(ix+2, c);
            mesh.setColor(ix+3, d);
        }
    }
    
    float rotateAmount = 20.f;
    
    //move the camera around the mesh
    ofVec3f camDirection(0,0,1);
    ofVec3f center(player.getWidth()/2.f, player.getHeight()/2.f, zom_.next());
    
    ofVec3f dir(rotx_.next(), roty_.next(), rotz_.next());
    ofVec3f camDirectionRotated = camDirection.rotated(rotateAmount, dir);
    ofVec3f camPosition = center + camDirectionRotated * 300.f;
    
    cam.setPosition(camPosition);
    cam.lookAt(center);

}

void ofApp::draw() {
    if (!player.isLoaded()) {
        return;
    }
    
//    player.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    ofEnableDepthTest();
    cam.begin();
    mesh.drawFaces();
    cam.end();
}

void ofApp::keyPressed(int key) {
}

void ofApp::keyReleased(int key) {
}

void ofApp::mouseMoved(int x, int y ) {
}

void ofApp::mouseDragged(int x, int y, int button) {
}

void ofApp::mousePressed(int x, int y, int button) {
}

void ofApp::mouseReleased(int x, int y, int button) {
}

void ofApp::windowResized(int w, int h) {
}

void ofApp::gotMessage(ofMessage msg) {
}

void ofApp::dragEvent(ofDragInfo dragInfo) {
}
