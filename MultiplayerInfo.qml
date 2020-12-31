import QtQuick 2.0

Rectangle {
    color: "whitesmoke"
    //visible: false
    function changeColor(color){
        playerColor.text = color;
    }
    function setPlayerName(name){
        playerNameText.text = name;
    }

    Row{
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        Text{
            text: "Player name: "
           // anchors.right: parent.right
            font.family: "Helvetica"
            font.pointSize: 20
            font.bold: true
            color: "black"
        }
        Text{
            id: playerNameText
            //anchors.right: parent.right
            text: ""
            font.family: "Helvetica"
            font.pointSize: 20
            font.bold: true
            color: "black"
        }
        Rectangle{
             width: 100
             height: parent.height
             color: "whitesmoke"
        }
        Text{
            text: "Player color: "
           // anchors.right: parent.right
            font.family: "Helvetica"
            font.pointSize: 20
            font.bold: true
            color: "black"
        }
        Text{
            id: playerColor
            //anchors.right: parent.right
            text: "White"
            font.family: "Helvetica"
            font.pointSize: 20
            font.bold: true
            color: "black"
        }
    }
}
