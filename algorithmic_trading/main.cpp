#include "mainwindow.h"
#include "vanillaoption.h"
#include "payoff.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    (void)argc, (void)argv;
    VanillaOption jie(20, 0.05, 1.0, 18.36, 0.7366);
    cout << jie.calc_call_price() << endl;
    cout << jie.calc_put_price() << endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    payoff yang;

    return a.exec();
}
