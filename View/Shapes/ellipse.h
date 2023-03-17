#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape
{

public:
    Ellipse( const int size, const QPen &pen, const QBrush &brush , const QPointF& pos );
    virtual int    type() const override;
};

#endif // ELLIPSE_H
