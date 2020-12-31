#ifndef TCPSOCKETHANDLER_H
#define TCPSOCKETHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

class TcpSocketHandler : public QObject
{
    Q_OBJECT
public:
    TcpSocketHandler();
    Q_INVOKABLE void hostGame(QString hostName);
    Q_INVOKABLE void joinGame(QString hostName, QString joinName);
    Q_INVOKABLE void move(QString hostName, QString from, QString to);
private:
    int serverPort = 2233;
    QHostAddress serverAddress = QHostAddress("46.250.220.57");
    void initSocket();
    QTcpSocket *tcpSocket;
    void readData();
    void afterDataWritten();
    void handleMove(QByteArray data);
signals:

};

#endif // TCPSOCKETHANDLER_H
