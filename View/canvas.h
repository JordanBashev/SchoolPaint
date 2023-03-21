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
#include "CustomDialogs/opacityslider.h"

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
	bool					m_isRotating		= false;
	bool					m_isChangingOpacity	= false;
	QColor					m_fillColor			= Qt::white;
	QColor					m_penColor			= Qt::black;
	double					m_size				= 60.0;
	int						m_counter			= 0;
	QGraphicsItemGroup*		m_group				= nullptr;
	QPainterPath*			m_selectionPath		= nullptr;
	QGraphicsPathItem*		m_deletePath		= nullptr;
	QDialog*				m_slider			= nullptr;
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
	void	changeFillColor( const QColor& fillColor = Qt::white );
	void	changePenColor( const QColor& penColor = Qt::black );
	void	changeSize( const double size = DEFAULT_SIZE );
	void	changeOpacity ( QWidget* parent = nullptr );
	void	rotateObject( QWidget* parent = nullptr );
	void	eraseItems();

private:
	virtual void	mousePressEvent
					( QGraphicsSceneMouseEvent* event ) override;
	virtual void	mouseReleaseEvent
					( QGraphicsSceneMouseEvent* event ) override;

	void	paintRect(	const QPointF&	pos			= QPointF(),
						const QColor&	fillColor	= DEFAULT_FILL_COLOR,
						const QColor&	penColor	= DEFAULT_PEN_COLOR,
						const int		size		= DEFAULT_SIZE );

	void	paintEllipse(	const QPointF&	pos			= QPointF(),
							const QColor&	fillColor	= DEFAULT_FILL_COLOR,
							const QColor&	penColor	= DEFAULT_PEN_COLOR,
							const int		size		= DEFAULT_SIZE );

	void	paintCircle(	const QPointF&	pos			= QPointF(),
							const QColor&	fillColor	= DEFAULT_FILL_COLOR,
							const QColor&	penColor	= DEFAULT_PEN_COLOR,
							const int		size		= DEFAULT_SIZE );

	void	paintHexagon(	const QPointF&	pos			= QPointF(),
							const QColor&	fillColor	= DEFAULT_FILL_COLOR,
							const QColor&	penColor	= DEFAULT_PEN_COLOR,
							const int		size		= DEFAULT_SIZE );

	void	paintStar(	const QPointF&	pos			= QPointF(),
						const QColor&	fillColor	= DEFAULT_FILL_COLOR,
						const QColor&	penColor	= DEFAULT_PEN_COLOR,
						const int		size		= DEFAULT_SIZE );

	Shape*	getItem( const QPointF& pos = QPointF() );
};

////////////////////////////////////////////////////////////////////////////////

#endif // CANVAS_H
