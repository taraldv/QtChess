import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.4

ApplicationWindow  {
    width: 900
    height: 950
    visible: true
    title: qsTr("Qt Chess")
    Rectangle{
        color: "whitesmoke"
        height: 50
        width: parent.width
        Text{
            id: boardMessage
            anchors.left: parent.left
            text: ""
            font.family: "Helvetica"
            font.pointSize: 24
            font.bold: true
            color: "red"
        }
        Text{
            id: turnMessage
            anchors.right: parent.right
            text: "White's turn"
            font.family: "Helvetica"
            font.pointSize: 24
            font.bold: true
            color: "black"
        }

    }
    Board{
        y: 50
        id: chessBoard
    }
    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem {
                text: "New Game"
                onTriggered: {
                    cppBoard.restart();
                    chessBoard.redrawBoard();
                    boardMessage.text = "";
                    turnMessage.text = "White's turn";
                }
            }
            MenuItem {
                text: "Quit"
                onTriggered: {
                    Qt.quit();
                }
            }
        }

    }
}

