#include "knight.h"

Knight::Knight(QString _pos, enum Color _color, QString _name):Piece(_pos, _color,_name,'R')
{

}

bool Knight::isMoveLegal(QString newPosition){
    return false;
}
