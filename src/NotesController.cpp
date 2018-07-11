/*
 * File:    NotesController.cpp
 * Author:  Spiros
 *
 * Created on Jun 10, 2018, 5:28 PM
 */

#include <NotesController.hpp>

#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>
#include <QtMath>
#include <QDebug>
#include <QStandardPaths>

#ifdef Q_OS_ANDROID
    #include <QtAndroidExtras/QtAndroid>
#endif


NotesController::NotesController(QObject *parent) : QObject(parent) {
#ifdef Q_OS_ANDROID
    QtAndroid::requestPermissionsSync( QStringList() << "android.permission.READ_EXTERNAL_STORAGE" );
#endif
#ifdef Q_OS_ANDROID
    QtAndroid::requestPermissionsSync( QStringList() << "android.permission.WRITE_EXTERNAL_STORAGE" );
#endif
    QDir folder = QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation);
    path = folder.path();
    readNotes();
}

void NotesController::changeBaseFrequency(quint32 newBaseFrequency) {
    baseFrequency = newBaseFrequency;
    noteFrequencies.clear();

    QFile fileForNoteFrequencies(path);
    if (!fileForNoteFrequencies.open(QIODevice::WriteOnly)) {
        QMessageBox::information(0, "error", fileForNoteFrequencies.errorString());
    } else {
        QTextStream stream( &fileForNoteFrequencies );

        qreal freq;
        for (quint16 i = 1; i <= 88; i++) {
           freq = newBaseFrequency * qPow(2, (i - 49) / 12.0);
           noteFrequencies.push_back(freq);
           stream << freq << "\n";
        }

        fileForNoteFrequencies.close();
    }
}

quint16 NotesController::getBaseFrequency() {
    return baseFrequency;
}

void NotesController::setCloseNoteAndPercentageAccordingToSetterID(QString &organSetter, qreal &confidentFrequency, QString &closestNote, qreal &percentageOfDistanceFromTheClosestNote) {
    if(organSetter == "freeMode") {
        setFreeMode(confidentFrequency, closestNote, percentageOfDistanceFromTheClosestNote);
    } else if (organSetter == "cello1") {
        setCelloXString(1, confidentFrequency, closestNote, percentageOfDistanceFromTheClosestNote);
    } else if (organSetter == "cello2") {
        setCelloXString(2, confidentFrequency, closestNote, percentageOfDistanceFromTheClosestNote);
    } else if (organSetter == "cello3") {
        setCelloXString(3, confidentFrequency, closestNote, percentageOfDistanceFromTheClosestNote);
    } else if (organSetter == "cello4") {
        setCelloXString(4, confidentFrequency, closestNote, percentageOfDistanceFromTheClosestNote);
    } else if (organSetter == "guitar1") {
        setGuitarXString(1, confidentFrequency, closestNote, percentageOfDistanceFromTheClosestNote);
    } else if (organSetter == "guitar2") {
        setGuitarXString(2, confidentFrequency, closestNote, percentageOfDistanceFromTheClosestNote);
    } else if (organSetter == "guitar3") {
        setGuitarXString(3, confidentFrequency, closestNote, percentageOfDistanceFromTheClosestNote);
    } else if (organSetter == "guitar4") {
        setGuitarXString(4, confidentFrequency, closestNote, percentageOfDistanceFromTheClosestNote);
    } else if (organSetter == "guitar5") {
        setGuitarXString(5, confidentFrequency, closestNote, percentageOfDistanceFromTheClosestNote);
    } else if (organSetter == "guitar6") {
        setGuitarXString(6, confidentFrequency, closestNote, percentageOfDistanceFromTheClosestNote);
    }
}

void NotesController::setCelloXString(quint16 x, qreal &confidentFrequency, QString &closestNote, qreal &percentageOfDistanceFromTheClosestNote) {
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
        if (noteNames[i] == closestNote) {
            break;
        }
    }

    setPercentageOfDistanceFromTheClosestNote(i, confidentFrequency, percentageOfDistanceFromTheClosestNote);
}

void NotesController::setGuitarXString(quint16 x, qreal &confidentFrequency, QString &closestNote, qreal &percentageOfDistanceFromTheClosestNote) {
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
        if (noteNames[i] == closestNote) {
            break;
        }
    }

    setPercentageOfDistanceFromTheClosestNote(i, confidentFrequency, percentageOfDistanceFromTheClosestNote);
}

