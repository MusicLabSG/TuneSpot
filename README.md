![alt tag](https://i.imgur.com/M9HlvZR.png)


Tune Spot requires:

* A C++ compiler with C++14 support
* make
* At least Qt 5.10
* The following Qt modules:
	- Qt Core 
	- Qt Quick (qt5-declarative)
	- Qt QML
	- Qt widgets
	- Qt Quick Controls 2 (qt5-quickcontrols2)
	- Qt Multimedia (qt5-multimedia)
* Aubio (Pulled as a submodule)

## Building

First make sure, that you have pulled the aubio sumbodule.
Either clone with the `--recursive` flag, or run `git submodule update --init` in the already cloned repo.

# Acknowledgements
- QuickPitch uses [aubio](https://github.com/aubio/aubio) for audio processing