import QtQuick 2.12

Rectangle {
    property var isSquareSelected;
    property var squareName;
    property var multiplayer;
    property var isPlayerTurn;
    Connections {
        target: cppSocket
        function onMultiplayerMove(from, to) {
            console.log("Opponent has moved from: "+from+" to: "+to);
            cppBoard.movePiece(from,to);
            turnMessage.text = cppBoard.getWhichColorCanMove();
            var isCheck = cppBoard.getIsCheck();
            if(isCheck){
                boardMessage.text = "Check!"
            }
            isPlayerTurn = true;
            isSquareSelected = false;
            squareName = "";
            boardModel.buildBoard();
        }
    }
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
    function singleplayerMove(letter, number, pngSource, image){
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
            selectSquare(letter,number,pngSource, image);
        }
    }
    function selectSquare(letter, number, pngSource,image){
        if(pngSource !== "blank" && cppBoard.doesPieceBelongToPlayer(letter+number)){
            isSquareSelected = true;
            squareName = letter+number;
            //console.log(image);
            image.source = "img/"+pngSource+"Selected.png"
        }
    }

    function multiplayerMove(letter,number, pngSource, image){
        if(isSquareSelected){
            var isMoveLegal = cppBoard.isMoveLegal(squareName,letter+number);
            //console.log(isMoveLegal)
            if(isMoveLegal){
                boardMessage.text = ""
                cppBoard.movePiece(squareName,letter+number);
                cppSocket.move("Hoster",squareName,letter+number);
                console.log("Player has moved from: "+squareName+" to: "+letter+number);
                isPlayerTurn = false;
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
            selectSquare(letter,number,pngSource,image);
        }
    }

    Component {
        id: squareDelegate
        Rectangle {
            color: squareColor;
            width: w;
            height: h;
            CustomBorder
            {
                commonBorderWidth: 2
                borderColor: "black"
            }
            MouseArea {
                anchors.fill: parent
                onPressed: {
                    //Do nothing if square number is 0 (outside the board)
                    if(number != 0){
                        if(multiplayer && isPlayerTurn){
                            multiplayerMove(letter,number,pngSource,rectangleImage);
                        } else if(!multiplayer) {
                            singleplayerMove(letter,number,pngSource, rectangleImage);
                        }
                    }
                }
            }
            Text{
                visible: textVisible
                text: letter
                color: "black"
                font.pointSize: 30
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Image {
                visible: imageVisible
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
                for(var column=-1;column<=8;column++){
                    //Red for undefined square
                    var color = "red";
                    var specialColor = "whitesmoke";
                    if(row === 0 && column === -1){
                        append(createListElement(0, "x", specialColor, "blank",
                                                 false, false, 50, 50));
                    } else if(column === 8){
                        if(row ===0){
                            var cornerSquare = createListElement(0, "x", specialColor, "blank",
                                                                false, false, 50, 50);
                            append(cornerSquare);
                        }

                        var blankSquare = createListElement(0, "x", specialColor, "blank",
                                                            false, false, 50, 100);
                        append(blankSquare);
                    }else if(row === 0){
                        var letterSquare = createListElement(0, String.fromCharCode(column+65), specialColor, "blank",
                                                             false, true, 100, 50);
                        append(letterSquare);
                    } else if(column === -1) {
                        var numberSquare = createListElement(0, String.fromCharCode(row+48), specialColor, "blank",
                                                             false, true, 50, 100);
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
                        var element = createListElement(row,letter,color, currentBoardPiecesArray[index], true, false, 100, 100);
                        append(element);
                        index++;
                    }
                }
            }
        }
        function createListElement(number, letter ,color, pngSource, imageVisible, textVisible, width, height) {
            return {
                number: number,
                letter: letter,
                squareColor: color,
                pngSource: pngSource,
                imageVisible: imageVisible,
                textVisible: textVisible,
                w: width,
                h: height
            };
        }

    }


}
