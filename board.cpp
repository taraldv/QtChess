#include "board.h"

Board::Board(QObject *parent) : QObject(parent)
{
    /*
    Loop iteration (same as QML expects):
        A8,B8,C8,D8,E8,F8,G8,H8,A7...

        0-7
        8-15

        16-23
        24-31
        32-39
        40-47

        48-55
        56-63

        Positions 0-15 is black pieces
        Positions 48-63 is white pieces
    */
    pieceArray[0] = (Piece*)new Rook("A8",BLACK,"bR");
    pieceArray[1] = (Piece*)new Knight("B8",BLACK,"bN");
    pieceArray[2] = (Piece*)new Bishop("C8",BLACK,"bB");
    pieceArray[3] = (Piece*)new Queen("D8",BLACK,"bQ");
    pieceArray[4] = (Piece*)new King("E8",BLACK,"bK");
    pieceArray[5] = (Piece*)new Bishop("F8",BLACK,"bB");
    pieceArray[6] = (Piece*)new Knight("G8",BLACK,"bN");
    pieceArray[7] = (Piece*)new Rook("H8",BLACK,"bR");

    pieceArray[8] = (Piece*)new Pawn("A7",BLACK,"bP");
    pieceArray[9] = (Piece*)new Pawn("B7",BLACK,"bP");
    pieceArray[10] = (Piece*)new Pawn("C7",BLACK,"bP");
    pieceArray[11] = (Piece*)new Pawn("D7",BLACK,"bP");
    pieceArray[12] = (Piece*)new Pawn("E7",BLACK,"bP");
    pieceArray[13] = (Piece*)new Pawn("F7",BLACK,"bP");
    pieceArray[14] = (Piece*)new Pawn("G7",BLACK,"bP");
    pieceArray[15] = (Piece*)new Pawn("H7",BLACK,"bP");

    pieceArray[48] = (Piece*)new Pawn("A2",WHITE,"wP");
    pieceArray[49] = (Piece*)new Pawn("B2",WHITE,"wP");
    pieceArray[50] = (Piece*)new Pawn("C2",WHITE,"wP");
    pieceArray[51] = (Piece*)new Pawn("D2",WHITE,"wP");
    pieceArray[52] = (Piece*)new Pawn("E2",WHITE,"wP");
    pieceArray[53] = (Piece*)new Pawn("F2",WHITE,"wP");
    pieceArray[54] = (Piece*)new Pawn("G2",WHITE,"wP");
    pieceArray[55] = (Piece*)new Pawn("H2",WHITE,"wP");

    pieceArray[56] = (Piece*)new Rook("A1",WHITE,"wR");
    pieceArray[57] = (Piece*)new Knight("B1",WHITE,"wN");
    pieceArray[58] = (Piece*)new Bishop("C1",WHITE,"wB");
    pieceArray[59] = (Piece*)new Queen("D1",WHITE,"wQ");
    pieceArray[60] = (Piece*)new King("E1",WHITE,"wK");
    pieceArray[61] = (Piece*)new Bishop("F1",WHITE,"wB");
    pieceArray[62] = (Piece*)new Knight("G1",WHITE,"wN");
    pieceArray[63] = (Piece*)new Rook("H1",WHITE,"wR");

    //Trodde nullptr var default, men krasjer uten dette
    for(int i=16;i<=47;i++){
        pieceArray[i] = nullptr;
    }

}

QVariantList Board::getPiecePNGList(){
    QVariantList output;
    for(int i=0;i<64;i++){
        if(pieceArray[i]){
            output.append(pieceArray[i]->getName());
        } else {
            output.append("blank");
        }
    }
    return output;
}
