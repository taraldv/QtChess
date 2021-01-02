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
            messageRect.setTurnMessage(cppBoard.getWhichColorCanMove());
            var isCheck = cppBoard.getIsCheck();
            if(isCheck){
                messageRect.setBoardMessage("Check!");
            }
            isPlayerTurn = true;
            isSquareSelected = false;
            squareName = "";
            boardModel.buildBoard();
        }
    }
    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onPressed: {
            if(isSquareSelected){
                isSquareSelected = false;
                squareName = "";
                boardModel.buildBoard();
            }
        }
    }
    function singleplayerMove(letter, number, pngSource, image){
        if(isSquareSelected){
            var isMoveLegal = cppBoard.isMoveLegal(squareName,letter+number);
            //console.log(isMoveLegal)
            if(isMoveLegal){
                messageRect.setBoardMessage("");
                cppBoard.movePiece(squareName,letter+number);
                messageRect.setTurnMessage(cppBoard.getWhichColorCanMove());
                var isCheck = cppBoard.getIsCheck();
                var isMate = cppBoard.getIsMate();
                if(isMate){
                    messageRect.setBoardMessage("Checkmate!");
                } else if(isCheck){
                    messageRect.setBoardMessage("Check!");
                }

            } else {
                messageRect.setBoardMessage("Invalid move");
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
                messageRect.setBoardMessage("");
                cppBoard.movePiece(squareName,letter+number);
                cppSocket.move(squareName,letter+number);
                // console.log("Player has moved from: "+squareName+" to: "+letter+number);
                isPlayerTurn = false;
                messageRect.setTurnMessage(cppBoard.getWhichColorCanMove());
                var isCheck = cppBoard.getIsCheck();
                var isMate = cppBoard.getIsMate();
                if(isMate){
                    messageRect.setBoardMessage("Checkmate!");
                } else if(isCheck){
                    messageRect.setBoardMessage("Check!");
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
            width: 100;
            height: 100;
            MouseArea {
                anchors.fill: parent
                onPressed: {
                    if(multiplayer && isPlayerTurn){
                        multiplayerMove(letter,number,pngSource,rectangleImage);
                    } else if(!multiplayer) {
                        singleplayerMove(letter,number,pngSource, rectangleImage);
                    }
                }
            }
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
        anchors.fill: parent
        model: boardModel
        delegate: squareDelegate
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
            for(var row=8;row>0;row--){
                //Add '-1' as extra column, to display numbers
                for(var column=0;column<8;column++){
                    //Red for undefined square
                    var color = "red";

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
