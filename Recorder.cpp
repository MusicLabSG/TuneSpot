/*
 * File:    Recorder.cpp
 * Author:  Spiros
 *
 * Created on Jun 10, 2018, 1:28 PM
 */

#include "Recorder.hpp"

#include <stdio.h>
#include <QDir>
#include <QStandardPaths>
#include <QTimer>
#include <QUrl>

#ifdef Q_OS_ANDROID
    #include <QtAndroidExtras/QtAndroid>
#endif

Recorder::Recorder() {
#ifdef Q_OS_ANDROID
    QtAndroid::requestPermissionsSync( QStringList() << "android.permission.WRITE_EXTERNAL_STORAGE" );
#endif


    QDir path;
    outputFolder = path.currentPath();
    outputFilePath = outputFolder;
    outputFilePath.append(QString("/test.wav"));

    settings.setCodec("audio/pcm");
    settings.setSampleRate(44100);
    settings.setSampleSize(16);
    settings.setChannelCount(1);
    settings.setByteOrder(QAudioFormat::LittleEndian);
    settings.setSampleType(QAudioFormat::UnSignedInt);

    audio = new QAudioInput(settings);
}

Recorder::~Recorder() {
    delete audio;
}

void Recorder::recordTestFile() {
    QTimer *timer = new QTimer(this);

    record();
    connect(timer, SIGNAL(timeout()), this, SLOT(stop()));
    timer->start(300); //time specified in ms
}

QString Recorder::getOutputFilePath() {
    return outputFilePath;
}

void Recorder::record() {
    output.setFileName(outputFilePath);
    output.open(QIODevice::WriteOnly);
    audio->start(&output);
}

int rawToWav(const char *rawfn, const char *wavfn, long frequency) {
    long chunksize = 0x10;

    struct {
        unsigned short wFormatTag;
        unsigned short wChannels;
        unsigned long dwSamplesPerSec;
        unsigned long dwAvgBytesPerSec;
        unsigned short wBlockAlign;
        unsigned short wBitsPerSample;
    } fmt;

    FILE *raw = fopen(rawfn, "rb");
    if (!raw)
        return -2;

    fseek(raw, 0, SEEK_END);
    long bytes = ftell(raw);
    fseek(raw, 0, SEEK_SET);

    long samplecount = bytes / 2;
    long riffsize = samplecount * 2 + 0x24;
    long datasize = samplecount * 2;

    FILE *wav = fopen(wavfn, "wb");
    if (!wav) {
        fclose(raw);
        return -3;
    }

    fwrite("RIFF", 1, 4, wav);
    fwrite(&riffsize, 4, 1, wav);
    fwrite("WAVEfmt ", 1, 8, wav);
    fwrite(&chunksize, 4, 1, wav);

    fmt.wFormatTag = 1;      // PCM
    fmt.wChannels = 1;      // MONO
    fmt.dwSamplesPerSec = frequency * 1;
    fmt.dwAvgBytesPerSec = frequency * 1 * 2; // 16 bit
    fmt.wBlockAlign = 2;
    fmt.wBitsPerSample = 16;

    fwrite(&fmt, sizeof(fmt), 1, wav);
    fwrite("data", 1, 4, wav);
    fwrite(&datasize, 4, 1, wav);
    short buff[1024];
    while (!feof(raw)) {
        int cnt = fread(buff, 2, 1024, raw);
        if (cnt == 0)
            break;
        fwrite(buff, 2, cnt, wav);
    }
    fclose(raw);
    QFile file(rawfn);
    file.remove();
    fclose(wav);

    rename(wavfn, rawfn);
    return 0;
}

void Recorder::stop() {
    audio->stop();
    output.close();

    QString newOutputFilePath = outputFolder;
    newOutputFilePath.append(QString("/test1.wav"));
    rawToWav(outputFilePath.toStdString().c_str(), newOutputFilePath.toStdString().c_str(), settings.sampleRate());
}
