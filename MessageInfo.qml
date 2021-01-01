import QtQuick 2.15

Rectangle{
    color: "whitesmoke"
    width: parent.width
    height: 40

    Grid{
        leftPadding: 10
        rightPadding: 10
        height: parent.height
        rows: 1;
        columns: 7;
        spacing: 10;
        horizontalItemAlignment: Grid.AlignHCenter;
        verticalItemAlignment: Grid.AlignVCenter;
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
            width: 30
            height: parent.height
            color: "whitesmoke"
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
        Rectangle{
            width: 30
            height: parent.height
            color: "whitesmoke"
        }
        Text{
            id: turnMessage
            text: "White's turn"
            font.family: "Helvetica"
            font.pointSize: 20
            font.bold: true
            color: "black"

        }
        Rectangle{
            width: 30
            height: parent.height
            color: "whitesmoke"
        }
        Text{
            id: boardMessage
            text: ""
            font.family: "Helvetica"
            font.pointSize: 20
            font.bold: true
            color: "red"

        }



    }

    function setTurnMessage(msg){
        turnMessage.text = msg;
    }
    function setBoardMessage(msg){
        boardMessage.text = msg;
    }
    function changeColor(color){
        playerColor.text = color;
    }
    function setPlayerName(name){
        playerNameText.text = name;
    }

}

