#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);

    void EditPlainTextServer(QString text);
    void EditPlainTextClient(QString text);

    void LineEditClientRemoteAddress(QString text);
    void LineEditClientRemotePort(QString text);
    QString getLineEditClientRemoteAdress();
    QString getLineEditClientRemotePort();

    void LabelClientLocalAddress(QString text);
    void LabelClientLocalPort(QString text);

    QString getLineEditServerPort();

    bool getStateServer();
    bool getStateClient();

    void ShowMessageBox();


    ~Dialog();

private:
    Ui::Dialog *ui;


public slots:

    void LabelServerActivateDesactivate();
    void LabelClientConnectDisconnect();
    void EnableDisableServerSettings();
    void EnableDisableClientSettings();
};

#endif // DIALOG_H
