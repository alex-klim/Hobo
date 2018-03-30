#include <QDebug>
#include "tester.h"

Tester::Tester(QObject *parent) : QObject(parent), m_counter(0)
{

}

void Tester::setCounter(int number){
    if (number < 0 || number > 100) {
        //throw someFuckingError();
        m_counter = 0;
        emit counterChanged();
        qDebug() << m_counter;
        return;
    }
    m_counter = number;
    emit counterChanged();
    qDebug() << m_counter;
}

int Tester::getCounter() {
    return m_counter;
}
