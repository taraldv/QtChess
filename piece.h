#ifndef PIECE_H
#define PIECE_H

#include <QObject>
enum Color {WHITE,BLACK};
class Piece : public QObject
{
    Q_OBJECT
public:
    Piece(QString pos, enum Color _color, QString name, char _type, QObject *parent = nullptr);
    virtual bool isMoveLegal(QString) = 0;
    char getType() const;
    Color getColor() const;
    QString getName() const;
    QString getCurrentPosition() const;
    void setCurrentPosition(const QString &value);

private:
    char type;
    Color color;
    QString pngName;
    QString currentPosition;

signals:

};

#endif // PIECE_H
