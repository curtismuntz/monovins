#include "monovins/app/app.h"

namespace monovins {
namespace app {


Status MonoVins::SetData (ServerContext *context, const SetDataRequest *request,
                      SetDataReply *reply) {
  if(request->has_camera()) {
    auto fname = request->camera().filename();
    LOG(INFO) << "new camera frame received: " << fname << " at time: " << request->camera().timestamp().seconds() << "." << request->camera().timestamp().nanos();
    monovo_.process(fname);
  } else if (request->has_imu()) {
    LOG(INFO) << "new imu frame recieved. ";
  }
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
