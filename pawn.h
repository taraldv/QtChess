#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(QString pos, enum Color _color, QString name);
    bool isMoveLegal(QString squareName, Piece* pieceAtNewLocation, Piece** arr);
private:
    bool pawnForwardOne(QString newPos);
    bool pawnForwardTwo(QString newPos);
    bool pawnTake(QString newPos);
};

#endif // PAWN_H
