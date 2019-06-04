#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include "logger.h"

void getInputDataWrapper(Logger& loggerObject);

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Logger loggerObject;

    // регистрируем пользовательский тип
    qmlRegisterUncreatableType<Logger>("Logger", 1, 0, "Logger", "");
    engine.rootContext()->setContextProperty("logger", &loggerObject);
    // поток для обработки входящих сообщений
    std::thread loggerThread(getInputDataWrapper, std::ref(loggerObject));
    loggerThread.detach();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

void getInputDataWrapper(Logger& loggerObject)
{
    loggerObject.getInputData();
}
