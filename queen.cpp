#include "queen.h"

Queen::Queen(QString _pos, enum Color _color, QString _name):Piece(_pos, _color,_name,'R')
{

}

bool Queen::isMoveLegal(QString newPosition){
    return false;
}

