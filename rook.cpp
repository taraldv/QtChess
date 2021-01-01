#include "rook.h"

Rook::Rook(QString _pos, enum Color _color, QString _name):Piece(_pos, _color,_name,'R')
{

}
/**
 * @brief Rook::isMoveLegal Rooks move in straight lines, like bishop only need to
 * check if the movement is blocked by another piece.
 * @param squareName QString
 * @param pieceAtNewLocation Piece*
 * @param arr Piece** array representing the board
 * @return bool
 */
bool Rook::isMoveLegal(QString squareName, Piece* pieceAtNewLocation, Piece** arr){
    if(isMovementLegal(squareName)){
        if(isMovementBlocked(squareName, arr)){
            return false;
        } else {
            if(pieceAtNewLocation){
                if(pieceAtNewLocation->getColor() == color){
                    return false;
                } else {
                    hasMoved = true;
                    return true;
                }
            } else {
                hasMoved = true;
                return true;
            }
        }
    }
    return false;
}

bool Rook::isMovementBlocked(QString to, Piece** arr)
{
    char currentColumn = currentPosition.at(0).toLatin1();
    char currentRow = currentPosition.at(1).toLatin1();

    char newColumn = to.at(0).toLatin1();
    char newRow = to.at(1).toLatin1();

    int rowDifference = newRow-currentRow;
    int colDifference = newColumn-currentColumn;

    int rowAbs = abs(rowDifference);
    int colAbs = abs(colDifference);


    int squaresMoved = std::max(rowAbs, colAbs);
    for(int i=1;i<squaresMoved;i++){
        QString tempPosition;
        //If row has not changed, increment column to see if path is blocked
        if(rowDifference == 0){
            if(colDifference > 0){
                tempPosition.append(currentColumn+i);
            } else{
                tempPosition.append(currentColumn-i);
            }
            tempPosition.append(currentRow);
        }
        //If col has not changed, increment row to see if path is blocked
        if(colDifference == 0){
            tempPosition.append(currentColumn);
            if(rowDifference > 0){
                tempPosition.append(currentRow+i);
            } else {
                tempPosition.append(currentRow-i);
            }
        }
        int tempIndex = convertMoveToIndex(tempPosition);
        if(arr[tempIndex]){
            return true;
        }
    }
    return false;
}

bool Rook::isMovementLegal(QString to)
{
    char currentColumn = currentPosition.at(0).toLatin1();
    char currentRow = currentPosition.at(1).toLatin1();

    char newColumn = to.at(0).toLatin1();
    char newRow = to.at(1).toLatin1();

    int rowDifference = newRow-currentRow;
    int colDifference = newColumn-currentColumn;
    //If one of these values is 0, the movement is straight
    return (rowDifference == 0 || colDifference == 0);
}

bool Rook::getHasMoved() const
{
    return hasMoved;
}
