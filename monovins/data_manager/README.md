# DataManager

This class will maintain a buffer of sensor data.

This can be used with live data as in:
* add camera data
* add imu data
* pop data

Or this can be used with completely offline datasets:
* loop thru imu data, append all
* loop thru camera data, append all
* return_in_order()
