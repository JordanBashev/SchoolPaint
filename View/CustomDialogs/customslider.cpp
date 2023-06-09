////////////////////////////////////////////////////////////////////////////////

#include "customslider.h"

////////////////////////////////////////////////////////////////////////////////

CustomSlider::CustomSlider( QWidget* parent , Shape* item ) :
	QDialog( parent ),
	m_item( item ),
	m_layout( new QHBoxLayout ),
	m_slider( new QSlider( Qt::Horizontal ) ),
	m_lable( new QLabel( this ) )
{
	m_slider	=	new		QSlider( Qt::Horizontal );
	m_slider->setMaximum( 360 );
	m_slider->setMinimum( -360 );
	m_slider->setValue( 0 );

	m_layout	=	new		QHBoxLayout( this );
	m_layout->addWidget( m_lable );
	m_layout->addWidget( m_slider );

	connect( m_slider ,
			 &QSlider::sliderMoved ,
			 this ,
			 &CustomSlider::changeRotation );

	connect( m_slider ,
			 &QSlider::sliderReleased ,
			 this ,
			 &CustomSlider::getRotation );

	exec();
}

////////////////////////////////////////////////////////////////////////////////

CustomSlider::CustomSlider( QWidget* parent,
							QList< QGraphicsItem* > itemGroup ) :
	QDialog( parent ),
	m_itemGroup( itemGroup ),
	m_layout( new QHBoxLayout ),
	m_slider( new QSlider( Qt::Horizontal ) ),
	m_lable( new QLabel( this ) )
{
	m_slider	=	new		QSlider( Qt::Horizontal );
	m_slider->setMaximum( 360 );
	m_slider->setMinimum( -360 );
	m_slider->setValue( 0 );

	m_layout	=	new		QHBoxLayout( this );
	m_layout->addWidget( m_lable );
	m_layout->addWidget( m_slider );

	connect( m_slider ,
			 &QSlider::sliderMoved ,
			 this ,
			 &CustomSlider::changeRotation );

	connect( m_slider ,
			 &QSlider::sliderReleased ,
			 this ,
			 &CustomSlider::getRotation );

	exec();
}

////////////////////////////////////////////////////////////////////////////////

CustomSlider::~CustomSlider()
{
	delete	m_layout;
	delete	m_slider;
	delete	m_item;
	for( auto item : m_itemGroup )
		delete item;
}

////////////////////////////////////////////////////////////////////////////////

QTransform	CustomSlider::setItemTransform( Shape* item )
{
	QPointF		offset	=	item->getBoundingRectCenter();
	QTransform	transform;
	transform.translate( offset.x(), offset.y() );
	transform.rotate( m_angle );
	transform.translate( -offset.x(), -offset.y() );
	return transform;
}

////////////////////////////////////////////////////////////////////////////////

void	CustomSlider::getRotation()
{
	m_angle	=	m_slider->value();

	if( !m_itemGroup.isEmpty() )
	{
		for( auto item : m_itemGroup )
			if( Shape*	toShape	=	dynamic_cast< Shape* >( item ) )
			{
				QTransform	transform = setItemTransform( toShape );
				toShape->setTransform( transform );
			}

		m_lable->setText( QString::number( m_angle ) );
		return;
	}

	QTransform	transform = setItemTransform( m_item );
	m_item->setTransform( transform );
	m_lable->setText( QString::number( m_angle ) );
}

////////////////////////////////////////////////////////////////////////////////

void	CustomSlider::changeRotation()
{
	m_angle	=	m_slider->value();

	if(	!m_itemGroup.isEmpty()	)
	{
		for( auto item : m_itemGroup )
			if( Shape*	toShape	=	dynamic_cast< Shape* >( item ) )
			{
				QTransform	transform = setItemTransform( toShape );
				toShape->setTransform( transform );
			}

		m_lable->setText( QString::number( m_angle ) );
		return;
	}

	QTransform	transform = setItemTransform( m_item );
	m_item->setTransform( transform );
	m_lable->setText( QString::number( m_angle ) );
}

////////////////////////////////////////////////////////////////////////////////
