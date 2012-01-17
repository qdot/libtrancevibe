#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdio>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	updateDeviceList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDeviceList()
{
	int device_count = trancevibe_get_count();
    ui->DeviceList->clear();
	if(device_count == 0)
	{
        ui->ConnectButton->setEnabled(false);
        ui->DeviceList->addItem("No Device Found!");
        return;
	}
    ui->ConnectButton->setEnabled(true);
    for(int i = 0; i < device_count; ++i)
    {
        ui->DeviceList->addItem(QString::number(i));
    }
}

void MainWindow::on_RefreshButton_clicked()
{
	updateDeviceList();
}

void MainWindow::on_ConnectButton_clicked()
{
    int device_index = ui->DeviceList->currentText().toInt();
    trancevibe_open(&m_tv, device_index);
    ui->ConnectButton->setText("Disconnect");
}

void MainWindow::on_LocalSpeedSlider_valueChanged(int value)
{
    if(m_tv)
    {
        trancevibe_set_speed(m_tv, value, 10);
    }
}
