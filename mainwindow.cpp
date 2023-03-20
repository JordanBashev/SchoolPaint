////////////////////////////////////////////////////////////////////////////////

#include "mainwindow.h"
#include "./ui_mainwindow.h"

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent )
	: QMainWindow( parent )
	, ui( new Ui::MainWindow )
{
	ui->setupUi( this );
	scene     = new Canvas( this );
	QRectF	rect( 0, 0 , width(), height() );
	ui->View->setSceneRect( rect );
	ui->View->setBackgroundBrush( Qt::white );
	ui->View->setScene( scene );

	setContextMenuPolicy( Qt::CustomContextMenu );

	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Select.png" ),
				tr("select")  );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/groupSelect.png" ),
				tr("group")   );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Brush.png" ),
				tr("brush")   );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Pen.png" ),
				tr("pen")     );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Resize.png" ),
				tr("resize")  );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Rectangle.png" ),
				tr("square")  );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Ellipse.png" ),
				tr("ellipse") );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Circle.png" ),
				tr("circle")  );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Hexagon.png" ),
				tr("hexagon") );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Star.png" ),
				tr("star")    );

	connect( ui->dropDownMenu, &QComboBox::activated,
			 this , &MainWindow::comboSelect );
	connect( this, &MainWindow::customContextMenuRequested,
			 this, &MainWindow::showContextMenu );
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
	delete ui;
	delete scene;
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::comboSelect( const int indx )
{
	switch( indx )
	{
	case	int(m_selection::SELECT):
		scene->select();
		break;

	case	int(m_selection::GROUP):
		scene->selectGroup();
		break;

	case	int(m_selection::BRUSH):
	{
		QColor	getFillColor
				= QColorDialog::getColor( Qt::white, this, "fillColor_Picker" );
		scene->setFillColor( getFillColor );
		break;
	}

	case	int(m_selection::PEN):
	{
		QColor	getPenColor
				= QColorDialog::getColor( Qt::white, this, "penColor_Picker" );
		scene->setPenColor( getPenColor );
		break;
	}

	case	int(m_selection::RESIZE):
	{
		int		getSize
				= QInputDialog::getInt( this, "elements_Size", "Size: ");
		scene->setSize( getSize );
		break;
	}

	case	int(m_selection::SQUARE):
		scene->drawRectangle();
		break;

	case	int(m_selection::ELLIPSE):
		scene->drawEllipse();
		break;

	case	int(m_selection::CIRCLE):
		scene->drawCircle();
		break;

	case	int(m_selection::HEXAGON):
		scene->drawHexagon();
		break;

	case	int(m_selection::STAR):
		scene->drawStar();
		break;

	default:
		qDebug() << "how did we get here";
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::showContextMenu( const QPoint &pos )
{
	if( !scene->isGroupSelected() )
	{
		QMenu	contextMenu( tr("Context menu"), this );

		QAction		action1( "Fill Color", this );
		QAction		action2( "Pen Color", this );
		QAction		action3( "Size", this );
		QAction		action4( "Rotate", this );

		connect( &action1, &QAction::triggered,
				 this, &MainWindow::changeFillColor );
		connect( &action2, &QAction::triggered,
				 this, &MainWindow::changePenColor );
		connect( &action3, &QAction::triggered,
				 this, &MainWindow::changeSize );
		connect( &action4, &QAction::triggered,
				 this, &MainWindow::changeRotation );

		contextMenu.addAction( &action1 );
		contextMenu.addAction( &action2 );
		contextMenu.addAction( &action3 );
		contextMenu.addAction( &action4 );

		contextMenu.exec( mapToGlobal(pos) );
	}
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::changeFillColor()
{
	QColor		newFillColor
			= QColorDialog::getColor( Qt::white, this, "fillColor_Picker" );
	scene->changeFillColor( newFillColor );
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::changePenColor()
{
	QColor		newPenColor
			= QColorDialog::getColor( Qt::white, this, "fillColor_Picker" );
	scene->changePenColor( newPenColor );
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::changeSize()
{
	int		newSize
			= QInputDialog::getInt( this, "elements_Size", "Size: ");
	scene->changeSize( newSize );
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::changeRotation()
{
	QSlider slider( this );

	ui->addWidget( slider );
}
