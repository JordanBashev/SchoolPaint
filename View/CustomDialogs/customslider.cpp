////////////////////////////////////////////////////////////////////////////////

#include "customslider.h"

////////////////////////////////////////////////////////////////////////////////

CustomSlider::CustomSlider(QWidget* parent , Shape* item ) :
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

	show();
}

////////////////////////////////////////////////////////////////////////////////

CustomSlider::~CustomSlider()
{
	delete	m_layout;
	delete	m_slider;
	delete	m_item;
}

////////////////////////////////////////////////////////////////////////////////

void	CustomSlider::getRotation()
{
	m_angle	=	m_slider->value();
	m_item->setRotation( m_angle );
	m_lable->setText( QString::number( m_angle ) );
}

////////////////////////////////////////////////////////////////////////////////

void	CustomSlider::changeRotation()
{
	m_angle	=	m_slider->value();
	m_item->setRotation( m_angle );
	m_lable->setText( QString::number( m_angle ) );
}

////////////////////////////////////////////////////////////////////////////////
