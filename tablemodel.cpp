#include "tablemodel.h"
#include <QDebug>

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent)
{
    m_roleNames[UrlRole] = "url";
    m_roleNames[StatusRole] = "status";
    m_data << ParsingData{QString("http://developex.com.ua"), "parsing"};
}

int TableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    qDebug() << "rowCount called\n";
    return m_data.size();
}

int TableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    qDebug() << "columnCount called\n";
    return 2;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    qDebug() << "data called\n";
    if (!index.isValid()) {
        return QVariant();
    }

    int row = index.row();
    if (row > m_data.size() || row < 0) {
        return QVariant();
    }

    switch(role) {
    case UrlRole:
        return m_data[row].url;
    case StatusRole:
        return m_data[row].status;
    }
    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const {
    qDebug() << "roleNames called\n";
    return m_roleNames;
}

bool TableModel::insertRow(int row, const QModelIndex &parent) {
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), row, row);
    m_data.append(ParsingData());
    endInsertRows();
    return true;
}

void TableModel::append(const QString url, const QString status) {
    insertRow(m_data.size(), QModelIndex());
    m_data.back().url = url;
    m_data.back().status = status;

    for(auto mem : m_data) {
        qDebug() << mem.url << " " << mem.status << '\n';
    }
}

void TableModel::onStatusChanged(QUrl url, QString new_status) {
    qDebug() << "onStatusChanged";
    auto itr = m_data.begin();
    while (itr != m_data.end()) {
        if (itr->url == url)
            break;
    }
    if (itr != m_data.end()) {
        qDebug() << itr->status;
        itr->status = new_status;
    } else {
        qDebug() << "no matches in onStatusChanged";
    }
}
