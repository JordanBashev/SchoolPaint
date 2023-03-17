#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QtCore>
#include <QtGui>

#include "View/canvas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = nullptr );
    ~MainWindow();

private:
    Ui::MainWindow*    ui;

private:
    Canvas*    scene;

private slots:
    void    comboSelect( const int indx );
    void    showContextMenu( const QPoint& pos );
    void    changeFillColor();
    void    changePenColor();
    void    changeSize();
    void    changeRotation();
};
#endif // MAINWINDOW_H
