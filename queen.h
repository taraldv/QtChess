#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"

class Queen : public Piece
{
public:
    Queen(QString pos, enum Color _color, QString name);
    bool isMoveLegal(QString newPosisiton);
};

#endif // QUEEN_H
