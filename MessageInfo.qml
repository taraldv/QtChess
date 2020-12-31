import QtQuick 2.0

Rectangle{
    color: "whitesmoke"
    Text{
        id: boardMessage
        anchors.left: parent.left
        text: ""
        font.family: "Helvetica"
        font.pointSize: 20
        font.bold: true
        color: "red"
    }
    Text{
        id: turnMessage
        anchors.right: parent.right
        text: "White's turn"
        font.family: "Helvetica"
        font.pointSize: 20
        font.bold: true
        color: "black"
    }
    Connections {
        target: cppSocket
        function onServerError(error) {
            setBoardMessage(error);
        }
    }
    function setTurnMessage(msg){
        turnMessage.text = msg;
    }
    function setBoardMessage(msg){
        boardMessage.text = msg;
    }

}
