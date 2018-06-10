/*
 * File:    Configurator.cpp
 * Author:  Spiros
 *
 * Created on Jun 10, 2018, 5:28 PM
 */

#include "Configurator.h"
#include "Recorder.h"
#include <QFile>
#include <QtMath>

Configurator::Configurator() {
    currentFrequency = 0;
    percentageOfDistanceFromTheClosestNote = 0;
    closestNote = "";
    recorder = new Recorder();
    readBaseFrequency();
    readNotes();
}

Configurator::~Configurator() {
    currentFrequency = 0;
    percentageOfDistanceFromTheClosestNote = 0;
    closestNote = "";
    delete recorder;
    baseFrequency = 440;
    notes.clear();
}

void Configurator::setCelloXString(quint16 x) {
    if (x == 1) {
        closestNote == "A3";
    } else if (x == 2) {
        closestNote == "D3";
    } else if (x == 3) {
        closestNote == "G2";
    } else if (x == 4) {
        closestNote == "C2";
    }
    // todo
}

void Configurator::setGuitarXString(quint16 x) {
    if (x == 1) {
        closestNote == "E4";
    } else if (x == 2) {
        closestNote == "B3";
    } else if (x == 3) {
        closestNote == "G3";
    } else if (x == 4) {
        closestNote == "D3";
    } else if (x == 5) {
        closestNote == "A2";
    } else if (x == 6) {
        closestNote == "E2";
    }
    // todo
}

void Configurator::setFreeMode() {
    // todo
}

quint16 Configurator::getBaseFrequency() {
    return baseFrequency;
}

void Configurator::changeBaseFrequency(quint16 frequency) {
    baseFrequency = frequency;

    qreal freq;
    for (quint16 i = 1; i <= 88; i++) {
       freq = frequency * qPow(2, (i - 49) / 12.0);
    }
    // todo
}

QString Configurator::getClosestNote() {
    // todo
    return closestNote;
}

quint16 Configurator::getPercentageOfDistanceFromTheClosestNote() {
    // todo
    return percentageOfDistanceFromTheClosestNote;
}

void Configurator::readBaseFrequency() {
    // todo
}

void Configurator::readNotes() {
    // todo
}

QString Configurator::findClosestNote() {
    // todo

    // eg
    closestNote = "A2";
    return "";
}

void Configurator::setCurrentFrequency() {
    recorder->recordForXMilliseconds(100);

    QFile file(recorder->getOutputFilePath());
    // todo fft

    // eg
    currentFrequency = 654.5;

    recorder ->deleteTestFile();
}
