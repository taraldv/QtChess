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
            return pawnTake(squareName);
        }
    } else {
        return pawnForwardOne(squareName) || pawnForwardTwo(squareName);
    }
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

