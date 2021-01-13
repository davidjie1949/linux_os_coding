#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gpb/TVF_To_DXP.pb.h"
#include "gpb/TVF_To_DXP_info.pb.h"

using namespace ford::av::taas;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    PassengerPulloverResp passengerPullover;
    passengerPullover.set_passenger_pullover_status(PassengerPulloverResp_PulloverStatus_PULLOVER_ACCEPTED);
}
