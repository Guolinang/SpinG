#include "custom_scene.h"

Custom_Scene::Custom_Scene()
{
    setBackgroundBrush(QColor(253,253,253));
    timer=nullptr;

}

float speeeed=8;
float deltaA = 0.1;
float deltaB = 0.05;
Custom_Scene::~Custom_Scene()
{
    clear();
}

QPointF Center(QList<QPoint> poly){
    QPointF center;
    center.setX(0);
    center.setY(0);
    for (auto p:poly)
    {
        center.setX(p.x()+center.x());
        center.setY(p.y()+center.y());
    }
    center.setX(center.x()/poly.size());
    center.setY(center.y()/poly.size());
    return center;
}

void Custom_Scene::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    if (event->button()==Qt::RightButton){
        moveflag=true;
    }
    if (event->button()==Qt::LeftButton && mode==1){
        HandleLMB(event);
    }
    if (event->button()==Qt::LeftButton && mode==-1){
        HandleLMB(event);
    }
}




void Custom_Scene::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
      if (moveflag)
      {
          HandleRMB(event);
      }
}

void Custom_Scene::HandleRMB(QGraphicsSceneMouseEvent * event){


    QList<QPoint>::iterator closest=path.end();
    float distance=40;
    for (auto p=path.begin();p!=path.end();p++){
        float d=sqrt(pow(event->scenePos().x() - p->x(),2)+pow(event->scenePos().y() - p->y(),2));
        if (d < distance){
            closest=p;
            distance=d;
        }

    }

    if (closest==path.end())
        return;
    (closest)->rx()=event->scenePos().x();
    (closest)->ry()=event->scenePos().y();
    refresh();
}

void moveToPoint(QList<QPoint>* figure, QPoint point){
    QPointF figCenter = Center(*figure);
    QPoint dist;
    dist.setX(figCenter.x()-point.x());
    dist.setY(figCenter.y()-point.y());
    for (auto f=figure->begin();f!=figure->end();f++){
        f->setX(f->x()-dist.x());
        f->setY(f->y()-dist.y());
    }

}
float culc(QPoint A,QPoint B){

    return 1/(sqrt(pow(A.x()-B.x(),2)+pow(A.y()-B.y(),2))/speeeed);

}
void Custom_Scene::run(){

    mode=0;
    if (!timer) {
    moveToPoint(&figure,path.first());
    QList<QPoint> initFig;
    for ( auto p:figure)
    {
        initFig.push_back(QPoint(p.x(),p.y()));
    }
    QList<QPoint> initPath;
    for ( auto p:path)
    {
        initPath.push_back(QPoint(p.x(),p.y()));
    }
    QPointF pathCenter=Center(path);
    QPointF intCenter=Center(initFig);
    refresh();
    static auto A = path.begin();
    static auto B = A + 1;
    float T = 0;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this, initFig, initPath, pathCenter, intCenter,A,B,T]() mutable {
            static float alpha=0;
            static float beta=0;
            for (int i=0;i<path.size();i++){
                path[i].setX(((initPath[i].x()-pathCenter.x())*cos(beta)-(initPath[i].y()-pathCenter.y())*sin(beta))+pathCenter.x());
                path[i].setY(((initPath[i].x()-pathCenter.x())*sin(beta)+(initPath[i].y()-pathCenter.y())*cos(beta))+pathCenter.y());
            }

            if (B == path.end()) {
                B=path.begin();
                A=path.end()-1;
                T=0;
            }

            float DT = culc(*A, *B);
            if (T < 1) {
                T += DT;
                QPoint S;
                S.setX(A->x() * (1 - T) + B->x() * T);
                S.setY(A->y() * (1 - T) + B->y() * T);
                for (int i = 0; i < figure.size(); i++) {
                    float x = initFig[i].x() - intCenter.x();
                    float y = initFig[i].y() - intCenter.y();

                    float newX = x * cos(alpha) - y * sin(alpha);
                    float newY = x * sin(alpha) + y * cos(alpha);

                    figure[i].setX(newX  + S.x());
                    figure[i].setY(newY  + S.y());
                }
                refresh();
                alpha+=deltaA;
                beta+=deltaB;
            } else {
                A = B;
                B++;
                T = 0;
            }
        });
        timer->start(100);
    }
    start();

}


void Custom_Scene::rotate(QList<QPoint> poly, QPoint cent){


}

void Custom_Scene::HandleLMB(QGraphicsSceneMouseEvent * event){

    if (mode==0)
    {
        return;
    }
    if (mode==1){
        path.push_back(QPoint(event->scenePos().x(),event->scenePos().y()));
    }
    else{
        figure.push_back(QPoint(event->scenePos().x(),event->scenePos().y()));
    }
    refresh();
}


void Custom_Scene::set_mode(int m){
    mode=m;  }




void Custom_Scene::refresh(){

    clear();
    if (path.size()==1)
    {
        addEllipse(path.first().x(),path.first().y(),4,4,QPen(Qt::black),QBrush(Qt::black));

    }
    else if (path.size()>1){
        if (mode!=1)
          {addLine(path.first().x(),path.first().y(),path.last().x(),path.last().y(),QPen(Qt::black));

        }
        auto from=path.begin();
        auto to=from+1;
        while (to!=path.end())
        {
            addLine(from->x(),from->y(),to->x(),to->y(),QPen(Qt::black));
            from=to;
            to=to+1;
        }
    }


    if (figure.size()==1)
    {
        addEllipse(figure.first().x(),figure.first().y(),4,4,QPen(Qt::red),QBrush(Qt::red));

    }
    else if (figure.size()>1){
        if (mode!=-1)
          {addLine(figure.first().x(),figure.first().y(),figure.last().x(),figure.last().y(),QPen(Qt::red));

        }
        auto from=figure.begin();
        auto to=from+1;
        qDebug()<<figure[0];
        while (to!=figure.end())
        {
            addLine(from->x(),from->y(),to->x(),to->y(),QPen(Qt::red));
            from=to;
            to=to+1;
        }
    }

}


void Custom_Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent * event){

    if (event->button()==Qt::RightButton){
        moveflag=false;

    }
}
void Custom_Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
{
    mode=0;
    refresh();
}


void Custom_Scene::clearFig(){
    figure.clear();
    refresh();
}

void Custom_Scene::clearPath(){
    path.clear();
    refresh();
}

void Custom_Scene::start(){

    if (!isRunning) {
        isRunning = true;
        timer->start(100);
    }
}

void Custom_Scene::stop(){
    if (isRunning) {
        isRunning = false;
        timer->stop();
        delete timer;
        timer=nullptr;
    }
}
