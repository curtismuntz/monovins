#pragma once

#include <gflags/gflags.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <unordered_map>

namespace monovins {
namespace vision {

DECLARE_string(output_photo_dir);
DECLARE_string(photo_extension);

class ImageManager {
 public:
  ImageManager(){};
  void imshow(std::string name, const cv::Mat &img);
  void show(std::string name, const cv::Mat &img) { imshow(name, img); };

 private:
  std::unordered_map<std::string, unsigned int> _map;
};

}  // namespace vision
}  // namespace monovins
