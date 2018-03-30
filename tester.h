#ifndef TESTER_H
#define TESTER_H

#include <QObject>
#include <QDebug>

class Tester : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int counter READ getCounter WRITE setCounter NOTIFY counterChanged)
public:
    explicit Tester(QObject *parent = nullptr);
    int getCounter();
    void setCounter(int);

private:
    int m_counter;

signals:
    void counterChanged();

public slots:
};

#endif // TESTER_H
