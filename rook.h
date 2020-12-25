#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Rook : public Piece
{
public:
    Rook(QString pos, enum Color _color, QString name);
    bool isMoveLegal(QString newPosisiton);
};

#endif // ROOK_H
