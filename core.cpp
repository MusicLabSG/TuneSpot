#include "core.h"

Core::Core(QObject *parent) : QObject(parent)
{

}

void Core::emitResults()
{
    emit onFrequencyResult(123);
}
