#ifndef MAINWINDOW_H
#define MAINWINDOW_H

////////////////////////////////////////////////////////////////////////////////

#include <QGraphicsView>
#include <QMainWindow>
#include <QtCore>
#include <QtGui>

////////////////////////////////////////////////////////////////////////////////

#include "View/canvas.h"

////////////////////////////////////////////////////////////////////////////////

enum class	m_selection : quint8 {
	SELECT = 0,
	GROUP,
	SEARCH,
	BRUSH,
	PEN,
	RESIZE,
	SQUARE,
	ELLIPSE,
	CIRCLE,
	HEXAGON,
	STAR
};

////////////////////////////////////////////////////////////////////////////////

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

////////////////////////////////////////////////////////////////////////////////

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow( QWidget*	parent	=	nullptr );
	~MainWindow();

private:
	Ui::MainWindow*		ui;

private:
	Canvas*		m_scene		= nullptr;

private slots:
	void	comboSelect( const int indx = 0 );
	void	showContextMenu( const QPoint& pos = QPoint() );
	void	changeFillColor();
	void	changePenColor();
	void	changeSize();
	void	changeRotation();
	void	changeOpacity();
	void	changeItemName();
	void	displayItemName();
	void	deleteItems();
};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
