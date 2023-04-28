
#ifndef COLA_H
#define COLA_H
#include <QList>
#include <QDebug>
#include<QObject>

template <typename T>
struct Cola
{
public:
    void enqueue(const T& value)
    {
        m_items.append(value);
    }

    T dequeue()
    {
        Q_ASSERT(!m_items.isEmpty());
        return m_items.takeFirst();
    }

    T peek(){
        if (!m_items.isEmpty()){
        return m_items.constFirst();
        }
    }

    bool isEmpty() const
    {
        return m_items.isEmpty();
    }

    int size() const
    {
        return m_items.size();
    }

    void print() const
    {
        qDebug() << "Queue size:" << size();
        qDebug() << "Queue contents:";
        for (const T& value : m_items) {
            qDebug() << value;
        }
    }

    QString _toString()
    {
        QString result;
        for (int i = m_items.size() - 1; i >= 0; --i) {
            if (i < m_items.size() - 1) {
                result.append('-');
            }
            result.append(QString::number(m_items.at(i)));
        }
        return result;
    }

private:
    QList<T> m_items;
};


#endif // COLA_H
