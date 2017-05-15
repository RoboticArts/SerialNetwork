#ifndef PORTWINDOW_H
#define PORTWINDOW_H

#include <QDialog>
#include <QString>



namespace Ui {
class PortWindow;
}

class PortWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PortWindow(QWidget *parent = 0);
    ~PortWindow();




private:
    Ui::PortWindow *ui;

public:
     QString getSerialPort();
     int getWaitTimeOut();
     bool event(QEvent *event);

private slots:

     void on_ConnectButton_clicked();
};

#endif // PORTWINDOW_H
