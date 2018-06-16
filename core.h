#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "Configurator.hpp"
#include "AudioFile.h"
#include "yin.h"
#include <stdint.h>
#include <thread>
#include <unordered_map>


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
    void frequencyResult(qint16 frequency);
public slots:

private:
    QString instrument;
    qint16 string;
    Configurator configurator;
    std::thread analisis_thread;
    typedef std::unordered_map<std::string, std::thread> ThreadMap;
    ThreadMap tm;

    void start_thread(const std::string &tname);
    void stop_thread(const std::string &tname);

    static void analize(Configurator &c);
    void emitResults();
};

#endif // CORE_H
