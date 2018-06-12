#include <QApplication>
#include <QQmlApplicationEngine>
#include <Configurator.hpp>

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    // Register the backend as a component
    qmlRegisterType<Configurator>("com.github.tune_spot.configurator", 1, 0, "Configurator");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
