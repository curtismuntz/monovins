#include "monovins/vision/odometer/odometer.h"

namespace monovins {
namespace vision {
namespace odometer {

void monovo::process(const cv::Mat& frame) {
  if(_frame_counter == 0) {
    _current_frame = frame;
    _previous_frame = frame;
    ++_frame_counter;
    return;
  }
  _previous_frame = _current_frame;
  _current_frame = frame;
  _im.imshow("_current_frame", _current_frame);
  ++_frame_counter;
}

} // namespace odometer
} // namespace vision
} // namespace monovins
