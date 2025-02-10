#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    new_scene=new Custom_Scene;
    ui->graphicsView->setScene(new_scene);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    timer->start(100);

}

MainWindow::~MainWindow()
{   delete timer;
    delete new_scene;
    delete ui;
}

void MainWindow::slotTimer()
{
    timer->stop();
    new_scene->setSceneRect(0,0, ui->graphicsView->width()+200 , ui->graphicsView->height()+200 );
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
    ui->graphicsView->fitInView(new_scene->sceneRect());
}

void MainWindow::on_b_poly_clicked()
{
    new_scene->clearFig();
    new_scene->set_mode(-1);

}


void MainWindow::on_b_path_clicked()
{
    new_scene->clearPath();
    new_scene->set_mode(1);
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->b_path->setEnabled(false);
    ui->b_poly->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    new_scene->run();
    new_scene->start();


}


void MainWindow::on_b_stop_clicked()
{
    ui->b_path->setEnabled(true);
    ui->b_poly->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    new_scene->stop();
}

