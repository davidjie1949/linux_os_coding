#ifndef TVF_DXP_INTERFACE_H
#define TVF_DXP_INTERFACE_H

#include <QDebug>
#include <QPoint>

#include <QObject>

class tvf_dxp_interface : public QObject
{
    Q_OBJECT
public:
    explicit tvf_dxp_interface(QObject *parent = nullptr);

    Q_INVOKABLE void CancellPullover(bool &temp);

signals:

};

#endif // TVF_DXP_INTERFACE_H
