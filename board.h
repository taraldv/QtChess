#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <qqml.h>
#include <QVariantList>
#include <piece.h>
#include <bishop.h>
#include <king.h>
#include <knight.h>
#include <pawn.h>
#include <queen.h>
#include <rook.h>

class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(QObject *parent = nullptr);
    Q_INVOKABLE QVariantList getPiecePNGList();

signals:
    void boardChanged();

private:
    Piece* pieceArray[64];

};

#endif // BOARD_H
