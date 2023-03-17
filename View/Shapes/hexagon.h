#ifndef HEXAGON_H
#define HEXAGON_H

#include "shape.h"

class Hexagon : public Shape
{

public:
    Hexagon( const int size, const QPen &pen, const QBrush &brush , const QPointF& pos );
    virtual int    type() const override;
};

#endif // HEXAGON_H
