#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QPointF>
#include <QTimer>
#include <QPainter>
#include "Custom_Scene.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
    QGraphicsItem* path;
    QGraphicsItem* figure;
    Custom_Scene* new_scene;
    QGraphicsView view;
    QTimer* timer;
private slots:
    void slotTimer();
    void resizeEvent(QResizeEvent *event);
    void on_b_poly_clicked();
    void on_b_path_clicked();
    void on_pushButton_3_clicked();
    void on_b_stop_clicked();
};
#endif // MAINWINDOW_H
