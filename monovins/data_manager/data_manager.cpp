#include "monovins/data_manager/data_manager.h"

namespace monovins {
namespace data_manager {

int64_t SensorData::getSeconds() {
  return time_.seconds_;
}

int32_t SensorData::getNanos() {
  return time_.nanos_;
};

timestamp SensorData::getTimeStamp() {
  return time_;
}

} // namespace data_manager
} // namespace monovins
