#include "knight.h"

Knight::Knight(QString _pos, enum Color _color, QString _name):Piece(_pos, _color,_name,'R')
{

}
/**
 * @brief Knight::isMoveLegal Knight has 8 different moves
 * @param squareName QString
 * @param pieceAtNewLocation Piece*
 * @param arr Piece** representing the board
 * @return bool
 */
bool Knight::isMoveLegal(QString squareName, Piece* pieceAtNewLocation, Piece** arr){
    if(isMovementLegal(squareName)){
        if(pieceAtNewLocation){
            if(pieceAtNewLocation->getColor() == color){
                return false;
            } else {
                return true;
            }
        } else {
            return true;
        }
    }
    return false;
}

bool Knight::isMovementLegal(QString to){
    char currentColumn = currentPosition.at(0).toLatin1();
    char currentRow = currentPosition.at(1).toLatin1();

    char newColumn = to.at(0).toLatin1();
    char newRow = to.at(1).toLatin1();

    bool one = (currentColumn+1 == newColumn) && (currentRow+2 == newRow);
    bool two = (currentColumn+1 == newColumn) && (currentRow-2 == newRow);
    bool three = (currentColumn-1 == newColumn) && (currentRow+2 == newRow);
    bool four = (currentColumn-1 == newColumn) && (currentRow-2 == newRow);

    bool five = (currentColumn+2 == newColumn) && (currentRow+1 == newRow);
    bool six = (currentColumn+2 == newColumn) && (currentRow-1 == newRow);
    bool seven = (currentColumn-2 == newColumn) && (currentRow+1 == newRow);
    bool eight = (currentColumn-2 == newColumn) && (currentRow-1 == newRow);

    return one || two || three || four || five || six || seven || eight;

}
