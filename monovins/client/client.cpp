#include "monovins/client/client.h"

namespace monovins {
namespace client {

VinsClient::VinsClient(std::shared_ptr<grpc::Channel> channel) :
  stub_(monovins::api::monovins::MonoVinsService::NewStub(channel)) {

};

bool VinsClient::SetCamera(const std::string &fname, int id, int seconds, int nanos) {
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

bool VinsClient::SetImu(int id, int seconds, int nanos) {
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

bool VinsClient::ProcessAll() {
  ProcessAllRequest request;
  ProcessAllReply reply;
  ClientContext context;
  auto status = stub_->ProcessAll(&context, request, &reply);

  if(status.ok()) {
    return true;
  } else {
    LOG(INFO) << "ProcessAll RPC failed. gRPC error code: " << status.error_code();
    return false;
  }
}

} // namespace client
} // namespace monovins
