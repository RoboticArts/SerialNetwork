#include <network.h>
#include <mainwindow.h>
#include <dialog.h>

extern Dialog *d;
extern MainWindow *w;

CConnection::CConnection(QObject *parent) :
    QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(Read()));
}

bool CConnection::SendMessage(const QString &message)
{
    if(message.isEmpty())
        return false;

    QByteArray msg = message.toUtf8();
    QByteArray data = "MESSAGE " + QByteArray::number(msg.size()) + ' ' + msg;
    return write(data) == data.size();
}



void CConnection::Read(void)  //Lectura del Servidor cuando el cliente manda un dato
{
    QString read = readAll(); //Se modifica. readAll solo se puede leer una vez
    QString auxRead = read; // Copia de seguridad

    //((MainWindow*)(parent()->parent()))->ui->plainTextEditServer->insertPlainText(QString("Read: ") + read + '\n');

    //Read es un buffer. Se halla la ultima X y se trunca el valor. X14X56X35 se obtiene 35 (el ultimo valor)

    if(read.startsWith("X"))
    {
        int n = read.lastIndexOf("X");
        read =  read.remove(0,n+1);
        //((MainWindow*)(parent()->parent()))->ui->SliderX -> setValue(read.toInt());
        w->setSliderX(read.toInt());


    }

    if(read.startsWith("Y"))
    {
        int n = read.lastIndexOf("Y"); //Se posiciona en la ultima Y recibida
        read =  read.remove(0,n+1); // y borra todo lo anterior, incluido la Y. Se queda el número
        //((MainWindow*)(parent()->parent()))->ui->SliderY -> setValue(read.toInt());
        w->setSliderY(read.toInt());

    }

    if(read.startsWith("S"))
    {
        int n = read.lastIndexOf("S");
        read = read.remove(0,n+1);
        //Escribe por puerto serie
        w ->SerialPortWrite("S" + read + "\n");
    }

    if(read.startsWith("A"))
    {
        int n = read.lastIndexOf("A");
        read = read.remove(0,n+1);
        //Escribe por puerto serie
         w ->SerialPortWrite("A" + read + "\n");
    }


    d -> EditPlainTextServer(QString("Read(") + auxRead.mid(0,1) + QString("): ")  + read + '\n');
}



CClient::CClient(QObject *parent) :
    QTcpSocket(parent)
{

}

CServer::CServer(QObject *parent) :
    QTcpServer(parent)
{

}

void CServer::incomingConnection(qintptr socketDescriptor)
{
    CConnection *connection = new CConnection(this);
    connection->setSocketDescriptor(socketDescriptor);
    emit newConnection(connection);
}
