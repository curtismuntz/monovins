#pragma once

#include "monovins/vision/imshow_wrapper.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

namespace monovins {
namespace vision {
namespace odometer {

class MonoVo {
 public:
  MonoVo() : frame_counter_(0){};
  ~MonoVo(){};
  void image_prep(const cv::Mat &frame, cv::Mat *ret);
  void process(const cv::Mat &frame);
  void process(const std::string &fname);

 private:
  ImageManager _im;
  cv::Mat current_frame_;
  cv::Mat previous_frame_;
  unsigned int frame_counter_;
};

}  // namespace odometer
}  // namespace vision
}  // namespace monovins
