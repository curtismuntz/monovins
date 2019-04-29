#pragma once

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <grpc++/security/server_credentials.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc/grpc.h>
#include <grpc/support/log.h>
#include <opencv2/core/core.hpp>
#include <thread>

#include "monovins/api/monovins.grpc.pb.h"
#include "monovins/dataframe/dataframe.h"
#include "monovins/filter/ukf/ukf.h"
#include "monovins/vision/odometer/odometer.h"

namespace monovins {
namespace app {

using grpc::Server;
using grpc::ServerAsyncWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;
using monovins::api::monovins::GetPoseReply;
using monovins::api::monovins::GetPoseRequest;
using monovins::api::monovins::MonoVinsService;
using monovins::api::monovins::ProcessAllReply;
using monovins::api::monovins::ProcessAllRequest;
using monovins::api::monovins::SetDataReply;
using monovins::api::monovins::SetDataRequest;

class MonoVins final : public MonoVinsService::Service {
 public:
  MonoVins() { LOG(INFO) << "Starting MonoVins"; };
  Status SetData(ServerContext *context, const SetDataRequest *request,
                 SetDataReply *reply) override;
  Status GetPose(ServerContext *context, const GetPoseRequest *request,
                 GetPoseReply *reply) override;
  Status ProcessAll(ServerContext *context, const ProcessAllRequest *request,
                    ProcessAllReply *reply) override;

 private:
  monovins::dataframe::DataManager dataman_;
  monovins::vision::odometer::MonoVo monovo_;
  monovins::filter::ukf::UKF ukf_;
};

void RunServer();

}  // namespace app
}  // namespace monovins
