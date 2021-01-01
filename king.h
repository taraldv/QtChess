#ifndef KING_H
#define KING_H
#include "piece.h"
#include "rook.h"

class King : public Piece
{
public:
    King(QString pos, enum Color _color, QString name);
    bool isMoveLegal(QString squareName, Piece* pieceAtNewLocation, Piece** arr);
private:
    bool isMovementLegal(QString to);
    bool isCastlingLegal(QString to, Piece** arr);
    bool hasMoved = false;
    bool isSquareSafe(QString square, Piece** arr);
};

#endif // KING_H
