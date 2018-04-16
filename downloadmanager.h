#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QUrl>
#include <QQueue>
#include <QThreadPool>
#include <QDebug>
#include <QSignalSpy>
#include <memory>

class DownloadManager : public QObject
{
    Q_OBJECT
public:
    explicit DownloadManager(unsigned max_thread = 2, QObject *parent = nullptr);

    Q_INVOKABLE void fetchPage(QUrl, QString);
    void fetchConcurrent(QQueue<QUrl>) const;
signals:
    void urlAdded(QUrl);
    void urlDownloaded(QUrl, QByteArray, QString);
    void startProcessingTheWholeStory() const;

public slots:

private:
    std::unique_ptr<QNetworkAccessManager> m_manager;
};

#endif // DOWNLOADMANAGER_H
