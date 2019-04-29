#include "monovins/dataframe/dataframe.h"

namespace monovins {
namespace dataframe {

int64_t SensorData::getSeconds() { return time_.seconds_; }

int32_t SensorData::getNanos() { return time_.nanos_; };

timestamp SensorData::getTimeStamp() { return time_; }

}  // namespace dataframe
}  // namespace monovins
