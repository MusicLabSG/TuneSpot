QT += quick widgets multimedia core
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++11

#android
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

# aubio
INCLUDEPATH += $$PWD/./aubio/src

QMAKE_CFLAGS += "-include $$_PRO_FILE_PWD_/CompilerFix.hpp"
QMAKE_CXXFLAGS += "-include $$_PRO_FILE_PWD_/CompilerFix.hpp"
SOURCES += ./aubio/src/pitch/pitch.c \
        ./aubio/src/fvec.c \
        ./aubio/src/utils/log.c \
        ./aubio/src/pitch/pitchyin.c \
        ./aubio/src/spectral/phasevoc.c \
        ./aubio/src/cvec.c \
        ./aubio/src/pitch/pitchmcomb.c \
        ./aubio/src/temporal/c_weighting.c \
        ./aubio/src/pitch/pitchfcomb.c \
        ./aubio/src/pitch/pitchschmitt.c \
        ./aubio/src/pitch/pitchspecacf.c \
        ./aubio/src/pitch/pitchyinfft.c \
        ./aubio/src/temporal/filter.c \
        ./aubio/src/mathutils.c \
        ./aubio/src/spectral/fft.c \
        ./aubio/src/lvec.c \
        ./aubio/src/spectral/ooura_fft8g.c

HEADERS = \
    NotesController.hpp \
    PitchBuffer.hpp \
    Configurator.hpp \
    AubioWrapper.hpp

SOURCES += \
    main.cpp \
    NotesController.cpp \
    PitchBuffer.cpp \
    Configurator.cpp \
    AubioWrapper.cpp


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
