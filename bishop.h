#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"

class Bishop : public Piece
{
public:
    Bishop(QString pos, enum Color _color, QString name);
    bool isMoveLegal(QString squareName, Piece* pieceAtNewLocation, Piece** arr);
private:
    bool isMovementBlocked(QString to, Piece** arr);
    bool isMovementLegal(QString to);
};

#endif // BISHOP_H
