#include "tablemodel.h"
#include <QDebug>

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent)
{
    m_roleNames[UrlRole] = "url";
    m_roleNames[StatusRole] = "status";
    m_data << ParsingData{ QUrl("http://Someshit.com"), QString("ololo") };
}

int TableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    //qDebug() << "rowCount called";
    return m_data.size();
}

int TableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    //qDebug() << "columnCount called";
    return 2;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    qDebug() << "data called";
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
    qDebug() << "roleNames called";
    return m_roleNames;
}

bool TableModel::insertRow(int row, const QModelIndex &parent) {
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), row, row);
    m_data.append(ParsingData());
    endInsertRows();
    return true;
}

void TableModel::append(const QString& url, const QString& status) {
    insertRow(m_data.size(), QModelIndex());
    m_data.back().url = url;
    m_data.back().status = status;

    for(auto mem : m_data) {
        qDebug() << mem.url << mem.status;
    }
}

void TableModel::onStatusChanged(QUrl url, QString new_status) {
    qDebug() << "onStatusChanged";
    auto itr = m_data.begin();
    unsigned position = 0;
    while (itr != m_data.end()) {
        if (itr->url == url)
            break;
        itr++;
        position++;
    }
    if (itr != m_data.end()) {
        qDebug() << "Changing status from" << itr->status;
        qDebug() << "to" << new_status;
        itr->status = new_status;
        setData(index(position, 1), QVariant(new_status), StatusRole);
    } else {
        qDebug() << "no matches in onStatusChanged";
    }
}

void TableModel::onUrlAdded(QUrl url) {
    append(url.url(), QString("downloading"));
    qDebug() << "Row added";
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    qDebug() << "setData called";
    if (role != StatusRole && role != UrlRole) {
        qDebug() << "wrong role from setData";
        return false;
    }
    if (index.column() == 1) {
        qDebug() << "changing status";
        m_data[index.row()].status = value.value<QString>();
        emit dataChanged(index, index);
        return true;
    }
    if (index.column() == 0) {
        qDebug() << "changing url";
        m_data[index.row()].url = value.value<QString>();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}
