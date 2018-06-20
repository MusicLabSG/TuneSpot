/*
 * File:    PitchBuffer.cpp
 * Author:  Spiros
 *
 * Created on Jun 16, 2018, 5:28 PM
 */

#include <QDebug>
#include <PitchBuffer.hpp>

PitchBuffer::PitchBuffer(QObject *parent) : QIODevice(parent) {

}

bool PitchBuffer::getSamples(fvec_t *samplesDest) {
    if (m_buf.size() < HOP_SIZE) {
        return false;
    }

    for (int i = 0; i < HOP_SIZE; ++i) {
        fvec_set_sample(samplesDest, m_buf.front(), i);
        m_buf.pop();
    }

    return true;
}

void PitchBuffer::setSampleType(QAudioFormat::SampleType type, int size) {
    sampleType = type;
    sampleSize = size;
}

qint64 PitchBuffer::readData(char *data, qint64 maxlen) {
    Q_UNUSED(data)
    Q_UNUSED(maxlen)

    return -1;
}

qint64 PitchBuffer::writeData(const char *data, qint64 len) {
    auto samples = getFloatSamples(data, len);
    const int numberNewSamples = samples.size();

    for (int i = 0; i < numberNewSamples; ++i) {
        const float sample = samples[i];
        m_buf.push(sample);
    }

    if (m_buf.size() >= HOP_SIZE) {
        emit samplesReady();
    }

    return len;
}

std::vector<float> PitchBuffer::getFloatSamples(const char *data, qint64 len) {
    const auto signedInt16ToFloat = [](const int16_t i) {
        return i / 32768.f;
    };

    const unsigned char *ptr = reinterpret_cast<const unsigned char *>(data);
    
    std::vector<float> result;

    const int numberSamples = len / sampleSize;

    result.resize(numberSamples);

    for (int i = 0; i < numberSamples; ++i) {
        float sample;

        switch (sampleType) {
            case QAudioFormat::SampleType::Float:
                sample = *reinterpret_cast<const float *>(ptr);
                break;
            case QAudioFormat::SampleType::SignedInt: {
                // for the time being just assume, that it is a 16 bit int
                int16_t s = *reinterpret_cast<const int16_t *>(ptr);
                sample = signedInt16ToFloat(s);
                break;
            }
            default:
                sample = 0;
                break;
        }
        result[i] = sample;
        ptr += sampleSize;
    }

    return result;
}
