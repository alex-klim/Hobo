#ifndef PAGEPARSER_H
#define PAGEPARSER_H

#include <QObject>
#include <QQueue>
#include <QUrl>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QDebug>

class PageParser : public QObject
{
    Q_OBJECT
public:
    explicit PageParser(QObject *parent = nullptr);

    void parsePage(QUrl, QByteArray, QString);
    void parseConcurrent(QQueue<QByteArray>);
signals:
    void addUrl() const;
    void statusChanged(QUrl, QString);

public slots:
    void onUrlDownloaded(QUrl, QByteArray, QString);
};

#endif // PAGEPARSER_H
