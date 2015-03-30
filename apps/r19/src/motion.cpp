#include "motion.h"


float Motion::next() {
    if (!enabled_) {
        value_ = (min_ + max_) / 2.f;
        return;
    }
    
    count_++;
    if (count_ >= limit_) {
        cur_rate_ = (rand() / (float)RAND_MAX) * 2*rate_ - rate_;
        count_ = 0;
        if (debug_) {
            printf("rate = %0.4f value = %0.4f count = %d limit = %d\n",
                   cur_rate_,
                   value_,
                   count_,
                   limit_);
        }
    }
    
    value_ *= (1 + cur_rate_);
    if (value_ > max_) {
        value_ = max_;
    } else if (value_ < min_) {
        value_ = min_;
    }
    return value_;
}

Motion::Motion(float min, float max, float rate, int limit, bool enabled, bool debug)
    : min_(min),
      max_(max),
      rate_(rate),
      limit_(limit),
      cur_rate_(0),
      count_(limit),
      value_(min),
      enabled_(enabled),
      debug_(debug) {
}
