#ifndef CORE_H
#define CORE_H

#include <QObject>

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);
    Q_INVOKABLE void emitResults();
signals:
    void frequencyResult(int frequency);
public slots:

private:
//    void emitResults();
};

#endif // CORE_H
