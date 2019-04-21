#include <gflags/gflags.h>
#include <glog/logging.h>
#include <opencv2/core/core.hpp>

#include "monovins/app/app.h"

namespace {

DEFINE_bool(verbose, false, "Display program name before message");
DEFINE_string(video, "", "video input file");

void run_dataset(std::string fname) {
  auto cap = cv::VideoCapture(fname);
  auto mv = monovins::app::MonoVins();

  cv::Mat frame;
  while(1){
    cap >> frame;
    if (frame.empty()) {
      break;
    }
    mv.add_camera(frame);
    mv.process();
  }

  cap.release();
}

} // namespace




int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::SetUsageMessage("Some usage message here");
  FLAGS_logtostderr = 1;
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  monovins::filter::ukf::woo();
  run_dataset(FLAGS_video);
  gflags::ShutDownCommandLineFlags();
  return 0;
}
