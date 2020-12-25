import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.4

ApplicationWindow  {
    width: 900
    height: 900
    visible: true
    title: qsTr("Qt Chess")
    Board{
        id: chessBoard
    }
    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem {
                text: "New Game"
                onTriggered: {
                    chessBoard.redrawBoard()
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

