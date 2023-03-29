////////////////////////////////////////////////////////////////////////////////

#include "shape.h"

////////////////////////////////////////////////////////////////////////////////

const int	TWO				= 2;
const int	FOUR			= 4;
const double	TWO_EIGHT	= 2.8;
const double	TWO_FOUR	= 2.4;
const double	TWO_TWO		= 2.2;
const double	ONE_NINE	= 1.9;
const double	ONE_FIVE	= 1.5;
const double	ONE_SIX		= 1.6;
const double	ONE_FOUR	= 1.4;
const double	ONE_TWO		= 1.2;
const double	ZERO_TWO	= 0.2;

////////////////////////////////////////////////////////////////////////////////

Shape::Shape() : m_brush( BASE_BRUSH ), m_pen( BASE_PEN ), m_size( BASE_SIZE )
{
	setFlag( ItemIsMovable );
	setFlag( ItemIsSelectable );
}

////////////////////////////////////////////////////////////////////////////////

void	Shape::changeFillColor( const QBrush& newBrush )
{
	m_brush		= newBrush;
}

////////////////////////////////////////////////////////////////////////////////

void	Shape::changePenColor( const QPen& newPen )
{
	m_pen		= newPen;
}

////////////////////////////////////////////////////////////////////////////////

void	Shape::changeSize( const double size )
{
	m_size		= size;
}

////////////////////////////////////////////////////////////////////////////////

QPointF	Shape::getBoundingRectCenter()
{
	return	boundingRect().center();
}

////////////////////////////////////////////////////////////////////////////////

QBrush	Shape::getBrush() const
{
	return m_brush;
}

////////////////////////////////////////////////////////////////////////////////

QPen	Shape::getPen() const
{
	return m_pen;
}

////////////////////////////////////////////////////////////////////////////////

double	Shape::getSize() const
{
	return m_size;
}

////////////////////////////////////////////////////////////////////////////////

QRectF	Shape::boundingRect() const
{
	return QRectF( 0, 0, m_size, m_size );
}

////////////////////////////////////////////////////////////////////////////////

void	Shape::paint(	QPainter*	painter,
						const QStyleOptionGraphicsItem*	option,
						QWidget*	widget )
{
	QRectF	rect		= boundingRect();
	QRectF	Ellipse		= QRectF( 0, 0, m_size / ONE_FIVE, m_size );
	switch( type() )
	{
	case	int( Shapetype::RECTANGLE ):
		painter->setPen( m_pen );
		painter->setBrush( m_brush );
		painter->drawRect( rect );
		break;

	case	int( Shapetype::ELLIPSE ):
		painter->setPen( m_pen );
		painter->setBrush( m_brush );
		painter->drawEllipse( Ellipse );
		break;

	case	int( Shapetype::CIRCLE ):
		painter->setPen( m_pen );
		painter->setBrush( m_brush );
		painter->drawEllipse( rect );
		break;

	case	int( Shapetype::HEXAGON ):
	{
		QPolygon	Hexagon		= QPolygon( createHexagon() );
		painter->setPen( m_pen );
		painter->setBrush( m_brush );
		painter->drawPolygon( Hexagon );
		break;
	}

	case	int( Shapetype::STAR ):
	{
		QPolygon	Star		= QPolygon( createStar() );
		painter->setPen( m_pen );
		painter->setBrush( m_brush );
		painter->drawPolygon( Star );
		break;
	}

	default:
		qDebug() << "nt selected";
		break;
	}

}

////////////////////////////////////////////////////////////////////////////////

QList<	QPoint	>	Shape::createHexagon()
{
	QList<	QPoint	>	HexagonPoints	=
	{
		{ int( m_size / TWO ), 0 } ,
		{ int( m_size ),		int( m_size / FOUR ) } ,
		{ int( m_size ),		int( m_size - m_size / FOUR ) } ,
		{ int( m_size / TWO ),	int( m_size ) } ,
		{ 0,					int( m_size - m_size / FOUR ) } ,
		{ 0,					int( m_size / FOUR ) }
	};

	return HexagonPoints;
}

////////////////////////////////////////////////////////////////////////////////

QList<	QPoint	>	Shape::createStar()
{
	QList<	QPoint	>	StarPoints		=
	{
		{ 0,						int( m_size / TWO_TWO ) } ,
		{ int( m_size / TWO_FOUR ),	int( m_size / TWO_TWO ) } ,
		{ int( m_size / ONE_NINE ),	0 } ,
		{ int( m_size / ONE_SIX ),	int( m_size / TWO_TWO ) } ,
		{ int( m_size ),			int( m_size / TWO_TWO ) } ,
		{ int( m_size / ONE_FOUR ),	int( m_size / ONE_SIX ) } ,
		{ int( m_size / ONE_TWO ),	int( m_size ) } ,
		{ int( m_size / ONE_NINE ),	int( m_size / ONE_FOUR ) } ,
		{ int( m_size * ZERO_TWO ),	int( m_size ) } ,
		{ int( m_size / TWO_EIGHT ),int( m_size / ONE_SIX ) },
	};

	return StarPoints;
}

////////////////////////////////////////////////////////////////////////////////
