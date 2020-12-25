#include "bishop.h"

Bishop::Bishop(QString _pos, enum Color _color, QString _name):Piece(_pos, _color,_name,'R')
{

}

bool Bishop::isMoveLegal(QString newPosition){
    return false;
}
