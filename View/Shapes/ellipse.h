#ifndef ELLIPSE_H
#define ELLIPSE_H

////////////////////////////////////////////////////////////////////////////////

#include "shape.h"

////////////////////////////////////////////////////////////////////////////////

class Ellipse : public Shape
{

public:
	Ellipse(	const	int			size	= BASE_SIZE,
				const	QPen		&pen	= BASE_PEN,
				const	QBrush		&brush	= BASE_BRUSH,
				const	QPointF&	pos		= QPointF() );
	virtual int		type() const override;
};

////////////////////////////////////////////////////////////////////////////////

#endif // ELLIPSE_H
