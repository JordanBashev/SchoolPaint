#include "shape.h"

Shape::Shape() : m_brush( BASE_BRUSH ), m_pen( BASE_PEN ), m_size( BASE_SIZE )
{
    setFlag( ItemIsMovable );
    setFlag( ItemIsSelectable );
}

void    Shape::changeFillColor(const QBrush& newBrush )
{
    m_brush      = newBrush;
}

void    Shape::changePenColor( const QPen& newPen )
{
    m_pen        = newPen;
}

void    Shape::changeSize( const double size )
{
    m_size       = size;
}

QRectF    Shape::boundingRect() const
{
    return QRectF( 0, 0, m_size, m_size );
}

void    Shape::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    QRectF    rect            = boundingRect();
    QRectF    Ellipse         = QRectF( 0, 0, m_size / 1.5, m_size );
    switch( type() )
    {
    case    int( Shapetype::RECTANGLE ):
        painter->setPen       ( m_pen );
        painter->setBrush     ( m_brush );
        painter->drawRect     ( rect );
        break;

    case    int( Shapetype::ELLIPSE ):
        painter->setPen       ( m_pen );
        painter->setBrush     ( m_brush );
        painter->drawEllipse  ( Ellipse );
        break;

    case    int( Shapetype::CIRCLE ):
        painter->setPen       ( m_pen );
        painter->setBrush     ( m_brush );
        painter->drawEllipse  ( rect );
        break;

    case    int( Shapetype::HEXAGON ):
    {
        QPolygon    Hexagon   = QPolygon( createHexagon() );
        painter->setPen       ( m_pen );
        painter->setBrush     ( m_brush );
        painter->drawPolygon  ( Hexagon );
        break;
    }

    case    int( Shapetype::STAR ):
    {
        QPolygon    Star      = QPolygon( createStar() );
        painter->setPen       ( m_pen );
        painter->setBrush     ( m_brush );
        painter->drawPolygon  ( Star );
        break;
    }

    default:
        qDebug() << "nt selected";
        break;
    }

}


QList<QPoint>    Shape::createHexagon()
{
    QList<QPoint>   HexagonPoints       =
    {
        { int( m_size / 2 ), 0 } ,
        { int( m_size ),     int( m_size / 4 ) } ,
        { int( m_size ),     int( m_size - m_size / 4 ) } ,
        { int( m_size / 2 ), int( m_size ) } ,
        { 0,                 int( m_size - m_size / 4 ) } ,
        { 0,                 int( m_size / 4 ) }
    };

    return HexagonPoints;
}

QList<QPoint>    Shape::createStar()
{
    QList<QPoint>   StarPoints          =
    {
        { 0,                   int( m_size / 2.2 ) } ,
        { int( m_size / 2.4 ), int( m_size / 2.2 ) } ,
        { int( m_size / 1.9 ), 0 } ,
        { int( m_size / 1.6 ), int( m_size / 2.2 ) } ,
        { int( m_size ),       int( m_size / 2.2 ) } ,
        { int( m_size / 1.4 ), int( m_size / 1.6 ) } ,
        { int( m_size / 1.2 ), int( m_size ) } ,
        { int( m_size / 1.9 ), int( m_size / 1.4 ) } ,
        { int( m_size * 0.2 ), int( m_size ) } ,
        { int( m_size / 2.8 ), int( m_size / 1.6 ) },
    };

    return StarPoints;
}

