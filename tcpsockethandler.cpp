#include "tcpsockethandler.h"

TcpSocketHandler::TcpSocketHandler() : QObject(nullptr){
    initSocket();
}

void TcpSocketHandler::hostGame(QString hostName)
{
    QByteArray output;
    int code = 0;
    output.append(code);
    output.append(hostName.length());
    output.append(hostName.toUtf8().data());
    tcpSocket->write(output);
}

void TcpSocketHandler::joinGame(QString hostName, QString joinName){
    QByteArray output;
    int code = 1;
    output.append(code);
    output.append(joinName.length());
    output.append(joinName.toUtf8().data());
    output.append(hostName.length());
    output.append(hostName.toUtf8().data());

    if(tcpSocket->state() == QAbstractSocket::UnconnectedState){
        if(!tcpSocket->waitForConnected(9000)){
            emit serverError("Unable to connect to game server");
        }
    }
    tcpSocket->write(output);
}

void TcpSocketHandler::move(QString hostName, QString from, QString to){
    QByteArray output;
    int code = 2;
    output.append(code);
    output.append(hostName.length());
    output.append(hostName.toUtf8().data());
    output.append(from.length());
    output.append(from.toUtf8().data());
    output.append(to.length());
    output.append(to.toUtf8().data());
    qDebug() << "Writing move: f " << from << " t " << to;
    tcpSocket->write(output);
}

QString TcpSocketHandler::getPlayerName(){
    return playerName;
}

void TcpSocketHandler::setPlayerName(QString newName){
    playerName = newName;
}

QString TcpSocketHandler::getHostName(){
    return hostName;
}

void TcpSocketHandler::setHostName(QString newHost){
    hostName = newHost;
}

/**
 * @brief TcpSocketHandler::init
 * @return
 */
void TcpSocketHandler::initSocket(){
    tcpSocket = new QTcpSocket(this);
    //tcpSocket->bind(Q, serverPort, QAbstractSocket::ShareAddress);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpSocketHandler::readData);
    connect(tcpSocket, &QTcpSocket::bytesWritten, this, &TcpSocketHandler::afterDataWritten);
    tcpSocket->connectToHost(serverAddress, serverPort);
    if(!tcpSocket->waitForConnected(9000)){
        qDebug() << "TcpSocketError: " << tcpSocket->errorString();
    }
}

void TcpSocketHandler::handleMove(QByteArray data){
    int fromMoveLength = data[0];
    data.remove(0, 1);
    QByteArray fromMoveArray = QByteArray(data, fromMoveLength);
    QString fromMove(fromMoveArray);
    data.remove(0, fromMoveLength);

    int toMoveLength = data[0];
    data.remove(0, 1);
    QByteArray toMoveArray = QByteArray(data, toMoveLength);
    QString toMove(toMoveArray);
    data.remove(0, toMoveLength);

    emit multiplayerMove(fromMove,toMove);
}

void TcpSocketHandler::readData(){
    QByteArray data = tcpSocket->readAll();
    qDebug() << "Data received: " << data;
    int messageCode = data[0];
    data.remove(0, 1);
    if(messageCode == 0){
        int errorLength = data[0];
        data.remove(0, 1);
        QByteArray errorMsgArray = QByteArray(data, errorLength);
        QString msg(errorMsgArray);
        emit serverError(msg);
    } else if(messageCode == 1){
        qDebug() << "Server got the message";
    } else if(messageCode == 2){
        handleMove(data);
    }

}

void TcpSocketHandler::afterDataWritten(){
    qDebug() << "Data sent";
}
