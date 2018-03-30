#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "tester.h"
#include "tablemodel.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Tester>("cpp.helptypes", 1, 0, "Tester");
    qmlRegisterType<Tester>("cpp.helptypes", 1, 0, "TableModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
