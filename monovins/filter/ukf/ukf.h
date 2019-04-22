#pragma once
#include <glog/logging.h>
#include <stdint.h>

namespace monovins {
namespace filter {
namespace ukf {

template <int KALMAN_STATES, int KALMAN_MEASUREMENTS>
class UKF {
 public:
  UKF(){};
  void state_update();
  void measurement_update();

 private:
};

/*
  Functions that are written in rust!
*/
extern "C" {
void hello_world();
}

void woo();

}  // namespace ukf
}  // namespace filter
}  // namespace monovins
