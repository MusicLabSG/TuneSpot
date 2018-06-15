#include "core.h"

Core::Core(QObject *parent) : QObject(parent)
{

}

void Core::setInstrument(QString instrument)
{
    this->instrument = instrument;
}

void Core::setString(qint16 string)
{
//    TODO check for strcpy
    this->string = string;
}

void Core::setBaseFrequency(qint16 frequency)
{
    configurator.changeBaseFrequency(frequency);
}

qint16 Core::getBaseFrequency()
{
    return configurator.getBaseFrequency();
}

qint16 Core::getPercentage()
{
    return configurator.getPercentageOfDistanceFromTheClosestNote();
}

QString Core::getClosestNote()
{
    return configurator.getClosestNote();
}

void Core::analize()
{
    // get the wav
    recorder.recordTestFile();
    string path = recorder.getOutputFilePath().toStdString();

    // parse the wav and get the data in a float array
    AudioFile<float> sample;
    sample.load(path);
    int sample_size = sample.samples.at(0).size();
    float *data = new float[sample_size];

    for(int i = 0; i < sample_size; i++)
    {
        data[i] = sample.samples.at(0).at(i);
    }

    // analize with yin and get the pitch
    AubioAnalyzer analizer;
    analizer.processAudio(data, sample_size);
//    float pitch = analizer.pitch;

    // pass the pitch throw the configurator

    // emit the results to front end
}

void Core::emitResults()
{
    emit frequencyResult(123);
}
