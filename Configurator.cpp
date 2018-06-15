/*
 * File:    Configurator.cpp
 * Author:  Spiros
 *
 * Created on Jun 10, 2018, 5:28 PM
 */

#include "Configurator.hpp"
#include "Recorder.hpp"
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QtMath>

Configurator::Configurator() {
    currentFrequency = 0;
    percentageOfDistanceFromTheClosestNote = 0;
    closestNote = "";
    recorder = new Recorder();
    notesController = new NotesController();
}

Configurator::~Configurator() {
    currentFrequency = 0;
    percentageOfDistanceFromTheClosestNote = 0;
    closestNote = "";
    delete recorder;
    delete notesController;
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

    quint16 i ;
    for (i = 0; i < 88; i++) {
        if (notesController->getNoteNames()[i] == closestNote) {
            break;
        }
    }

    qreal freq = notesController->getNoteFrequencies()[i];
    qreal freqPrevious = notesController->getNoteFrequencies()[i - 1];
    qreal freqNext = notesController->getNoteFrequencies()[i + 1];

    if (currentFrequency <= freqPrevious) {
        percentageOfDistanceFromTheClosestNote = -100;
    } else if (currentFrequency >= freqNext) {
        percentageOfDistanceFromTheClosestNote = 100;
    } else if (currentFrequency >= freq){
        percentageOfDistanceFromTheClosestNote =
                ((currentFrequency - freq) / (freqNext - freq)) * 100;
    } else {
        percentageOfDistanceFromTheClosestNote =
                ((currentFrequency - freq) / (freq - freqPrevious)) * 100;
    }
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

    quint16 i ;
    for (i = 0; i < 88; i++) {
        if (notesController->getNoteNames()[i] == closestNote) {
            break;
        }
    }

    qreal freq = notesController->getNoteFrequencies()[i];
    qreal freqPrevious = notesController->getNoteFrequencies()[i - 1];
    qreal freqNext = notesController->getNoteFrequencies()[i + 1];

    if (currentFrequency <= freqPrevious) {
        percentageOfDistanceFromTheClosestNote = -100;
    } else if (currentFrequency >= freqNext) {
        percentageOfDistanceFromTheClosestNote = 100;
    } else if (currentFrequency >= freq){
        percentageOfDistanceFromTheClosestNote =
                ((currentFrequency - freq) / (freqNext - freq)) * 100;
    } else {
        percentageOfDistanceFromTheClosestNote =
                ((currentFrequency - freq) / (freq - freqPrevious)) * 100;
    }
}

void Configurator::setFreeMode() {
    quint16 minI = -1;
    qreal minDistance = 10000, test ;
    for (quint16 i = 0; i < 88; i++) {
        test = qFabs(currentFrequency - notesController->getNoteFrequencies()[i]);
        if (minDistance > test) {
            minDistance = test;
            minI = i;
        }
    }

    closestNote = notesController->getNoteNames()[minI];

    qreal freq = notesController->getNoteFrequencies()[minI];
    qreal freqPrevious = notesController->getNoteFrequencies()[minI - 1];
    qreal freqNext = notesController->getNoteFrequencies()[minI + 1];

    if (currentFrequency <= freqPrevious) {
        percentageOfDistanceFromTheClosestNote = -100;
    } else if (currentFrequency >= freqNext) {
        percentageOfDistanceFromTheClosestNote = 100;
    } else if (currentFrequency >= freq){
        percentageOfDistanceFromTheClosestNote =
                ((currentFrequency - freq) / (freqNext - freq)) * 100;
    } else {
        percentageOfDistanceFromTheClosestNote =
                ((currentFrequency - freq) / (freq - freqPrevious)) * 100;
    }
}

quint16 Configurator::getBaseFrequency() {
    return notesController->getBaseFrequency();
}

void Configurator::changeBaseFrequency(quint16 newBaseFrequency) {
    notesController->changeBaseFrequency(newBaseFrequency);
}

QString Configurator::getClosestNote() {
    return closestNote;
}

quint16 Configurator::getPercentageOfDistanceFromTheClosestNote() {
    return percentageOfDistanceFromTheClosestNote;
}

void Configurator::setCurrentFrequency() {
    recorder->recordTestFile();

    //  check only the last 100ms of the file (i have to create an 1 sec file in order to get something)
    QFile file(recorder->getOutputFilePath());

    // todo fft

    // eg
    currentFrequency = 442.3;
}
