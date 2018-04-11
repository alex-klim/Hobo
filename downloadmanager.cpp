#include "downloadmanager.h"

DownloadManager::DownloadManager(unsigned max_thread, QObject *parent) : QObject(parent), m_manager(new QNetworkAccessManager)
{
    QThreadPool::globalInstance()->setMaxThreadCount(max_thread);
}

void DownloadManager::fetchPage(QUrl url, QString word) const {
    qDebug() << url << word;
    if (url.isEmpty() || word.isEmpty()) {
        qDebug() << "empty values";
        return;
    }
    QNetworkReply* reply = m_manager->get(QNetworkRequest(url));
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    qDebug() << "Wat up";
    emit urlAdded(url, reply->readAll(), word);
    //emit startProcessingTheWholeStory();
    reply->deleteLater();
}

void DownloadManager::fetchConcurrent(QQueue<QUrl> urls) const {
/*    if (urls.isEmpty()) {
        qDebug() << "end of all worlds";
        return;
    }
    mapreduce queue;
    swap queues;
    fetch;
    emit newDataPrepared(QQueue data);*/
}
