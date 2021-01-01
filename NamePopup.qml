import QtQuick 2.0
import QtQuick.Dialogs 1.3

Dialog {
    visible: false
    height: 100
    title: "Change player name"
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
            id: playerNameInput
            anchors.verticalCenter: parent.verticalCenter
            text: "";
            width: parent.width
            font.family: "Helvetica"
            font.pointSize: 20
            font.bold: true
            //color: black
            onAccepted: {
                cppSocket.setPlayerName(playerNameInput.text);
                messageRect.setPlayerName(playerNameInput.text);

            }
        }

    }

    Component.onCompleted: {
        playerNameInput.text = cppSocket.getPlayerName();
    }
    onApply: {
        cppSocket.setPlayerName(playerNameInput.text);
        messageRect.setPlayerName(playerNameInput.text);
        this.close();
    }
    onRejected: {
        this.close();
    }
}
