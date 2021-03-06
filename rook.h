#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Rook : public Piece
{
public:
    Rook(QString pos, enum Color _color, QString name);
    bool isMoveLegal(QString squareName, Piece* pieceAtNewLocation, Piece** arr);
    bool getHasMoved() const;

private:
    bool isMovementBlocked(QString to, Piece** arr);
    bool isMovementLegal(QString to);
    bool hasMoved = false;
};

#endif // ROOK_H
