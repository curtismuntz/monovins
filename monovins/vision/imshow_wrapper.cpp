#include "monovins/vision/imshow_wrapper.h"
#include <glog/logging.h>

namespace monovins {
namespace vision {

DEFINE_string(output_photo_dir, "/tmp", "Output photo directory");
DEFINE_string(photo_extension, ".jpg", "Photo extension");

void ImageManager::imshow(std::string name, const cv::Mat& img) {
  if(_map.find(name) == _map.end()) {
    auto insertme = std::pair<std::string, unsigned int>(name, 1);
    _map.insert(insertme);
  } else {
    _map[name] = _map[name] + 1;
  }
  auto fname = FLAGS_output_photo_dir + "/" + name + "_" + std::to_string(_map[name]) + FLAGS_photo_extension;
  LOG(INFO) << "FILENAME " << fname << std::endl;
  cv::imwrite(fname, img);
}

} // namespace vision
} // namespace monovins
