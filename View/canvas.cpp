////////////////////////////////////////////////////////////////////////////////

#include <QDebug>

////////////////////////////////////////////////////////////////////////////////

#include "canvas.h"

////////////////////////////////////////////////////////////////////////////////

Canvas::Canvas( QObject* parent )
	: QGraphicsScene( parent )
{ }

////////////////////////////////////////////////////////////////////////////////

Canvas::~Canvas()
{
	delete	m_group;
	delete	m_deletePath;
	delete	m_selectionPath;
	delete	m_slider;
	delete	m_item;
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::mousePressEvent( QGraphicsSceneMouseEvent*	event )
{

	if( event->button() == Qt::LeftButton && m_isDrawingRect )
		paintRect( event->scenePos(), m_fillColor, m_penColor, m_size );

	if( event->button() == Qt::LeftButton && m_isDrawingEllipse )
		paintEllipse( event->scenePos(), m_fillColor, m_penColor, m_size );

	if( event->button() == Qt::LeftButton && m_isDrawingCircle )
		paintCircle( event->scenePos(), m_fillColor, m_penColor, m_size );

	if( event->button() == Qt::LeftButton && m_isDrawingHexagon )
		paintHexagon( event->scenePos(), m_fillColor, m_penColor, m_size );

	if( event->button() == Qt::LeftButton && m_isDrawingStar )
		paintStar( event->scenePos(), m_fillColor, m_penColor, m_size );

	if( event->button() == Qt::LeftButton )
		m_itemSelect		= event->scenePos();

	if( event->button() == Qt::RightButton && m_isGroupSelected )
	{
		if( m_deletePath != nullptr )
		{
			removeItem( m_deletePath );
			delete m_deletePath;
			m_deletePath	= nullptr;
		}

		if( m_group != nullptr )
		{
			destroyItemGroup( m_group );
			m_group			= nullptr;
		}

		m_selectionPath		= new QPainterPath();
		m_selectionTopLeft	= event->scenePos();
	}

	QGraphicsScene::mousePressEvent( event );
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::mouseReleaseEvent( QGraphicsSceneMouseEvent*	event )
{
	auto	allItems	= selectedItems();

	if( event->button() == Qt::RightButton && m_isGroupSelected )
	{
		m_selectionPath->addRect
				( QRectF( m_selectionTopLeft, event->scenePos() ) );
		// creating path with (0 ,0) in a double click will crash the app. think of potential fix
		m_deletePath	= addPath( *m_selectionPath );
		m_deletePath->setFlag( m_deletePath->ItemIsMovable );
		m_deletePath->setFlag( m_deletePath->ItemIsSelectable );
		setSelectionArea( *m_selectionPath );

		if ( selectedItems().count() > 0 )
		{
			m_group		= createItemGroup( allItems );
			m_group->setFlag( m_group->ItemIsMovable );// look at selectable may reduce code alot

			m_selectionTopLeft	= QPointF( 0, 0 );
			allItems.clear();
		}

		delete	m_selectionPath;
		m_selectionPath		= nullptr;
	}

	if( event->button() == Qt::LeftButton && m_deletePath != nullptr )
	{
		if( !m_deletePath->isSelected() )
		{
			removeItem( m_deletePath );
			delete	m_deletePath;
			m_deletePath	= nullptr;
		}

		allItems.clear();
	}

	QGraphicsScene::mouseReleaseEvent( event );
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::keyPressEvent( QKeyEvent* event )
{
	if( event->key() == Qt::Key_C && event->modifiers() == Qt::MetaModifier )
	{
		m_item		= getItem( m_itemSelect );
	}

	if( event->key() == Qt::Key_V && event->modifiers() == Qt::MetaModifier )
	{
		if( m_group != nullptr )
		{
			for( auto item : selectedItems() )
				if( Shape*	toShape = dynamic_cast< Shape* >( item ) )
					pasteItems( toShape );

			return;
		}

		if( m_item != nullptr )
			pasteItems( m_item );
	}

	QGraphicsScene::keyPressEvent( event );
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::paintRect(	const QPointF&		pos,
							const QColor&		fillColor,
							const QColor&		penColor,
							const int			size ,
							const QString		name ,
							const QTransform	rotation )
{
	QBrush*		brush	= new QBrush( fillColor );
	QPen*		pen		= new QPen( penColor );
	Shape*		item	= new Rect( size, *pen, *brush, pos );
	item->m_tag.append( "Rect" );
	item->m_name.append( name );
	item->setTransform( rotation );
	addItem( item );
	delete	brush;
	delete	pen;
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::paintEllipse(	const QPointF&		pos,
								const QColor&		fillColor,
								const QColor&		penColor,
								const int			size ,
								const QString		name ,
								const QTransform	rotation )
{
	QBrush*		brush	= new QBrush( fillColor );
	QPen*		pen		= new QPen( penColor );
	Shape*		item	= new Ellipse( size, *pen, *brush, pos );
	item->m_tag.append( "Ellipse" );
	item->m_name.append( name );
	item->setTransform( rotation );
	addItem( item );
	delete	brush;
	delete	pen;
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::paintCircle(	const QPointF&		pos,
								const QColor&		fillColor,
								const QColor&		penColor,
								const int			size,
								const QString		name,
								const QTransform	rotation )
{
	QBrush*		brush	= new QBrush( fillColor );
	QPen*		pen		= new QPen( penColor );
	Shape*		item	= new Circle( size, *pen, *brush, pos );
	item->m_tag.append( "Circle" );
	item->m_name.append( name );
	item->setTransform( rotation );
	addItem( item );
	delete	brush;
	delete	pen;
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::paintHexagon(	const QPointF&		pos,
								const QColor&		fillColor,
								const QColor&		penColor,
								const int			size ,
								const QString		name,
								const QTransform	rotation )
{
	QBrush*		brush	= new QBrush( fillColor );
	QPen*		pen		= new QPen( penColor );
	Shape*		item	= new Hexagon( size, *pen, *brush, pos );
	item->m_tag.append( "Hexagon" );
	item->m_name.append( name );
	item->setTransform( rotation );
	addItem( item);
	delete	brush;
	delete	pen;
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::paintStar(	const QPointF&		pos,
							const QColor&		fillColor,
							const QColor&		penColor,
							const int			size,
							const QString		name,
							const QTransform	rotation )
{
	QBrush*		brush	= new QBrush( fillColor );
	QPen*		pen		= new QPen( penColor );
	Shape*		item	= new Star( size, *pen, *brush, pos );
	item->m_tag.append( "Star" );
	item->m_name.append( name );
	item->setTransform( rotation );
	addItem( item );
	delete	brush;
	delete	pen;
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::pasteItems( Shape* item )
{
	switch( item->type() )
	{
	case int( Shapetype::RECTANGLE ):
		paintRect(	item->scenePos(), item->getBrush().color(),
					item->getPen().color(),
					item->getSize() );
		break;
	case int( Shapetype::ELLIPSE ):
		paintEllipse(	item->scenePos(), item->getBrush().color(),
						item->getPen().color(),
						item->getSize() );
		break;
	case int( Shapetype::CIRCLE ):
		paintCircle(	item->scenePos(), item->getBrush().color(),
						item->getPen().color(),
						item->getSize() );
		break;
	case int( Shapetype::HEXAGON ):
		paintHexagon(	item->scenePos(), item->getBrush().color(),
						item->getPen().color(),
						item->getSize() );
		break;
	case int( Shapetype::STAR ):
		paintStar(	item->scenePos(), item->getBrush().color(),
					item->getPen().color(),
					item->getSize() );
		break;
	default:
		qDebug() << "Nothing Selected";
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////

Shape*	Canvas::getItem( const QPointF& pos )
{
	QTransform	transform;
	QGraphicsItem*	selectedItem	=	itemAt( pos, transform );
	return static_cast< Shape* >( selectedItem );
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::changeFillColor( const QColor& fillColor )
{
	QBrush	newBrush( fillColor );

	if( !selectedItems().isEmpty() )
	{
		for( auto	item : selectedItems() )
			if( Shape*	toShape = dynamic_cast< Shape* >( item ) )
				toShape->changeFillColor( newBrush );

		return;
	}

	Shape*	item	=	getItem( m_itemSelect );
	if( item != nullptr )
		item->changeFillColor( newBrush );
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::changePenColor( const QColor& penColor )
{
	QPen	newPen( penColor );

	if( !selectedItems().isEmpty() )
	{
		for( auto	item : selectedItems() )
			if( Shape*	toShape = dynamic_cast< Shape* >( item ) )
				toShape->changePenColor( newPen );
		return;
	}

	Shape*	item	=	getItem( m_itemSelect );
	if( item != nullptr )
		item->changePenColor( newPen );

}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::changeSize( const double size )
{
	if( !selectedItems().isEmpty() )
	{
		for( auto	item : selectedItems() )
			if( Shape*	toShape = dynamic_cast< Shape* >( item ) )
				toShape->changeSize( size );

		return;
	}

	Shape*	item	=	getItem( m_itemSelect );
	if( item != nullptr )
		item->changeSize( size );
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::changeOpacity( QWidget* parent )
{
	if( !selectedItems().isEmpty() )
	{
		m_slider	=	new OpacitySlider( parent, selectedItems() );
		return;
	}

	Shape*	item	=	getItem( m_itemSelect );
	if( item != nullptr )
		m_slider	=	new OpacitySlider( parent, item );
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::rotateObject( QWidget* parent )
{
	if( !selectedItems().isEmpty() )
	{
		m_slider	=	new CustomSlider( parent, selectedItems() );
		return;
	}

	Shape*	item	=	getItem( m_itemSelect );
	if( item != nullptr )
		m_slider	=	new CustomSlider( parent, item );
}

////////////////////////////////////////////////////////////////////////////////

void Canvas::loadItems(	const QBrush&		brush, const	QPen& pen,
						const double		size, const		QString& name,
						const int			type , const	QPointF& scenePos,
						const QTransform	rotation )
{
	switch( type )
	{
	case int( Shapetype::RECTANGLE ):
		paintRect(	scenePos, brush.color(),
					pen.color(),
					size,
					name,
					rotation );
		break;
	case int( Shapetype::ELLIPSE ):
		paintEllipse(	scenePos, brush.color(),
						pen.color(),
						size,
						name,
						rotation );
		break;
	case int( Shapetype::CIRCLE ):
		paintCircle(	scenePos, brush.color(),
						pen.color(),
						size,
						name,
						rotation );
		break;
	case int( Shapetype::HEXAGON ):
		paintHexagon(	scenePos, brush.color(),
						pen.color(),
						size,
						name,
						rotation );
		break;
	case int( Shapetype::STAR ):
		paintStar(	scenePos, brush.color(),
					pen.color(),
					size,
					name,
					rotation );
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////

void	 Canvas::eraseItems()
{
	if( !selectedItems().isEmpty() )
	{
		for( auto	item : selectedItems() )
		{
			if( Shape*	toShape = dynamic_cast< Shape* >( item ) )
			{
				removeItem( toShape );
				delete toShape;
			}
		}

		return;
	}

	Shape*	item	=	getItem( m_itemSelect );
	if( item != nullptr )
	{
		removeItem( item );
		delete item;
	}
}

////////////////////////////////////////////////////////////////////////////////

void	 Canvas::displayName()
{
	Shape*	item	=	getItem( m_itemSelect );
	if( item != nullptr )
	{
		QMessageBox msgBox;
		msgBox.setText( item->m_name );
		msgBox.exec();
	}
}

////////////////////////////////////////////////////////////////////////////////

bool	Canvas::isGroupSelected()
{
	return	m_isGroupSelected;
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::itemName( const QString& name )
{
	Shape*	item = getItem( m_itemSelect );
	if( item != nullptr )
	{
		item->m_name = name;
	}
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::drawRectangle()
{
	m_isDrawingRect		= true;
	m_isDrawingEllipse	= false;
	m_isDrawingCircle	= false;
	m_isDrawingHexagon	= false;
	m_isDrawingStar		= false;
	m_isGroupSelected	= false;
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::drawEllipse()
{
	m_isDrawingRect		= false;
	m_isDrawingEllipse	= true;
	m_isDrawingCircle	= false;
	m_isDrawingHexagon	= false;
	m_isDrawingStar		= false;
	m_isGroupSelected	= false;
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::drawCircle()
{
	m_isDrawingRect		= false;
	m_isDrawingEllipse	= false;
	m_isDrawingCircle	= true;
	m_isDrawingHexagon	= false;
	m_isDrawingStar		= false;
	m_isGroupSelected	= false;
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::drawHexagon()
{
	m_isDrawingRect		= false;
	m_isDrawingEllipse	= false;
	m_isDrawingCircle	= false;
	m_isDrawingHexagon	= true;
	m_isDrawingStar		= false;
	m_isGroupSelected	= false;
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::drawStar()
{
	m_isDrawingRect		= false;
	m_isDrawingEllipse	= false;
	m_isDrawingCircle	= false;
	m_isDrawingHexagon	= false;
	m_isDrawingStar		= true;
	m_isGroupSelected	= false;
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::select()
{
	m_isDrawingRect		= false;
	m_isDrawingEllipse	= false;
	m_isDrawingCircle	= false;
	m_isDrawingHexagon	= false;
	m_isDrawingStar		= false;
	m_isGroupSelected	= false;
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::selectGroup()
{
	m_isDrawingRect		= false;
	m_isDrawingEllipse	= false;
	m_isDrawingCircle	= false;
	m_isDrawingHexagon	= false;
	m_isDrawingStar		= false;
	m_isGroupSelected	= true;
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::searchItems( const QString& text )
{
	for( auto	item : items() )
		if( Shape*	toShape = dynamic_cast< Shape* >( item ) )
			toShape->setSelected(	toShape->m_tag == text ||
									toShape->m_name == text );
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::setFillColor( const QColor& fillColor )
{
	m_fillColor		= fillColor;
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::setPenColor ( const QColor& penColor )
{
	m_penColor		= penColor;
}

////////////////////////////////////////////////////////////////////////////////

void	Canvas::setSize( const double size )
{
	m_size			= size;
}

////////////////////////////////////////////////////////////////////////////////
