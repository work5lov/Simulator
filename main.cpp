#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "simulator.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    // Регистрируем тип C++ класса Simulator в QML, чтобы его можно было использовать в QML-коде.
    // "VPNSimulator" - это имя модуля, в котором будет доступен тип Simulator.
    // 1 - основная версия модуля.
    // 0 - минорная версия модуля.
    // "Simulator" - это имя типа, которое будет использоваться в QML для создания экземпляров класса Simulator.
    qmlRegisterType<Simulator>("VPNSimulator", 1, 0, "Simulator");


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
