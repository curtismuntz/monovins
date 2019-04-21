#pragma once

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <grpc++/security/server_credentials.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc/grpc.h>
#include <grpc/support/log.h>
#include <thread>
#include <opencv2/core/core.hpp>

#include "monovins/vision/odometer/odometer.h"
#include "monovins/filter/ukf/ukf.h"
#include "monovins/data_manager/data_manager.h"
#include "monovins/api/monovins.grpc.pb.h"

namespace monovins {
namespace app {

using grpc::Server;
using grpc::ServerWriter;
using grpc::ServerAsyncWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;
using monovins::api::monovins::MonoVinsService;
using monovins::api::monovins::SetDataRequest;
using monovins::api::monovins::SetDataReply;
using monovins::api::monovins::GetPoseRequest;
using monovins::api::monovins::GetPoseReply;

class MonoVins final : public MonoVinsService::Service {
public:
  MonoVins() {
    LOG(INFO) << "Starting MonoVins";
  };
  Status SetData(ServerContext *context, const SetDataRequest *request,
                        SetDataReply *reply) override;
  Status GetPose(ServerContext *context, const GetPoseRequest *request,
                      GetPoseReply *reply) override;

private:
  monovins::data_manager::DataManager dataman_;
  monovins::vision::odometer::MonoVo monovo_;
  monovins::filter::ukf::UKF ukf_;
};


void RunServer();


} // namespace app
} // namespace monovins
