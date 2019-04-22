#include "monovins/data_manager/data_manager.h"
#include "gtest/gtest.h"

namespace monovins {
namespace data_manager {
namespace {

// TODO(curtismuntz) add more meaningful tests
TEST(BasicSensorTests, All) {
  auto vo = ImageData("test.jpg", 100, 1);
  ASSERT_EQ(vo.getSeconds(), 100);
  auto imu = ImuData(1,2);
  ASSERT_EQ(imu.getNanos(), 2);
}

TEST(TimestampTests, All) {
  auto t1 = timestamp(1, 1);
  auto t2 = timestamp(1, 1);
  auto t3 = timestamp(3, 0);
  auto t4 = timestamp(3, 1);
  ASSERT_TRUE(t1 == t2);
  ASSERT_TRUE(t1 != t3);
  ASSERT_TRUE(t1 < t3);
  ASSERT_TRUE(t3 < t4);
  ASSERT_TRUE(t4 > t1);
}

TEST(QueueTests, All) {
  auto vo1 = ImageData("test.jpg", timestamp(20,300));
  auto imu1 = ImuData(timestamp(20,400));
  auto imu2 = ImuData(timestamp(20,420));
  auto vo2 = ImageData("test.jpg", timestamp(20,600));
  auto imu3 = ImuData(timestamp(20,620));

  auto dm = DataManager();
  ASSERT_EQ(dm.imu_size(), 0);
  ASSERT_EQ(dm.camera_size(), 0);

  dm.add_camera(vo1);
  dm.add_camera(vo2);
  dm.add_imu(imu1);
  dm.add_imu(imu2);
  dm.add_imu(imu3);

  ASSERT_EQ(dm.imu_size(), 3);
  ASSERT_EQ(dm.camera_size(), 2);

  ASSERT_TRUE(dm.pop().getTimeStamp() == vo1.getTimeStamp());
  ASSERT_EQ(dm.camera_size(), 1);
  ASSERT_TRUE(dm.pop().getTimeStamp() == imu1.getTimeStamp());
  ASSERT_TRUE(dm.pop().getTimeStamp() == imu2.getTimeStamp());
  ASSERT_TRUE(dm.pop().getTimeStamp() == vo2.getTimeStamp());
  ASSERT_TRUE(dm.pop().getTimeStamp() == imu3.getTimeStamp());
  ASSERT_EQ(dm.imu_size(), 0);
  ASSERT_EQ(dm.camera_size(), 0);
}

TEST(ReturnInOrder, All) {
  auto vo1 = ImageData("test.jpg", timestamp(20,300));
  auto imu1 = ImuData(timestamp(20,400));
  auto imu2 = ImuData(timestamp(20,420));
  auto vo2 = ImageData("test.jpg", timestamp(20,600));
  auto imu3 = ImuData(timestamp(20,620));

  auto dm = DataManager();
  ASSERT_EQ(dm.imu_size(), 0);
  ASSERT_EQ(dm.camera_size(), 0);

  dm.add_camera(vo1);
  dm.add_camera(vo2);
  dm.add_imu(imu1);
  dm.add_imu(imu2);
  dm.add_imu(imu3);

  std::vector<SensorData> expected;
  expected.push_back(vo1);
  expected.push_back(imu1);
  expected.push_back(imu2);
  expected.push_back(vo2);
  expected.push_back(imu3);

  ASSERT_TRUE(dm.return_in_order() == expected);
}


}  // namespace
}  // namespace data_manager
}  // namespace monovins

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
