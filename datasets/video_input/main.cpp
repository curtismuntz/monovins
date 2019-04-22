#include <gflags/gflags.h>
#include <glog/logging.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/videoio.hpp"

#include "monovins/client/client.h"

namespace {

using monovins::client::VinsClient;
DEFINE_string(video, "", "video input file");
DEFINE_string(tmp_photo_dir, "/tmp", "Output photo directory");
void run_dataset(const std::string video_name) {
  auto client =
      VinsClient(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

  LOG(INFO) << "opening " << video_name;
  cv::VideoCapture cap(video_name);
  cv::Mat frame;
  unsigned int frame_count = 0;
  while (1) {
    cap >> frame;
    if (frame.empty()) {
      break;
      LOG(INFO) << "End of video";
    }
    auto fname = FLAGS_tmp_photo_dir + "/" + std::to_string(frame_count) + ".jpg";
    cv::imwrite(fname, frame);
    client.SetCamera(fname, 0, floor(frame_count / 30), ceil(frame_count % 30) * 33333333);
    // client.SetImu(0, floor(frame_count / 30), ceil(frame_count % 30) * 33333333);
    ++frame_count;
  }

  client.ProcessAll();
}

}  // namespace

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::SetUsageMessage("Some usage message here");
  FLAGS_logtostderr = 1;
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  run_dataset(FLAGS_video);
  gflags::ShutDownCommandLineFlags();
  return 0;
}
