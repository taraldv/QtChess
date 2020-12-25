#include "rook.h"

Rook::Rook(QString _pos, enum Color _color, QString _name):Piece(_pos, _color,_name,'R')
{

}

bool Rook::isMoveLegal(QString newPosition){
    return false;
}
