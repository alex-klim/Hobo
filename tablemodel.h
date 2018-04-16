#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QUrl>
#include <QVariant>


struct ParsingData {
    QUrl url;
    QString status;
};

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Role {
        UrlRole=Qt::UserRole+1,
        StatusRole=Qt::UserRole+2
    };

    Q_INVOKABLE void append(const QString&, const QString&);
    explicit TableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool insertRow(int row, const QModelIndex &index=QModelIndex());
     bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole) Q_DECL_OVERRIDE;

    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

signals:

public slots:
    void onStatusChanged(QUrl, QString);
    void onUrlAdded(QUrl);

private:
    QList<ParsingData> m_data;
    QHash<int, QByteArray> m_roleNames;
};

#endif // TABLEMODEL_H
