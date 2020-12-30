#include "queen.h"

Queen::Queen(QString _pos, enum Color _color, QString _name):Piece(_pos, _color,_name,'Q')
{

}
/**
 * @brief Queen::isMoveLegal Queen movement is simply Rook+Bishop movement
 * @param squareName QString
 * @param pieceAtNewLocation Piece*
 * @param arr Piece** representing the board
 * @return bool
 */
bool Queen::isMoveLegal(QString squareName, Piece* pieceAtNewLocation, Piece** arr){
    if(isMovementLegal(squareName)){
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
    return false;
}

bool Queen::isMovementLegal(QString to){
    char currentColumn = currentPosition.at(0).toLatin1();
    char currentRow = currentPosition.at(1).toLatin1();

    char newColumn = to.at(0).toLatin1();
    char newRow = to.at(1).toLatin1();

    int rowDifference = newRow-currentRow;
    int colDifference = newColumn-currentColumn;

    int rowAbs = abs(rowDifference);
    int colAbs = abs(colDifference);

    bool straightMovement = (rowDifference == 0 || colDifference == 0);
    bool diagonallyMovement = (rowAbs == colAbs);

    return straightMovement || diagonallyMovement;
}

bool Queen::isMovementBlocked(QString to, Piece **arr){
    char currentColumn = currentPosition.at(0).toLatin1();
    char currentRow = currentPosition.at(1).toLatin1();

    char newColumn = to.at(0).toLatin1();
    char newRow = to.at(1).toLatin1();

    int rowDifference = newRow-currentRow;
    int colDifference = newColumn-currentColumn;

    int rowAbs = abs(rowDifference);
    int colAbs = abs(colDifference);

    bool straightMovement = (rowDifference == 0 || colDifference == 0);
    bool diagonallyMovement = (rowAbs == colAbs);
    if(straightMovement){
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
    }else if(diagonallyMovement){
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

