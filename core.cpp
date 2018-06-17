#include "core.h"

Core::Core(QObject *parent) : QObject(parent)
{
    w = new Worker(std::ref(configurator));

    connect(&configurator, SIGNAL(Configurator::results()), this, SLOT(analisysResults()));
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
//    configurator.changeBaseFrequency(frequency);
    w->start();
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

void Core::analisysResults()
{
    emit frequencyResult();
}

void Core::emitResults()
{
    emit frequencyResult();
}
