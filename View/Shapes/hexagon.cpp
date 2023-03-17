#include "hexagon.h"

Hexagon::Hexagon( const int size, const QPen &pen, const QBrush &brush, const QPointF &pos )
{
    m_size     = size;
    m_pen      = pen;
    m_brush    = brush;
    setPos     ( pos.x() - 25, pos.y() - 25 );
}

int    Hexagon::type() const
{
    return int( Shapetype::HEXAGON );
}
