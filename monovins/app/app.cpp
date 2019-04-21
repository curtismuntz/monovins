#include "monovins/app/app.h"

namespace monovins {
namespace app {


Status MonoVins::SetData (ServerContext *context, const SetDataRequest *request,
                      SetDataReply *reply) {
  return Status::OK;
}

Status MonoVins::GetPose(ServerContext *context, const GetPoseRequest *request,
                    GetPoseReply *reply) {
  return Status::OK;
}

void RunServer() {
   const std::string kServerAddress{"0.0.0.0:50051"};
   MonoVins service;
   ServerBuilder builder;
   builder.AddListeningPort(kServerAddress, grpc::InsecureServerCredentials());
   builder.RegisterService(&service);
   std::unique_ptr<Server> server(builder.BuildAndStart());
   LOG(INFO) << "Server listening on " << kServerAddress << std::endl;
   server->Wait();
}

} // namespace app
} // namespace monovins
