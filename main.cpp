#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "tester.h"
#include "tablemodel.h"
#include "downloadmanager.h"
#include "pageparser.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    PageParser pparser;
    DownloadManager dmanager;
    TableModel tmodel;

    // bunch of connect statements
    bool success = QObject::connect(&dmanager, SIGNAL(urlAdded(QUrl,QByteArray,QString)), &pparser, SLOT(onUrlAdded(QUrl,QByteArray,QString)));
    Q_ASSERT(success);
    qDebug() << success;
    bool success2 = QObject::connect(&pparser, SIGNAL(statusChanged(QUrl,QString)), &tmodel, SLOT(onStatusChanged(QUrl,QString)));
    Q_ASSERT(success2);
    qDebug() << success2;

    qmlRegisterType<Tester>("cpp.helptypes", 1, 0, "Tester");
    qmlRegisterType<TableModel>("cpp.helptypes", 1, 0, "TableModel");
    qmlRegisterType<DownloadManager>("cpp.helptypes", 1, 0, "DManager");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("dmanager", &dmanager);
    engine.rootContext()->setContextProperty("tmodel", &tmodel);
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
