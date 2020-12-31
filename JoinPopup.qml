import QtQuick 2.0
import QtQuick.Dialogs 1.3

Dialog {
    visible: false
    height: 100
    title: "Type host name"
    //modal: true
    //anchors.centerIn: parent
    standardButtons:  Dialog.Close | Dialog.Apply
    Rectangle{
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        color: "white"
        border.color: "black"

        width: parent.width
        height: 40
        TextInput{
            id: hostNameInput
            width: parent.width
            anchors.verticalCenter: parent.verticalCenter
            text: "";
            font.family: "Helvetica"
            font.pointSize: 20
            font.bold: true
            //color: black
            onAccepted: {
                joinGame();
            }
        }

    }
    function joinGame(){
        messageRect.setBoardMessage("");
        messageRect.setTurnMessage("White's turn");
        cppBoard.restart();
        chessBoard.redrawBoard();
        chessBoard.multiplayer = true;
        chessBoard.isPlayerTurn = false;
        //multiRect.visible = true;
        multiRect.changeColor("black");
        cppSocket.setHostName(hostNameInput.text);
        cppSocket.joinGame(hostNameInput.text,cppSocket.getPlayerName());

    }

    Component.onCompleted: {
        hostNameInput.text = cppSocket.getHostName();
    }
    onApply: {
        joinGame();
        this.close();
    }
    onRejected: {
        this.close();
    }
}
