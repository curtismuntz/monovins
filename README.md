# monovins
A monocular visual-inertial estimator.

`monovins` uses gRPC as an API for input/output of the estimator. All datasets will simply convert to the gRPC data types and interface that way.

## running
`bazel run monovins/app -- --output_photo_dir /home/murt/murt/open_source/monovins/data-out/frames`.

then from another terminal:
`bazel run datasets/kmav_dataset -- --data_folder /home/murt/murt/open_source/monovins/data-in/V1_01_easy`

## debugging
debugging output frames can be accomplished via [Natron](https://natrongithub.github.io/). I recommend installing via flatpak: `flatpak install flathub fr.natron.Natron`

# Additional Information
## why cpp?
I need to practice for interviews in c++.

## TODO
* Solve highgui build using bazel. QT? moc_window_QT.h/cpp?
