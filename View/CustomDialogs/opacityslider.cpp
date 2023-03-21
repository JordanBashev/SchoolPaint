////////////////////////////////////////////////////////////////////////////////

#include "opacityslider.h"

////////////////////////////////////////////////////////////////////////////////

OpacitySlider::OpacitySlider( QWidget* parent, Shape* item ) :
	QDialog( parent ),
	m_item( item ),
	m_layout( new QHBoxLayout ),
	m_slider( new QSlider( Qt::Horizontal ) ),
	m_lable( new QLabel( this ) )
{
	m_slider	=	new		QSlider( Qt::Horizontal );
	m_slider->setMaximum( 10 );
	m_slider->setMinimum( 0 );
	m_slider->setValue( 0 );

	m_layout	=	new		QHBoxLayout( this );
	m_layout->addWidget( m_lable );
	m_layout->addWidget( m_slider );

	connect( m_slider ,
			 &QSlider::sliderReleased ,
			 this ,
			 &OpacitySlider::getOpacity );

	connect( m_slider ,
			 &QSlider::sliderMoved ,
			 this ,
			 &OpacitySlider::changeOpacity );

	exec();
}

////////////////////////////////////////////////////////////////////////////////

OpacitySlider::OpacitySlider( QWidget* parent,
								QList< QGraphicsItem* > itemGroup ) :
	QDialog( parent ),
	m_itemGroup( itemGroup ),
	m_layout( new QHBoxLayout ),
	m_slider( new QSlider( Qt::Horizontal ) ),
	m_lable( new QLabel( this ) )
{

	m_slider	=	new		QSlider( Qt::Horizontal );
	m_slider->setMaximum( 10 );
	m_slider->setMinimum( 0 );
	m_slider->setValue( 0 );

	m_layout	=	new		QHBoxLayout( this );
	m_layout->addWidget( m_lable );
	m_layout->addWidget( m_slider );

	connect( m_slider ,
			 &QSlider::sliderReleased ,
			 this ,
			 &OpacitySlider::getOpacity );

	connect( m_slider ,
			 &QSlider::sliderMoved ,
			 this ,
			 &OpacitySlider::changeOpacity );

	exec();
}

////////////////////////////////////////////////////////////////////////////////

OpacitySlider::~OpacitySlider()
{
	delete	m_layout;
	delete	m_slider;
	for( auto item : m_itemGroup )
		delete item;
}

////////////////////////////////////////////////////////////////////////////////

void	OpacitySlider::getOpacity()
{
	m_opacity	=	m_slider->value() / 10.0;

	if( m_slider->value() == 0 )
		m_opacity = 0;

	if( !m_itemGroup.isEmpty() )
	{
		for( auto item : m_itemGroup )
			if( Shape*	toShape	=	dynamic_cast< Shape* >( item ) )
				toShape->setOpacity( m_opacity );

		m_lable->setText( QString::number( m_opacity ) );
		return;
	}

	m_item->setOpacity( m_opacity );
	m_lable->setText( QString::number( m_opacity ) );
}

////////////////////////////////////////////////////////////////////////////////

void	OpacitySlider::changeOpacity()
{
	m_opacity	=	m_slider->value() / 10.0;

	if( m_slider->value() == 0 )
		m_opacity = 0;

	if( !m_itemGroup.isEmpty() )
	{
		for( auto item : m_itemGroup )
			if( Shape*	toShape	=	dynamic_cast< Shape* >( item ) )
				toShape->setOpacity( m_opacity );

		m_lable->setText( QString::number( m_opacity ) );
		return;
	}

	m_item->setOpacity( m_opacity );
	m_lable->setText( QString::number( m_opacity ) );
}
////////////////////////////////////////////////////////////////////////////////
