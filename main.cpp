#include <QApplication>
#include <QQmlApplicationEngine>
#include <Configurator.hpp>

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    Configurator *configurator = new Configurator();
    qInfo() << configurator->getBaseFrequency();
    qInfo() << configurator->getClosestNote();
    configurator->setCelloXString(1);
    qInfo() << configurator->getPercentageOfDistanceFromTheClosestNote();


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
