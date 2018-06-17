#include "core.h"

Core::Core(QObject *parent) : QObject(parent)
{
    w = new Worker(std::ref(configurator));
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
//    w->start();
    configurator.recordSample();
//    configurator.analizeSample();
}

void Core::stop()
{
    w->terminate();
}

void Core::emitResults()
{
    emit frequencyResult(123);
}
