#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"

class Queen : public Piece
{
public:
    Queen(QString pos, enum Color _color, QString name);
    bool isMoveLegal(QString squareName, Piece* pieceAtNewLocation, Piece** arr);
private:
    bool isMovementLegal(QString to);
    bool isMovementBlocked(QString to, Piece** arr);
};

#endif // QUEEN_H
