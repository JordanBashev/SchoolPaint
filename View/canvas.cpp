#include <QDebug>

#include "canvas.h"

Canvas::Canvas( QObject *parent )
    : QGraphicsScene( parent )
{ }

Canvas::~Canvas()
{
    delete m_group;
    delete m_deletePath;
    delete m_selectionPath;
}

void     Canvas::mousePressEvent( QGraphicsSceneMouseEvent *event )
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

    if( event->button() == Qt::RightButton && m_isGroupSelected )
    {
        if( m_deletePath != nullptr )
        {
            removeItem            ( m_deletePath );
            delete m_deletePath;
            m_deletePath          = nullptr;
        }

        if( m_group != nullptr )
        {
            destroyItemGroup      ( m_group );
            m_group               = nullptr;
        }

        m_selectionPath           = new QPainterPath();
        m_selectionTopLeft        = event->scenePos();
    }

    if( event->button() == Qt::RightButton )
        m_itemSelect              = event->scenePos();

    QGraphicsScene::mousePressEvent( event );
}

void     Canvas::mouseReleaseEvent( QGraphicsSceneMouseEvent *event )
{
    if( event->button() == Qt::RightButton && m_isGroupSelected )
    {
        m_selectionPath->addRect   ( QRectF( m_selectionTopLeft, event->scenePos() )); // creating path with (0 ,0) in a double click will crash the app. think of potential fix
        m_deletePath               = addPath( *m_selectionPath );
        m_deletePath->setFlag      ( m_deletePath->ItemIsMovable );
        m_deletePath->setFlag      ( m_deletePath->ItemIsSelectable );
        auto    allItems           = selectedItems();
        setSelectionArea           ( *m_selectionPath );

        if ( selectedItems().count() > 0 )
        {
            m_group                = createItemGroup( allItems );
            m_group->setFlag       ( m_group->ItemIsMovable );

            m_selectionTopLeft     = QPointF( 0, 0 );
            allItems.clear();
        }

        delete m_selectionPath;
        m_selectionPath            = nullptr;
    }

    if( event->button() == Qt::LeftButton && m_deletePath != nullptr )
    {
        if( !m_deletePath->isSelected() )
        {
            removeItem             ( m_deletePath );
            delete m_deletePath;
            m_deletePath           = nullptr;
        }
    }

    QGraphicsScene::mouseReleaseEvent( event );
}


void     Canvas::paintRect( const QPointF& pos, const QColor& fillColor, const QColor& penColor , const int size )
{
    QBrush*    brush            = new QBrush( fillColor );
    QPen*      pen              = new QPen( penColor );
    Shape*     item             = new Rect( size, *pen, *brush, pos );
    item->m_tag.append          ( "Rect" );
    addItem                     ( item );
    delete brush;
    delete pen;
}



void     Canvas::paintEllipse( const QPointF &pos, const QColor &fillColor, const QColor &penColor, const int size )
{
    QBrush*    brush            = new QBrush( fillColor );
    QPen*      pen              = new QPen( penColor );
    Shape*     item             = new Ellipse( size, *pen, *brush, pos );
    item->m_tag.append          ( "Ellipse" );
    addItem                     ( item );
    delete brush;
    delete pen;
}



void     Canvas::paintCircle( const QPointF &pos, const QColor &fillColor, const QColor &penColor, const int size )
{
    QBrush*    brush            = new QBrush( fillColor );
    QPen*      pen              = new QPen( penColor );
    Shape*     item             = new Circle( size, *pen, *brush, pos );
    item->m_tag.append          ( "Circle" );
    addItem                     ( item );
    delete brush;
    delete pen;
}



void     Canvas::paintHexagon( const QPointF &pos, const QColor &fillColor, const QColor &penColor, const int size )
{
    QBrush*    brush            = new QBrush( fillColor );
    QPen*      pen              = new QPen( penColor );
    Shape*     item             = new Hexagon( size, *pen, *brush, pos );
    item->m_tag.append          ( "Hexagon" );
    addItem                     ( item);
    delete brush;
    delete pen;
}



