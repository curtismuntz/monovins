#pragma once
#include <stdint.h>
#include <glog/logging.h>

namespace monovins {
namespace filter {
namespace ukf {

class UKF {
public:
  UKF() {};
private:

};

/*
  Functions that are written in rust!
*/
extern "C" {
  void hello_world();
}

void woo();

} // namespace ukf
} // namespace filter
} // namespace monovins
