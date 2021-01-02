#include "pawn.h"

Pawn::Pawn(QString _pos, enum Color _color, QString _name):Piece(_pos, _color,_name,'P')
{

}
/**
 * @brief Pawn::isMoveLegal Pawn has three different movements, two forward, one forward or take.
 * @param squareName QString
 * @param pieceAtNewLocation Piece*
 * @param arr Piece** array representing the board
 * @return bool
 */
bool Pawn::isMoveLegal(QString squareName, Piece* pieceAtNewLocation, Piece** arr){
    if(pieceAtNewLocation){
        if(pieceAtNewLocation->getColor() == color){
            return false;
        } else {
            if(pawnTake(squareName)){
                recentlyMovedTwice = false;
                return true;
            }
        }
    } else {
        if(pawnForwardTwo(squareName)){
            recentlyMovedTwice = true;
            return true;
        } else if(pawnForwardOne(squareName)){
            recentlyMovedTwice = false;
            return true;
        } else if(enPassantTake(arr, squareName)){
            recentlyMovedTwice = false;
            return true;
        }
    }
    return false;
}

bool Pawn::getRecentlyMovedTwice() const
{
    return recentlyMovedTwice;
}
/**
 * @brief Pawn::hasReachedEndOfBoard, checks if this piece has reached the end of board
 * and should be replaced with a Queen. This function should only be called after a move.
 * @return
 */
bool Pawn::hasReachedEndOfBoard(){
    char currentRow = currentPosition.at(1).toLatin1();
    if(color == WHITE){
        return currentRow == '8';
    } else if(color == BLACK) {
        return currentRow == '1';
    }
    return false;
}
/**
 * @brief Pawn::pawnForwardOne Forward one means no change in column and one increment
 * decrement in row, depending on color. White should increase, black should decrease.
 * @param newPosition QString
 * @return bool
 */
bool Pawn::pawnForwardOne(QString newPosition)
{
    //Column means letters
    char currentColumn = currentPosition.at(0).toLatin1();
    char currentRow = currentPosition.at(1).toLatin1();

    char newColumn = newPosition.at(0).toLatin1();
    char newRow = newPosition.at(1).toLatin1();

    int difference = newRow-currentRow;

    if(currentColumn == newColumn){
        if(color == WHITE){
            return difference == 1;
        } else if(color == BLACK){
            return difference == -1;
        }
    }
    return false;
}
/**
 * @brief Pawn::pawnForwardTwo Forward two can only be done at the starting position.
 * Which can be checked with the row, 2 for white, 7 for black.
 * @param newPos QString
 * @return bool
 */
bool Pawn::pawnForwardTwo(QString newPos)
{
    //Column means letters
    char currentColumn = currentPosition.at(0).toLatin1();
    char currentRow = currentPosition.at(1).toLatin1();

    char newColumn = newPos.at(0).toLatin1();
    char newRow = newPos.at(1).toLatin1();
    int difference = newRow-currentRow;

    if(currentColumn == newColumn){
        if(color == WHITE && currentRow == (2+48)){
            return difference == 2;
        } else if(color == BLACK && currentRow == (7+48)){
            return difference == -2;
        }
    }
    return false;

}
/**
 * @brief Pawn::enPassantTake need to check if an opponent pawn is adjecent.
 * If yes, check if it moved twice.
 * If it moved twice, this is a legal take.
 * The board does not have the logic to remove a piece not on 'From' or 'To' squares.
 * So the piece is removed in this function.
 * @param arr Piece array
 * @return bool
 */
bool Pawn::enPassantTake(Piece **arr, QString newPos){
    char currentColumn = currentPosition.at(0).toLatin1();
    char currentRow = currentPosition.at(1).toLatin1();

    char newColumn = newPos.at(0).toLatin1();
    char newRow = newPos.at(1).toLatin1();
    int rowDifference = newRow-currentRow;
    int colDifference = newColumn-currentColumn;
    bool isSingleDiagonallyMovement = false;
    if(color == WHITE){
        isSingleDiagonallyMovement = rowDifference == 1 && (colDifference == 1 || colDifference == -1);
    } else if(color == BLACK){
        isSingleDiagonallyMovement = rowDifference == -1 && (colDifference == 1 || colDifference == -1);
    }

    //To find the location of the piece we use current row with the new column
    if(isSingleDiagonallyMovement){
        QString adjecentSquare = "";
        adjecentSquare += newColumn;
        adjecentSquare += currentRow;
        int index = Piece::convertMoveToIndex(adjecentSquare);
        Piece* tempPiece = arr[index];
        //Separated into two ifs for readability
        if(tempPiece && tempPiece->getType()=='P' && tempPiece->getColor() != color){
            if(((Pawn*)tempPiece)->getRecentlyMovedTwice()){
                //Deletes the piece and returns the move is legal
                arr[index] = nullptr;
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Pawn::pawnTake Pawns can only take diagonally, a hostile piece already exists at the newPos
 * Only need to check if it is 1 diagonally depending on color
 * @param newPos QString
 * @return bool
 */
bool Pawn::pawnTake(QString newPos)
{
    //Column means letters
    char currentColumn = currentPosition.at(0).toLatin1();
    char currentRow = currentPosition.at(1).toLatin1();

    char newColumn = newPos.at(0).toLatin1();
    char newRow = newPos.at(1).toLatin1();

    int rowDifference = newRow-currentRow;
    int colDifference = newColumn-currentColumn;
    if(color == WHITE){
        return rowDifference == 1 && (colDifference == 1 || colDifference == -1);
    } else if(color == BLACK){
        return rowDifference == -1 && (colDifference == 1 || colDifference == -1);
    }
    return false;
}
/**
 * @brief Pawn::convertToQueen
 * Create a new Queen and replace this pointer with queen
 * Move this Piece to the newposision, so the board will remove it when it calls 'movePiece'
 */
void Pawn::convertToQueen(){

}

