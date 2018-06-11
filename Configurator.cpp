/*
 * File:    Configurator.cpp
 * Author:  Spiros
 *
 * Created on Jun 10, 2018, 5:28 PM
 */

#include "Configurator.h"
#include "Recorder.h"
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QtMath>

Configurator::Configurator() {
    currentFrequency = 0;
    percentageOfDistanceFromTheClosestNote = 0;
    closestNote = "";
    recorder = new Recorder();
    readBaseFrequency();
    readNotes();

    QString db_path = QDir::currentPath();
    qInfo() <<db_path;    //current path
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
    //  changing base frequency
    baseFrequency = frequency;
    //  opening the file to define it
    QFile baseFrequencyFile(":/data/notes/baseFrequency.txt");
    if(!baseFrequencyFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::information(0, "error", baseFrequencyFile.errorString());
    }
    QTextStream out1(&baseFrequencyFile);

    out1 << frequency << "\n";
    baseFrequencyFile.close();


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

void Configurator::setCurrentFrequency() {
    recorder->recordForXMilliseconds(100);

    QFile file(recorder->getOutputFilePath());
    // todo fft

    // eg
    currentFrequency = 654.5;

    //  recorder ->deleteTestFile();
}

void Configurator::readBaseFrequency() {
    QFile file(":/data/notes/baseFrequency.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in(&file);

    baseFrequency = in.readLine().toInt();
    file.close();
}

void Configurator::readNotes() {
    notes.clear();
    //  opening the file with the frequencies of the notes
    QFile fileForNoteFrequencies(":/data/notes/frequenciesOfNotes.txt");
    if(!fileForNoteFrequencies.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", fileForNoteFrequencies.errorString());
    }

    //  opening the file with the name of notes
    QFile fileForNoteNames(":/data/notes/namesOfNotes.txt");
    if(!fileForNoteNames.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", fileForNoteNames.errorString());
    }

    QTextStream in1(&fileForNoteFrequencies);
    QTextStream in2(&fileForNoteNames);

    for (quint16 i = 1; i <= 88; i++) {
       notes.insert(in1.readLine().toFloat(), in2.readLine());
    }
    fileForNoteFrequencies.close();
    fileForNoteNames.close();

    QMap<qreal, QString>::iterator i;
    for (i = notes.begin(); i != notes.end(); i++) {
        qInfo() << i.key() << " " << i.value() << "\n";
    }
}

QString Configurator::findClosestNote() {
    // todo

    // eg
    closestNote = "A2";
    return "";
}
