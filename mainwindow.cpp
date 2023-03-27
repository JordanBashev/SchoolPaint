////////////////////////////////////////////////////////////////////////////////

#include "mainwindow.h"
#include "./ui_mainwindow.h"

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget* parent )
	: QMainWindow( parent )
	, ui( new Ui::MainWindow )
{
	ui->setupUi( this );
	m_scene	= new Canvas( this );
	QRectF	rect( 0, 0 , width(), height() );
	ui->View->setSceneRect( rect );
	ui->View->setBackgroundBrush( Qt::white );
	ui->View->setScene( m_scene );

	setContextMenuPolicy( Qt::CustomContextMenu );

	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Select.png" ),
				tr("select") );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/groupSelect.png" ),
				tr("group") );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Search.png" ),
				tr("search") );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Brush.png" ),
				tr("brush") );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Pen.png" ),
				tr("pen") );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Resize.png" ),
				tr("resize") );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Rectangle.png" ),
				tr("square") );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Ellipse.png" ),
				tr("ellipse") );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Circle.png" ),
				tr("circle") );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Hexagon.png" ),
				tr("hexagon") );
	ui->dropDownMenu->addItem(
				QIcon( "/Users/monterey/Documents/Icons/Star.png" ),
				tr("star") );

	connect( ui->save, &QPushButton::clicked, this, &MainWindow::saveFile );
	connect( ui->open, &QPushButton::clicked, this, &MainWindow::openFile );

	connect( ui->dropDownMenu, &QComboBox::activated,
			 this , &MainWindow::comboSelect );

	connect( this, &MainWindow::customContextMenuRequested,
			 this, &MainWindow::showContextMenu );
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
	delete ui;
	delete m_scene;
	workerThread.quit();
	workerThread.wait();
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::comboSelect( const int indx )
{
	switch( indx )
	{
	case	int( m_selection::SELECT ):
		m_scene->select();
		break;

	case	int( m_selection::GROUP ):
		m_scene->selectGroup();
		break;

	case	int( m_selection::SEARCH ):
	{
		m_scene->select();
		QString	getText
				= QInputDialog::getText( this, "Text", "Name/Tag: " );
		m_scene->searchItems( getText );
		break;
	}
	case	int( m_selection::BRUSH ):
	{
		QColor	getFillColor
				= QColorDialog::getColor( Qt::white, this, "fillColor_Picker" );
		m_scene->setFillColor( getFillColor );
		break;
	}
	case	int( m_selection::PEN ):
	{
		QColor	getPenColor
				= QColorDialog::getColor( Qt::white, this, "penColor_Picker" );
		m_scene->setPenColor( getPenColor );
		break;
	}
	case	int( m_selection::RESIZE ):
	{
		int		getSize
				= QInputDialog::getInt( this, "elements_Size", "Size: ");
		m_scene->setSize( getSize );
		break;
	}
	case	int( m_selection::SQUARE ):
		m_scene->drawRectangle();
		break;

	case	int( m_selection::ELLIPSE ):
		m_scene->drawEllipse();
		break;

	case	int( m_selection::CIRCLE ):
		m_scene->drawCircle();
		break;

	case	int( m_selection::HEXAGON ):
		m_scene->drawHexagon();
		break;

	case	int( m_selection::STAR ):
		m_scene->drawStar();
		break;

	default:
		qDebug() << "how did we get here";
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::showContextMenu( const QPoint& pos )
{
	if( !m_scene->isGroupSelected() )
	{
		QMenu	contextMenu( tr("Context menu"), this );

		QAction		action1( "Fill Color", this );
		QAction		action2( "Pen Color", this );
		QAction		action3( "Size", this );
		QAction		action4( "Rotate", this );
		QAction		action5( "Opacity", this );
		QAction		action6( "Change Name" , this );
		QAction		action7( "Display Name" , this );
		QAction		action8( "Delete" , this );

		connect( &action1, &QAction::triggered,
				 this, &MainWindow::changeFillColor );

		connect( &action2, &QAction::triggered,
				 this, &MainWindow::changePenColor );

		connect( &action3, &QAction::triggered,
				 this, &MainWindow::changeSize );

		connect( &action4, &QAction::triggered,
				 this, &MainWindow::changeRotation );

		connect( &action5, &QAction::triggered,
				 this, &MainWindow::changeOpacity );

		connect( &action6, &QAction::triggered,
				 this, &MainWindow::changeItemName );

		connect( &action7, &QAction::triggered,
				 this, &MainWindow::displayItemName );

		connect( &action8, &QAction::triggered,
				 this, &MainWindow::deleteItems );

		contextMenu.addAction( &action1 );
		contextMenu.addAction( &action2 );
		contextMenu.addAction( &action3 );
		contextMenu.addAction( &action4 );
		contextMenu.addAction( &action5 );
		contextMenu.addAction( &action6 );
		contextMenu.addAction( &action7 );
		contextMenu.addAction( &action8 );

		contextMenu.exec( mapToGlobal(pos) );
	}
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::handleResults( const QString& result )
{
	if( result == "Success" )
	{
		workerThread.quit();
		workerThread.wait();
	}
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::saveFile()
{
	QList< QGraphicsItem* > allItems = m_scene->items();
	QString					fileName = QFileDialog::getSaveFileName(
							this, tr( "Save image" ),
							QCoreApplication::applicationDirPath(),
							tr( "Text Files (*.txt)" ) );

	Worker* worker = new Worker;
	worker->moveToThread( &workerThread );
	connect( &workerThread, &QThread::finished, worker, &QObject::deleteLater );
	connect( this, &MainWindow::saveFiles, worker, &Worker::saveFile );
	connect( worker, &Worker::resultReady, this, &MainWindow::handleResults );
	workerThread.start();

	emit MainWindow::saveFiles( allItems , fileName );
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::openFile()
{
	QString		fileName = QFileDialog::getOpenFileName(
				this, tr( "Open File" ),
				QCoreApplication::applicationDirPath(),
				tr( "Text Files (*.txt)" ) );

	Worker* worker = new Worker;
	worker->moveToThread( &workerThread );
	connect( &workerThread, &QThread::finished, worker, &QObject::deleteLater );
	connect( this, &MainWindow::openFiles, worker, &Worker::openFile );
	connect( worker, &Worker::resultReady, this, &MainWindow::handleResults );
	workerThread.start();

	emit MainWindow::openFiles(	m_scene,
								fileName );
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::changeFillColor()
{
	QColor	newFillColor
			= QColorDialog::getColor( Qt::white, this, "fillColor_Picker" );

	m_scene->changeFillColor( newFillColor );
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::changePenColor()
{
	QColor	newPenColor
			= QColorDialog::getColor( Qt::white, this, "fillColor_Picker" );

	m_scene->changePenColor( newPenColor );
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::changeSize()
{
	int		newSize
			=	QInputDialog::getInt( this, "elements_Size", "Size: " );

	m_scene->changeSize( newSize );
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::changeRotation()
{
	m_scene->rotateObject( this );
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::changeOpacity()
{
	m_scene->changeOpacity( this );
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::changeItemName()
{
	QString	getText
			= QInputDialog::getText( this, "Name", "Name: " );

	m_scene->itemName( getText );
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::displayItemName()
{
	m_scene->displayName();
}

////////////////////////////////////////////////////////////////////////////////

void	MainWindow::deleteItems()
{
	m_scene->eraseItems();
}

////////////////////////////////////////////////////////////////////////////////
