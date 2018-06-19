/*
 * File:    Configurator.cpp
 * Author:  Spiros
 *
 * Created on Jun 16, 2018, 5:28 PM
 */

#include <Configurator.hpp>
#include <QDebug>
#include <QtMath>

#ifdef Q_OS_ANDROID
    #include <QtAndroidExtras/QtAndroid>
#endif

Configurator::Configurator(QObject *parent) : QObject(parent) {
#ifdef Q_OS_ANDROID
    QtAndroid::requestPermissionsSync( QStringList() << "android.permission.RECORD_AUDIO" );
#endif

    applyFormat();
    recorder = std::make_unique<QAudioInput>(formatSettings);

    currentFrequency = 0;
    lastConfidentFrequency = 0;
    percentageOfDistanceFromTheClosestNote = 0;
    closestNote = "";
    organSetter = "freeMode";

    connect(&pitchBuffer, SIGNAL(samplesReady()), this, SLOT(analyzeSamples()));
}

void Configurator::setActive(bool active) {
    if (active) {
        if (!pitchBuffer.open(QIODevice::WriteOnly)) {
            qDebug() << "Something went wrong while opening the device";
        }
        recorder->start(&pitchBuffer);
    } else {
        recorder->stop();
    }
    activeTuner = active;
}

void Configurator::setOrganSetter(QString setter) {
    organSetter = setter;

    emit organSetterChanged();
}

QString Configurator::getOrganSetter() {
    return organSetter;
}


quint16 Configurator::getBaseFrequency() {
    return notesController.getBaseFrequency();
}

void Configurator::setBaseFrequency(quint16 newBaseFrequency) {
    notesController.changeBaseFrequency(newBaseFrequency);

    emit baseFrequencyChanged();
}

QString Configurator::getClosestNote() {
    return closestNote;
}

qreal Configurator::getPercentageOfDistanceFromTheClosestNote() {
    return percentageOfDistanceFromTheClosestNote;
}

qreal Configurator::getFrequency() {
    return lastConfidentFrequency;
}

void Configurator::applyFormat() {
    formatSettings.setCodec("audio/pcm");
    formatSettings.setChannelCount(1);
    formatSettings.setSampleRate(48000);
    formatSettings.setSampleType(QAudioFormat::SampleType::Float);
    formatSettings.setSampleSize(sizeof(float) * 8);

    // test if the format is supported
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(formatSettings)) {
        qWarning() << "Default format not supported, trying to use 16bit signed integer samples";
        formatSettings = info.nearestFormat(formatSettings);
    }
    pitchBuffer.setSampleType(formatSettings.sampleType(), formatSettings.sampleSize() / 8);
}


void Configurator::setCloseNoteAndPercentageAccordingToSetterID() {
    if(organSetter == "freeMode") {
        setFreeMode();
    } else if (organSetter == "cello1") {
        setCelloXString(1);
    } else if (organSetter == "cello2") {
        setCelloXString(2);
    } else if (organSetter == "cello3") {
        setCelloXString(3);
    } else if (organSetter == "cello4") {
        setCelloXString(4);
    } else if (organSetter == "guitar1") {
        setGuitarXString(1);
    } else if (organSetter == "guitar2") {
        setGuitarXString(2);
    } else if (organSetter == "guitar3") {
        setGuitarXString(3);
    } else if (organSetter == "guitar4") {
        setGuitarXString(4);
    } else if (organSetter == "guitar5") {
        setGuitarXString(5);
    } else if (organSetter == "guitar6") {
        setGuitarXString(6);
    }
}

void Configurator::setCelloXString(quint16 x) {
    if (x == 1) {
        closestNote = "A3";
    } else if (x == 2) {
        closestNote = "D3";
    } else if (x == 3) {
        closestNote = "G2";
    } else if (x == 4) {
        closestNote = "C2";
    }

    quint16 i;
    for (i = 0; i < 88; i++) {
        if (notesController.getNoteNames()[i] == closestNote) {
            break;
        }
    }

    setPercentageOfDistanceFromTheClosestNote(i);
}

