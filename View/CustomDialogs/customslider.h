#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

////////////////////////////////////////////////////////////////////////////////

#include <QObject>
#include <QWidget>
#include <QBoxLayout>
#include <QSlider>
#include <QPushButton>
#include <QDialog>
#include <QLabel>

////////////////////////////////////////////////////////////////////////////////

#include "../Shapes/shape.h"

class CustomSlider : public QDialog
{
	Q_OBJECT

private:
	Shape*			m_item = nullptr;
	QHBoxLayout*	m_layout;
	QSlider*		m_slider;
	QLabel*			m_lable;
	int				m_angle;

public:
	CustomSlider( QWidget* parent = nullptr , Shape* item	=	nullptr );
	~CustomSlider();

public slots:
	void	changeRotation();
	void	getRotation();

};

////////////////////////////////////////////////////////////////////////////////

#endif // CUSTOMSLIDER_H