void     Canvas::paintStar( const QPointF &pos, const QColor &fillColor, const QColor &penColor, const int size )
{
    QBrush*    brush            = new QBrush( fillColor );
    QPen*      pen              = new QPen( penColor );
    Shape*     item             = new Star( size, *pen, *brush, pos );
    item->m_tag.append          ( "Star" );
    addItem                     ( item );
    delete brush;
    delete pen;
}

Shape*     Canvas::getItem( const QPointF& pos )
{
    QTransform    transform;
    QGraphicsItem*    selectedItem      = itemAt( pos, transform );
    return static_cast< Shape* >( selectedItem );
}

void     Canvas::changeFillColor( const QColor& fillColor ) // crashes when called for more then 1 item simultaniusly. think of potential fix.
{
    Shape*    item      = getItem( m_itemSelect );
    QBrush    newBrush  ( fillColor );
    if( item != nullptr )
        item->changeFillColor( newBrush );
    update();
}

void     Canvas::changePenColor( const QColor &penColor )
{
    Shape*    item      = getItem( m_itemSelect );
    QPen    newPen  ( penColor );
    if( item != nullptr )
        item->changePenColor( newPen );
    update();
}

void     Canvas::changeSize( const double size )
{
    Shape*    item      = getItem( m_itemSelect );
    if( item != nullptr )
        item->changeSize( size );
    update();
}

bool     Canvas::isGroupSelected()
{
    return m_isGroupSelected;
}


void     Canvas::drawRectangle()
{
    m_isDrawingRect      = true;
    m_isDrawingEllipse   = false;
    m_isDrawingCircle    = false;
    m_isDrawingHexagon   = false;
    m_isDrawingStar      = false;
    m_isGroupSelected    = false;
}

void     Canvas::drawEllipse()
{
    m_isDrawingRect      = false;
    m_isDrawingEllipse   = true;
    m_isDrawingCircle    = false;
    m_isDrawingHexagon   = false;
    m_isDrawingStar      = false;
    m_isGroupSelected    = false;
}

void     Canvas::drawCircle()
{
    m_isDrawingRect      = false;
    m_isDrawingEllipse   = false;
    m_isDrawingCircle    = true;
    m_isDrawingHexagon   = false;
    m_isDrawingStar      = false;
    m_isGroupSelected    = false;
}

void     Canvas::drawHexagon()
{
    m_isDrawingRect      = false;
    m_isDrawingEllipse   = false;
    m_isDrawingCircle    = false;
    m_isDrawingHexagon   = true;
    m_isDrawingStar      = false;
    m_isGroupSelected    = false;
}

void     Canvas::drawStar()
{
    m_isDrawingRect      = false;
    m_isDrawingEllipse   = false;
    m_isDrawingCircle    = false;
    m_isDrawingHexagon   = false;
    m_isDrawingStar      = true;
    m_isGroupSelected    = false;
}

void     Canvas::select()
{
    m_isDrawingRect      = false;
    m_isDrawingEllipse   = false;
    m_isDrawingCircle    = false;
    m_isDrawingHexagon   = false;
    m_isDrawingStar      = false;
    m_isGroupSelected    = false;
}

void     Canvas::selectGroup()
{
    m_isDrawingRect      = false;
    m_isDrawingEllipse   = false;
    m_isDrawingCircle    = false;
    m_isDrawingHexagon   = false;
    m_isDrawingStar      = false;
    m_isGroupSelected    = true;
}

void     Canvas::setFillColor( const QColor& fillColor )
{
    m_fillColor      = fillColor;
}

void     Canvas::setPenColor ( const QColor& penColor  )
{
    m_penColor       = penColor;
}

void     Canvas::setSize( const double size )
{
    m_size           = size;
}
