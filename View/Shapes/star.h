#ifndef STAR_H
#define STAR_H

#include "shape.h"

class Star : public Shape
{
public:
    Star( const int size, const QPen &pen, const QBrush &brush , const QPointF& pos );
    virtual int    type() const override;
};

#endif // STAR_H
