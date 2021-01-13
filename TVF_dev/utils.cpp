#include "utils.h"

utils::utils(QObject *parent) : QObject(parent)
{

}

void utils::test()
{
    qDebug() << "Hello from C++";
}
