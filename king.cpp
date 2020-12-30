#include "king.h"

King::King(QString _pos, enum Color _color, QString _name):Piece(_pos, _color,_name,'K')
{

}
/**
 * @brief King::isMoveLegal King can move 1 step in any direction.
 * @param squareName QString
 * @param pieceAtNewLocation Piece*
 * @param arr Piece** representing the board
 * @return bool
 */
bool King::isMoveLegal(QString squareName, Piece* pieceAtNewLocation, Piece** arr){
    if(pieceAtNewLocation){
        if(pieceAtNewLocation->getColor() == color){
            return false;
        } else {
            return true;
        }
    } else {
        return isMovementLegal(squareName);
    }
}

bool King::isMovementLegal(QString to){
    char currentColumn = currentPosition.at(0).toLatin1();
    char currentRow = currentPosition.at(1).toLatin1();

    char newColumn = to.at(0).toLatin1();
    char newRow = to.at(1).toLatin1();

    int rowDifference = newRow-currentRow;
    int colDifference = newColumn-currentColumn;

    int rowAbs = abs(rowDifference);
    int colAbs = abs(colDifference);
    return (rowAbs == 0 || rowAbs == 1) && (colAbs == 0 || colAbs == 1);
}
