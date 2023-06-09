#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

////////////////////////////////////////////////////////////////////////////////

#include <QObject>
#include <QWidget>
#include <QBoxLayout>
#include <QSlider>
#include <QDialog>
#include <QLabel>

////////////////////////////////////////////////////////////////////////////////

#include "../Shapes/shape.h"

////////////////////////////////////////////////////////////////////////////////

class CustomSlider : public QDialog
{
	Q_OBJECT

private:
	Shape*					m_item				= nullptr;
	QList< QGraphicsItem* >	m_itemGroup;
	QHBoxLayout*			m_layout;
	QSlider*				m_slider;
	QLabel*					m_lable;
	int						m_angle;
	double					m_opacity;

public:
	CustomSlider( QWidget*	parent	=	nullptr , Shape*	item	= nullptr );
	CustomSlider(QWidget*	parent	=	nullptr ,
				QList< QGraphicsItem* >	itemGroup = QList< QGraphicsItem* >() );
	~CustomSlider();

private:
	QTransform	setItemTransform( Shape* item );

public slots:
	void	changeRotation();
	void	getRotation();
};

////////////////////////////////////////////////////////////////////////////////

#endif // CUSTOMSLIDER_H
