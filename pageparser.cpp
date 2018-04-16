#include "pageparser.h"

PageParser::PageParser(QObject *parent) : QObject(parent)
{

}

void PageParser::onUrlDownloaded(QUrl url, QByteArray data, QString word) {
    qDebug() << "onUrlDownloaded";
    QString page = QString(data);
    parsePage(url, data, word);
    return;
}

void PageParser::parseConcurrent(QQueue<QByteArray> data) {
/*    QtConcurrent::mappedReduced(data, parsePage,
                                [](QQueue<QUrl> urls) {
                                    for (auto url : urls) {
                                        someQueue.append(url);
                                    }
                                });*/
}

void PageParser::parsePage(QUrl url, QByteArray page, QString word) {
    qDebug() << "parsePage";
    // Here we searchig for the target word
    if(page.lastIndexOf(word) == -1){
        qDebug() << "emitting statusChanged";
        emit statusChanged(url, QString("not found"));
    } else {
        qDebug() << "emitting statusChanged";
        emit statusChanged(url, QString("found"));
    }
    // Here we sending update to our tablemodel
    // Here we iterating over url matching pattern
}
