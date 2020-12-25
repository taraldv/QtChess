#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

class Knight : public Piece
{
public:
    Knight(QString pos, enum Color _color, QString name);
    bool isMoveLegal(QString newPosisiton);
};

#endif // KNIGHT_H
