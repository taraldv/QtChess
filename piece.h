#ifndef PIECE_H
#define PIECE_H
#include <exception>
#include <QDebug>
#include <QObject>
enum Color {WHITE,BLACK};
class Piece : public QObject
{
    Q_OBJECT
public:
    Piece(QString pos, enum Color _color, QString name, char _type, QObject *parent = nullptr);
    virtual bool isMoveLegal(QString squareName, Piece* pieceAtNewLocation, Piece** arr) = 0;
    char getType() const;
    Color getColor() const;
    QString getName() const;
    QString getCurrentPosition() const;
    void setCurrentPosition(const QString &value);
    static int convertMoveToIndex(QString move);
    static QString convertIndexToMove(int index);
protected:
    char type;
    Color color;
    QString pngName;
    QString currentPosition;

signals:

};

#endif // PIECE_H