void Configurator::setGuitarXString(quint16 x) {
    if (x == 1) {
        closestNote = "E4";
    } else if (x == 2) {
        closestNote = "B3";
    } else if (x == 3) {
        closestNote = "G3";
    } else if (x == 4) {
        closestNote = "D3";
    } else if (x == 5) {
        closestNote = "A2";
    } else if (x == 6) {
        closestNote = "E2";
    }

    quint16 i;
    for (i = 0; i < 88; i++) {
        if (notesController.getNoteNames()[i] == closestNote) {
            break;
        }
    }

    setPercentageOfDistanceFromTheClosestNote(i);
}

void Configurator::setFreeMode() {
    quint16 minI = -1;
    qreal minDistance = 10000, test;
    for (quint16 i = 0; i < 88; i++) {
        test = qFabs(lastConfidentFrequency - notesController.getNoteFrequencies()[i]);
        if (minDistance > test) {
            minDistance = test;
            minI = i;
        }
    }

    closestNote = notesController.getNoteNames()[minI];
    setPercentageOfDistanceFromTheClosestNote(minI);
}

void Configurator::setPercentageOfDistanceFromTheClosestNote(quint16 i) {
    if (i == 0) {
        qreal freq = notesController.getNoteFrequencies()[i];
        qreal freqNext = notesController.getNoteFrequencies()[i + 1];
        if (lastConfidentFrequency >= freqNext) {
            percentageOfDistanceFromTheClosestNote = 100;
        } else if (lastConfidentFrequency >= freq) {
            percentageOfDistanceFromTheClosestNote =
                    ((lastConfidentFrequency - freq) / (freqNext - freq)) * 100;
        }
    } else if (i == 87) {
        qreal freq = notesController.getNoteFrequencies()[i];
        qreal freqPrevious = notesController.getNoteFrequencies()[i - 1];
        if (lastConfidentFrequency <= freqPrevious) {
            percentageOfDistanceFromTheClosestNote = -100;
        } else {
            percentageOfDistanceFromTheClosestNote =
                    ((lastConfidentFrequency - freq) / (freq - freqPrevious)) * 100;
        }
    } else {
        qreal freq = notesController.getNoteFrequencies()[i];
        qreal freqPrevious = notesController.getNoteFrequencies()[i - 1];
        qreal freqNext = notesController.getNoteFrequencies()[i + 1];

        if (lastConfidentFrequency <= freqPrevious) {
            percentageOfDistanceFromTheClosestNote = -100;
        } else if (lastConfidentFrequency >= freqNext) {
            percentageOfDistanceFromTheClosestNote = 100;
        } else if (lastConfidentFrequency >= freq) {
            percentageOfDistanceFromTheClosestNote =
                    ((lastConfidentFrequency - freq) / (freqNext - freq)) * 100;
        } else {
            percentageOfDistanceFromTheClosestNote = ((lastConfidentFrequency - freq) / (freq - freqPrevious)) * 100;
        }
    }


    if (percentageOfDistanceFromTheClosestNote > 50 ) {
        percentageOfDistanceFromTheClosestNote = 100;
    } else if (percentageOfDistanceFromTheClosestNote < -50) {
        percentageOfDistanceFromTheClosestNote = -100;
    } else {
       percentageOfDistanceFromTheClosestNote *= 2;
    }
}

void Configurator::analyzeSamples() {
    // while new samples are available
    while (pitchBuffer.getSamples(aubio.aubioIn)) {
        //  recognize the pitch
        aubio_pitch_do(aubio.getAubioPitch(), aubio.aubioIn, aubio.aubioOut);

        currentFrequency = aubio.aubioOut->data[0];
        float confidence = aubio_pitch_get_confidence(aubio.getAubioPitch());

        if (confidence >= confidenceThresHold) {
            lastConfidentFrequency = currentFrequency;
            qDebug() << lastConfidentFrequency << "\n";
        }

        setCloseNoteAndPercentageAccordingToSetterID();

        emit samplesAnalyzed();
    }
}
