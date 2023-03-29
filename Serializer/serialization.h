#ifndef SERIALIZATION_H
#define SERIALIZATION_H

////////////////////////////////////////////////////////////////////////////////

#include <QObject>
#include <QFileDialog>
#include <QGraphicsItem>

////////////////////////////////////////////////////////////////////////////////

#include "../View/Shapes/shape.h"
#include "../View/canvas.h"

////////////////////////////////////////////////////////////////////////////////

class Serialization : public QThread
{
	Q_OBJECT

	enum m_type : quint8 {
		SAVE_FILE = 0,
		OPEN_FILE
	};

public:
	Serialization();
	void run(	const QList< QGraphicsItem* > allItems = QList< QGraphicsItem* >(),
				Canvas* scene = nullptr, const QString& fileName = "",
				const int type = -1);

	void	saveFile(	const QList<QGraphicsItem*> allItems ,
						const QString& fileName );
	void	openFile(	Canvas* scene , const QString& fileName );

signals:
	void resultReady( const QString& result );

};

////////////////////////////////////////////////////////////////////////////////

#endif // SERIALIZATION_H



