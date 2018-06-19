/*
 * File:    PitchBuffer.ηππ
 * Author:  Spiros
 *
 * Created on Jun 16, 2018, 5:28 PM
 */

#ifndef PITCHBUFFER_H
#define PITCHBUFFER_H

#include <QIODevice>
#include <QBuffer>
#include <QAudioInput>
#include <queue>

extern "C" {
#include <aubio.h>
}

#define BUF_SIZE 8192
#define HOP_SIZE 2048

class PitchBuffer : public QIODevice {
	Q_OBJECT
public:
	explicit PitchBuffer(QObject *parent = nullptr);

    /**
     * @brief getSamples is a functing that returns if there are other samples
     * @param samples are the samples that are gonna be used
     * @return if there are other samples
     */
    bool getSamples(fvec_t *samplesDest);

    /**
     * @brief setSampleType is a function sets SampleType and and the sample size
     * @param type is the sample type
     * @param size is the sample size
     */
	void setSampleType(QAudioFormat::SampleType type, int size);
signals:
    /**
     * @brief samplesReady is a signal that tells that the samples are ready to be analized
     */
	void samplesReady();
protected:
    //  implementations of read data function of qiodevice
    qint64 readData(char *data, qint64 maxlen);

    //  implementations of write data function of qiodevice
	qint64 writeData(const char *data, qint64 len);
private:
    /**
     * @brief getFloatSamples is that function that is used in the write data function
     * @param data is data that are comming through write data funciton
     * @param len is the len that is coming through write data function
     * @return the float samples
     */
	std::vector<float> getFloatSamples(const char *data, qint64 len);

    //  this variable saves the samples that have been "heard"
	std::queue<float> m_buf;

    //  is the sample type of the audioformat
    QAudioFormat::SampleType sampleType = QAudioFormat::SampleType::Float;

    // is the size of the sample size
    int sampleSize = sizeof(float);
};

#endif // PITCHBUFFER_H
