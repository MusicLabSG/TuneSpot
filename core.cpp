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
    start_thread("analisis");
}

void Core::stop()
{
    stop_thread("analisis");
}

void Core::start_thread(const std::string &tname)
{
    // std::thread thrd = std::thread(std::ref(configurator));
    // thrd.detach();
    // tm[tname] = std::move(thrd);
}

void Core::stop_thread(const std::string &tname)
{
    ThreadMap::const_iterator it = tm.find(tname);
    if (it != tm.end()) {
        it->second.std::thread::~thread(); // thread not killed
        tm.erase(tname);
    }
}

void Core::emitResults()
{
    emit frequencyResult(123);
}
