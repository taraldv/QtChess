import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.4

ApplicationWindow  {

    width: 800+50
    height: 800+80+60+21
    visible: true
    title: qsTr("Qt Chess")


    NamePopup{
        id: changeNameDialog
    }
    JoinPopup{
        id: joinDialog
    }

    Column{
        MultiplayerInfo{
            id: multiRect
            height: 40
            width: parent.width
            //color: "blue"
            Component.onCompleted: {
                setPlayerName(cppSocket.getPlayerName())
            }
        }
        MessageInfo{
            id: messageRect
            height: 40
            width: parent.width
            //anchors.top: multiRect.bottom
        }
        Row{
            NumbersColumn{
                id:leftNumbersColumn
            }

            Column{
                LettersRow{
                    id: topLettersRow
                    //anchors.top: messageRect.bottom
                }

                Board{
                    id: chessBoard
                    //anchors.top: topLettersRow.bottom
                    //y: multiRect.height+messageRect.height
                    width: 100*8;
                    height: 100*8;

                }
                LettersRow{
                    id: bottomLettersRow
                    //anchors.top: chessBoard.bottom

                }
            }
            NumbersColumn{
                id:rightNumbersColumn
            }
        }
    }

    menuBar: MenuBar {

        Menu {
            title: "File"
            MenuItem {
                text: "New Game"
                onTriggered: {
                    cppBoard.restart();
                    chessBoard.redrawBoard();
                    //multiRect.visible = false;
                    //multiRect.setPlayerName(cppSocket.getPlayerName());
                    chessBoard.multiplayer = false;
                    chessBoard.isPlayerTurn = true;
                    messageRect.setBoardMessage("");
                    messageRect.setTurnMessage("White's turn");
                }
            }
            MenuItem {
                text: "Host Game"
                onTriggered: {
                    cppBoard.restart();
                    chessBoard.redrawBoard();
                    //multiRect.visible = true;
                    multiRect.changeColor("white");
                    //multiRect.setPlayerName(cppSocket.getPlayerName());
                    chessBoard.multiplayer = true;
                    chessBoard.isPlayerTurn = true;
                    cppSocket.setHostName(cppSocket.getPlayerName());
                    cppSocket.hostGame(cppSocket.getPlayerName());
                    messageRect.setBoardMessage("");
                    messageRect.setTurnMessage("White's turn");
                }
            }
            MenuItem {
                text: "Join Game"
                onTriggered: {
                    joinDialog.open();
                }
            }
            MenuItem {
                text: "Quit"
                onTriggered: {
                    Qt.quit();
                }
            }
        }
        Menu {
            title: "Options"
            MenuItem {
                text: "Change name"
                onTriggered: {
                    changeNameDialog.open();
                }
            }
        }
    }
}

