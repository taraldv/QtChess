import QtQuick 2.12

Rectangle {
    width: 100*9; height: 100*9
    property var isSquareSelected;
    property var squareName;


    Image{
        id: cursorImage
        source: "img/blank.png"
        x: 0
        y: 0
    }
    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onPressed: {
            isSquareSelected = false;
            squareName = "";
            boardModel.buildBoard();
        }
    }

    Component {
        id: squareDelegate
        Rectangle {
            color: squareColor;
            width: 100;
            height: 100;
            CustomBorder
            {
                commonBorderWidth: 2
                borderColor: "black"
            }
            MouseArea {
                anchors.fill: parent
                onPressed: {
                    if(number == 0){

                    } else {
                        if(isSquareSelected){
                            var isMoveLegal = cppBoard.isMoveLegal(squareName,letter+number);
                            //console.log(isMoveLegal)
                            if(isMoveLegal){
                                boardMessage.text = ""
                                cppBoard.movePiece(squareName,letter+number);
                                turnMessage.text = cppBoard.getWhichColorCanMove();
                                var isCheck = cppBoard.getIsCheck();
                                if(isCheck){
                                    boardMessage.text = "Check!"
                                }
                            } else {
                                boardMessage.text = "Invalid move"
                            }

                            isSquareSelected = false;
                            squareName = "";
                            boardModel.buildBoard();
                        } else {
                            if(pngSource != "blank" && cppBoard.doesPieceBelongToPlayer(letter+number)){
                                isSquareSelected = true;
                                squareName = letter+number;
                                rectangleImage.source = "img/"+pngSource+"Selected.png"
                            }
                        }
                    }
                    /*console.log(letter+number);
                    console.log(mouse.x)
                    console.log(mouse.y)
                    //This makes the click propagate to mouseArea "below" this mouseArea
                    mouse.accepted = false*/

                }
            }
            /* Text{
                text: letter + number
                color: "black"
            }*/
            Image {
                id: rectangleImage
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                source: "img/"+pngSource+".png"

            }
        }

    }

    GridView {
        interactive: false
        //cellHeight: 60
        // cellWidth: 60
        anchors.fill: parent
        model: boardModel
        delegate: squareDelegate
        //highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        //focus: true
    }
    Component.onCompleted: {
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
            // var pngSource = "blank";
            var currentBoardPiecesArray = cppBoard.getPiecePNGList();
            /*
            Loop iteration:
                A8,B8,C8,D8,E8,F8,G8,H8,A7...
            */
            var index = 0;
            //Add '0' as extra row, which is not part of the board, for displaying letters
            for(var row=8;row>=0;row--){
                //Add '-1' as extra column, to display numbers
                for(var column=-1;column<8;column++){
                    //Red for undefined square
                    var color = "red";
                    var specialColor = "whitesmoke";
                    if(row === 0 && column === -1){
                        append(createListElement(0,"x",specialColor,"blank"));
                    }else if(row === 0){
                        var letterSquare = createListElement(0,"x",specialColor, String.fromCharCode(column+65));
                        append(letterSquare);
                    } else if(column === -1) {
                        var numberSquare = createListElement(0,"x",specialColor, String.fromCharCode(row+48));
                        append(numberSquare);
                    } else {
                        if(row % 2 == 0){
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
                        var element = createListElement(row,letter,color, currentBoardPiecesArray[index]);
                        append(element);
                        index++;
                    }
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
