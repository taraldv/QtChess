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
    Q_INVOKABLE void hostGame();
    Q_INVOKABLE void joinGame();
    Q_INVOKABLE void move(QString from, QString to);
    Q_INVOKABLE QString getPlayerName();
    Q_INVOKABLE void setPlayerName(QString newName);
    Q_INVOKABLE void requestGames();
    Q_INVOKABLE void setGameId(const QString &value);
private:
    QString getNextStringSegement(QByteArray *data);
    void initSocket();
    void sendData(QByteArray bytes);
    int serverPort = 2233;
    QString playerName = "Player1";
    QString gameId;
    QHostAddress serverAddress = QHostAddress("46.250.220.57");
    QTcpSocket *tcpSocket;
    void readData();
    void connectedToServer();
    void handleError();
    void handleDisconnect();
    void afterDataWritten();
    void handleMove(QByteArray data);
    void handleGameList(QByteArray data);
    void handleHostSuccess(QByteArray data);
signals:
    void multiplayerMove(QString from, QString to);
    void serverError(QString error);
    void setListOfGames(QList<QString> hostNames, QList<QString> gameIds);
};

#endif // TCPSOCKETHANDLER_H
