#include "monovins/vision/odometer/odometer.h"

namespace monovins {
namespace vision {
namespace odometer {


void MonoVo::image_prep(const cv::Mat& frame, cv::Mat *ret) {
    // convert to greyscale
    cvtColor(frame, *ret, cv::COLOR_RGB2GRAY);
}

void MonoVo::process(const std::string& fname) {
  auto frame = cv::imread(fname);
  process(frame);
}

void MonoVo::process(const cv::Mat& frame) {
  // we can't do anything at all if this is our first frame.
  if(frame_counter_ == 0) {
    image_prep(frame, &current_frame_);
    image_prep(frame, &previous_frame_);
    ++frame_counter_;
    return;
  }
  previous_frame_ = current_frame_;
  image_prep(frame, &current_frame_);

  _im.show("input_frame", frame);
  _im.show("current_frame", current_frame_);

  ++frame_counter_;
}

} // namespace odometer
} // namespace vision
} // namespace monovins
