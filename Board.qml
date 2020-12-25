import QtQuick 2.0

Rectangle {
    width: 60*8; height: 60*8

    Component {
        id: contactDelegate
        Rectangle {
            color: squareColor;
            width: 60;
            height: 60
            Text{
                text: letter + number
                color: "black"
            }
            Image {
                anchors.verticalCenter: parent.verticalCenter
                source: {"img/wR.png"}
                //  width: maDownloadImage.containsMouse ? 34 : 32
                // height: maDownloadImage.containsMouse ? 34 : 32

                MouseArea {
                    id: maDownloadImage
                    anchors.fill: parent
                    onClicked: {
                        publicTorrrentTitle = title;
                        publicTorrentId = torrentId;
                        fileDialog.open();
                        //torrentHandler.downloadFile(torrentId, user.getTorrentPass());
                    }
                }
            }
        }

    }

    GridView {
        cellHeight: 60
        cellWidth: 60
        anchors.fill: parent
        model: boardModel
        delegate: contactDelegate
        //highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        // focus: true
    }
    Component.onCompleted: {
        boardModel.buildBoard();
    }
    ListModel {
        id: boardModel
        function buildBoard(){
            var white = "bisque";
            var black = "saddlebrown";
            for(var row=8;row>0;row--){
                for(var column=0;column<8;column++){
                    //Red for undefined square
                    var color = "red"
                    if(row % 2 ==0){
                        if(column % 2 ==0){
                            color = white
                        } else {
                            color = black
                        }
                    } else {
                        if(column % 2 ==0){
                            color = black
                        } else {
                            color = white
                        }
                    }
                    //Big letter 'A' in ascii is 65
                    var letter = String.fromCharCode(column+65);
                    var element = createListElement(row,letter,color);
                    append(element);
                }
            }
        }
        function createListElement(number, letter ,color) {
            return {
                number: number,
                letter: letter,
                squareColor: color
            };
        }

    }


}
