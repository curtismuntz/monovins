# monovins
A monocular visual-inertial estimator.

`monovins` uses gRPC as an API for input/output of the estimator. All datasets will simply convert to the gRPC data types and interface that way.

## running
`bazel run monovo/app -- --photo $HOME/murt/open_source/monovo/data-in/Lenna.png --output_photo_dir $HOME/murt/open_source/monovo/data-out/frames --video $HOME/murt/open_source/monovo/data-in/monitor.avi`.

## debugging
debugging output frames can be accomplished via [Natron](https://natrongithub.github.io/). I recommend installing via flatpak: `flatpak install flathub fr.natron.Natron`

# Additional Information
## why cpp?
I need to practice for interviews in c++.

## TODO
* Solve highgui build using bazel. QT? moc_window_QT.h/cpp?
