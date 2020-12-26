#include "bishop.h"

Bishop::Bishop(QString _pos, enum Color _color, QString _name):Piece(_pos, _color,_name,'R')
{

}
/**
 * @brief Bishop::isMoveLegal Bishop can move in any direction, but only diagonally.
 * Important to check if any piece is blocking the move.
 * @param squareName QString
 * @param pieceAtNewLocation QString
 * @param arr Piece** array representing the board
 * @return bool
 */
bool Bishop::isMoveLegal(QString squareName, Piece* pieceAtNewLocation, Piece** arr){

    if(isMovementBlocked(squareName, arr)){
        return false;
    } else {
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

}

bool Bishop::isMovementBlocked(QString to, Piece** arr)
{
    char currentColumn = currentPosition.at(0).toLatin1();
    char currentRow = currentPosition.at(1).toLatin1();

    char newColumn = to.at(0).toLatin1();
    char newRow = to.at(1).toLatin1();

    int rowDifference = newRow-currentRow;
    int colDifference = newColumn-currentColumn;

    int rowAbs = abs(rowDifference);
    int colAbs = abs(colDifference);

    //If these two values are the same, the move should be diagonally
    if(rowAbs == colAbs){
        for(int i=1;i<rowAbs;i++){
            QString tempPosition;

            if(colDifference > 0){
                tempPosition.append(currentColumn+i);
            } else{
                tempPosition.append(currentColumn-i);
            }
            if(rowDifference > 0){
                tempPosition.append(currentRow+i);
            } else {
                tempPosition.append(currentRow-i);
            }
            int tempIndex = convertMoveToIndex(tempPosition);
            if(arr[tempIndex]){
                return true;
            }
        }
    }
    return false;
}

