#ifndef RECT_H
#define RECT_H

#include "shape.h"

class Rect : public Shape
{

public:
    Rect( const int size, const QPen &pen, const QBrush &brush , const QPointF& pos );
    virtual int    type() const override;
};

#endif // RECT_H
