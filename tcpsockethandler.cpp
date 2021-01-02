#include "tcpsockethandler.h"

TcpSocketHandler::TcpSocketHandler() : QObject(nullptr){
    initSocket();
}

void TcpSocketHandler::hostGame()
{
    QByteArray output;
    int code = 0;
    output.append(code);
    output.append(playerName.length());
    output.append(playerName.toUtf8().data());
    sendData(output);
}

void TcpSocketHandler::joinGame(){
    QByteArray output;
    int code = 1;
    output.append(code);
    output.append(playerName.length());
    output.append(playerName.toUtf8().data());
    output.append(gameId.length());
    output.append(gameId.toUtf8().data());
    sendData(output);
}

void TcpSocketHandler::move(QString from, QString to){
    QByteArray output;
    int code = 2;
    output.append(code);
    output.append(gameId.length());
    output.append(gameId.toUtf8().data());
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

void TcpSocketHandler::requestGames(){
    QByteArray output;
    output.append(3);
    tcpSocket->write(output);
}

QString TcpSocketHandler::getNextStringSegement(QByteArray *data){
    int segmentLength = *data[0];
    data->remove(0, 1);
    QByteArray segment = QByteArray(*data, segmentLength);
    QString stringSegment(segment);
    data->remove(0, segmentLength);
    return stringSegment;
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
        if(tcpSocket->state() != QAbstractSocket::ConnectingState){
            tcpSocket->connectToHost(serverAddress, serverPort);
        }
        if(!tcpSocket->waitForConnected(3000)){
            emit serverError("Connection failed");
            return;
        }
    }
    tcpSocket->write(bytes);
}

void TcpSocketHandler::setGameId(const QString &value)
{
    gameId = value;
}

void TcpSocketHandler::handleMove(QByteArray data){
    
    QString fromMove = getNextStringSegement(&data);
    QString toMove = getNextStringSegement(&data);

    emit multiplayerMove(fromMove,toMove);
}

void TcpSocketHandler::handleGameList(QByteArray data){

    //List of games: gameCount forEach(hostName, gameId)
    QList<QString> hostNames;
    QList<QString> gameIds;
    int gameCount = data[0];
    qDebug() << "games recieved: " << gameCount;
    data.remove(0, 1);
    for(int i=0;i<gameCount;i++){
        QString tempHostName = getNextStringSegement(&data);
        QString tempGameId = getNextStringSegement(&data);
        hostNames.append(tempHostName);
        gameIds.append(tempGameId);
    }
    emit setListOfGames(hostNames,gameIds);
}

void TcpSocketHandler::handleHostSuccess(QByteArray data){
    QString gameIdFromServer = getNextStringSegement(&data);
    gameId = gameIdFromServer;
    qDebug() << "updated gameId: " << gameId;
}

void TcpSocketHandler::readData(){
    QByteArray data = tcpSocket->readAll();
    qDebug() << "Data received: " << data;
    int messageCode = data[0];
    data.remove(0, 1);
    if(messageCode == 0){
        QString msg = getNextStringSegement(&data);
        emit serverError(msg);
    } else if(messageCode == 1){
        qDebug() << "Server got the message";
    } else if(messageCode == 2){
        //Take a move
        handleMove(data);
    } else if(messageCode == 3){
        //List of games
        handleGameList(data);
    } else if(messageCode == 4){
        //Host was successfull
        handleHostSuccess(data);
    }

}

void TcpSocketHandler::connectedToServer(){
    emit serverError("Connected to game server");
}

void TcpSocketHandler::handleError(){
    emit serverError("Server error: " + tcpSocket->errorString());
}

void TcpSocketHandler::handleDisconnect(){
    emit serverError("Disconnected from server");
}

void TcpSocketHandler::afterDataWritten(){
    qDebug() << "Data sent";
}
