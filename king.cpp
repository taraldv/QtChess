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
    if(isMovementLegal(squareName)){
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
    if(isCastlingLegal(squareName, arr)){
        hasMoved = true;
        return true;
    }
    return false;
}
/**
 * @brief King::isCastlingLegal
 * Castling is done by moving the King two squares left or right.
 * The King or the Rook should not have moved previously.
 * There should not be any blocking pieces
 * This function will move the Rook, since the Board logic can only
 * move 1 piece.
 * @param to QString
 * @param arr Piece array
 * @return bool
 */
bool King::isCastlingLegal(QString to, Piece** arr){
    if(!hasMoved){
        char currentColumn = currentPosition.at(0).toLatin1();
        char currentRow = currentPosition.at(1).toLatin1();

        char newColumn = to.at(0).toLatin1();

        int colDifference = newColumn-currentColumn;
        QString rookSquare = "";
        if(color == WHITE){
            if(colDifference > 0){
                rookSquare = "A1";
                //Rook at A1
            } else {
                rookSquare = "H1";
                //Rook at H1
            }

        } else if(color == BLACK){
            if(colDifference > 0){
                rookSquare = "A8";
                //Rook at A8
            } else {
                rookSquare = "H8";
                //Rook at H8
            }
        }
        char rookColumn = rookSquare.at(0).toLatin1();
        int rookIndex = Piece::convertMoveToIndex(rookSquare);
        Piece* rookPiece = arr[rookIndex];
        //If there is no Rook
        if(!rookPiece){
            return false;
        }
        //If the Rook has previously moved
        if(((Rook*)rookPiece)->getHasMoved()){
            return false;
        }
        int rookAndKingDifference = abs(currentColumn-rookColumn);
        //Checks if any pieces exist between Rook and King
        for(int i=1;i<rookAndKingDifference;i++){
            QString tempSquare = "";
            //If the colDifference is a positive number, we should check between column E and H
            if(colDifference > 0){
                tempSquare += currentColumn+i;
            } else {
                tempSquare += currentColumn-i;
            }
            tempSquare += currentRow;
            if(arr[Piece::convertMoveToIndex(tempSquare)]){
                return false;
            }
        }
        //At this point the move should be legal
        char newRookColumn = rookColumn;
        if(newColumn == 'C'){
            newRookColumn = 'D';
        } else if(newColumn == 'G'){
            newRookColumn = 'F';
        }
        QString newRookSquare = "";
        newRookSquare += newRookColumn;
        newRookSquare += currentRow;
        arr[Piece::convertMoveToIndex(newRookSquare)] = rookPiece;
        arr[rookIndex] = nullptr;

    }
    return false;
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
