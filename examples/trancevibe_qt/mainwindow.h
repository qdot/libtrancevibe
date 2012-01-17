#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trancevibe/trancevibe.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_RefreshButton_clicked();

    void on_ConnectButton_clicked();

    void on_LocalSpeedSlider_valueChanged(int value);

private:
    void updateDeviceList();
    Ui::MainWindow *ui;
    trancevibe m_tv;
};

#endif // MAINWINDOW_H
