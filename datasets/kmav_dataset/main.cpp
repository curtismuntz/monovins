#include <gflags/gflags.h>
#include <glog/logging.h>

#include "monovins/client/client.h"

namespace {

using monovins::client::VinsClient;

DEFINE_bool(verbose, false, "Display program name before message");
DEFINE_string(data_folder, "", "Data folder containing kmav dataset");

void run_dataset(std::string folder_name) {
  auto client = VinsClient(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

}

} // namespace




int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::SetUsageMessage("Some usage message here");
  FLAGS_logtostderr = 1;
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  run_dataset(FLAGS_data_folder);
  gflags::ShutDownCommandLineFlags();
  return 0;
}
