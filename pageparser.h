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

    QQueue<QUrl> parsePage(QUrl, QByteArray, QString) const;
    void parseConcurrent(QQueue<QByteArray>);
signals:
    void addUrl() const;
    void statusChanged(QUrl, QString) const;

public slots:
    void onUrlAdded(QUrl, QByteArray, QString);
};

#endif // PAGEPARSER_H
