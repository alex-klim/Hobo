#include "pageparser.h"

PageParser::PageParser(QObject *parent) : QObject(parent)
{

}

void PageParser::onUrlAdded(QUrl url, QByteArray data, QString word) {
    qDebug() << "onUrlAdded";
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

QQueue<QUrl> PageParser::parsePage(QUrl url, QByteArray page, QString word) const {
    qDebug() << "parsePage";
    // Here we searchig for the target word
    if(page.lastIndexOf(word) == -1){
                emit statusChanged(url, "not found");
                qDebug() << "emitting status";
            }
            else {
                emit statusChanged(url, "found");
                qDebug() << "emitting status";
    }
    // Here we sending update to our tablemodel
    // Here we iterating over url matching pattern
}
