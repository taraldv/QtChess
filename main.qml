import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.4

ApplicationWindow  {
    width: 1000
    height: 950
    visible: true
    title: qsTr("Qt Chess")
    MultiplayerInfo{
        id: multiRect
        height: 40
        width: parent.width
        color: "red"
    }

    Rectangle{
        y: 40
        color: "whitesmoke"
        height: 40
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
        y: 80
        width: 100*10;
        height: 100*9
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
                    chessBoard.multiplayer = false;
                    chessBoard.isPlayerTurn = true;
                    boardMessage.text = "";
                    turnMessage.text = "White's turn";
                }
            }
            MenuItem {
                text: "Host Game"
                onTriggered: {
                    cppBoard.restart();
                    chessBoard.redrawBoard();
                    chessBoard.multiplayer = true;
                    chessBoard.isPlayerTurn = true;
                    cppSocket.hostGame("Hoster");
                    boardMessage.text = "";
                    turnMessage.text = "White's turn";
                }
            }
            MenuItem {
                text: "Join Game"
                onTriggered: {
                    cppBoard.restart();
                    chessBoard.redrawBoard();
                    chessBoard.multiplayer = true;
                    chessBoard.isPlayerTurn = false;
                    cppSocket.joinGame("Hoster","Joiner");
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

