#include "worker.h"


Worker::Worker(Configurator &rec) : configurator(rec)
{
}

void Worker::run()
{
    configurator.setCurrentFrequency();
}
