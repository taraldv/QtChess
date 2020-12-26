#ifndef KING_H
#define KING_H
#include "piece.h"

class King : public Piece
{
public:
    King(QString pos, enum Color _color, QString name);
    bool isMoveLegal(QString squareName, Piece* pieceAtNewLocation, Piece** arr);
private:
    bool isMovementLegal(QString to);
};

#endif // KING_H