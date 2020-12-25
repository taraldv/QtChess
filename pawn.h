#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(QString pos, enum Color _color, QString name);
    bool isMoveLegal(QString newPosisiton);
};

#endif // PAWN_H
