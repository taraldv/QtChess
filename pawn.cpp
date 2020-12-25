#include "pawn.h"

Pawn::Pawn(QString _pos, enum Color _color, QString _name):Piece(_pos, _color,_name,'P')
{

}

bool Pawn::isMoveLegal(QString newPosition){
    return false;
}
