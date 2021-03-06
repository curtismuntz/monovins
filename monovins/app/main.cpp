#include <gflags/gflags.h>
#include <glog/logging.h>

#include "monovins/app/app.h"

DEFINE_bool(verbose, false, "Display program name before message");

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::SetUsageMessage("Some usage message here");
  FLAGS_logtostderr = 1;
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  monovins::app::RunServer();
  gflags::ShutDownCommandLineFlags();
  return 0;
}
