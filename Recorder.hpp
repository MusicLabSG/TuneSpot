/*
 * File:    Recorder.h
 * Author:  Spiros
 *
 * Created on Jun 10, 2018, 1:28 PM
 */

#ifndef Recorder_H
#define Recorder_H

#include <QAudioInput>
#include <QFile>

class Recorder : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Recorder is a trivial constructor of the Recorder class
     */
    explicit Recorder();

    /**
     * @brief ~Recorder is a trivial destructor of the Recorder class
     */
    ~Recorder();

public slots:
    /**
     * @brief recordTestFile is a function that records sound for the test sound file that we need to analise
     */
    void recordTestFile();

    /**
     * @brief getOutputFilePath is a function that return the outputFilePath
     * @return the outputFilePath
     */
    QString getOutputFilePath();

private slots:
    /**
     * @brief record is a function that starts the recording
     */
    void record();

    /**
     * @brief stop is a function that stops the recording
     */
    void stop();

private:
    //  A variable that acts as an input stream
    QAudioInput *audio;

    //  the settings of the recorder
    QAudioFormat settings;

    //  the outputFile
    QFile output;

    //  the output file path
    QString outputFilePath;
};

#endif // Recorder_H
