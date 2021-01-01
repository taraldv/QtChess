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
    Q_INVOKABLE QString getPlayerName();
    Q_INVOKABLE void setPlayerName(QString newName);
    Q_INVOKABLE QString getHostName();
    Q_INVOKABLE void setHostName(QString newHost);
    Q_INVOKABLE void initSocket();
private:
    int serverPort = 2233;
    QString playerName = "Player1";
    QString hostName;
    QHostAddress serverAddress = QHostAddress("46.250.220.57");
    QTcpSocket *tcpSocket;
    void readData();
    void connectedToServer();
    void handleError();
    void handleDisconnect();
    void afterDataWritten();
    void handleMove(QByteArray data);
signals:
    void multiplayerMove(QString from, QString to);
    void serverError(QString error);
};

#endif // TCPSOCKETHANDLER_H
