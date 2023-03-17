#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape
{

public:
    Circle( const int size, const QPen &pen, const QBrush &brush , const QPointF& pos );
    virtual int    type() const override;
};

#endif // CIRCLE_H
