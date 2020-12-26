#ifndef BOARD_H
#define BOARD_H

#include <QObject>
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
    Q_INVOKABLE bool isMoveLegal(QString from, QString to);
    Q_INVOKABLE void movePiece(QString from, QString to);
    Q_INVOKABLE void restart();
    Q_INVOKABLE QString getWhichColorCanMove();
    Q_INVOKABLE bool doesPieceBelongToPlayer(QString square);
    void toggleWhichColorCanMove();
private:
    bool isChecked;
    bool isMated;
    Piece* pieceArray[64];
    Color whichColorCanMove = WHITE;
    bool isSquareFree(QString square);
    bool isHostile(QString from, QString to);
    bool isMovementLegal(QString from, QString to);
    bool isTakeLegal(QString from, QString to);
    bool isCheck(QString square);
    bool isMate(QString square);
    //TODO: rokkade og repeterende trekk
};

#endif // BOARD_H
