#ifndef WORKER_H
#define WORKER_H

////////////////////////////////////////////////////////////////////////////////

#include <QObject>
#include <QFileDialog>
#include <QGraphicsItem>

////////////////////////////////////////////////////////////////////////////////

#include "../View/Shapes/shape.h"
#include "../View/canvas.h"

////////////////////////////////////////////////////////////////////////////////

class Worker : public QObject
{
	Q_OBJECT

public:
	Worker();

public slots:
	void	saveFile(	QList< QGraphicsItem* > allItems ,
						const QString& fileName );
	void	openFile(	Canvas* scene , const QString& fileName );

signals:
	void	resultReady( const QString& result );

};

////////////////////////////////////////////////////////////////////////////////

#endif // WORKER_H
