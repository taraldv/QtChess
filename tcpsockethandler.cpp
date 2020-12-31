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
    tcpSocket->write(output);
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
}

void TcpSocketHandler::readData(){
    QByteArray data = tcpSocket->readAll();
    qDebug() << "Data received: " << data;
    int messageCode = data[0];
    data.remove(0, 1);
    if(messageCode == 0){
        qDebug() << "Something went wrong";
    } else if(messageCode == 1){
        qDebug() << "Server got the message";
    } else if(messageCode == 2){
        handleMove(data);
    }

}

void TcpSocketHandler::afterDataWritten(){
    qDebug() << "Data sent";
}
