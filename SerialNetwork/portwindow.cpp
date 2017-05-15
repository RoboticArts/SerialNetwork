#include "portwindow.h"
#include "ui_portwindow.h"
#include "mainwindow.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QSerialPort>
#include <QEvent>

PortWindow::PortWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PortWindow)
{
    ui->setupUi(this);
/*
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        ui -> comboBox -> addItem(info.portName());
*/
}


PortWindow::~PortWindow()
{
    delete ui;
}



QString PortWindow::getSerialPort()
{
   return ui -> comboBox -> currentText();
}

int PortWindow::getWaitTimeOut(){
   return ui ->spinBox -> value();
}


void PortWindow::on_ConnectButton_clicked() // Is connect
{
    close();
}


bool PortWindow::event(QEvent *event) //When PortWindow is opened, we read the availables COM and write them in comboBox
{
    if (event->type() == QEvent::WindowActivate) {

        ui->comboBox->clear();

        const auto infos = QSerialPortInfo::availablePorts();
        for (const QSerialPortInfo &info : infos)
            ui -> comboBox -> addItem(info.portName());

    }
    return QWidget::event(event);

}

