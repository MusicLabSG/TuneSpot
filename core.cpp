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

void Core::start()
{

}

void Core::stop()
{

}

void Core::analize()
{
    std::string path = ""; // TODO change that with the path for the configurator

    // set up the audio file using double vectors
    AudioFile<double> recorded_sample;
    recorded_sample.load(path);

    // get the data vector from the sample
    std::vector<double> data(recorded_sample.samples[0]);
}

void Core::emitResults()
{
    emit frequencyResult(123);
}
