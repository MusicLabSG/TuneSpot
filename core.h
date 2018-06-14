#ifndef CORE_H
#define CORE_H

#include <QObject>

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);

signals:
    void onFrequencyResult(int frequency);
public slots:
private:
    void emitResults();
};

#endif // CORE_H
