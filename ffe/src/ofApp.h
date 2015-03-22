#pragma once

#include "ofMain.h"

class Motion {
 public:
    Motion(float min, float max, float rate, int limit)
        : min_(min),
          max_(max),
          rate_(rate),
          limit_(limit),
          cur_rate_(0),
          count_(limit),
          value_(min) {
    }
    
    float next() {
        count_++;
        if (count_ >= limit_) {
            cur_rate_ = (rand() / (float)RAND_MAX) * 2*rate_ - rate_;
            count_ = 0;
            printf("rate = %0.4f value = %0.4f count = %d limit = %d\n", cur_rate_, value_, count_, limit_);
        }
        
        value_ *= (1 - cur_rate_);
        if (value_ > max_) {
            value_ = max_;
        } else if (value_ < min_) {
            value_ = min_;
        }
        return value_;
    }
    
    
 private:
    float min_;
    float max_;
    float rate_;
    int limit_;
    float cur_rate_;
    int count_;
    float value_;
};

class ofApp : public ofBaseApp{
 public:
    ofApp();
    void setup();
    void update();
    void draw();
		
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
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
    Motion rot_;
    Motion zom_;
};