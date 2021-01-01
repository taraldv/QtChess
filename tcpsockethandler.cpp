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
    sendData(output);
}

void TcpSocketHandler::joinGame(QString hostName, QString joinName){
    QByteArray output;
    int code = 1;
    output.append(code);
    output.append(joinName.length());
    output.append(joinName.toUtf8().data());
    output.append(hostName.length());
    output.append(hostName.toUtf8().data());
    sendData(output);
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

    sendData(output);

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
    connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpSocketHandler::readData);
    connect(tcpSocket, &QTcpSocket::bytesWritten, this, &TcpSocketHandler::afterDataWritten);
    connect(tcpSocket, &QTcpSocket::connected, this, &TcpSocketHandler::connectedToServer);
    connect(tcpSocket, &QTcpSocket::errorOccurred, this, &TcpSocketHandler::handleError);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &TcpSocketHandler::handleDisconnect);
    tcpSocket->connectToHost(serverAddress, serverPort);
}

void TcpSocketHandler::sendData(QByteArray bytes){
    if(tcpSocket->state() != QAbstractSocket::ConnectedState){
        emit serverError("Connecting to server");
        tcpSocket->connectToHost(serverAddress, serverPort);
        if(!tcpSocket->waitForConnected(5000)){
            emit serverError("Connection failed");
            return;
        }
    }
    tcpSocket->write(bytes);
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

void TcpSocketHandler::connectedToServer(){
    emit serverError("Connected");
}

void TcpSocketHandler::handleError(){
    emit serverError(tcpSocket->errorString());
}

void TcpSocketHandler::handleDisconnect(){
    emit serverError("Disconnected from server");
}

void TcpSocketHandler::afterDataWritten(){
    qDebug() << "Data sent";
}
