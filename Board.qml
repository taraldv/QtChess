import QtQuick 2.12

Rectangle {
    width: 100*8; height: 100*8
    Component {
        id: squareDelegate
        Rectangle {
            color: squareColor;
            width: 100;
            height: 100;
            Text{
                text: letter + number
                color: "black"
            }
            Image {
                anchors.verticalCenter: parent.verticalCenter
                source: "img/"+pngSource+".png"
                //  width: maDownloadImage.containsMouse ? 34 : 32
                // height: maDownloadImage.containsMouse ? 34 : 32

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log(letter+number)
                        // parent.parent.border.color = "red";
                        // publicTorrrentTitle = title;
                        // publicTorrentId = torrentId;
                        // fileDialog.open();
                        //torrentHandler.downloadFile(torrentId, user.getTorrentPass());
                    }
                }
            }
        }

    }

    GridView {
        //cellHeight: 60
        // cellWidth: 60
        anchors.fill: parent
        model: boardModel
        delegate: squareDelegate
        //highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        // focus: true
    }
    Component.onCompleted: {
        console.log(cppBoard.getPiecePNGList());
        boardModel.buildBoard();
    }

    function redrawBoard(){
        boardModel.buildBoard();
    }

    ListModel {
        id: boardModel
        function buildBoard(list){
            boardModel.clear();
            var white = "bisque";
            var black = "saddlebrown";
            var pngSource = "blank";
            /*
            Loop iteration:
                A8,B8,C8,D8,E8,F8,G8,H8,A7...
            */
            var index = 0;
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
                    console.log(letter+row)
                    var element = createListElement(row,letter,color, pngSource);
                    append(element);
                    index++;
                }
            }
        }
        function createListElement(number, letter ,color, pngSource) {
            return {
                number: number,
                letter: letter,
                squareColor: color,
                pngSource: pngSource
            };
        }

    }


}
