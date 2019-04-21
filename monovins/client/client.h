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
using monovins::api::monovins::SetDataRequest;
using monovins::api::monovins::SetDataReply;
using monovins::api::Camera;

class VinsClient {
public:
  VinsClient(std::shared_ptr<grpc::Channel> channel) : stub_(monovins::api::monovins::MonoVinsService::NewStub(channel)) {};

  bool SetCamera(const std::string &fname, int id, int seconds, int nanos) {
    SetDataRequest request;
    request.mutable_camera()->mutable_timestamp()->set_seconds(seconds);
    request.mutable_camera()->mutable_timestamp()->set_nanos(nanos);
    request.mutable_camera()->set_id(id);
    request.mutable_camera()->set_filename(fname);

    SetDataReply reply;
    ClientContext context;
    auto status = stub_->SetData(&context, request, &reply);

    if(status.ok()) {
      return true;
    } else {
      LOG(INFO) << "SetData (camera) RPC failed. gRPC error code: " << status.error_code();
      return false;
    }
  }

  bool SetImu(int id, int seconds, int nanos) {
    SetDataRequest request;
    request.mutable_imu()->mutable_timestamp()->set_seconds(seconds);
    request.mutable_imu()->mutable_timestamp()->set_nanos(nanos);
    request.mutable_imu()->set_id(id);
    request.mutable_imu()->mutable_gyroscope()->set_x(1.0);
    request.mutable_imu()->mutable_gyroscope()->set_y(2.0);
    request.mutable_imu()->mutable_gyroscope()->set_z(3.0);
    request.mutable_imu()->mutable_accelerometer()->set_x(4.0);
    request.mutable_imu()->mutable_accelerometer()->set_y(5.0);
    request.mutable_imu()->mutable_accelerometer()->set_z(6.0);

    SetDataReply reply;
    ClientContext context;
    auto status = stub_->SetData(&context, request, &reply);

    if(status.ok()) {
      return true;
    } else {
      LOG(INFO) << "SetData (imu) RPC failed. gRPC error code: " << status.error_code();
      return false;
    }
  }

private:
  std::unique_ptr<monovins::api::monovins::MonoVinsService::Stub> stub_;
};


} // namespace client
} // namespace monovins
