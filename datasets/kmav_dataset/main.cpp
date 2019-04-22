#include <gflags/gflags.h>
#include <glog/logging.h>
#include <fstream>
#include <iostream>
#include <string>
#include "monovins/client/client.h"
#include "csv.h"

namespace {

using monovins::client::VinsClient;

DEFINE_bool(verbose, false, "Display program name before message");
DEFINE_string(data_folder, "", "Data folder containing kmav dataset");

std::pair<uint64_t, uint32_t> convertToSecNano(const long long int time) {
  std::pair<uint64_t, uint32_t> pair;
  uint64_t seconds = floor(time / int(1e9));
  uint32_t nanos = time - (seconds * int(1e9));
  pair.first = seconds;
  pair.second = nanos;
  return pair;
}

void run_dataset(std::string folder_name) {
  auto client = VinsClient(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
  auto imu_csv = FLAGS_data_folder + "/mav0/imu0/data.csv";
  auto cam_csv = FLAGS_data_folder + "/mav0/cam0/data.csv";
  auto cam_folder = FLAGS_data_folder + "/mav0/cam0/data/";

  io::CSVReader<2> cam_in(cam_csv);
  cam_in.read_header(io::ignore_extra_column, "#timestamp [ns]", "filename");
  long long int cam_time; std::string fname;
  int cam_id = 0;
  while(cam_in.read_row(cam_time, fname)){
    auto time_pair = convertToSecNano(cam_time);
    auto filename = cam_folder + fname;
    client.SetCamera(filename, cam_id, time_pair.first, time_pair.second);
  }

  io::CSVReader<7> imu_in(imu_csv);
  imu_in.read_header(io::ignore_extra_column,
    "#timestamp [ns]", "w_RS_S_x [rad s^-1]", "w_RS_S_y [rad s^-1]",
    "w_RS_S_z [rad s^-1]", "a_RS_S_x [m s^-2]", "a_RS_S_y [m s^-2]",
    "a_RS_S_z [m s^-2]");
  long long int imu_time;
  double gx, gy, gz, ax, ay, az;
  int imu_id = 0;
  while(imu_in.read_row(imu_time, gx, gy, gz, ax, ay, az)){
    auto time_pair = convertToSecNano(imu_time);
    client.SetImu(gx, gy, gz, ax, ay, az, imu_id, time_pair.first, time_pair.second);
  }

  client.ProcessAll();
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