void NotesController::setFreeMode(qreal &confidentFrequency, QString &closestNote, qreal &percentageOfDistanceFromTheClosestNote) {
    quint16 minI = -1;
    qreal minDistance = 10000, test;
    for (quint16 i = 0; i < 88; i++) {
        test = qFabs(confidentFrequency - noteFrequencies[i]);
        if (minDistance > test) {
            minDistance = test;
            minI = i;
        }
    }

    closestNote = noteNames[minI];
    setPercentageOfDistanceFromTheClosestNote(minI, confidentFrequency, percentageOfDistanceFromTheClosestNote);
}

void NotesController::setPercentageOfDistanceFromTheClosestNote(quint16 i, qreal &confidentFrequency, qreal &percentageOfDistanceFromTheClosestNote) {
    if (i == 0) {
        qreal freq = noteFrequencies[i];
        qreal freqNext = noteFrequencies[i + 1];
        if (confidentFrequency >= freqNext) {
            percentageOfDistanceFromTheClosestNote = 100;
        } else if (confidentFrequency >= freq) {
            percentageOfDistanceFromTheClosestNote =
                    ((confidentFrequency - freq) / (freqNext - freq)) * 100;
        }
    } else if (i == 87) {
        qreal freq = noteFrequencies[i];
        qreal freqPrevious = noteFrequencies[i - 1];
        if (confidentFrequency <= freqPrevious) {
            percentageOfDistanceFromTheClosestNote = -100;
        } else {
            percentageOfDistanceFromTheClosestNote =
                    ((confidentFrequency - freq) / (freq - freqPrevious)) * 100;
        }
    } else {
        qreal freq = noteFrequencies[i];
        qreal freqPrevious = noteFrequencies[i - 1];
        qreal freqNext = noteFrequencies[i + 1];

        if (confidentFrequency <= freqPrevious) {
            percentageOfDistanceFromTheClosestNote = -100;
        } else if (confidentFrequency >= freqNext) {
            percentageOfDistanceFromTheClosestNote = 100;
        } else if (confidentFrequency >= freq) {
            percentageOfDistanceFromTheClosestNote =
                    ((confidentFrequency - freq) / (freqNext - freq)) * 100;
        } else {
            percentageOfDistanceFromTheClosestNote = ((confidentFrequency - freq) / (freq - freqPrevious)) * 100;
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

void NotesController::readNotes() {
    //  opening the file with the name of notes
    QFile fileForNoteNames(":/data/notes/namesOfNotes.txt");
    if(!fileForNoteNames.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error not finding namesOfNotes.txt", fileForNoteNames.errorString());
    } else {
        QTextStream in(&fileForNoteNames);

        for (quint16 i = 1; i <= 88; i++) {
           noteNames.push_back(in.readLine());
        }
        fileForNoteNames.close();
    }

    // reading or creating for the first time the frequencies
    path.append("/frequenciesOfNotes.txt");
    QFileInfo check_file(path);

    // check if file exists
    if (check_file.exists()) {
        //  opening the file with the frequencies
        QFile fileForNoteFrequencies(path);
        if(!fileForNoteFrequencies.open(QIODevice::ReadWrite)) {
            QMessageBox::information(0, "error not finding frequenciesOfNotes.txt", fileForNoteFrequencies.errorString());
        } else {
            QTextStream in(&fileForNoteFrequencies);

            for (quint16 i = 1; i <= 88; i++) {
               noteFrequencies.push_back(in.readLine().toFloat());
            }
            baseFrequency = noteFrequencies[48];
            fileForNoteFrequencies.close();
        }

    } else {

        //  creating a file with the frequencies
        QFile fileForNoteFrequencies(path);
        if (!fileForNoteFrequencies.open(QIODevice::ReadWrite)) {
            QMessageBox::information(0, "error can not create frequenciesOfNotes.txt", fileForNoteFrequencies.errorString());
        } else {
            QTextStream stream( &fileForNoteFrequencies );

            qreal freq;
            for (quint16 i = 1; i <= 88; i++) {
               freq = 440 * qPow(2, (i - 49) / 12.0);
               noteFrequencies.push_back(freq);
               stream << freq << "\n";
            }

            baseFrequency = 440;
            fileForNoteFrequencies.close();
        }
    }
}
