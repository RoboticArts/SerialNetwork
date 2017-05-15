#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

#include <network.h>

/* Para el puerto serie */

#include "masterthread.h"
#include "portwindow.h"
#include <QDialog>
#include <QString>

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

    CServer *server;
    CClient *client;

public:
    explicit MainWindow(QWidget *parent = 0);

    /* Network */

    void LabelInformationServerClient(QString mode);
    void EnableDisableMainMenu(bool state);
    void closeEvent (QCloseEvent *event);

    /*Puerto serie*/

    PortWindow MiPuertoSerie;

    QString port;// Store COM port and wait-timeout introduced on the PortWindow
    int timeout; //
    QString request; // Store request introduced on the MainWindow

    bool toggle = 1; // Toggle button "Activate" with the goal activate and desactivate when button is pressed.
    bool getKeyboardEnable();
    void setKeyboardEnable(bool state);



    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent * event); //Para detectar el teclado

private:

    /* Puerto serie */

    int transactionCount;

    MasterThread thread;

    bool KeyboardState = 0;


public slots:

    /*Network*/
    void ServerActivateDeactivate(void);
    void ServerNewConnection(void);
    void ServerRead(void);


    void ClientConnectDisconnect(void);
    void ClientStateChanged(QAbstractSocket::SocketState state);
    void ClientHostFound(void);
    void ClientConnected(void);
    void ClientError(QAbstractSocket::SocketError error);

    void ClientRead(void);

    bool SliderXSend(void);
    bool SliderYSend(void);

    void setSliderX(int value);
    void setSliderY(int value);

    bool ShootSendZero(void);
    bool ShootSendOne(void);

    bool ArmedSendClicked(void);

    void on_pushButtonSetting_clicked(); //Boton "configuracion"

    /*Puerto serie*/
    void SettingSerialPort();


private slots:

    /* Puerto serie */

    void transaction();
    void showResponse(const QString &s);
    void processError(const QString &s);
    void processTimeout(const QString &s);

    void on_ButtonSerialPort_clicked();
    void on_SendButton_clicked();
    void on_SliderX_valueChanged(int value);
    void on_SliderY_valueChanged(int value);
    void on_EnableSliderButton_clicked();

};

#endif // MAINWINDOW_H
