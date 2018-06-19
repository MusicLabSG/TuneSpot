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
    QtAndroid::requestPermissionsSync( QStringList() << "android.permission.WRITE_EXTERNAL_STORAGE" );
#endif
    QDir folder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
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

QVector<QString> NotesController::getNoteNames() {
    return noteNames;
}

QVector<qreal> NotesController::getNoteFrequencies() {
    return noteFrequencies;
}

quint16 NotesController::getBaseFrequency() {
    return baseFrequency;
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
            QMessageBox::information(0, "error not finding frequenciesOfNotes.txt", fileForNoteFrequencies.errorString());
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
