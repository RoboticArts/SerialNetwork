#ifndef NETWORK_H
#define NETWORK_H

#include <QTcpServer>
#include <QTcpSocket>

class CConnection : public QTcpSocket
{
    Q_OBJECT

public:
    CConnection(QObject *parent = 0);
    bool SendMessage(const QString &message);

public slots:
    void Read(void);
};




class CClient : public QTcpSocket
{
    Q_OBJECT

public:
    CClient(QObject *parent = 0);
};





class CServer : public QTcpServer
{
    Q_OBJECT

public:
    CServer(QObject *parent = 0);

signals:
    void newConnection(CConnection *connection);

protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;
};


#endif // NETWORK_H
