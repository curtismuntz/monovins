#pragma once

#include <cstdint>
#include <string>
#include <deque>
#include <vector>

namespace monovins {
namespace data_manager {

struct timestamp {
  timestamp(int64_t seconds, int32_t nanos) {
    nanos_ = nanos;
    seconds_ = seconds;
  }
  int64_t seconds_;
  int32_t nanos_;
  friend bool operator< (const timestamp &lhs, const timestamp &rhs) {
    if(lhs.seconds_ == rhs.seconds_) {
      return (lhs.nanos_ <= rhs.nanos_);
    } else {
      return (lhs.seconds_ <= rhs.seconds_);
    }
  }
  friend bool operator> (const timestamp &lhs, const timestamp &rhs) {
    return rhs < lhs;
  }
  friend bool operator== (const timestamp &lhs, const timestamp &rhs) {
    return (lhs.seconds_ == rhs.seconds_) && (lhs.nanos_ == rhs.nanos_);
  }
  friend bool operator!= (const timestamp &lhs, const timestamp &rhs) {
    return !(lhs == rhs);
  }
};

struct imu {
  imu() {
    gx_ = 0.0;
    gy_ = 0.0;
    gz_ = 0.0;
    ax_ = 0.0;
    ay_ = 0.0;
    az_ = 0.0;
  }
  imu(double gx, double gy, double gz, double ax, double ay, double az){
    gx_ = gx;
    gy_ = gy;
    gz_ = gz;
    ax_ = ax;
    ay_ = ay;
    az_ = az;
  }

  void setGyro(double x, double y, double z) {
    gx_ = x;
    gy_ = y;
    gz_ = z;
  }

  void setAccel(double x, double y, double z) {
    ax_ = x;
    ay_ = y;
    az_ = z;
  }


  double gx_, gy_, gz_;
  double ax_, ay_, az_;
};

enum SensorType {
  IMU,
  CAMERA,
};

class SensorData {
public:
  SensorData(const timestamp &time, SensorType type) : time_(time), type_(type) {};
  SensorData(int64_t seconds, int32_t nanos, SensorType type) : time_(seconds, nanos), type_(type) {};
  int64_t getSeconds();
  int32_t getNanos();
  timestamp getTimeStamp();
  SensorType getType() {return type_;};

  friend bool operator== (const SensorData &lhs, const SensorData &rhs) {
    return (lhs.type_ == rhs.type_) && (lhs.time_ == rhs.time_);
  }
  friend bool operator!= (const SensorData &lhs, const SensorData &rhs) {
    return !(lhs == rhs);
  }
private:
  timestamp time_;
  SensorType type_;
};

class ImageData : public SensorData {
public:
  ImageData(const std::string &fname, int64_t seconds, int32_t nanos) : SensorData(seconds, nanos, SensorType::CAMERA), fname_(fname)  {};
  ImageData(const std::string &fname, const timestamp &time) : SensorData(time, SensorType::CAMERA), fname_(fname) {};
  std::string getFileName() {return fname_;};
private:
  std::string fname_;
};


class ImuData : public SensorData {
public:
  ImuData(const imu &data, int64_t seconds, int32_t nanos) : SensorData(seconds, nanos, SensorType::IMU), imu_(data) {};
  ImuData(const imu &data, const timestamp &time) : SensorData(time, SensorType::IMU), imu_(data) {};
  ImuData(int64_t seconds, int32_t nanos) : SensorData(seconds, nanos, SensorType::IMU), imu_() {};
  ImuData(const timestamp &time) : SensorData(time, SensorType::IMU), imu_() {};
  imu getImu() {return imu_;};
  void setGyro(double x, double y, double z) {
    imu_.setGyro(x, y, z);
  }
  void setAccel(double x, double y, double z) {
    imu_.setAccel(x, y, z);
  }
private:
  imu imu_;
};


class DataManager {
public:
  DataManager() {};

  void add_camera(const ImageData &data) {
    camera_.push_back(data);
  }

  void add_imu(const ImuData &data) {
    imu_.push_back(data);
  }

  SensorData pop() {
    if(imu_size() > 0 && camera_size() > 0) {
      if(imu_.front().getTimeStamp() < camera_.front().getTimeStamp()) {
          auto ret = imu_.front();
          imu_.pop_front();
          return ret;
      } else {
          auto ret = camera_.front();
          camera_.pop_front();
          return ret;
      }
    } else if(imu_size() <= 0 && camera_size() > 0) {
      auto ret = camera_.front();
      camera_.pop_front();
      return ret;
    } else if(camera_size() <= 0 && imu_size() > 0) {
      auto ret = imu_.front();
      imu_.pop_front();
      return ret;
    }
  }

  std::vector<SensorData> return_in_order() {
    std::vector<SensorData> vec;
    vec.reserve(imu_size() + camera_size());
    while(imu_size() + camera_size() > 0) {
      vec.push_back(pop());
    }
    return vec;
  }

  inline size_t imu_size() {
    return imu_.size();
  }
  inline size_t camera_size() {
    return camera_.size();
  }

private:
  std::deque<ImuData> imu_;
  std::deque<ImageData> camera_;
};


} // namespace data_manager
} // namespace monovins
