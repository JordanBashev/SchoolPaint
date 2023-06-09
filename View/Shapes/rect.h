#ifndef RECT_H
#define RECT_H

////////////////////////////////////////////////////////////////////////////////

#include "shape.h"

////////////////////////////////////////////////////////////////////////////////

class Rect : public Shape
{

public:
	Rect(	const int		size	= BASE_SIZE,
			const QPen		&pen	= BASE_PEN,
			const QBrush	&brush	= BASE_BRUSH,
			const QPointF&	pos		= QPointF() );
	virtual int		type() const override;
};

////////////////////////////////////////////////////////////////////////////////

#endif // RECT_H
