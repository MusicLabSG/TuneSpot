/*
 * File:    Configurator.cpp
 * Author:  Spiros
 *
 * Created on Jun 16, 2018, 5:28 PM
 */

#include <Configurator.hpp>
#include <QDebug>
#include <QtMath>

#ifdef Q_OS_ANDROID
    #include <QtAndroidExtras/QtAndroid>
#endif

Configurator::Configurator(QObject *parent) : QObject(parent) {
#ifdef Q_OS_ANDROID
    QtAndroid::requestPermissionsSync( QStringList() << "android.permission.RECORD_AUDIO" );
#endif

    applyFormat();
    recorder = std::make_unique<QAudioInput>(formatSettings);

    confidentFrequency = 0;
    percentageOfDistanceFromTheClosestNote = 0;
    closestNote = "";
    organSetter = "freeMode";

    connect(&pitchBuffer, SIGNAL(samplesReady()), this, SLOT(analyzeSamples()));
}

void Configurator::setActive(bool active) {
    if (active) {
        if (!pitchBuffer.open(QIODevice::WriteOnly)) {
            qDebug() << "Something went wrong while opening the device";
        }
        recorder->start(&pitchBuffer);
    } else {
        recorder->stop();
    }
    activeTuner = active;
}

void Configurator::setOrganSetter(QString setter) {
    organSetter = setter;

    emit organSetterChanged();
}

QString Configurator::getOrganSetter() {
    return organSetter;
}


quint16 Configurator::getBaseFrequency() {
    return notesController.getBaseFrequency();
}

void Configurator::setBaseFrequency(quint16 newBaseFrequency) {
    notesController.changeBaseFrequency(newBaseFrequency);

    emit baseFrequencyChanged();
}

QString Configurator::getClosestNote() {
    return closestNote;
}

qreal Configurator::getPercentageOfDistanceFromTheClosestNote() {
    return percentageOfDistanceFromTheClosestNote;
}

qreal Configurator::getFrequency() {
    return confidentFrequency;
}

void Configurator::applyFormat() {
    formatSettings.setCodec("audio/pcm");
    formatSettings.setChannelCount(1);
    formatSettings.setSampleRate(48000);
    formatSettings.setSampleType(QAudioFormat::SampleType::Float);
    formatSettings.setSampleSize(sizeof(float) * 8);
    formatSettings.setByteOrder(QAudioFormat::LittleEndian);

    // test if the format is supported
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(formatSettings)) {
        qDebug() << "Default format not supported, trying to use 16bit signed integer samples";
        formatSettings.setSampleType(QAudioFormat::SampleType::SignedInt);
        formatSettings.setSampleSize(sizeof(int16_t) * 8);
        if (!info.isFormatSupported(formatSettings)) {
            qDebug() << "No support for 16bit signed integer samples. Trying nearest format, the program will probably not work.";
            formatSettings = info.nearestFormat(formatSettings);
        }
    }
    pitchBuffer.setSampleType(formatSettings.sampleType(), formatSettings.sampleSize() / 8);
}

void Configurator::analyzeSamples() {
    // while new samples are available
    while (pitchBuffer.getSamples(aubio.aubioIn)) {
        //  recognize the pitch
        aubio_pitch_do(aubio.getAubioPitch(), aubio.aubioIn, aubio.aubioOut);

        qreal currentFrequency = aubio.aubioOut->data[0];
        float confidence = aubio_pitch_get_confidence(aubio.getAubioPitch());

        if (confidence >= confidenceThresHold) {
            confidentFrequency = currentFrequency;
            qDebug() << confidentFrequency << "\n";
        }

        notesController.setCloseNoteAndPercentageAccordingToSetterID(organSetter, confidentFrequency, closestNote, percentageOfDistanceFromTheClosestNote);

        emit samplesAnalyzed();
    }
}
