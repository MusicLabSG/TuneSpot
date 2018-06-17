#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "Configurator.hpp"
#include "worker.h"
#include <stdint.h>


class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);

    /*!
     * @brief
     */
    Q_INVOKABLE void setInstrument(QString instrument);
    Q_INVOKABLE void setString(qint16 string);
    Q_INVOKABLE void setBaseFrequency(qint16 frequency);
    Q_INVOKABLE qint16 getBaseFrequency();
    Q_INVOKABLE qint16 getPercentage();
    Q_INVOKABLE QString getClosestNote();

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
signals:
    void frequencyResult();
public slots:
    void analisysResults();

private:
    QString instrument;
    qint16 string;
    Configurator configurator;

    Worker *w;

    void start_thread(const std::string &tname);
    void stop_thread(const std::string &tname);

    void emitResults();
};

#endif // CORE_H
