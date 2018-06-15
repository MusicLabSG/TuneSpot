#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "Configurator.hpp"
#include "Recorder.hpp"
#include "AudioFile.h"
#include "PitchDetection/aubioAnalyzer.h"

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);

    /*!
     * @brief
     */
    Q_INVOKABLE void setInstrument(QString instrument);
    Q_INVOKABLE void setString(qint16 string);
    Q_INVOKABLE void setBaseFrequency(qint16 frequency);
    Q_INVOKABLE qint16 getBaseFrequency();
    Q_INVOKABLE qint16 getPercentage();
    Q_INVOKABLE QString getClosestNote();

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
signals:
    void frequencyResult(qint16 frequency);
public slots:

private:
    QString instrument;
    qint16 string;
    Configurator configurator;
    Recorder recorder;

    void analize();
    void emitResults();
};

#endif // CORE_H
