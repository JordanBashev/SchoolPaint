#ifndef OPACITYSLIDER_H
#define OPACITYSLIDER_H

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

class OpacitySlider : public QDialog
{
	Q_OBJECT

private:
	Shape*					m_item;
	QList< QGraphicsItem* >	m_itemGroup;
	QHBoxLayout*			m_layout;
	QSlider*				m_slider;
	QLabel*					m_lable;
	double					m_opacity;

public:
	OpacitySlider( QWidget* parent = nullptr, Shape* item = nullptr );
	OpacitySlider( QWidget* parent = nullptr ,
				QList< QGraphicsItem* > itemGroup = QList< QGraphicsItem* >() );
	~OpacitySlider();

private slots:
	void	getOpacity();
	void	changeOpacity();

};

////////////////////////////////////////////////////////////////////////////////

#endif // OPACITYSLIDER_H
