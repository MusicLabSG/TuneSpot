/*
 * File:    Configurator.cpp
 * Author:  Spiros
 *
 * Created on Jun 16, 2018, 5:28 PM
 */

#include <Configurator.hpp>
#include <QDebug>
#include <QtMath>

Configurator::Configurator(QObject *parent) : QObject(parent) {
    applyFormat();
    recorder = std::make_unique<QAudioInput>(formatSettings);

    currentFrequency = 0;
    percentageOfDistanceFromTheClosestNote = 0;
    closestNote = "";
    setterIdentifier = "freeMode";
    notesController = new NotesController();

    connect(&pitchBuffer, SIGNAL(samplesReady()), this, SLOT(analyzeSamples()));
}

void Configurator::setActive(bool active)
{
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

void Configurator::setOrganSetter(QString setterIdentifier) {
    this->setterIdentifier = setterIdentifier;
}

void Configurator::setCloseNoteAndPercentageAccordingToSetterID() {
    if(setterIdentifier == "freeMode") {
        setFreeMode();
    } else if (setterIdentifier == "cello1") {
        setCelloXString(1);
    } else if (setterIdentifier == "cello2") {
        setCelloXString(2);
    } else if (setterIdentifier == "cello3") {
        setCelloXString(3);
    } else if (setterIdentifier == "cello4") {
        setCelloXString(4);
    } else if (setterIdentifier == "guitar1") {
        setGuitarXString(1);
    } else if (setterIdentifier == "guitar2") {
        setGuitarXString(2);
    } else if (setterIdentifier == "guitar3") {
        setGuitarXString(3);
    } else if (setterIdentifier == "guitar4") {
        setGuitarXString(4);
    } else if (setterIdentifier == "guitar5") {
        setGuitarXString(5);
    } else if (setterIdentifier == "guitar6") {
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
        if (notesController->getNoteNames()[i] == closestNote) {
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
        if (notesController->getNoteNames()[i] == closestNote) {
            break;
        }
    }

    setPercentageOfDistanceFromTheClosestNote(i);
}

void Configurator::setFreeMode() {
    quint16 minI = -1;
    qreal minDistance = 10000, test;
    for (quint16 i = 0; i < 88; i++) {
        test = qFabs(currentFrequency - notesController->getNoteFrequencies()[i]);
        if (minDistance > test) {
            minDistance = test;
            minI = i;
        }
    }

    closestNote = notesController->getNoteNames()[minI];
    setPercentageOfDistanceFromTheClosestNote(minI);
}

quint16 Configurator::getBaseFrequency() {
    return notesController->getBaseFrequency();
}

void Configurator::setBaseFrequency(quint16 newBaseFrequency) {
    notesController->changeBaseFrequency(newBaseFrequency);
}

QString Configurator::getClosestNote() {
    return closestNote;
}

qreal Configurator::getPercentageOfDistanceFromTheClosestNote() {
    return percentageOfDistanceFromTheClosestNote;
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

void Configurator::setPercentageOfDistanceFromTheClosestNote(quint16 i) {
    if (i == 0) {
        qreal freq = notesController->getNoteFrequencies()[i];
        qreal freqNext = notesController->getNoteFrequencies()[i + 1];
        if (currentFrequency >= freqNext) {
            percentageOfDistanceFromTheClosestNote = 100;
        } else if (currentFrequency >= freq) {
            percentageOfDistanceFromTheClosestNote =
                    ((currentFrequency - freq) / (freqNext - freq)) * 100;
        }
    } else if (i == 87) {
        qreal freq = notesController->getNoteFrequencies()[i];
        qreal freqPrevious = notesController->getNoteFrequencies()[i - 1];
        if (currentFrequency <= freqPrevious) {
            percentageOfDistanceFromTheClosestNote = -100;
        } else {
            percentageOfDistanceFromTheClosestNote =
                    ((currentFrequency - freq) / (freq - freqPrevious)) * 100;
        }
    } else {
        qreal freq = notesController->getNoteFrequencies()[i];
        qreal freqPrevious = notesController->getNoteFrequencies()[i - 1];
        qreal freqNext = notesController->getNoteFrequencies()[i + 1];

        if (currentFrequency <= freqPrevious) {
            percentageOfDistanceFromTheClosestNote = -100;
        } else if (currentFrequency >= freqNext) {
            percentageOfDistanceFromTheClosestNote = 100;
        } else if (currentFrequency >= freq) {
            percentageOfDistanceFromTheClosestNote =
                    ((currentFrequency - freq) / (freqNext - freq)) * 100;
        } else {
            percentageOfDistanceFromTheClosestNote = ((currentFrequency - freq) / (freq - freqPrevious)) * 100;
        }
    }
}

void Configurator::analyzeSamples() {
    // while new samples are available
    while (pitchBuffer.getSamples(aubio.aubioIn)) {
        aubio_pitch_do(aubio.getAubioPitch(), aubio.aubioIn, aubio.aubioOut);
        currentFrequency = aubio.aubioOut->data[0];

        //  float confidence = aubio_pitch_get_confidence(aubio.getAubioPitch());

        setCloseNoteAndPercentageAccordingToSetterID();

        emit samplesAnalyzed();
    }
}
