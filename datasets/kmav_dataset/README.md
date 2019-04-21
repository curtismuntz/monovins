# EuRoC MAV Dataset

https://projects.asl.ethz.ch/datasets/doku.php?id=kmavvisualinertialdatasets

# Getting:
`wget robotics.ethz.ch/~asl-datasets/ijrr_euroc_mav_dataset/vicon_room1/V1_01_easy/V1_01_easy.zip`

# TODO:
Write a parser. Looks like

IMU:
imu.csv --> timestamp, {data}

Camera:
camera.csv --> timestamp, {data} (where data includes a filename to look up)

Vicon:
vicon.csv -->timestamp, {data}

Simplest way is to merge these csv's using timestamp as a key, then iterate over the resultant csv.
