////////////////////////////////////////////////////////////////////////////////

#include "worker.h"

////////////////////////////////////////////////////////////////////////////////

Worker::Worker()
{

}

////////////////////////////////////////////////////////////////////////////////

void Worker::saveFile(	QList< QGraphicsItem* > allItems ,
						const QString& fileName )
{
	QString		result = "Failed To Open Dir";
	if ( !fileName.isNull() )
	{
		QFile	file( QFileInfo( fileName ).absoluteFilePath() );
		result = "Failed To Open File";

		if ( file.open(QIODevice::WriteOnly) )
		{
			quint16		counter = allItems.count();

			QDataStream		out( &file );
			out.setFloatingPointPrecision( out.DoublePrecision );

			out << counter;
			for( auto item : allItems )
			{
				if( Shape*	toShape = dynamic_cast< Shape* >( item ) )
				{
					qint32		type		= toShape->type();
					QTransform	rotation	= toShape->transform();
					out << toShape->getBrush()
						<< toShape->getPen()
						<< toShape->getSize()
						<< toShape->m_name
						<< type
						<< toShape->scenePos()
						<< rotation;
				}
			}
			file.close();
			result = "Success";
		}
	}

	emit resultReady( result );
}

////////////////////////////////////////////////////////////////////////////////

void Worker::openFile( QGraphicsScene* scene, const QString& fileName )
{
	QString		result = "Failed To Open Dir";

	if ( !fileName.isNull() )
	{
		QFile	file( QFileInfo( fileName ).absoluteFilePath() );
		result = "Failed To Open file";
		if ( file.open( QIODevice::ReadOnly ) )
		{
			QBrush			brush;
			double			size;
			QPen			pen;
			QString			name;
			qint32			type;
			QPointF			scenePos;
			quint16			count;
			QTransform		rotation;
			QDataStream		in( &file );

			in	>> count;
			for( int	i = 0; i < count; ++i )
			{
				in	>> brush
					>> pen
					>> size
					>> name
					>> type
					>> scenePos
					>> rotation;

				static_cast< Canvas* >(scene)->loadItems( brush, pen, size,
									name, type , scenePos , rotation );
			}
			file.close();
			result = "Success";
		}
	}

	emit resultReady( result );
}

////////////////////////////////////////////////////////////////////////////////
