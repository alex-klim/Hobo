#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QUrl>


struct ParsingData {
    QUrl url;
    QString status;
};

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Role {
        OneRole=Qt::UserRole,
        TwoRole
    };

    Q_INVOKABLE void append(const QString, const QString);
    explicit TableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int, Qt::Orientation, int) const;

    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

signals:

public slots:
    void theDataChanged();

private:
    QList<ParsingData> m_data;
};

#endif // TABLEMODEL_H
