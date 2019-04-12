# pragma once

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "monovins/vision/imshow_wrapper.h"

namespace monovins {
namespace vision {
namespace odometer {

class monovo {
public:
  monovo() : _frame_counter(0) {};
  ~monovo() {};
  void process(const cv::Mat& frame);

private:
  ImageManager _im;
  cv::Mat _current_frame;
  cv::Mat _previous_frame;
  unsigned int _frame_counter;
};

} // namespace odometer
} // namespace vision
} // namespace monovins
