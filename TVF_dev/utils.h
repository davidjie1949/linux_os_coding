#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QDebug>
#include <QPoint>

class utils : public QObject
{
    Q_OBJECT
public:
    explicit utils(QObject *parent = nullptr);

    Q_INVOKABLE void test();

signals:

};

#endif // UTILS_H
