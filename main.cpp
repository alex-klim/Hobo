#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSignalSpy>
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
    QSignalSpy spy(&dmanager, SIGNAL(urlDownloaded(QUrl,QByteArray,QString)));

    // bunch of connect statements
    bool success = QObject::connect(&dmanager, &DownloadManager::urlDownloaded, &pparser, &PageParser::onUrlDownloaded);
    Q_ASSERT(success);
    qDebug() << success;

    bool success2 = QObject::connect(&pparser, &PageParser::statusChanged, &tmodel, &TableModel::onStatusChanged);
    Q_ASSERT(success2);
    qDebug() << success2;

    bool success3 = QObject::connect(&dmanager, &DownloadManager::urlAdded, &tmodel, &TableModel::onUrlAdded);
    Q_ASSERT(success3);
    qDebug() << success3;

    QObject::connect(&dmanager, &QObject::destroyed,
                     [=] { qDebug() << "dm deleted";});
    QObject::connect(&pparser, &QObject::destroyed,
                     [=] { qDebug() << "pp deleted";});
    QObject::connect(&app, &QCoreApplication::aboutToQuit, &spy, [&] { qDebug() << spy.count();});

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
