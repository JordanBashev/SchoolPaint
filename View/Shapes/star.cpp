#include "star.h"

Star::Star( const int size, const QPen &pen, const QBrush &brush, const QPointF &pos )
{
    m_size     = size;
    m_pen      = pen;
    m_brush    = brush;
    setPos     ( pos.x() - 25, pos.y() - 25 );
}

int     Star::type() const
{
    return int( Shapetype::STAR );
}
