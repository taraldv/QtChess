import QtQuick 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Controls 1.4

Dialog {
    property var selectedHost;
    property var isSelected;
    standardButtons: StandardButton.Cancel | StandardButton.Apply
    visible: false
    title: "Select host to join"

    TableView {
        id: tableView
        anchors.fill: parent
        model: hostlistModel
        TableViewColumn {
            role: "hostName"
            title: "Host Name"
        }
        onClicked:  {
            if (hostlistModel.get(currentRow)) {
                selectedHost = hostlistModel.get(currentRow)
                isSelected = true;
            } else {
                selectedHost = null;
                isSelected = false;
            }
        }
    }
    Connections {
        target: cppSocket
        function onSetListOfGames(hostNames, gameIds) {
            hostlistModel.buildList(hostNames,gameIds);
        }
    }
    onApply: {
        joinGame();
        this.close();
    }
    onRejected: {
        this.close();
    }


    ListModel {
        id: hostlistModel
        function buildList(hostNames,gameIds){
            hostlistModel.clear();
            for(var i=0;i<hostNames.length;i++){
                append(createListElement(hostNames[i],gameIds[i]));
            }
        }
        function createListElement(hostName, gameId) {
            return {
                hostName: hostName,
                gameId: gameId
            };
        }

    }
    function joinGame(){
        if(isSelected){
            messageRect.setTurnMessage("White's turn");
            cppBoard.restart();
            chessBoard.redrawBoard();
            chessBoard.multiplayer = true;
            chessBoard.isPlayerTurn = false;
            messageRect.changeColor("Black");
            cppSocket.setGameId(selectedHost.gameId);
            cppSocket.joinGame();

        }
    }
}
