#ifndef PUBLISH_H
#define PUBLISH_H
#include <QDebug>
#include <QPoint>

#include <QObject>

class publish : public QObject
{
    Q_OBJECT
public:
    explicit publish(QObject *parent = nullptr);

    Q_INVOKABLE void CancellPullover(bool &temp);

signals:


};

#endif // PUBLISH_H
