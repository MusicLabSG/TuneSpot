#include <QApplication>
#include <QQmlApplicationEngine>
#include <Configurator.hpp>
#include <NotesController.hpp>
#include <QAudioDeviceInfo>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();

    qDebug() << "ByteOrders\n";
    for (auto codec: info.supportedByteOrders()) {
        qDebug() << codec << "\n";
    }

    qDebug() << "ChannelCounts\n";
    for (auto codec: info.supportedChannelCounts()) {
        qDebug() << codec << "\n";
    }

    qDebug() << "Codecs\n";
    for (auto codec: info.supportedCodecs()) {
        qDebug() << codec << "\n";
    }

    qDebug() << "SampleRates\n";
    for (auto codec: info.supportedSampleRates()) {
        qDebug() << codec << "\n";
    }

    qDebug() << "SampleSizes\n";
    for (auto codec: info.supportedSampleSizes()) {
        qDebug() << codec << "\n";
    }

    qDebug() << "SampleTypes\n";
    for (auto codec: info.supportedSampleTypes()) {
        qDebug() << codec << "\n";
    }

    // Register the backend as a component
    qmlRegisterType<Configurator>("Configurator", 1, 0, "Configurator");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
