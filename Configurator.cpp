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
#include <QtMath>
#include "AudioFile.h"
#include "yin.h"

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

    quint16 i ;
    for (i = 0; i < 88; i++) {
        if (notesController->getNoteNames()[i] == closestNote) {
            break;
        }
    }

    setPercentageOfDistanceFromTheClosestNote(i);
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
    setPercentageOfDistanceFromTheClosestNote(minI);
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
    currentFrequency = analize(recorder->getOutputFilePath());
}

void Configurator::setPercentageOfDistanceFromTheClosestNote(quint16 i) {
    if (i == 0) {
        qreal freq = notesController->getNoteFrequencies()[i];
        qreal freqNext = notesController->getNoteFrequencies()[i + 1];
        if (currentFrequency >= freqNext) {
            percentageOfDistanceFromTheClosestNote = 100;
        } else if (currentFrequency >= freq){
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
        } else if (currentFrequency >= freq){
            percentageOfDistanceFromTheClosestNote =
                    ((currentFrequency - freq) / (freqNext - freq)) * 100;
        } else {
            percentageOfDistanceFromTheClosestNote =
                    ((currentFrequency - freq) / (freq - freqPrevious)) * 100;
        }
    }
}

qreal Configurator::analize(QString path) {
    std::string pathOfFile = path.toUtf8().constData();

    // set up the audio file using double vectors
    AudioFile<float> recorded_sample;
    recorded_sample.load(pathOfFile);

    // get the data vector from the sample
    std::vector<float> data_temp(recorded_sample.samples[0]);
    int size = data_temp.size();
    float *data = (float*) malloc(sizeof(float)*size);
    for(int i = 0; i < size; i++)
    {
        data[i] = data_temp[i];
    }

    // init of a yin object
    Yin yin;
    Yin_init(&yin, size, 0.05);
    return Yin_getPitch(&yin, data);
}
