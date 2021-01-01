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
    Component.onCompleted: {
        hostlistModel.buildList();
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
        function buildList(){
            append(createListElement("test name","testId"));
        }
        function createListElement(hostName, hostId) {
            return {
                hostName: hostName,
                hostId: hostId
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
            cppSocket.setHostName(selectedHost.hostId);
            cppSocket.joinGame(cppSocket.getHostName(),cppSocket.getPlayerName());

        }
    }
}
