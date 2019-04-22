#include <gflags/gflags.h>
#include <glog/logging.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "monovins/api/monovins.grpc.pb.h"

namespace monovins {
namespace client {

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using monovins::api::Camera;
using monovins::api::monovins::ProcessAllReply;
using monovins::api::monovins::ProcessAllRequest;
using monovins::api::monovins::SetDataReply;
using monovins::api::monovins::SetDataRequest;

class VinsClient {
 public:
  VinsClient(std::shared_ptr<grpc::Channel> channel);
  bool SetCamera(const std::string &fname, int id, int seconds, int nanos);
  bool SetImu(double gx, double gy, double gz, double ax, double ay, double az, int id, int seconds,
              int nanos);
  bool ProcessAll();

 private:
  std::unique_ptr<monovins::api::monovins::MonoVinsService::Stub> stub_;
};

}  // namespace client
}  // namespace monovins
