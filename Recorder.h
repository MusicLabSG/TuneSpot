/*
 * File:    Recorder.h
 * Author:  Spiros
 *
 * Created on Jun 10, 2018, 1:28 PM
 */

#ifndef Recorder_H
#define Recorder_H

#include <QAudioRecorder>

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
     * @brief recordXMilliseconds is a function that records sound for the test sound file that we need to analise for x milliseconds
     * @param x is the amount of the milliseconds
     */
    void recordForXMilliseconds(quint32 x);

    /**
     * @brief getOutputFilePath is a function that return the outputFilePath
     * @return the outputFilePath
     */
    QString getOutputFilePath();

    /**
     * @brief deleteTestFile is a function that deletes the test file that we created
     */
    void deleteTestFile();
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
    QAudioRecorder *audioRecorder;

    QString outputFilePath;
};

#endif // Recorder_H
