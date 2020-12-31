#include "board.h"

Board::Board(QObject *parent) : QObject(parent){
    restart();
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
/**
 * @brief Board::isMoveLegal Checks if the chess move is legal.
 * Needs to verify a list of things:
 * If checked, does move change this.
 * Is square free, if yes then check if movement is legal.
 * If no, check if piece is friendly or hostile.
 * If piece is hostile, check if take is legal.
 * @param from
 * @param to
 * @return
 */

bool Board::isMoveLegal(QString from, QString to){
    if(!isMoveStringValid(from) || !isMoveStringValid(to)){
        qDebug() << "from: " << from << " to: " << to;
        return false;
    }
    if(isCheck){

        int fromIndex = Piece::convertMoveToIndex(from);
        int toIndex = Piece::convertMoveToIndex(to);
        if(pieceArray[fromIndex]->isMoveLegal(to,pieceArray[toIndex],pieceArray)){
            //Simulate a move
            Piece* toPiece = pieceArray[toIndex];
            Piece* fromPiece = pieceArray[fromIndex];
            fromPiece->setCurrentPosition(to);
            pieceArray[toIndex] = fromPiece;
            pieceArray[fromIndex] = nullptr;

            bool isChecked = getBoardCheckStatus();
           // qDebug() << whichColorCanMove << " is checked. Will this move remove the check: " << !isChecked;

            //Reset piece locations
            pieceArray[toIndex] = toPiece;
            fromPiece->setCurrentPosition(from);
            pieceArray[fromIndex] = fromPiece;

            //If check was removed, the move is legal.
            return !isChecked;
        }
        return false;
    } else {
        //Needs to check if the move is legal, and if it puts the king in a vulnerable position
        int fromIndex = Piece::convertMoveToIndex(from);
        int toIndex = Piece::convertMoveToIndex(to);
        if(pieceArray[fromIndex]->isMoveLegal(to,pieceArray[toIndex],pieceArray)){

            Piece* toPiece = pieceArray[toIndex];
            Piece* fromPiece = pieceArray[fromIndex];
            fromPiece->setCurrentPosition(to);
            pieceArray[toIndex] = fromPiece;
            pieceArray[fromIndex] = nullptr;

            bool isChecked = getBoardCheckStatus();

            //qDebug() << whichColorCanMove << " has attempted a move, did the move put his own King in check: " << isChecked;

            //Reset piece locations
            pieceArray[toIndex] = toPiece;
            fromPiece->setCurrentPosition(from);
            pieceArray[fromIndex] = fromPiece;

            //If check was removed, the move is legal.
            return !isChecked;
        }
        return false;
    }
    /*if(isSquareFree(to)){
        return isMovementLegal(from,to);
    } else {
        if(isHostile(from, to)){
            return isTakeLegal(from,to);
        } else {
            //Only Exception to this rule is 'rokkade' which is NYI
            return false;
        }
    }
    return true;*/
}

void Board::movePiece(QString from, QString to){
    int fromIndex = Piece::convertMoveToIndex(from);
    int toIndex = Piece::convertMoveToIndex(to);
    Piece* removed = pieceArray[toIndex];
    pieceArray[toIndex] = pieceArray[fromIndex];
    pieceArray[fromIndex] = nullptr;
    pieceArray[toIndex]->setCurrentPosition(to);
    if(removed){
        delete removed;
    }
    toggleWhichColorCanMove();
    isCheck = getBoardCheckStatus();
    updateIsMate();
}

void Board::restart(){
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
    whichColorCanMove = WHITE;
}

QString Board::getWhichColorCanMove(){
    if(whichColorCanMove == WHITE){
        return "White's turn";
    } else {
        return "Black's turn";
    }
}

bool Board::doesPieceBelongToPlayer(QString square){
    int index = Piece::convertMoveToIndex(square);
    return pieceArray[index]->getColor() == whichColorCanMove;
}

void Board::toggleWhichColorCanMove(){
    if(whichColorCanMove == WHITE){
        whichColorCanMove = BLACK;
    } else {
        whichColorCanMove = WHITE;
    }
}


bool Board::getIsCheck(){
    return isCheck;
}

bool Board::getIsMate(){
    return isMate;
}


bool Board::isSquareFree(QString square){
    int index = Piece::convertMoveToIndex(square);
    return pieceArray[index];
}

bool Board::isMoveStringValid(QString move){
    if(move.length() == 2){
        //TODO add checks for A->H & 1->8
        return true;
    }
    return false;
}

QString Board::getKingSquareString(Color c){
    for(int i=0;i<64;i++){
        if(pieceArray[i] && pieceArray[i]->getType() == 'K' && pieceArray[i]->getColor() == c){
            return pieceArray[i]->getCurrentPosition();
        }
    }
    return "";
}

bool Board::getBoardCheckStatus(){
    QString vulnerableKingPosition = getKingSquareString(whichColorCanMove);
    //qDebug() << "Checking if the King @ " << vulnerableKingPosition << " is checked";
    Piece* vulnerableKingPiece = pieceArray[Piece::convertMoveToIndex(vulnerableKingPosition)];
    Color oppositeColor;
    if(whichColorCanMove == BLACK){
        oppositeColor = WHITE;
    } else {
        oppositeColor = BLACK;
    }
    for(int i=0;i<64;i++){
        if(pieceArray[i]){
            if(pieceArray[i]->getColor() == oppositeColor){
                if(pieceArray[i]->isMoveLegal(vulnerableKingPosition,vulnerableKingPiece,pieceArray)){
                    return true;
                }
            }
        }
    }
    return false;
}
/**
 * @brief Board::updateIsMate check if there exists a move which can 'un-check' the
 * vulnerable King
 */
void Board::updateIsMate(){
    if(isCheck){

    } else {
        isMate = false;
    }
}

/**
 * @brief Board::isHostile checks if the colors of the pieces are different.
 * Both squares should already be verified to contain pieces.
 * @param from QString
 * @param to QString
 * @return bool
 */
/*bool Board::isHostile(QString from, QString to){
    int fromIndex = Piece::convertMoveToIndex(from);
    int toIndex = Piece::convertMoveToIndex(to);
    return pieceArray[fromIndex]->getColor() != pieceArray[toIndex]->getColor();
}

bool Board::isTakeLegal(QString from, QString to){
    int fromIndex = Piece::convertMoveToIndex(from);
   // return pieceArray[fromIndex]->is
    int toIndex = Piece::convertMoveToIndex(to);
}

bool Board::isMovementLegal(QString from, QString to){
    int fromIndex = Piece::convertMoveToIndex(from);
    int toIndex = Piece::convertMoveToIndex(to);
}*/


