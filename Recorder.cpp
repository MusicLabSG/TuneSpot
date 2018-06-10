/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

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
