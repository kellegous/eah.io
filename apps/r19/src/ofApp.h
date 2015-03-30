#pragma once

#include "ofMain.h"
#include "motion.h"

class ofApp : public ofBaseApp{
 public:
    ofApp();
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
 private:
    ofVideoPlayer player;
    ofVboMesh mesh;
    ofCamera cam;
    
    Motion amp_;
    Motion zom_;
    Motion rotx_;
    Motion roty_;
    Motion rotz_;
};
