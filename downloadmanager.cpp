#include "downloadmanager.h"

DownloadManager::DownloadManager(unsigned max_thread, QObject *parent) : QObject(parent), m_manager(new QNetworkAccessManager)
{
    QThreadPool::globalInstance()->setMaxThreadCount(max_thread);
}

void DownloadManager::fetchPage(QUrl url, QString word) {
    qDebug() << url << word;
    if (url.isEmpty() || word.isEmpty()) {
        qDebug() << "empty initial values";
        return;
    }
    emit urlAdded(url);
    qDebug() << "Right before downloading page";
    QNetworkReply* reply = m_manager->get(QNetworkRequest(url));
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    qDebug() << "Right after page downloaded";

    emit urlDownloaded(url, reply->readAll(), word);
    qDebug() << "End of fetchPage";
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
