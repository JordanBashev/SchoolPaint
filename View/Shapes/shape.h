#ifndef SHAPE_H
#define SHAPE_H

#include <QGraphicsItem>
#include <QColor>
#include <QBrush>
#include <QPen>
#include <QPainter>

const QColor    BASE_BRUSH       = Qt::white;
const QColor    BASE_PEN         = Qt::black;
const double    BASE_SIZE        = 60.0;

enum class Shapetype : int
{
    RECTANGLE = QGraphicsItem::UserType + 1,
    ELLIPSE,
    CIRCLE,
    HEXAGON,
    STAR
};

class Shape : public QGraphicsItem
{
protected:
    double     m_size;
    QBrush     m_brush;
    QPen       m_pen;

public:
    QString    m_name;
    QString    m_tag;

public:
    Shape();
    void    changeFillColor( const QBrush& newBrush );
    void    changePenColor( const QPen& newPen );
    void    changeSize( const double size );

protected:
    virtual QRectF    boundingRect() const override;
    virtual void    paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) override;

private:
    QList<QPoint>    createHexagon();
    QList<QPoint>    createStar();
};

#endif // SHAPE_H
