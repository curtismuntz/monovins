# DataManager

This class will maintain a buffer of sensor data. It is meant to be similar in nature to a pandas dataframe. It can hold potentially heterogeneous data types within the same time series index.

This can be used with live data as in:
* add camera data
* add imu data
* pop data

Or this can be used with completely offline datasets:
* loop thru imu data, append all
* loop thru camera data, append all
* return_in_order()
