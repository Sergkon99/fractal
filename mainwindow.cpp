#include "mainwindow.h"
#include "ui_mainwindow.h"

bool MainWindow::checkArea(QPoint pos, QRect rect)
{
    if(pos.x() >= rect.x() && pos.x() <= rect.x() + rect.width() &&
            pos.y() >= rect.y() && pos.y() <= rect.y() + rect.height()){
        return true;
    }

    return false;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    paint = new Painter(ui->lbGraph);
    paint->setAutoChooseN(ui->cb_nAuto->isChecked());
    paint->setShowGrid(ui->cb_showGrid->isChecked());
    paint->setFill(ui->cb_fill->isChecked());

    paint->update();

    ui->lbGraph->setCursor(Qt::OpenHandCursor);

    connect(this, &MainWindow::signalMousePress, this, &MainWindow::slotMousePress);
    connect(this, &MainWindow::signalMouseMove, this, &MainWindow::slotMouseMove);
    connect(this, &MainWindow::signalMouseRelease, this, &MainWindow::slotMouseRelease);
    connect(this, &MainWindow::signalWhell, this, &MainWindow::slotWhell);
    connect(this, &MainWindow::signalAddPoins, this, &MainWindow::slotAddPoints);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent * e)
{
    auto cursorPos = e->pos();
    auto graphGeometry = ui->lbGraph->geometry();

    if(checkArea(cursorPos, graphGeometry)){       
        emit signalMousePress(cursorPos);
        if(ui->cb_choosePoint->isChecked()){
            emit signalAddPoins(cursorPos);
        }
    }else{
        ui->statusBar->showMessage("Out graph",500);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent * e)
{
    auto cursorPos = e->pos();
    auto graphGeometry = ui->lbGraph->geometry();

    if(checkArea(cursorPos, graphGeometry)){
        emit signalMouseRelease();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent * e)
{
    auto cursorPos = e->pos();
    auto graphGeometry = ui->lbGraph->geometry();

    if(checkArea(cursorPos, graphGeometry)){
        emit signalMouseMove(cursorPos);
    }
}

void MainWindow::wheelEvent(QWheelEvent * e)
{
    auto cursorPos = e->pos();
    auto graphGeometry = ui->lbGraph->geometry();

    if(checkArea(cursorPos, graphGeometry)){
        emit signalWhell(e->delta());
    }
}

void MainWindow::slotMousePress(QPoint p)
{
    if(!moving){
        ui->lbGraph->setCursor(Qt::ClosedHandCursor);
        moving = true;
        movingStart = QPair<int,int>(p.x(), p.y());
    }
}

void MainWindow::slotMouseRelease()
{
    moving = false;
    if(!ui->cb_choosePoint->isChecked())
        ui->lbGraph->setCursor(Qt::OpenHandCursor);
    else
        ui->lbGraph->setCursor(Qt::PointingHandCursor);
}

void MainWindow::slotMouseMove(QPoint p)
{    
    double dx = movingStart.first - p.x();
    double dy = movingStart.second - p.y();

    dx /= paint->getScaleX() * -20;
    dy /= paint->getScaleY() * -20;

    paint->changeO(dx, dy);
    paint->update();
}

void MainWindow::slotWhell(int delta)
{
    if(delta > 0){
        paint->changeScale(1.1);
        paint->changeO(1.1);
    }else{
        paint->changeScale(0.9);
        paint->changeO(0.9);
    }

    paint->update();
}

void MainWindow::slotAddPoints(QPoint p)
{
    p = QPoint(p.x() - ui->lbGraph->x(), p.y() - ui->lbGraph->y());
    paint->drawPoint(p);


    QVector<QPointF> points = paint->getPoints();
    bool rem = false;

    for(int i = 0; i < points.size(); i++){
        if(fabs((points.at(i).x() + paint->getOx()) * paint->getScaleX() - p.x()) < 10 &&
                fabs((-points.at(i).y() + paint->getOy()) * paint->getScaleY() - p.y()) < 10){
            return;
            paint->removePoint(i);
            rem = true;
        }
    }

    QPointF _p(1.0 * p.x() / paint->getScaleX() - paint->getOx(),
               -1.0 * p.y() / paint->getScaleY() + paint->getOy());
    if(!rem){       
        paint->addPoint(_p);
    }

    QString info = "Осталось добавить точек: ";
    info += QString::number(3 - paint->getSize());


    ui->label_2->setText(info);

    if(paint->getSize() == 3){
        paint->setPen();
        paint->update();
        ui->cb_choosePoint->setChecked(false);
        ui->label_2->setEnabled(false);
    }

    ui->statusBar->showMessage(QString("%1, %2 : %3, %4").arg(p.x()).arg(p.y()).arg(_p.x()).arg(_p.y()));
}


void MainWindow::on_cb_nAuto_stateChanged(int arg1)
{
    if(arg1 == 0){
        ui->label->setEnabled(true);
        ui->sb_n->setEnabled(true);
        paint->setAutoChooseN(false, ui->sb_n->value());
    }else {
        ui->label->setEnabled(false);
        ui->sb_n->setEnabled(false);
        paint->setAutoChooseN(true);
    }
}

void MainWindow::on_sb_n_valueChanged(int arg1)
{
    if(!paint->getAutoN())
        paint->setAutoChooseN(false, arg1);
}

void MainWindow::on_pb_clear_clicked()
{
    paint->setEmptyGraph();
    paint->removeAll();
}

void MainWindow::on_pb_saveAs_clicked()
{
    paint->saveAs();
}

void MainWindow::on_pb_update_clicked()
{
    //paint->removeAll();
    paint->update();
}

void MainWindow::on_cb_choosePoint_stateChanged(int arg1)
{
    if(ui->cb_choosePoint->isChecked()){
        paint->removeAll();
        paint->update();
        paint->setPen(Qt::black, 3);
        ui->label_2->setEnabled(true);
        ui->label_2->setText("Осталось добавить точек: 3");
        ui->lbGraph->setCursor(Qt::PointingHandCursor);
    }
}

void MainWindow::on_cb_fill_stateChanged(int arg1)
{
    paint->setFill(ui->cb_fill->isChecked());
    paint->update();
}

void MainWindow::on_cb_showGrid_stateChanged(int arg1)
{
    paint->setShowGrid(ui->cb_showGrid->isChecked());
    paint->update();
}
