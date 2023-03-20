#ifndef CANVAS_H
#define CANVAS_H

////////////////////////////////////////////////////////////////////////////////

#include <QGraphicsSceneEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QColorDialog>
#include <QInputDialog>
#include <QDialog>

////////////////////////////////////////////////////////////////////////////////

#include "Shapes/includeShapes.h"
#include "CustomDialogs/customslider.h"

////////////////////////////////////////////////////////////////////////////////

const QColor	DEFAULT_FILL_COLOR	= Qt::white;
const QColor	DEFAULT_PEN_COLOR	= Qt::black;
const double	DEFAULT_SIZE		= 60.0;

////////////////////////////////////////////////////////////////////////////////

class Canvas : public QGraphicsScene
{
	Q_OBJECT

private:
	bool					m_isDrawingRect		= false;
	bool					m_isDrawingEllipse	= false;
	bool					m_isDrawingCircle	= false;
	bool					m_isDrawingStar		= false;
	bool					m_isDrawingHexagon	= false;
	bool					m_isGroupSelected	= false;
	QColor					m_fillColor			= Qt::white;
	QColor					m_penColor			= Qt::black;
	double					m_size				= 60.0;
	int						m_counter			= 0;
	QGraphicsItemGroup*		m_group				= nullptr;
	QPainterPath*			m_selectionPath		= nullptr;
	QGraphicsPathItem*		m_deletePath		= nullptr;
	CustomSlider*			slider				= nullptr;
	QPointF					m_itemSelect;
	QPointF					m_selectionTopLeft;

public:
	Canvas( QObject* parent = nullptr );
	~Canvas();
	void	drawRectangle();
	void	drawEllipse();
	void	drawCircle();
	void	drawHexagon();
	void	drawStar();
	void	select();
	void	selectGroup();
	bool	isGroupSelected();
	void	setFillColor( const QColor& fillColor = DEFAULT_FILL_COLOR );
	void	setPenColor( const QColor& penColor = DEFAULT_PEN_COLOR);
	void	setSize( const double size = DEFAULT_SIZE );
	void	changeFillColor( const QColor& fillColor );
	void	changePenColor( const QColor& penColor );
	void	changeSize( const double size );
	void	rotateObject( QWidget* parent );

private:
	virtual void	mousePressEvent( QGraphicsSceneMouseEvent* event ) override;
	virtual void	mouseReleaseEvent
					( QGraphicsSceneMouseEvent* event ) override;
	void	paintRect( const QPointF& pos,
							   const QColor& fillColor,
							   const QColor& penColor,
							   const int size );
	void	paintEllipse( const QPointF& pos,
								  const QColor& fillColor,
								  const QColor& penColor,
								  const int size );
	void	paintCircle( const QPointF& pos,
								 const QColor& fillColor,
								 const QColor& penColor,
								 const int size );
	void	paintHexagon( const QPointF& pos,
								  const QColor& fillColor,
								  const QColor& penColor,
								  const int size );
	void	paintStar( const QPointF& pos,
							   const QColor& fillColor,
							   const QColor& penColor,
							   const int size );
	Shape*	getItem( const QPointF& pos );
};

////////////////////////////////////////////////////////////////////////////////

#endif // CANVAS_H
