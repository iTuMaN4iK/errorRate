#include "errorRate.hpp"
#include <iostream>
#include <vector>

std::istream& operator>>(std::istream& is, Frames& fr) {
  is >> fr.frames >> fr.lost_frames;
  return is;
}

float getErrorRateIntervals(const Frames& last, const Frames& next) {
  return (next.lost_frames - last.lost_frames) / ((next.frames - last.frames) * 1.0);
}

void ErrorRate::setCurrent(uint64_t time, const Frames& frames) {
  mErrorRate[time] = frames;
}

float ErrorRate::getErrorRate(uint32_t duration) const {
  if (mErrorRate.empty()) {
    return 0;
  }
  if (duration == 0) {
    return mErrorRate.rbegin()->second.lost_frames / (mErrorRate.rbegin()->second.frames * 1.0);
  }
  auto it = mErrorRate.begin();
  if (mErrorRate.rbegin()->first > duration) {
    it = mErrorRate.lower_bound(mErrorRate.rbegin()->first - duration);
  }
  float sumER = 0;
  float sumDurationIntervals = 0;
  while (next(it) != mErrorRate.end()) {
    uint64_t durationIntervals = next(it)->first - it->first;
    sumER += getErrorRateIntervals(it->second, next(it)->second) * durationIntervals;
    sumDurationIntervals += durationIntervals;
    it = next(it);
  }
  return sumER / sumDurationIntervals;
}
