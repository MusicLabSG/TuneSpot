/*
 * File:    Recorder.cpp
 * Author:  Spiros
 *
 * Created on Jun 10, 2018, 1:28 PM
 */

#include "Recorder.h"

#include <QDir>
#include <QStandardPaths>
#include <QTimer>
#include <QUrl>

#ifdef Q_OS_ANDROID
    #include <QtAndroidExtras/QtAndroid>
#endif

Recorder::Recorder() {
    audioRecorder = new QAudioRecorder();

    #ifdef Q_OS_ANDROID
        QtAndroid::requestPermissionsSync( QStringList() << "android.permission.WRITE_EXTERNAL_STORAGE" );
    #endif

    // we set the default audio input device
    audioRecorder->setAudioInput(audioRecorder->audioInputs().at(0));

    // we define the encoder settings
    QAudioEncoderSettings settings;
    settings.setCodec("audio/pcm");
    // one channel only, change is if you want for fft
    settings.setChannelCount(1);
    settings.setQuality(QMultimedia::HighQuality);
    audioRecorder->setEncodingSettings(settings);

    // we set define the path of the output location and the name of the test file
    QDir folder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    outputFilePath = folder.path();
    outputFilePath.append(QString("/test.wav"));
    audioRecorder->setOutputLocation(QUrl::fromLocalFile(outputFilePath));
}

Recorder::~Recorder() {
    delete audioRecorder;
}

void Recorder::recordForXMilliseconds(quint32 x) {
    record();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(stop()));
    timer->start(x); //time specified in ms
}

void Recorder::deleteTestFile() {
    QFile file (outputFilePath);
    file.remove();
}

QString Recorder::getOutputFilePath() {
    return outputFilePath;
}

void Recorder::record() {
    audioRecorder->record();
}

void Recorder::stop() {
    audioRecorder->stop();
}
