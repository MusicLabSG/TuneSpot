#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QQuickItem>
#include <QThread>
#include <QtCore>

#include "Configurator.hpp"
#include "Recorder.hpp"

class Worker : public QThread
{
public:
    Worker(Configurator &rec);

    void run();

private:
    Configurator& configurator;
};

#endif // WORKER_H
