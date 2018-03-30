#include "tablemodel.h"
#include <QDebug>

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent)
{
    m_data << ParsingData{QString("http://developex.com.ua"), "parsing"};
}

int TableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_data.size();
}

int TableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 2;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (index.row() > m_data.size() || index.row() < 0) {
        return QVariant();
    }

    switch(role) {
    case OneRole:
        return m_data[index.row()].url;
    case TwoRole:
        return m_data[index.row()].status;
    }
}

QHash<int, QByteArray> TableModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[OneRole] = "url";
    roles[TwoRole] = "status";
    return roles;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("URL");

            case 1:
                return tr("Status");

            default:
                return QVariant();
        }
    }
    return QVariant();
}

void TableModel::theDataChanged() {

}

void TableModel::append(const QString url, const QString status) {
    m_data << ParsingData{QUrl(url), status};
    for(auto mem : m_data) {
        qDebug() << mem.url << " " << mem.status << '\n';
    }
}
