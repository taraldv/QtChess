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
