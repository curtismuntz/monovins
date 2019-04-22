#include "monovins/app/app.h"

namespace monovins {
namespace app {

Status MonoVins::SetData(ServerContext *context, const SetDataRequest *request,
                         SetDataReply *reply) {
  if (request->has_camera()) {
    auto fname = request->camera().filename();
    LOG(INFO) << "new camera frame received: " << fname
              << " at time: " << request->camera().timestamp().seconds() << "."
              << request->camera().timestamp().nanos();
    auto t = monovins::data_manager::timestamp(request->camera().timestamp().seconds(),
                                               request->camera().timestamp().nanos());
    auto imgdata = monovins::data_manager::SensorData(fname, t);
    dataman_.add_camera(imgdata);
    return Status::OK;
  } else if (request->has_imu()) {
    LOG(INFO) << "new imu frame recieved. ";
    auto t = monovins::data_manager::timestamp(request->imu().timestamp().seconds(),
                                               request->camera().timestamp().nanos());
    auto imudata = monovins::data_manager::SensorData(t);
    auto gx = request->imu().gyroscope().x();
    auto gy = request->imu().gyroscope().y();
    auto gz = request->imu().gyroscope().z();
    imudata.setGyro(gx, gy, gz);
    auto ax = request->imu().accelerometer().x();
    auto ay = request->imu().accelerometer().y();
    auto az = request->imu().accelerometer().z();
    imudata.setAccel(ax, ay, az);
    dataman_.add_imu(imudata);
    return Status::OK;
  } else {
    // TODO(curtismuntz) use this instead:
    // return Status::INVALID_ARGUMENT
    return Status::CANCELLED;
  }
}

Status MonoVins::ProcessAll(ServerContext *context, const ProcessAllRequest *request,
                            ProcessAllReply *reply) {
  LOG(INFO) << "Processing all data in buffer.";
  auto vec = dataman_.return_in_order();
  LOG(INFO) << vec.size() << " elements.";
  for (size_t i = 0; i < vec.size(); ++i) {
    if (vec[i].getType() == monovins::data_manager::SensorType::CAMERA) {
      auto fname = vec[i].getFileName();
      LOG(INFO) << "  " << fname;
      monovo_.process(fname);
    }
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

}  // namespace app
}  // namespace monovins
