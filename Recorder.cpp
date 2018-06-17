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
    outputFilePath = path.currentPath();
    outputFilePath.append(QString("/test.wav"));

    settings.setCodec("audio/pcm");
    settings.setSampleRate(44100);
    settings.setSampleSize(8);
    settings.setChannelCount(1);
    settings.setByteOrder(QAudioFormat::LittleEndian);
    settings.setSampleType(QAudioFormat::UnSignedInt);

    audio = new QAudioInput(settings);
}

Recorder::~Recorder() {
    delete audio;
}

void Recorder::recordTestFile() {
    QThread* somethread = new QThread(this);
    QTimer *timer = new QTimer(this->thread());

    record();
    connect(timer, SIGNAL(timeout()), this, SLOT(stop()));

    timer->moveToThread(somethread);

    timer->start(400); //time specified in ms
}

QString Recorder::getOutputFilePath() {
    return outputFilePath;
}

void Recorder::record() {
    output.setFileName(outputFilePath);
    output.open(QIODevice::WriteOnly);
    audio->start(&output);
}

void rawToWav(QString filename, QAudioFormat &settings) {
    typedef struct {
        char chunk_id[4];        // RIFF string
        unsigned int chunk_size;         // overall size of file in bytes (36 + data_size)
        char sub_chunk1_id[8];   // WAVEfmt string with trailing null char
        unsigned int sub_chunk1_size;    // 16 for PCM.  This is the size of the rest of the Subchunk which follows this number.
        unsigned short audio_format;       // format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
        unsigned short num_channels;       // Mono = 1, Stereo = 2
        unsigned int sample_rate;        // 8000, 16000, 44100, etc. (blocks per second)
        unsigned int byte_rate;          // SampleRate * NumChannels * BitsPerSample/8
        unsigned short block_align;        // NumChannels * BitsPerSample/8
        unsigned short bits_per_sample;    // bits per sample, 8- 8bits, 16- 16 bits etc
        char sub_chunk2_id[4];   // Contains the letters "data"
        unsigned int sub_chunk2_size;    // NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk that will be read
    } wav_header_t;

    int rawSize = 0;
    wav_header_t waveHeader;
    memset(&waveHeader, '\0', sizeof(wav_header_t));

    char *pcm_buf;
    FILE *wavFile;

    wavFile = fopen(filename.toStdString().c_str(), "rb+");

    // obtain file size:
    fseek(wavFile, 0, SEEK_END);
    rawSize = ftell(wavFile);
    rewind(wavFile);

    // allocate memory to contain the whole file:
    pcm_buf = (char *) malloc(sizeof(char) * rawSize);


    // copy the file into the pcm_buf:
    fread(pcm_buf, 1, rawSize, wavFile);
    rewind(wavFile);

    // RIFF chunk
    strcpy(waveHeader.chunk_id, "RIFF");
    waveHeader.chunk_size = 36 + rawSize;

    // fmt sub-chunk (to be optimized)
    strncpy(waveHeader.sub_chunk1_id, "WAVEfmt ", strlen("WAVEfmt "));
    waveHeader.sub_chunk1_size = 16;
    waveHeader.audio_format = 1;
    waveHeader.num_channels = settings.channelCount();
    waveHeader.sample_rate = settings.sampleRate();
    waveHeader.bits_per_sample = settings.sampleSize();
    waveHeader.block_align = waveHeader.num_channels * waveHeader.bits_per_sample / 8;
    waveHeader.byte_rate = waveHeader.sample_rate * waveHeader.num_channels * waveHeader.bits_per_sample / 8;

    // data sub-chunk
    strncpy(waveHeader.sub_chunk2_id, "data", strlen("data"));
    waveHeader.sub_chunk2_size = rawSize;

    fwrite(&waveHeader, 1, sizeof(waveHeader), wavFile);
    fwrite(pcm_buf, 1, rawSize, wavFile);
    fclose(wavFile);
}

void Recorder::stop() {
    audio->stop();
    output.close();
    rawToWav(outputFilePath, settings);

    emit recoredSignal();
}
