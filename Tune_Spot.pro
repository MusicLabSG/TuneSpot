CONFIG += c++11
QT += quick
QT += widgets
QT += multimedia
QT += core
android : QT += androidextras

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS = \
    NotesController.hpp \
    Configurator.hpp \
    Recorder.hpp \
    core.h \
    AudioFile.h \
    PitchDetection/aubio/include/aubio/aubio.h \
    PitchDetection/aubio/include/aubio/aubio_priv.h \
    PitchDetection/aubio/include/aubio/beattracking.h \
    PitchDetection/aubio/include/aubio/biquad.h \
    PitchDetection/aubio/include/aubio/fft.h \
    PitchDetection/aubio/include/aubio/filter.h \
    PitchDetection/aubio/include/aubio/hist.h \
    PitchDetection/aubio/include/aubio/mathutils.h \
    PitchDetection/aubio/include/aubio/onset.h \
    PitchDetection/aubio/include/aubio/onsetdetection.h \
    PitchDetection/aubio/include/aubio/peakpick.h \
    PitchDetection/aubio/include/aubio/phasevoc.h \
    PitchDetection/aubio/include/aubio/pitchdetection.h \
    PitchDetection/aubio/include/aubio/pitchfcomb.h \
    PitchDetection/aubio/include/aubio/pitchmcomb.h \
    PitchDetection/aubio/include/aubio/pitchschmitt.h \
    PitchDetection/aubio/include/aubio/pitchyin.h \
    PitchDetection/aubio/include/aubio/pitchyinfft.h \
    PitchDetection/aubio/include/aubio/resample.h \
    PitchDetection/aubio/include/aubio/sample.h \
    PitchDetection/aubio/include/aubio/scale.h \
    PitchDetection/aubio/include/aubio/tempo.h \
    PitchDetection/aubio/include/aubio/tss.h \
    PitchDetection/aubio/include/aubio/types.h \
    PitchDetection/aubio/include/fft/fftw3.h \
    PitchDetection/aubio/include/libsamplerate/common.h \
    PitchDetection/aubio/include/libsamplerate/config.h \
    PitchDetection/aubio/include/libsamplerate/fastest_coeffs.h \
    PitchDetection/aubio/include/libsamplerate/float_cast.h \
    PitchDetection/aubio/include/libsamplerate/high_qual_coeffs.h \
    PitchDetection/aubio/include/libsamplerate/mid_qual_coeffs.h \
    PitchDetection/aubio/include/libsamplerate/samplerate.h \
    PitchDetection/aubio/include/libsndfile/sndfile.h \
    PitchDetection/aubio/include/libsndfile/sndfile.hh \
    PitchDetection/aubioAnalyzer.h \
    AudioFile.h \
    Configurator.hpp \
    core.h \
    NotesController.hpp \
    Recorder.hpp

SOURCES += \
    main.cpp \
    Recorder.cpp \
    Configurator.cpp \
    NotesController.cpp \
    core.cpp \
    AudioFile.cpp \
    PitchDetection/aubioAnalyzer.cpp \
    AudioFile.cpp \
    Configurator.cpp \
    core.cpp \
    main.cpp \
    NotesController.cpp \
    Recorder.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    data/fonts/OpenSans-Bold.ttf \
    data/fonts/OpenSans-BoldItalic.ttf \
    data/fonts/OpenSans-ExtraBold.ttf \
    data/fonts/OpenSans-ExtraBoldItalic.ttf \
    data/fonts/OpenSans-Italic.ttf \
    data/fonts/OpenSans-Light.ttf \
    data/fonts/OpenSans-LightItalic.ttf \
    data/fonts/OpenSans-Regular.ttf \
    data/fonts/OpenSans-SemiBold.ttf \
    data/fonts/OpenSans-SemiBoldItalic.ttf\
    data/notes/namesOfNotes.txt \
    PitchDetection/aubio/lib/aubioOSX.a
