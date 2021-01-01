#include "piece.h"



Piece::Piece(QString _pos, enum Color _color, QString _name, char _type, QObject *parent) : QObject(parent)
{
    currentPosition = _pos;
    pngName = _name;
    type = _type;
    color = _color;
}

char Piece::getType() const
{
    return type;
}

Color Piece::getColor() const
{
    return color;
}

QString Piece::getName() const
{
    return pngName;
}

QString Piece::getCurrentPosition() const
{
    return currentPosition;
}

void Piece::setCurrentPosition(const QString &value)
{
    currentPosition = value;
}

int Piece::convertMoveToIndex(QString move){
    char letter = move.at(0).toLatin1();
    char number = move.at(1).toLatin1();
    int col = (int)letter - 65;
    int row = (int)number - 49;
    int arrRow = 7-row;
    int index = arrRow*8+col;
    return index;
}

QString Piece::convertIndexToMove(int index){
    char col = (index % 8)+65;
    char row = (7-(index / 8))+49;
    QString output = "";
    output += col;
    output += row;
    return output;
}
