#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include <QMessageBox>


extern MainWindow *w;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->checkBoxClient, SIGNAL(clicked(bool)), w, SLOT(ClientConnectDisconnect()));
    connect(ui->checkBoxClient, SIGNAL(clicked(bool)), this, SLOT(LabelClientConnectDisconnect()));
    connect(ui->checkBoxClient, SIGNAL(clicked(bool)), this, SLOT(EnableDisableServerSettings()));

    connect(ui->checkBoxServer, SIGNAL(pressed()), w, SLOT(ServerActivateDeactivate())); //Se usa pressed para evitar que llegue a clicked y se lea si hay COM
    connect(ui->checkBoxServer, SIGNAL(clicked(bool)), this, SLOT(LabelServerActivateDesactivate()));
    connect(ui->checkBoxServer, SIGNAL(clicked(bool)),this, SLOT(EnableDisableClientSettings()));

}

Dialog::~Dialog()
{
    delete ui;
}


void  Dialog::LabelClientConnectDisconnect(){


    if(ui->checkBoxClient->isChecked())
        ui -> labelConnectDisconnect -> setText("Conectado");
    else
        ui -> labelConnectDisconnect -> setText("Desconectado");

}


void Dialog::LabelServerActivateDesactivate(){

    if(ui->checkBoxServer->isChecked())
        ui -> labelActivateDesactivate -> setText("Activado");
    else
        ui -> labelActivateDesactivate -> setText("Desactivado");

}


void Dialog::EditPlainTextClient(QString text){

     ui->plainTextEditClient->insertPlainText(text);

     // Autoscroll
     ui -> plainTextEditClient -> moveCursor(QTextCursor::End);
     ui -> plainTextEditClient -> ensureCursorVisible();
}


void Dialog::EditPlainTextServer(QString text){

     ui->plainTextEditServer->insertPlainText(text);

     // Autoscroll
     ui -> plainTextEditServer -> moveCursor(QTextCursor::End);
     ui -> plainTextEditServer -> ensureCursorVisible();
}



void Dialog::LineEditClientRemoteAddress(QString text)
{
    ui -> lineEditClientRemoteAddress -> setText(text);
}


void Dialog::LineEditClientRemotePort(QString text)
{
    ui -> lineEditClientRemotePort -> setText(text);
}


QString Dialog::getLineEditClientRemoteAdress()
{
    return ui -> lineEditClientRemoteAddress -> text();
}

QString Dialog::getLineEditClientRemotePort()
{
    return ui -> lineEditClientRemotePort -> text();
}


void Dialog::LabelClientLocalAddress(QString text)
{
    ui -> labelClientLocalAddress -> setText(text);
}

void Dialog::LabelClientLocalPort(QString text)
{
    ui -> labelClientLocalPort -> setText(text);
}

QString Dialog::getLineEditServerPort()
{
    return ui -> lineEditServerPort -> text();
}


void Dialog::EnableDisableClientSettings() //Activa o Desactiva el CLIENTE
{

        if(ui->checkBoxServer->isChecked())
        {
            w -> EnableDisableSliderButton(0); //Deshabilita el modo manual
            // Desactiva la configuración del cliente
            ui -> checkBoxClient -> setEnabled(0);
            ui -> lineEditClientRemoteAddress ->setEnabled(0);
            ui -> lineEditClientRemotePort -> setEnabled(0);
            w -> LabelInformationServerClient("server");
            w -> EnableDisableMainMenu(0); // No se permite usar el menu en esta máquina
            // Actuando como SERVIDOR

        }
        else
        {
            w -> EnableDisableSliderButton(1); //Habilita el modo manual
            // Activa la configuracion del cliente
            ui -> checkBoxClient -> setEnabled(1);
            ui -> lineEditClientRemoteAddress ->setEnabled(1);
            ui -> lineEditClientRemotePort -> setEnabled(1);
            w -> LabelInformationServerClient("nothing");
            w -> EnableDisableMainMenu(0); // No se habilita el menu
            // Actuando como
        }


}

void Dialog::EnableDisableServerSettings() //Activa o Desactiva el SERVIDOR
{

        if(ui->checkBoxClient->isChecked())
        {
            w -> EnableDisableSliderButton(0); //Deshabilita el modo manual
            // Desactiva la configuracion del servidor
            ui -> checkBoxServer -> setEnabled(0);
            ui -> lineEditServerPort -> setEnabled(0);
            w -> LabelInformationServerClient("client");
            w -> EnableDisableMainMenu(1); // La maquina remota puede usar el menu
            // Actuando como CLIENTE
        }
        else
        {
            w -> EnableDisableSliderButton(1); //Habilita el modo manual
            // Activa la configuración del servidor
            ui -> checkBoxServer -> setEnabled(1);
            ui -> lineEditServerPort -> setEnabled(1);
            w -> LabelInformationServerClient("nothing");
            w -> EnableDisableMainMenu(0); //No se habilita el menu (estado inicial)
            //Actuando como
        }
}

bool Dialog::getStateClient()
{
    return ui -> checkBoxClient -> checkState();
}

bool Dialog::getStateServer()
{
    return ui -> checkBoxServer -> checkState();
}

void Dialog::ShowMessageBox()
{
    QMessageBox::information(this,"COM","Puerto COM no detectado");
}

