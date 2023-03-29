#ifndef MAINWINDOW_H
#define MAINWINDOW_H

////////////////////////////////////////////////////////////////////////////////

#include <QGraphicsView>
#include <QMainWindow>
#include <QFileDialog>
#include <QtCore>
#include <QtGui>

////////////////////////////////////////////////////////////////////////////////

#include "View/canvas.h"
#include "Workers/worker.h"
#include "Serializer/serialization.h"

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

	enum m_serialization : quint8 {
		SAVE_FILE = 0,
		OPEN_FILE
	};

public:
	MainWindow( QWidget*	parent	=	nullptr );
	~MainWindow();

private:
	Ui::MainWindow*		ui;
//	QThread		workerThread;
	Serialization	serializationThread;

private:
	Canvas*		m_scene		= nullptr;

private slots:
	void	comboSelect( const int	indx = 0 );
	void	showContextMenu( const QPoint&	pos = QPoint() );
	void	handleResults( const QString& result );
	void	saveFile();
	void	openFile();
	void	changeFillColor();
	void	changePenColor();
	void	changeSize();
	void	changeRotation();
	void	changeOpacity();
	void	changeItemName();
	void	displayItemName();
	void	deleteItems();

signals:
	void	saveFiles(	QList< QGraphicsItem* > allItems ,
						const QString& fileName );
	void	openFiles(	Canvas* scene , const QString& fileName );

};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
