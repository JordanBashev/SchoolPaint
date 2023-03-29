////////////////////////////////////////////////////////////////////////////////

#include "serialization.h"

////////////////////////////////////////////////////////////////////////////////

const QString SUCCESS_SAVE = "Saved Successfuly";
const QString SUCCESS_OPEN = "Opened Successfuly";

////////////////////////////////////////////////////////////////////////////////

Serialization::Serialization()
{}

////////////////////////////////////////////////////////////////////////////////

void	Serialization::run(	const QList< QGraphicsItem* > allItems,
							Canvas* scene , const QString& fileName,
							const int type )
{
	if( type == SAVE_FILE )
	{
		saveFile( allItems, fileName );
		return;
	}

	openFile( scene, fileName );
}

////////////////////////////////////////////////////////////////////////////////

void	Serialization::saveFile(	const QList< QGraphicsItem* > allItems,
									const QString& fileName)
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
			result = SUCCESS_SAVE;
		}
	}

	emit resultReady( result );
}

////////////////////////////////////////////////////////////////////////////////

void	Serialization::openFile( Canvas* scene, const QString& fileName )
{
	QString		result = "Success";
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

				scene->loadItems(	brush, pen, size,
									name, type , scenePos , rotation );
			}
			file.close();
			result = SUCCESS_OPEN;
		}
	}

	emit resultReady( result );
}

////////////////////////////////////////////////////////////////////////////////
