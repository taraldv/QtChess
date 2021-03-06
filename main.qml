import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.4

ApplicationWindow  {

    // width: 1000
    //height: 1000
    visible: true
    title: qsTr("Qt Chess")
    //color: "red"


    NamePopup{
        id: changeNameDialog
    }
    JoinPopup{
        id: joinDialog
    }

    Column{
        MessageInfo{
            id: messageRect
            Component.onCompleted: {
                setPlayerName(cppSocket.getPlayerName())
            }
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
        ErrorMessage{
            id: errorRect
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
                    messageRect.changeColor("White");
                    chessBoard.multiplayer = true;
                    chessBoard.isPlayerTurn = true;
                    cppSocket.hostGame();
                    messageRect.setTurnMessage("White's turn");

                }
            }
            MenuItem {
                text: "Join Game"
                onTriggered: {
                    cppSocket.requestGames();
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

