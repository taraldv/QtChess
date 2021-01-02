#ifndef PAWN_H
#define PAWN_H
#include "piece.h"
#include "queen.h"

class Pawn : public Piece
{
public:
    Pawn(QString pos, enum Color _color, QString name);
    bool isMoveLegal(QString squareName, Piece* pieceAtNewLocation, Piece** arr);
    bool getRecentlyMovedTwice() const;
    bool hasReachedEndOfBoard();
private:
    bool recentlyMovedTwice = false;
    bool pawnForwardOne(QString newPos);
    bool pawnForwardTwo(QString newPos);
    bool enPassantTake(Piece** arr, QString newPos);
    bool pawnTake(QString newPos);
    void convertToQueen();
};

#endif // PAWN_H
