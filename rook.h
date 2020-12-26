#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Rook : public Piece
{
public:
    Rook(QString pos, enum Color _color, QString name);
    bool isMoveLegal(QString squareName, Piece* pieceAtNewLocation, Piece** arr);
private:
    bool isMovementBlocked(QString to, Piece** arr);
    bool isMovementLegal(QString to);
};

#endif // ROOK_H
