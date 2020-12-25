#include "king.h"

King::King(QString _pos, enum Color _color, QString _name):Piece(_pos, _color,_name,'R')
{

}

bool King::isMoveLegal(QString newPosition){
    return false;
}
