#pragma once

namespace monovins {
namespace data_manager {

class ImageData {
public:
  ImageData(const std::string &fname) {

  }
  ImageData(const cv::Mat frame) {

  }
private:
  cv::Mat frame_;
  long long int timestamp_;
};


class ImuData {
public:
  ImuData() {};
};


class DataManager {
public:
  DataManager() {};

  void add_camera(const std::string &fname) {

  }

  void add_camera(const cv::Mat &frame) {

  }

private:
};


}
}
