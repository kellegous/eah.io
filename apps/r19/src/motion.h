#ifndef MOTION_H_
#define MOTION_H_

#include <stdio.h>
#include <cstdlib>

class Motion {
public:
    Motion(float min, float max, float rate, int limit, bool enabled=true, bool debug=false);
    float next();
private:
    float min_;
    float max_;
    float rate_;
    int limit_;
    float cur_rate_;
    int count_;
    float value_;
    bool enabled_;
    bool debug_;
};

#endif // MOTION_H_
