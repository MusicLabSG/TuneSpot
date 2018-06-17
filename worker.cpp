#include "worker.h"


Worker::Worker(Configurator &rec) : configurator(rec)
{
}

void Worker::run()
{
    while (true)
    {
        configurator.recordSample();
        configurator.analizeSample();
        qInfo() << configurator.getClosestNote() << " " << configurator.getPercentageOfDistanceFromTheClosestNote();
    }
}
