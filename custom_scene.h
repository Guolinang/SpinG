#ifndef CUSTOM_SCENE_H
#define CUSTOM_SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QPointF>
#include <QDebug>
#include <QPainter>
#include <QList>
#include <QTimer>
#include <Windows.h>

class Custom_Scene:  public QGraphicsScene
{
    Q_OBJECT
public:
    Custom_Scene();
    ~Custom_Scene();


    void set_mode(int m);
    void clearFig();
    void clearPath();
    void run();
    void rotate(QList<QPoint> poly, QPoint cent);
    void stop();
    void start();


private:

    int mode;
    QList<QPoint> path;
    QList<QPoint> figure;
    void refresh();    
    bool moveflag=false;
    void HandleRMB(QGraphicsSceneMouseEvent * event);
    void HandleLMB(QGraphicsSceneMouseEvent * event);
    QTimer *timer;
    bool isRunning=false;

private slots:


    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

};



#endif // CUSTOM_SCENE_H
